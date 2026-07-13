#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PoliceController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class GTARACE_API APoliceController : public AAIController
{
	GENERATED_BODY()
	
public:
	APoliceController();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
