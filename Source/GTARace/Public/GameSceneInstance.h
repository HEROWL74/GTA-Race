#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "GameSceneInstance.generated.h"
/**
 * 
 */
UCLASS()
class GTARACE_API UGameSceneInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UGameSceneInstance();
	
protected:
	IOnlineSessionPtr SessionInterface;
	
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	virtual void Init() override;
	
	virtual void OnCreateSessionComplete(FName ServerName, bool Succeeded);
	virtual void OnFindSessionComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	UFUNCTION(BlueprintCallable)
	void CreateServer();
	
	UFUNCTION(BlueprintCallable)
	void JoinServer();
};
