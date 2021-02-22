#include "LevelPage.h"
#include "../Helpers/BotMenuCreator.h"
#include <Minhook/MinhookExt.h>
using namespace cocos2d;

void __fastcall Hook::LevelPage::onPlay(CCLayer* self, int edx, CCObject* sender){
	tryMenuCreation(self, onPlayPtr); 
	//std::cout << "LevelPage" self->getChildrenCount();
}

void Hook::LevelPage::memInit()
{
	DWORD base = reinterpret_cast<DWORD>(GetModuleHandleA(0));
	CreateHook(base + 0x188C70, onPlay, &onPlayPtr);
}
