#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include "ZCutscene.h"
#include "tinyxml2.h"

class ZCutsceneMM : public ZCutsceneBase
{
public:
	uint32_t segmentOffset;

	ZCutsceneMM(std::vector<uint8_t> nRawData, int rawDataIndex, int rawDataSize);
	~ZCutsceneMM();

	std::string GetSourceOutputCode(const std::string& prefix) override;
	int GetRawDataSize() override;
	uint32_t getSegmentOffset() override { return segmentOffset; }

	ZResourceType GetResourceType() override;

protected:
	int numCommands;
	int endFrame;
	std::vector<CutsceneCommand*> commands;

	std::vector<uint32_t> data;
};
