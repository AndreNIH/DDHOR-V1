#include "GJBaseGameLayer.h"
#include "Helpers/RecorderSelector.h"
#include "../Engine/SharedBot.h"
#include <Minhook/MinHookExt.h>
#include <Windows.h>
#include "Helpers/InputStatus.h"

void processEvent(DDHBRecorder& targetRecorder, PlayerAction event) {
	if (targetRecorder.isDuplicated(event))
		return;
	targetRecorder.add(event);
}

void __fastcall Hook::GJBaseGameLayer::pushButtonHook(GT::GJBaseGameLayer* self, int edx, int a1, bool leftTouch){
	if (BotManager::shared()->getStage() == BotStage::RECORDING && !self->player1->isDead) {
		processEvent(
			selectRecorder(self, leftTouch),
			{ self->player1->XPos, Actions::HOLD }
		);
	}
	
	GDIS::reportInputStatus(isPlayer1(self,leftTouch), Actions::HOLD);
	printf_s("Reporting PUSH, isPlayer1: %d\n", isPlayer1(self, leftTouch));
	pushButtonPtr(self, a1, leftTouch);

}

void __fastcall Hook::GJBaseGameLayer::releaseButtonHook(GT::GJBaseGameLayer* self, int edx, int a1, bool leftTouch){
	if (BotManager::shared()->getStage() == BotStage::RECORDING && !self->player1->isDead) {
		processEvent(
			selectRecorder(self, leftTouch),
			{ self->player1->XPos, Actions::RELEASE}
		);
	}
	GDIS::reportInputStatus(isPlayer1(self, leftTouch), Actions::RELEASE);
	printf_s("Reporting RELEASE, isPlayer1: %d\n", isPlayer1(self, leftTouch));
	releaseButtonPtr(self, a1, leftTouch);
}

void Hook::GJBaseGameLayer::memInit()
{
	DWORD base = reinterpret_cast<DWORD>(GetModuleHandleA(0));
	CreateHook(base + 0x111500, pushButtonHook, &pushButtonPtr);
	CreateHook(base + 0x111660, releaseButtonHook, &releaseButtonPtr);
}
