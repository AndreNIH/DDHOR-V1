#pragma once
#include "PlayerCheckpoint.h"
namespace GT {
	class CheckpointObject{
	public:
		char pad_0000[240]; //0x0000
		PlayerCheckpoint* playerCheckpoint; //0x00F0
	}; //Size: 0x00F4
}
