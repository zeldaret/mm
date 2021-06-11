#include "ZCutsceneMM.h"
#include "BitConverter.h"
#include "StringHelper.h"

using namespace std;

ZCutsceneMM::ZCutsceneMM(std::vector<uint8_t> nRawData, int rawDataIndex, int rawDataSize)
{
	rawData = std::move(nRawData);
	segmentOffset = rawDataIndex;

	numCommands = BitConverter::ToInt32BE(rawData, rawDataIndex + 0);
	commands = vector<CutsceneCommand*>();

	endFrame = BitConverter::ToInt32BE(rawData, rawDataIndex + 4);
	uint32_t currentPtr = rawDataIndex + 8;
	uint32_t lastData = 0;

	// TODO cutscenes have an inconsistent amount of padding after them. Figure it out
	do
	{
		lastData = BitConverter::ToInt32BE(rawData, currentPtr);
		data.push_back(lastData);
		currentPtr += 4;
	} while (lastData != 0xFFFFFFFF);
}

ZCutsceneMM::~ZCutsceneMM()
{
	for (CutsceneCommand* cmd : commands)
		delete cmd;
}

string ZCutsceneMM::GetSourceOutputCode(const std::string& prefix)
{
	string output = "";
	size_t size = 0;
	int32_t curPtr = 0;

	// output += StringHelper::Sprintf("// SIZE = 0x%04X\n", GetRawDataSize());
	output += StringHelper::Sprintf("\tCS_BEGIN_CUTSCENE(%i, %i),\n", numCommands, endFrame);

	for (size_t i = 0; i < data.size(); i++)
	{
		output += StringHelper::Sprintf("\t0x%08X,", data[i]);
		if ((i % 4) == 3)
		    output += "\n";
	}

	//output += StringHelper::Sprintf("\tCS_END(),\n", commands.size(), endFrame);

	return output;
}

int ZCutsceneMM::GetRawDataSize()
{
	return 8 + data.size() * 4;
}

ZResourceType ZCutsceneMM::GetResourceType()
{
	return ZResourceType::Cutscene;
}
