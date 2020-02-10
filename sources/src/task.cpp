#include <task.h>

namespace dc
{
void CTask::Execute()
{
    if (!m_job)
    {
        return;
    }

    m_job();
    Finish();
    printf("[CTask::Execute] Finished\n");
}
}  // namespace dc
