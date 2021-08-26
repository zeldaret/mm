#pragma once

#include "ZRoom/ZRoomCommand.h"

class ActorSpawnEntry
{
public:
	uint16_t actorNum;
	int16_t posX;
	int16_t posY;
	int16_t posZ;
	int16_t rotX;
	int16_t rotY;
	int16_t rotZ;
	uint16_t initVar;

	ActorSpawnEntry(const std::vector<uint8_t>& rawData, uint32_t rawDataIndex);

	std::string GetBodySourceCode() const;

	std::string GetSourceTypeName() const;
	int32_t GetRawDataSize() const;

	uint16_t GetActorId() const;
};

class SetActorList : public ZRoomCommand
{
public:
	uint8_t numActors;
	std::vector<ActorSpawnEntry> actors;

	SetActorList(ZFile* nParent);

	void ParseRawData() override;
	void DeclareReferences(const std::string& prefix) override;

	std::string GetBodySourceCode() const override;

	RoomCommand GetRoomCommand() const override;
	size_t GetRawDataSize() const override;
	std::string GetCommandCName() const override;

protected:
	size_t GetActorListArraySize() const;
};
