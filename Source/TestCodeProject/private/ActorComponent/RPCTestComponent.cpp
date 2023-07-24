#include "ActorComponent/RPCTestComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
URPCTestComponent::URPCTestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	SetIsReplicatedByDefault(true);
}

void URPCTestComponent::ChangeTestProperty_3_Server_Implementation(const FString& InNewVal)
{
	ChangeTestProperty_3_Multicast(InNewVal);
}

void URPCTestComponent::ChangeTestProperty_3_Multicast_Implementation(const FString& InNewVal)
{
	OnTestProperty_3.Broadcast(TestProperty_3, InNewVal);
	TestProperty_3 = InNewVal;
}

// Called when the game starts
void URPCTestComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void URPCTestComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URPCTestComponent, TestProperty_1);
	DOREPLIFETIME(URPCTestComponent, TestProperty_2);
}

void URPCTestComponent::OnRep_TestProperty_2(FString OldVal)
{
	OnTestProperty_2.Broadcast(OldVal, TestProperty_2);
}

