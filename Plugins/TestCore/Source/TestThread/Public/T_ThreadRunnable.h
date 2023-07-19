#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "GameFramework/Actor.h"
#include "T_ThreadRunnable.generated.h"

class FT_ThreadRunnable : public FRunnable
{
public:
	FT_ThreadRunnable();
	virtual ~FT_ThreadRunnable() override;

	void CreateSafeThread();

	void Trigger();
	
	//Where threads actually execute 
	virtual uint32 Run() override;
	virtual bool Init() override;
	virtual void Stop() override;
	virtual void Exit() override;

public:
	bool bSuspend;
	FEvent *Event;
	
private:
	FThreadSafeCounter ThreadSafeCounter;
	FRunnableThread* Thread;
	FName RunnableName;

	static int32 ThreadCount;
};


UCLASS()
class AThreadRunnableActor : public AActor
{
	GENERATED_BODY()
public:
	AThreadRunnableActor();

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	void Stop1();

	UFUNCTION(BlueprintCallable)
	void Trigger(bool bInSuspend);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn))
	bool bSuspend;

private:
	FT_ThreadRunnable *ThreadRunnable;
};