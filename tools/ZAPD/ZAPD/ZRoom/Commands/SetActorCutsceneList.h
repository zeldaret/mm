#pragma once

#include "../ZRoomCommand.h"

class ActorCutsceneEntry
{
public:
	int16_t priority;
	int16_t length;
	int16_t unk4;
	int16_t unk6;
	int16_t additionalCutscene;
	uint8_t sound;
	uint8_t unkB;
	int16_t unkC;
	uint8_t unkE;
	uint8_t letterboxSize;

	ActorCutsceneEntry(std::vector<uint8_t> rawData, int rawDataIndex);
};

class SetActorCutsceneList : public ZRoomCommand
{
public:
	SetActorCutsceneList(ZRoom* nZRoom, std::vector<uint8_t> rawData, int rawDataIndex);
	~SetActorCutsceneList();

	virtual std::string GenerateSourceCodePass1(std::string roomName, int baseAddress);
	virtual std::string GenerateSourceCodePass2(std::string roomName, int baseAddress);
	virtual std::string GetCommandCName();
	virtual std::string GenerateExterns();
	virtual RoomCommand GetRoomCommand();
	virtual std::string PreGenSourceFiles();
	virtual std::string Save();

private:
	std::vector<ActorCutsceneEntry*> cutscenes;
	uint32_t segmentOffset;
};