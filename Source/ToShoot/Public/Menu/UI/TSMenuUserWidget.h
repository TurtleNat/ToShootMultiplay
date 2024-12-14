// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSMenuUserWidget.generated.h"

class UButton;

UCLASS()
class TOSHOOT_API UTSMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinGameButton;

	virtual void NativeOnInitialized() override;

public:

	void ConnectToServer(const FString& ServerIP);
	
private:
	UFUNCTION()
	void OnStartGame();
	
	UFUNCTION()
	void OnQuitGame();

	UFUNCTION()
	void OnJoinGame();
};
