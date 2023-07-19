#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Interface/ProxyInterface.h"
#include "Core/SimpleSemaphore.h"

//UE4 RunnableThreads, you can create thread instances 
class SIMPLETHREAD_API FThreadRunnable : public FRunnable, public IThreadProxy
{
public:
	FThreadRunnable(bool InSuspendAtFirst = false);
	virtual ~FThreadRunnable() override;

	//Create a secure thread 
	virtual void CreateSafeThread() override;

	//Wake up thread 
	virtual void WakeupThread() override;

	//Whether the thread is suspended 
	virtual bool IsSuspend() override;

	//Let the startup thread wait until the current task is completed 
	virtual void WaitAndCompleted() override;

	//Block start thread 
	virtual void BlockingAndCompletion() override;

private:

	//Where threads actually execute 
	virtual uint32 Run() override;

	virtual bool Init() override;
	virtual void Stop() override;
	virtual void Exit() override;

private:

	
	FThreadSafeCounter					StopTaskCounter; //Thread safety count .
	bool								bSuspendAtFirst; //Whether to block the thread for the first time .
	class FRunnableThread*				Thread;			 //Thread specific instance 
	FName								RunnableName;	 //Thread name will be extended later 
	FSimpleSemaphore					ThreadEvent;     //Semaphore blocking thread 
	FSimpleSemaphore					StartUpEvent;	 //Semaphore block start thread 
	FSimpleSemaphore					WaitExecuteEvent;//Semaphore suspend start thread 
	FCriticalSection					Mutex;			 //lock 

	static int32						ThreadCount;	 //Thread sequence count 
};