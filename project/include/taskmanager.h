//
//  taskmanager.hpp
//  ThreadPool
//
//  Created by Jorge López on 30/5/17.
//  Copyright © 2017 Jorge López. All rights reserved.
//

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include <map>

#include <assert.h>

#include <functional>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "task.h"
#include "thread.h"

namespace dc
{
	class CTaskManager
	{
	public:
		const bool			PendingTasks();
		const unsigned int	NumTasks();
		
	public:
		CTaskManager();
		~CTaskManager() {}
		
	public:
		void Add(const TJob& job, const unsigned int theadId);
		
		void Start();
		
		void Finish();
		void FinishAllTasks();
		
		void NotifyCondition();
	private:
		
		std::vector<CThread*>	m_threadList;
		
		unsigned int			m_threadNum;
		
		std::mutex				m_waitMutex;
		std::condition_variable	m_condition;
		
	};
}

#endif /* TASKMANAGER_H */
