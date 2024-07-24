#pragma once

#include "CoreMinimal.h"
#include "RPCTestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTestProperty, const FString&, OldValue, const FString&, NewValue);


UCLASS(Blueprintable, BlueprintType,  ClassGroup=(Test), meta=(BlueprintSpawnableComponent) )
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

	UFUNCTION(BlueprintCallable, Category = "Test|RPC")
	void ChangeTestProperty_4(const FString& InNewVal);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test|RPC", ReplicatedUsing = OnRep_TestProperty_1)
	int32 TestProperty_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test|RPC", ReplicatedUsing = OnRep_TestProperty_2)
	FString TestProperty_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test|RPC")
	FString TestProperty_3;
	
	UPROPERTY(Replicated, BlueprintReadWrite)
    FString TestProperty_4;
    

	UPROPERTY(BlueprintAssignable, Category = "Test|RPC")
	FOnTestProperty OnTestProperty_1;

	UPROPERTY(BlueprintAssignable, Category = "Test|RPC")
	FOnTestProperty OnTestProperty_2;

	UPROPERTY(BlueprintAssignable, Category = "Test|RPC")
	FOnTestProperty OnTestProperty_3;

	UPROPERTY(BlueprintAssignable, Category = "Test|RPC")
	FOnTestProperty OnTestProperty_4;

protected:
	UFUNCTION()
	void OnRep_TestProperty_1();

	UFUNCTION()
	void OnRep_TestProperty_2(FString OldVal);

	UFUNCTION()
	void OnRep_TestProperty_4(FString OldVal);
};
