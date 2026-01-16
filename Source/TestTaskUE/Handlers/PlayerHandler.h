// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/Handlers/CharacterHandler.h"
#include "ProjectCoreRuntime/Services/Base/Fragmentable.h"
#include "PlayerHandler.generated.h"

class UInputConfig;
class UPlayerConfig;

UCLASS()
class TESTTASKUE_API APlayerHandler : public ACharacterHandler,
public IInjectable,
public IFragmentable
{
	GENERATED_BODY()

public:
	APlayerHandler();
	
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void BuildFragments(UFragmentsContainer* FragmentsContainer) override;

private:
	UPROPERTY()
	TObjectPtr<UInputConfig> InputConfig;
	UPROPERTY()
	TObjectPtr<UPlayerConfig> PlayerConfig;
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
};
