#pragma once
#include <cocos2d.h>
namespace Hook {
	namespace EditLevelLayer {
		inline void(__thiscall* onPlayPtr)(cocos2d::CCLayer*, cocos2d::CCObject*) = nullptr;
		void __fastcall onPlay(cocos2d::CCLayer* self, int edx, cocos2d::CCObject* sender);
		void memInit();
	};
}