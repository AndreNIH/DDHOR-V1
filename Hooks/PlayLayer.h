#pragma once
#include "../Types/PlayLayer.h"
namespace Hook {
	namespace PlayLayer {
		inline void(__thiscall* updatePtr)(GT::PlayLayer*, float) = nullptr;
		inline void(__thiscall* resetLevelPtr)(GT::PlayLayer*) = nullptr;
		inline void(__thiscall* levelCompletePtr)(GT::PlayLayer*) = nullptr;
		inline bool(__thiscall* initPtr)(GT::PlayLayer*, void*) = nullptr;
		inline void(__thiscall* onQuitPtr)(GT::PlayLayer*) = nullptr;
		
		void __fastcall update(GT::PlayLayer* self, int edx, float dt);
		void __fastcall resetLevel(GT::PlayLayer* self);
		void __fastcall levelComplete(GT::PlayLayer* self);
		bool __fastcall init(GT::PlayLayer* self, int edx, void* gameLevel);
		void __fastcall onQuit(GT::PlayLayer* self);
		
		void memInit();
	};
}