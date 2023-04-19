#include "Subsystem/SubsystemTest.h"

#include "Kismet/KismetMathLibrary.h"

UScoreGameInstanceSubsystem::UScoreGameInstanceSubsystem()
	: Score(0)
{
}

int32 UScoreGameInstanceSubsystem::AddScore(int32 BaseScore)
{
	Score = UKismetMathLibrary::Max(0, Score + BaseScore);
	// 调用委托
	ScoreChange.Broadcast(Score);
	return Score;
}

bool UScoreGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	UE_LOG(LogTemp, Warning, TEXT("UScoreGameInstanceSubsystem::ShouldCreateSubsystem"));
	return Super::ShouldCreateSubsystem(Outer);
}

void UScoreGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("UScoreGameInstanceSubsystem::Initialize"));
}

void UScoreGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Warning, TEXT("UScoreGameInstanceSubsystem::Deinitialize"));
}

UMyWorldSubsystem::UMyWorldSubsystem()
{
}

void UMyWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("UMyWorldSubsystem::Initialize--[WorldName: %s]--[WorldType: %s]"), *GetWorld()->GetName(), *GetWorldType());
}

void UMyWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Warning, TEXT("UMyWorldSubsystem::Deinitialize--[WorldName: %s]--[WorldType: %s]"), *GetWorld()->GetName(), *GetWorldType());
}

FString UMyWorldSubsystem::GetWorldType()
{
	FString WorldTypeName;
	switch (GetWorld()->WorldType) {
	case EWorldType::None: {WorldTypeName = TEXT("None"); }break;
	case EWorldType::Game: {WorldTypeName = TEXT("Game"); }break;
	case EWorldType::Editor: {WorldTypeName = TEXT("Editor"); }break;
	case EWorldType::PIE: {WorldTypeName = TEXT("PIE"); }break;
	case EWorldType::EditorPreview: {WorldTypeName = TEXT("EditorPreview"); }break;
	case EWorldType::GamePreview: {WorldTypeName = TEXT("GamePreview"); }break;
	case EWorldType::GameRPC: {WorldTypeName = TEXT("GameRPC"); }break;
	case EWorldType::Inactive: {WorldTypeName = TEXT("Inactive"); }break;
	default: WorldTypeName = TEXT("default");
	};
	return WorldTypeName;
}
