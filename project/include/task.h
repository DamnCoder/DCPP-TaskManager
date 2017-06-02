//
//  Task.hpp
//  ThreadPool
//
//  Created by Jorge López on 30/5/17.
//  Copyright © 2017 Jorge López. All rights reserved.
//

#ifndef TASK_H
#define TASK_H

#include <tuple>
#include <functional>

namespace dc
{
	using TJob = std::function<void(void)>;
	
	class CTask
	{
	public:
		const bool	Finished() const		{ return m_finished; }
		void		Finish()				{ m_finished = true; }
		
		void		Job(const TJob& job)	{ m_job = job; }
		
	public:
		CTask(const TJob& job) :
			m_job(job),
			m_finished(false)
		{}
		
		virtual ~CTask()
		{}
		
	public:
		void Execute()
		{
			m_job();
			Finish();
			printf("[CTask::Execute] Finished\n");
		};
		
	private:
		TJob m_job;
		bool m_finished;
	};
	
}

#endif /* TASK_H */
