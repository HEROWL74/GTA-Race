#pragma  once

#include "CoreMinimal.h"
#include "Runtime/MassEntity/Public/MassEntityTypes.h"

// ---------------------------
// Fragments (個別のデータ)
// ---------------------------

// 位置、移動速度を所持するデータ
USTRUCT(BlueprintType)
struct FMyDataFragment : public FMassFragment
{
	GENERATED_BODY()
	
	UPROPERTY()
	FVector Velocity = FVector::ZeroVector;
	
	UPROPERTY()
	float Speed = 100.0f;
};

// ---------------------------
// Tags (識別子)
// ---------------------------
USTRUCT()
struct FCrowdTag : public FMassTag
{
	GENERATED_BODY()
};
