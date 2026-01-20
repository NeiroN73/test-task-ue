// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ElevatorsJsonConfig.h"

void UElevatorsJsonConfig::Initialize()
{
	ElevatorsByTag.Empty();
	for (auto StagedMove : Elevators.StagedMovesByTag)
	{
		ElevatorsByTag.Add(StagedMove.Tag, StagedMove);
	}
}

const FStagedMoveParams* UElevatorsJsonConfig::GetElevatorParamsByTag(FGameplayTag InTag) const
{
	return ElevatorsByTag.Find(InTag);
}

#if WITH_EDITOR
void UElevatorsJsonConfig::ReadJson()
{
	Elevators = ReadStructFromJson<FStagedMovesParams>();
}

void UElevatorsJsonConfig::WriteJson()
{
	WriteStructToJson(Elevators);
}
#endif

