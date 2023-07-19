#include "T_ThreadRunnable.h"
#include "HAL/RunnableThread.h"
#include "TestThread.h"

int32 FT_ThreadRunnable::ThreadCount = 0;

FT_ThreadRunnable::FT_ThreadRunnable()
	: bSuspend(false)
	, Event(FPlatformProcess::GetSynchEventFromPool())
	, ThreadSafeCounter(0)
	, Thread(nullptr)
{
	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-执行构造"), *RunnableName.ToString());
}

FT_ThreadRunnable::~FT_ThreadRunnable()
{
	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-执行析构"), *RunnableName.ToString());
	FPlatformProcess::ReturnSynchEventToPool(Event);
	if (Thread != nullptr)
	{
		delete Thread;
		Thread = nullptr;
	}
}

void FT_ThreadRunnable::CreateSafeThread()
{
	RunnableName = *FString::Printf(TEXT("TestThread-%i"), ThreadCount);
	Thread = FRunnableThread::Create(this, *RunnableName.ToString(), 0, TPri_BelowNormal);
	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-线程创建成功"), *RunnableName.ToString());

	ThreadCount++;
}

void FT_ThreadRunnable::Trigger()
{
	if (Event)
	{
		Event->Trigger();
	}
}

uint32 FT_ThreadRunnable::Run()
{
	static uint64 RunCount = 0;
	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-[%i]-开始运行-%llu"), *RunnableName.ToString(), FPlatformTLS::GetCurrentThreadId(), RunCount);
	while (ThreadSafeCounter.GetValue() == 0)
	{
		UE_LOG(TestThreadLog, Warning, TEXT("[%s]-[%i]-运行中-%llu"), *RunnableName.ToString(), FPlatformTLS::GetCurrentThreadId(), RunCount);

		if (bSuspend)
		{
			Event->Wait();
		}
		
		FPlatformProcess::Sleep(1);
		RunCount++;
	}
	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-[%i]-结束运行-%llu"), *RunnableName.ToString(), FPlatformTLS::GetCurrentThreadId(), RunCount);
	return 0;
}

bool FT_ThreadRunnable::Init()
{
	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-开始初始化"), *RunnableName.ToString());
	if (!FPlatformProcess::SupportsMultithreading())
	{
		Stop();
	}

	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-初始化完成"), *RunnableName.ToString());
	return ThreadSafeCounter.GetValue() == 0;
}

void FT_ThreadRunnable::Stop()
{
	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-结束"), *RunnableName.ToString());
	ThreadSafeCounter.Increment();
}

void FT_ThreadRunnable::Exit()
{
	UE_LOG(TestThreadLog, Warning, TEXT("[%s]-退出"), *RunnableName.ToString());
}

AThreadRunnableActor::AThreadRunnableActor()
{
}

void AThreadRunnableActor::BeginPlay()
{
	Super::BeginPlay();

	ThreadRunnable = new FT_ThreadRunnable();
	ThreadRunnable->bSuspend = bSuspend;
	ThreadRunnable->CreateSafeThread();
}

void AThreadRunnableActor::BeginDestroy()
{
	if (ThreadRunnable)
	{
		delete ThreadRunnable;
		ThreadRunnable = nullptr;
	}
	Super::BeginDestroy();
}

void AThreadRunnableActor::Stop1()
{
	if (ThreadRunnable)
	{
		ThreadRunnable->Stop();
	}
}

void AThreadRunnableActor::Trigger(bool bInSuspend)
{
	if (ThreadRunnable)
	{
		ThreadRunnable->Trigger();
		ThreadRunnable->bSuspend = bInSuspend;
	}
}
