// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/MoveControllable.h"
#include "Base/RotateControllable.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "PlayerControllerFragment.generated.h"

class UInputConfig;

UCLASS()
class TESTTASKUE_API UPlayerControllerFragment : public UFragment,
public IInjectable,
public IInitializable,
public IMoveControllable,
public IRotateControllable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UInputConfig> InputConfig;
	UPROPERTY()
	TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
	
	FVector2D MoveInputDirection;
	FVector2D RotateInputDirection;
	
public:
	void Configure(UEnhancedInputComponent* InEnhancedInputComponent);
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void Initialize() override;
	
	virtual const FVector2D& GetMoveDirection() const override;
	virtual const FVector2D& GetRotateDirection() const override;
};
