#include "GameSceneInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"

UGameSceneInstance::UGameSceneInstance()
{
}

void UGameSceneInstance::Init()
{
	Super::Init();
	
    if (IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld()))
    {
       SessionInterface = Subsystem->GetSessionInterface();
       if (SessionInterface.IsValid())
       {
          SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGameSceneInstance::OnCreateSessionComplete);
          SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UGameSceneInstance::OnFindSessionComplete);
          SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UGameSceneInstance::OnJoinSessionComplete);
       }
    }
}

void UGameSceneInstance::OnCreateSessionComplete(FName ServerName, bool Succeeded)
{
    UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, Succeeded: %d"), Succeeded);
    if (Succeeded)
    {
       GetWorld()->ServerTravel("/Game/Game/Maps/Levels/GameScene?listen");
    }
}

void UGameSceneInstance::OnFindSessionComplete(bool Succeeded)
{
    UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete, Succeeded: %d"), Succeeded);
    if (Succeeded)
    {
       TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
       
       UE_LOG(LogTemp, Warning, TEXT("SearchResults, Server Count: %d"), SearchResults.Num());
       
       if (SearchResults.Num() > 0)
       {
          UE_LOG(LogTemp, Warning, TEXT("Joining Server"));
          SessionInterface->JoinSession(0, FName("MySession"), SearchResults[0]);
       }
    }
}

void UGameSceneInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete, SessionName: %s"), *SessionName.ToString());
    if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
       FString JoinAddress = "";
       if (SessionInterface.IsValid() && SessionInterface->GetResolvedConnectString(SessionName, JoinAddress))
       {
          if (!JoinAddress.IsEmpty())
          {
             PController->ClientTravel(JoinAddress, TRAVEL_Relative);
          }
       }
    }
}

void UGameSceneInstance::CreateServer()
{
    UE_LOG(LogTemp, Warning, TEXT("CreateServer"));
    if (!SessionInterface.IsValid()) return;

    FOnlineSessionSettings SessionSettings;
    SessionSettings.bAllowJoinInProgress = true;
    SessionSettings.bIsDedicated = false;
    SessionSettings.bIsLANMatch = true;       // LANモード有効
    SessionSettings.bShouldAdvertise = true;    // 検索にヒットさせる
    SessionSettings.NumPublicConnections = 5;
    
    SessionInterface->CreateSession(0, FName("MySession"), SessionSettings);
}

void UGameSceneInstance::JoinServer()
{
    UE_LOG(LogTemp, Warning, TEXT("JoinServer"));
    if (!SessionInterface.IsValid()) return;

    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    SessionSearch->bIsLanQuery = true;
    SessionSearch->MaxSearchResults = 100;
    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}