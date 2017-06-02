//
//  main.cpp
//  ThreadPool
//
//  Created by Jorge López on 30/5/17.
//  Copyright © 2017 Jorge López. All rights reserved.
//

#include "taskmanager.h"

void PrintSomething()
{
	printf("Hello world\n");
}

void DotProductAtomic(std::vector<int>& v1, std::vector<int>& v2, std::atomic<int>& result, int L, int R)
{
	int partialSum = 0;
	for(int i = L; i < R; ++i)
	{
		partialSum += v1[i] * v2[i];
	}
	printf("From %d to %d partial result is %d\n", L, R, partialSum);
	result += partialSum;
}

std::vector<int> Bounds(int numElements, int threads)
{
	std::vector<int> bounds;
	int division = numElements / threads;
	for(int i=0; i<threads; ++i)
	{
		bounds.push_back(division * i);
	}
	bounds.push_back(numElements);
	return bounds;
}

class CFoo
{
public:
	void FooM();
};

int numElements = 10000000;
int numThreads = 4;
std::atomic<int> result(0);

std::vector<int> v1(numElements, 1), v2(numElements, 2);

int main(int argc, const char * argv[])
{
	dc::CTaskManager* taskManager = new dc::CTaskManager();
	
	std::vector<int> bounds = Bounds(numElements, numThreads);
	
	
	auto functionTask1 = [&]{
		DotProductAtomic(v1, v2, result, bounds[0], bounds[1]);
		
		auto functionTask2 = [&]{
			DotProductAtomic(v1, v2, result, bounds[1], bounds[2]);
		};
		taskManager->Add(functionTask2, 0);

	};
	
	auto functionTask3 = [&]{
		DotProductAtomic(v1, v2, result, bounds[2], bounds[3]);
	};
	
	auto functionTask4 = [&]{
		DotProductAtomic(v1, v2, result, bounds[3], bounds[4]);
	};
	
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point t2;
	
	taskManager->Start();
	
	taskManager->Add(functionTask1, 0);
	
	taskManager->Add(functionTask3, 1);
	taskManager->Add(functionTask4, 2);
	
	//taskManager->FinishAllTasks();
	taskManager->Finish();
	
	printf("No more tasks!\n");
	
	t2 = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	
	printf("threads time %f\n", time_span.count());
	printf("Result is: %d\n", result.load());
	
	delete taskManager;
	taskManager = 0;
	
	return 0;
}
