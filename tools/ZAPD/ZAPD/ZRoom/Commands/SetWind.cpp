#include "SetWind.h"
#include "StringHelper.h"

SetWind::SetWind(ZFile* nParent) : ZRoomCommand(nParent)
{
}

void SetWind::ParseRawData()
{
	ZRoomCommand::ParseRawData();
	auto& parentRawData = parent->GetRawData();
	windDir.x = parentRawData.at(rawDataIndex + 0x04);
	windDir.y = parentRawData.at(rawDataIndex + 0x05);
	windDir.z = parentRawData.at(rawDataIndex + 0x06);
	clothFlappingStrength = parentRawData.at(rawDataIndex + 0x07);
}

std::string SetWind::GetBodySourceCode() const
{
	return StringHelper::Sprintf("SCENE_CMD_WIND_SETTINGS(%i, %i, %i, %i)", windDir.x, windDir.y,
	                             windDir.z, clothFlappingStrength);
}

std::string SetWind::GetCommandCName() const
{
	return "SCmdWindSettings";
}

RoomCommand SetWind::GetRoomCommand() const
{
	return RoomCommand::SetWind;
}
