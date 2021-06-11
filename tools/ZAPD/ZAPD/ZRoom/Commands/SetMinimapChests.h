#pragma once

#include "../ZRoomCommand.h"

class MinimapChest
{
public:
	uint16_t unk0;
	uint16_t unk2;
	uint16_t unk4;
	uint16_t unk6;
	uint16_t unk8;

	MinimapChest(std::vector<uint8_t> rawData, int rawDataIndex);
};

class SetMinimapChests : public ZRoomCommand
{
public:
	SetMinimapChests(ZRoom* nZRoom, std::vector<uint8_t> rawData, int rawDataIndex);
	~SetMinimapChests();

	virtual std::string GenerateSourceCodePass1(std::string roomName, int baseAddress);
	virtual std::string GenerateSourceCodePass2(std::string roomName, int baseAddress);
	virtual std::string GetCommandCName();
	virtual std::string GenerateExterns();
	virtual RoomCommand GetRoomCommand();
	virtual std::string PreGenSourceFiles();
	virtual std::string Save();

private:
	std::vector<MinimapChest*> chests;
	uint32_t segmentOffset;
};