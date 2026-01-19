// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ElevatorsJsonConfig.h"


const FStagedMoveParams* UElevatorsJsonConfig::GetElevatorParamsByTag(FGameplayTag InTag) const
{
	for (const auto& Elevator : Elevators.ElevatorsByTag)
	{
		if (Elevator.Tag == InTag)
		{
			return &Elevator;
		}
	}
	return nullptr;
}

void UElevatorsJsonConfig::ReadJson()
{
	Elevators = ReadStructFromJson<FStagedMovesParams>();
}

void UElevatorsJsonConfig::WriteJson()
{
	WriteStructToJson(Elevators);
}
