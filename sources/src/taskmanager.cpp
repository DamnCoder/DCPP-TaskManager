//
//  taskmanager.cpp
//  ThreadPool
//
//  Created by Jorge López on 30/5/17.
//  Copyright © 2017 Jorge López. All rights reserved.
//

#include "taskmanager.h"
#include "thread.h"

namespace dc
{
CTaskManager::CTaskManager()
{
    auto threadCount = std::thread::hardware_concurrency();
    threadCount = (0 < threadCount) ? threadCount : 1;

    m_threadList.reserve(threadCount);
    for (unsigned i = 0; i < threadCount; ++i)
    {
        m_threadList.push_back(new CThread(i, *this));
    }
    printf("[Constructor] Number of threads: %zu\n", m_threadList.size());
}

bool CTaskManager::PendingTasks()
{
    bool pendingTasks = false;
    for (const auto* thread : m_threadList)
    {
        pendingTasks |= thread->PendingTasks();
    }
    return pendingTasks;
}

unsigned CTaskManager::TaskCount()
{
    unsigned totalTasks = 0;
    for (const auto* thread : m_threadList)
    {
        totalTasks += thread->TaskCount();
    }
    // printf("Total tasks %d\n", totalTasks);
    return totalTasks;
}

void CTaskManager::Add(const TJob& job, const unsigned threadId)
{
    assert(job && "[CTaskManager::Add] No task passed");
    assert(threadId < m_threadList.size() && "[CTaskManager::Add] Wrong thread id");

    // Added to the queue to be executed in a secondary thread
    auto* thread = m_threadList[threadId];
    thread->Add(job);
}

void CTaskManager::Start()
{
    for (auto* thread : m_threadList)
    {
        thread->Start();
    }
    printf("[CTaskManager::Start] All threads started\n");
}  // namespace dc

void CTaskManager::Finish()
{
    for (unsigned i = 0; i < m_threadList.size(); ++i)
    {
        auto* thread = m_threadList[i];
        thread->Finish();
        delete thread;
    }
    m_threadList.clear();

    printf("[CTaskManager::Start] Thread manager finished\n");
}

void CTaskManager::FinishAllTasks()
{
    std::unique_lock<std::mutex> lock(m_waitMutex);
    printf("Has tasks? %s\n", this->PendingTasks() ? "true" : "false");
    do
    {
        printf("Has tasks? %s\n", this->PendingTasks() ? "true" : "false");
        m_condition.wait(lock, [this] {
            printf("WAIT: Has tasks? %s\n", this->PendingTasks() ? "true" : "false");
            return !this->PendingTasks();
        });
    } while (PendingTasks());
    Finish();
}

void CTaskManager::NotifyCondition()
{
    m_condition.notify_one();
}
}  // namespace dc
