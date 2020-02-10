#include "thread.h"
#include "task.h"
#include "taskmanager.h"

namespace dc
{
CThread::CThread(const unsigned identifier, CTaskManager& taskManager)
    : m_id(identifier)
    , mp_taskManager(taskManager)
    , mp_currentTask(nullptr)
    , m_finish(false)
{
}

CThread::~CThread()
{
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

unsigned CThread::Identifier() const
{
    return m_id;
}

bool CThread::PendingTasks() const
{
    return !m_taskQueue.empty() || mp_currentTask;
}

bool CThread::WaitCondition()
{
    return m_finish || PendingTasks();
}

unsigned CThread::TaskCount() const
{
    return static_cast<unsigned>(m_taskQueue.size());
}

void CThread::Add(const TJob& job)
{
    // If something happens inside, like an exception, the mutex will be unlocked automatically
    std::unique_lock<std::mutex> lock(m_queueMutex);
    TTaskPtr task = nullptr;
    if (!m_freeTasks.empty())
    {
        task = m_freeTasks.back();
        m_freeTasks.pop_back();

        task->Job(job);
        printf("[Thread::Add] We get a free task\n");
    }
    else
    {
        task = std::make_shared<CTask>(job);
        printf("[Thread::Add] We create a new task\n");
    }

    m_taskQueue.push(task);

    m_condition.notify_one();
    printf("[Thread::Add] Task added\n");
}

void CThread::Start()
{
    m_thread = std::thread(&CThread::Run, this);
    printf("[Thread::Start] Thread %d started\n", Identifier());
}

void CThread::Finish()
{
    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_finish = true;
    m_condition.notify_one();
    printf("[Thread::Finish] Thread %d finished\n", Identifier());
}

void CThread::Run()
{
    while (!m_finish)
    {
        if (!mp_currentTask)
        {
            // Wait till there are tasks pending
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_condition.wait(lock, [thread = this] { return thread->WaitCondition(); });

            // Just in case of an spurious wake up
            if (PendingTasks())
            {
                mp_currentTask = m_taskQueue.front();
                m_taskQueue.pop();
            }

            if (!PendingTasks())
            {
                mp_taskManager.NotifyCondition();
            }
        }

        // If there is no task available
        if (mp_currentTask)
        {
            if (mp_currentTask->Finished())
            {
                m_freeTasks.push_back(mp_currentTask);
                mp_currentTask = nullptr;
                mp_taskManager.NotifyCondition();
            }
            else
            {
                mp_currentTask->Execute();
            }
        }
    }
    // printf("[Thread::Run] Thread run end\n");
}
}  // namespace dc
