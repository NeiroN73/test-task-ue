// Copyright Ilya Prokhorov, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "ProjectCoreRuntime/Interfaces/Initializable.h"
#include "OverlapFragment.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOverlapBegan, AActor* OtherActor);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOverlapEnded, AActor* OtherActor);

UCLASS()
class TESTTASKUE_API UOverlapFragment : public UFragment,
public IInitializable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TWeakObjectPtr<UPrimitiveComponent> PrimitiveComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
public:
	FOnOverlapBegan OnOverlapBegan;
	FOnOverlapEnded OnOverlapEnded;
	
	void Configure(UPrimitiveComponent* InPrimitiveComponent);
	virtual void Initialize() override;
};
