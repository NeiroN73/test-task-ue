#include "ElevatorPreviewComponent.h"
#include "Engine/World.h"
#include "TestTaskUE/Handlers/ElevatorHandler.h"


UElevatorPreviewComponent::UElevatorPreviewComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bTickInEditor = true;
}

#if WITH_EDITOR
void UElevatorPreviewComponent::TickComponent(float DeltaTime, ELevelTick TickType, 
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    DrawElevatorPreview();
}

void UElevatorPreviewComponent::PostLoad()
{
    Super::PostLoad();

    if (!ElevatorTag.IsValid())
    {
        if (auto Owner = GetOwner())
        {
            if (auto Elevator = Cast<AElevatorHandler>(Owner))
            {
                if (Elevator->GetTag().IsValid())
                {
                    ElevatorTag = Elevator->GetTag();
                }
            }
        }
    }

    if (ElevatorsJsonConfig != nullptr && ElevatorTag.IsValid())
    {
        ElevatorsJsonConfig->Initialize();
        if (const auto FoundParams = ElevatorsJsonConfig->GetElevatorParamsByTag(ElevatorTag))
        {
            StagedMoveParams = *FoundParams;
        }
    }
}

void UElevatorPreviewComponent::DrawElevatorPreview()
{
    UWorld* World = GetWorld();
    if (!World || World->WorldType != EWorldType::Editor)
    {
        return;
    }

    auto StartPos = GetComponentLocation();
    auto EndPos = StartPos + StagedMoveParams.Position;
    auto BoxExtent = GetOwner()->GetComponentsBoundingBox().GetExtent();
    
    DrawDebugBox(World, EndPos, BoxExtent, FColor::Green);
    DrawDebugLine(World, StartPos, EndPos, FColor::Green);
}

#endif
