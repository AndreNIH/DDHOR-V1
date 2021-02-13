#pragma once
#include <cocos2d.h>

namespace Hook {
	namespace PauseLayer {
		inline void(__thiscall* customSetupPtr)(cocos2d::CCLayer*);
		void __fastcall customSetupHook(cocos2d::CCLayer* self);
		void setup();
	}
}
