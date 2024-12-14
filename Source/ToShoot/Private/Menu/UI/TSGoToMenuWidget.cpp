// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/TSGoToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TSGameInstance.h"


void UTSGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UTSGoToMenuWidget::OnGoToMenu);
	}
}


void UTSGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	const auto TSGameInstance = GetWorld()->GetGameInstance<UTSGameInstance>();
	if (!TSGameInstance) return;

	if (TSGameInstance->GetMenuLevelName().IsNone())
	{
		return;
		//UE_LOG(LogTSMenuWidget, Error, TEXT("Level name is NONE"));
	}


	UGameplayStatics::OpenLevel(this, TSGameInstance->GetMenuLevelName());
}
