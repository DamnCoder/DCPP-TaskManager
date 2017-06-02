//
//  taskmanager.cpp
//  ThreadPool
//
//  Created by Jorge López on 30/5/17.
//  Copyright © 2017 Jorge López. All rights reserved.
//

#include "taskmanager.h"

namespace dc
{
	CTaskManager::CTaskManager()
	{
		m_threadNum = std::thread::hardware_concurrency();
		if(m_threadNum == 0)
		{
			m_threadNum = 1;
		}
		m_threadList.reserve(m_threadNum);
		printf("[Constructor] Number of threads: %d\n", m_threadNum);
	}
	
	const bool CTaskManager::PendingTasks()
	{
		bool pendingTasks = false;
		for(auto* thread : m_threadList)
		{
			pendingTasks |= thread->PendingTasks();
		}
		return pendingTasks;
	}
	
	const unsigned int CTaskManager::NumTasks()
	{
		unsigned int totalTasks = 0;
		for(auto* thread : m_threadList)
		{
			totalTasks += thread->NumTasks();
		}
		//printf("Total tasks %d\n", totalTasks);
		return totalTasks;
	}
	
	void CTaskManager::Add(const TJob& job, const unsigned int threadId)
	{
		assert(job && "[CTaskManager::Add] No task passed");
		assert(threadId < m_threadNum &&"[CTaskManager::Add] Wrong thread id");

		// Added to the queue to be executed in a secondary thread
		CThread* thread = m_threadList[threadId];
		thread->Add(job);
	}
	
	void CTaskManager::Start()
	{
		for(int i=0; i<m_threadNum; ++i)
		{
			auto* thread = new CThread(i, this);
			thread->Start();
			m_threadList.push_back(thread);
		}
		printf("[CTaskManager::Start] All threads started\n");
	}
	
	void CTaskManager::Finish()
	{
		for(int i=0; i<m_threadNum; ++i)
		{
			CThread* thread = m_threadList[i];
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
		while(PendingTasks())
		{
			printf("Has tasks? %s\n", this->PendingTasks() ? "true" : "false");
			m_condition.wait(lock, [this] {
				printf("WAIT: Has tasks? %s\n", this->PendingTasks() ? "true" : "false");
				return !this->PendingTasks();
			});
		}
		Finish();
	}
	
	void CTaskManager::NotifyCondition()
	{
		m_condition.notify_one();
	}
}
