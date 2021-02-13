#pragma once
#include "PlayerObject.h"
#include "GJEffectManager.h"
#include <cocoa/CCArray.h>
namespace GT {
#pragma pack(push, 1)
	class PlayLayer
	{
	public:
		char pad_0000[548]; //0x0000
		PlayerObject* player1; //0x0224
		PlayerObject* player2; //0x0228
		GJEffectManager* effectManager; //0x022C
		char pad_0230[121]; //0x0230
		bool isDualMode; //0x02A9
		char pad_02AA[51]; //0x02AA
		bool isHacked; //0x02DD
		int dontAwardFlag1; //0x02DE
		int dontAwardFlag2; //0x02E2
		char pad_02E6[82]; //0x02E6
		cocos2d::CCArray* checkpointArray; //0x0338


	}; //Size: 0x02DE
#pragma pack(pop)

}
