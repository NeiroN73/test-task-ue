#include "ElevatorPreviewComponent.h"
#include "Engine/World.h"

#if WITH_EDITOR

UElevatorPreviewComponent::UElevatorPreviewComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bTickInEditor = true;
}

void UElevatorPreviewComponent::TickComponent(float DeltaTime, ELevelTick TickType, 
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UWorld* World = GetWorld();
    if (!World || World->WorldType != EWorldType::Editor)
    {
        return;
    }

    if (ElevatorsJsonConfig != nullptr && ElevatorTag.IsValid())
    {
        StagedMoveParams = *ElevatorsJsonConfig->GetElevatorParamsByTag(ElevatorTag);
    }

    if (StagedMoveParams.Position.IsZero())
    {
        return;
    }

    auto StartPos = GetComponentLocation();
    auto EndPos = StartPos + StagedMoveParams.Position;
    auto BoxExtent = GetOwner()->GetComponentsBoundingBox().GetExtent();
    
    DrawDebugBox(World, EndPos, BoxExtent, FColor::Green);
    DrawDebugLine(World, StartPos, EndPos, FColor::Green);
}

#endif // WITH_EDITOR