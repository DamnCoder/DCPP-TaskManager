#pragma once

#include <functional>
#include <memory>
#include <tuple>

namespace dc
{
using TJob = std::function<void(void)>;

class CTask
{
public:
    bool Finished() const { return m_finished; }
    void Finish() { m_finished = true; }

    void Job(const TJob& job) { m_job = job; }

public:
    CTask(const TJob& job)
        : m_job(job)
        , m_finished(false)
    {
    }

    virtual ~CTask() {}

    CTask(const CTask& rhs) = delete;
    CTask& operator=(const CTask& rhs) = delete;

    CTask(CTask&& rhs) = delete;
    CTask& operator=(CTask&& rhs) = delete;

public:
    void Execute();

private:
    TJob m_job;
    bool m_finished;
};

using TTaskPtr = std::shared_ptr<CTask>;

}  // namespace dc
