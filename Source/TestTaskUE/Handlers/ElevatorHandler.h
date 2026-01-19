// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/DependencyInjection/Injectable.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/Services/Base/Fragmentable.h"
#include "ElevatorHandler.generated.h"

class UElevatorPreviewComponent;
class UBoxComponent;
class UElevatorsJsonConfig;

UCLASS()
class TESTTASKUE_API AElevatorHandler : public AActorHandler,
public IInjectable,
public IFragmentable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> OverlapBox;
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	TObjectPtr<UElevatorPreviewComponent> ElevatorPreview;
#endif
	
	UPROPERTY()
	TWeakObjectPtr<UElevatorsJsonConfig> ElevatorsJsonConfig;
	
public:
	AElevatorHandler();
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void BuildFragments(UFragmentsContainer* FragmentsContainer) override;
};
