#pragma once

#include "ZRoom/ZRoomCommand.h"

class SetWind : public ZRoomCommand
{
public:
	SetWind(ZFile* nParent);

	void ParseRawData() override;

	std::string GetBodySourceCode() const override;

	std::string GetCommandCName() const override;
	RoomCommand GetRoomCommand() const override;

private:
	uint8_t windDir.x;
	uint8_t windDir.y;
	uint8_t windDir.z;
	uint8_t clothFlappingStrength;
};
