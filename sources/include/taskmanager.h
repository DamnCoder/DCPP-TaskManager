#pragma once

#include <assert.h>
#include <condition_variable>
#include <functional>
#include <map>
#include <mutex>
#include <vector>

namespace dc
{
class CThread;
using TJob = std::function<void(void)>;

class CTaskManager
{
public:
    bool PendingTasks();
    unsigned TaskCount();

public:
    CTaskManager();
    ~CTaskManager() {}

    CTaskManager(const CTaskManager& rhs) = delete;
    CTaskManager& operator=(const CTaskManager& rhs) = delete;

    CTaskManager(CTaskManager&& rhs) = delete;
    CTaskManager& operator=(CTaskManager&& rhs) = delete;

public:
    void Add(const TJob& job, const unsigned theadId);

    void Start();

    void Finish();
    void FinishAllTasks();

    void NotifyCondition();

private:
    using TThreadPtrList = std::vector<CThread*>;
    TThreadPtrList m_threadList;

    std::mutex m_waitMutex;
    std::condition_variable m_condition;
};
}  // namespace dc
