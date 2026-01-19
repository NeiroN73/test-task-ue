// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "OverlapFragment.h"

void UOverlapFragment::Configure(UPrimitiveComponent* InPrimitiveComponent)
{
	PrimitiveComponent = InPrimitiveComponent;
}

void UOverlapFragment::Initialize()
{
	PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UOverlapFragment::OnOverlapBegin);
	PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &UOverlapFragment::OnOverlapEnd);
}

void UOverlapFragment::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlapBegan.Broadcast(OtherActor);
}

void UOverlapFragment::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnOverlapEnded.Broadcast(OtherActor);
}
