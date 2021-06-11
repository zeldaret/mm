#pragma once

#include "ActorList.h"
#include "../Globals.h"
#include "../StringHelper.h"
#include "ObjectList.h"
//#include "RoomList.h"

#include <string>

class ZNames
{
public:
	//static std::string GetRoomName(int offset)
	//{
	//	if (Globals::Instance->game == ZGame::OOT)
	//		return RoomList[offset];
	//	else
	//		return RoomListMM[offset];
	//}

	static std::string GetObjectName(int id)
	{
		switch (Globals::Instance->game)
		{
		case ZGame::OOT_RETAIL:
		case ZGame::OOT_SW97:
			return ObjectList[id];
		case ZGame::MM_RETAIL:
			return ObjectListMM[id];
		}

		return "";
	}

	static std::string GetActorName(int id)
	{
		switch (Globals::Instance->game)
		{
		case ZGame::OOT_RETAIL:
		case ZGame::OOT_SW97:
			if (id < ZNames::GetNumActors())
				return ActorList[id];
			else
				return StringHelper::Sprintf("0x%04X", id);
		case ZGame::MM_RETAIL:
			{
				int flags = id & 0xF000;
				id &= 0xFFF;
				std::string name = "";
				if (id < ZNames::GetNumActors())
					name = ActorListMM[id];
				else
					name = StringHelper::Sprintf("0x%04X", id);

				if (flags == 0)
				    return name;
				else
					return StringHelper::Sprintf("%s | 0x%04X", name.c_str(), flags);
			}
		}

		return "";
	}

	static int GetNumActors()
	{
		switch (Globals::Instance->game)
		{
		case ZGame::OOT_RETAIL:
		case ZGame::OOT_SW97:
			return sizeof(ActorList) / sizeof(ActorList[0]);
		case ZGame::MM_RETAIL:
			return sizeof(ActorListMM) / sizeof(ActorListMM[0]);
		}

		return 0;
	}
};
