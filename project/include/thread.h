//
//  Thread.hpp
//  ThreadPool
//
//  Created by Jorge López on 31/5/17.
//  Copyright © 2017 Jorge López. All rights reserved.
//

#ifndef THREAD_H
#define THREAD_H

#include <queue>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "task.h"

namespace dc
{
	class CTaskManager;
	
	class CThread
	{
	public:
		const unsigned int	Identifier() const;
		const bool			PendingTasks() const;
		const unsigned int	NumTasks() const;
		
	private:
		const bool WaitCondition();
		
	public:
		CThread(const unsigned int identifier, CTaskManager* taskManager);
		
		~CThread();
		
	public:
		void Add(const TJob& job);
		
		void Start();
		void Finish();
		
		void Run();

	private:
		unsigned int				m_id;
		std::thread					m_thread;
		std::queue<CTask*>			m_taskQueue;
		std::vector<CTask*>			m_freeTasks;
		
		CTaskManager*				mp_taskManager;
		CTask*						mp_currentTask;
		
		// synchronization
		std::mutex					m_queueMutex;
		std::condition_variable		m_condition;
		
		// Finalization
		bool						m_finish;
	};	
}

#endif /* THREAD_H */
