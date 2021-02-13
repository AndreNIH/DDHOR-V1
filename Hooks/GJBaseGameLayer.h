#pragma once
#include "../Types/GJBaseGameLayer.h"

namespace Hook {
	namespace GJBaseGameLayer {
		inline bool pauseRecording = false;
		inline void(__thiscall* pushButtonPtr)(GT::GJBaseGameLayer*, int, bool) = nullptr;
		inline void(__thiscall* releaseButtonPtr)(GT::GJBaseGameLayer*, int, bool) = nullptr;

		void __fastcall pushButtonHook(GT::GJBaseGameLayer* self, int edx, int a1, bool leftTouch);
		void __fastcall releaseButtonHook(GT::GJBaseGameLayer* self, int edx, int a1, bool leftTouch);
		void memInit();
	}
}