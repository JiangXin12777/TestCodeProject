#pragma once

#include "CoreMinimal.h"
#include "RPCTestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTestProperty_2, FString, OldValue, const FString&, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTestProperty_3, const FString&, OldValue, const FString&, NewValue);


UCLASS( ClassGroup=(Test), meta=(BlueprintSpawnableComponent) )
class TESTCODEPROJECT_API URPCTestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPCTestComponent();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Test|RPC")
	void ChangeTestProperty_3_Server(const FString& InNewVal);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Test|RPC")
	void ChangeTestProperty_3_Multicast(const FString& InNewVal);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test|RPC", Replicated)
	int32 TestProperty_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test|RPC", ReplicatedUsing = OnRep_TestProperty_2)
	FString TestProperty_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test|RPC")
	FString TestProperty_3;

	UPROPERTY(BlueprintAssignable, Category = "Test|RPC")
	FOnTestProperty_2 OnTestProperty_2;

	UPROPERTY(BlueprintAssignable, Category = "Test|RPC")
	FOnTestProperty_3 OnTestProperty_3;

protected:
	UFUNCTION()
	void OnRep_TestProperty_2(FString OldVal);
};
