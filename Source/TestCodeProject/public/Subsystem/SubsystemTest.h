#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SubsystemTest.generated.h"

UCLASS()
class UScoreGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UScoreGameInstanceSubsystem();

	// 声明委托
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChanged, int32, CurrentScore);
	UPROPERTY(BlueprintAssignable)
	FScoreChanged ScoreChange;

	UFUNCTION(BlueprintCallable, Category = "MySubsystem | ScoreGameInsSubsystem")
	int32 AddScore(int32 BaseScore);

protected:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// 游戏启动时调用
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// 游戏退出时调用
	virtual void Deinitialize() override;

private:
	int32 Score;	
};


UCLASS()
class UMyWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UMyWorldSubsystem();

protected:
	// 地图打开时调用
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// 地图关闭时调用
	virtual void Deinitialize() override;

	FString GetWorldType();
};
