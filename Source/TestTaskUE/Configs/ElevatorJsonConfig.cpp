// Copyright Ilya Prokhorov, Inc. All Rights Reserved.


#include "ElevatorJsonConfig.h"


void UElevatorJsonConfig::ReadJson()
{
	ElevatorParams = ReadStructFromJson<FElevatorParams>();
}

void UElevatorJsonConfig::WriteJson()
{
	WriteStructToJson(ElevatorParams);
}
