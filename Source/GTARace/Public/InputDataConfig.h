#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"

class UInputAction;

UCLASS()
class GTARACE_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Move;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Look;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Jump;
};
