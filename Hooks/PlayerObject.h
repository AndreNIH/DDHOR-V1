#pragma once
#include "../../../Types/PlayerObject.h"
#include "../../../Types/PlayerCheckpoint.h"
namespace Hook {
	namespace PlayerObject {
		inline void(__thiscall* saveToCheckpointPtr)(GT::PlayerObject* self, GT::PlayerCheckpoint*);
		inline void(__thiscall* loadFromCheckpointPtr)(GT::PlayerObject* self, GT::PlayerCheckpoint*);
		void __fastcall saveToCheckpoint(GT::PlayerObject* self, int edx, GT::PlayerCheckpoint*);
		void __fastcall loadFromCheckpoint(GT::PlayerObject* self, int edx, GT::PlayerCheckpoint*);
		void memInit();
	}
}