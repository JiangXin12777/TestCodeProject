#pragma once
#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "TestViewModel.generated.h"

// Blueprintable 必须写，默认的VM不支持蓝图
UCLASS(Blueprintable, BlueprintType, DisplayName="Test ViewModel")
class MVVM_TEST_API UTestViewModel : public UMVVMViewModelBase
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
    float Scale = 1.0f;
    
    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter=SetInt32, Getter=GetInt32)
    int32 Int32Value = 1;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter=SetInt64, Getter=GetInt64)
    int64 Int64Value = 1;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter=SetFloat, Getter=GetFloat)
    float FloatValue = 1.0f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter=SetVector, Getter=GetVector)
    FVector VectorValue = FVector::OneVector;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter=SetVector2D, Getter=GetVector2D)
    FVector2D Vector2DValue = FVector2D::UnitVector;

    
private:
    void SetScale(float Value) { UE_MVVM_SET_PROPERTY_VALUE(Scale, Value); }
    float GetScale() const { return Scale; }
    
    void SetInt32(int32 Value) { UE_MVVM_SET_PROPERTY_VALUE(Int32Value, Value); }
    int32 GetInt32() const { return Int32Value; }
    
    void SetInt64(int64 Value) { UE_MVVM_SET_PROPERTY_VALUE(Int64Value, Value); }
    int64 GetInt64() const { return Int64Value; }
    
    void SetFloat(float Value) { UE_MVVM_SET_PROPERTY_VALUE(FloatValue, Value); }
    float GetFloat() const { return FloatValue; }
    
    void SetVector(FVector Value) { UE_MVVM_SET_PROPERTY_VALUE(VectorValue, Value); }
    FVector GetVector() const { return VectorValue; }
    
    void SetVector2D(FVector2D Value) { UE_MVVM_SET_PROPERTY_VALUE(Vector2DValue, Value); }
    FVector2D GetVector2D() const { return Vector2DValue; }
};

