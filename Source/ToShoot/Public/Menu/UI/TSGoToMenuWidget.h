// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSGoToMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class TOSHOOT_API UTSGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	UButton* GoToMenuButton;

	virtual void NativeOnInitialized() override;

private:

	UFUNCTION()
	void OnGoToMenu();
};
