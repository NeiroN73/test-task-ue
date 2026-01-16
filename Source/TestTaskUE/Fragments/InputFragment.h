// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "InputFragment.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoveVectorChanged, const FVector2D&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRotateVectorChanged, const FVector2D&);

class UInputConfig;

UCLASS()
class TESTTASKUE_API UInputFragment : public UFragment,
public IInjectable,
public IInitializable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UInputConfig> InputConfig;
	UPROPERTY()
	TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
	
public:
	FOnMoveVectorChanged OnMoveVectorChanged;
	FOnRotateVectorChanged OnRotateVectorChanged;
	
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void Initialize() override;
	
	void Configure(UEnhancedInputComponent* InEnhancedInputComponent);
};
