#pragma once
#include "PlayerObject.h"
#include "GJEffectManager.h"

namespace GT {
	class GJBaseGameLayer
	{
	public:
		char pad_0000[548]; //0x0000
		PlayerObject* player1; //0x0224
		PlayerObject* player2; //0x0228
		GJEffectManager* effectManager; //0x022C
		char pad_0230[121]; //0x0230
		bool isDualMode; //0x02A9
		char pad_02AA[48]; //0x02AA
	};
	//Total Size: 0x2C8
}