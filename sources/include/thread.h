#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace dc
{
class CTaskManager;

class CTask;
using TTaskPtr = std::shared_ptr<CTask>;

using TJob = std::function<void(void)>;

class CThread
{
public:
    unsigned Identifier() const;
    bool PendingTasks() const;
    unsigned TaskCount() const;

public:
    CThread(const unsigned identifier, CTaskManager& taskManager);
    ~CThread();

public:
    void Add(const TJob& job);

    void Start();
    void Finish();

    void Run();

private:
    bool WaitCondition();

private:
    unsigned m_id;
    std::thread m_thread;
    std::queue<TTaskPtr> m_taskQueue;
    std::vector<TTaskPtr> m_freeTasks;

    CTaskManager& mp_taskManager;
    TTaskPtr mp_currentTask;

    // synchronization
    std::mutex m_queueMutex;
    std::condition_variable m_condition;

    bool m_finish;
};
}  // namespace dc
