#define WIN32_LEAN_AND_MEAN
#include "PlayLayer.h"
#include "GJBaseGameLayer.h"
#include "Helpers/Performer.h"
#include "Helpers/InputStatus.h"
#include "../Engine/SharedBot.h"
#include "../Settings/BGDSettings.h"
#include "../../../Classes/Layers/InputDesycLayer.h"
#include "../../../Types/PlayerCheckpoint.h"
#include "../../../Types/CheckpointObject.h"

#include <Windows.h>
#include <cocos2d.h>
#include <CCScheduler.h>
#include <Minhook/MinHookExt.h>





namespace Hook {
	void __fastcall PlayLayer::update(GT::PlayLayer* self, int edx, float dt){
		BotStage stage = BotManager::shared()->getStage();
		if (stage == BotStage::IDLE) {
			updatePtr(self, dt);
			return;
		}
		else if (stage == BotStage::PLAYING) {
			tryActionOnPlayer(self, self->player1, true);
			tryActionOnPlayer(self, self->player2, false);
		}
		else if (stage == BotStage::RECORDING) {
			if (BGDSettings::shared()->getFrameFreeze()) {
				if (GetAsyncKeyState('W') != -32767) return;
			}
		}
		const float newDt = BGDSettings::shared()->getDisableDeltaOverride()
			? dt : 1.0f / BGDSettings::shared()->getFPS();
		updatePtr(self, newDt);
	}
	
	void __fastcall PlayLayer::resetLevel(GT::PlayLayer* self){
		BotManager* bot = BotManager::shared();
		if (bot->getStage() == BotStage::IDLE) {
			resetLevelPtr(self);
		}else if(bot->getStage() == BotStage::RECORDING){
			//add rewind code
			float lastCheckpointXpos = self->checkpointArray->count()
				? reinterpret_cast<GT::CheckpointObject*>(self->checkpointArray->lastObject())->playerCheckpoint->xPos
				: 0;
			
			bot->recorders().first.rollback(lastCheckpointXpos);
			bot->recorders().second.rollback(lastCheckpointXpos);

			const bool stateMatches =
				GDIS::recorderMatchesState(bot->recorders().first, true) &&
				GDIS::recorderMatchesState(bot->recorders().second, false);
			if (stateMatches) 
				resetLevelPtr(self);
			else {
				auto layer = InputDesyncLayer::create();
				layer->setPlayLayerDelegate(self);
				reinterpret_cast<cocos2d::CCLayer*>(self)->addChild(layer,3);
				printf("Mismatch, do not respawn\n");
			}
		}
		else if (bot->getStage() == BotStage::PLAYING) {
			resetLevelPtr(self);
			bot->players().first.rewind(self->player1->XPos);
			bot->players().second.rewind(self->player1->XPos);
			
		}
		assert(true, "This statement should NEVER execute, PlayLayer");
	}
	
	void __fastcall PlayLayer::levelComplete(GT::PlayLayer* self)
	{
		levelCompletePtr(self);
	}
	
	bool __fastcall PlayLayer::init(GT::PlayLayer* self, int edx, void* gameLevel)
	{
		return PlayLayer::initPtr(self,gameLevel);
	}
	
	void __fastcall PlayLayer::onQuit(GT::PlayLayer* self)
	{
		onQuitPtr(self);
	}
	void PlayLayer::memInit()
	{
		DWORD base = reinterpret_cast<DWORD>(GetModuleHandleA(0));
		CreateHook(base + 0x2029C0, update, &updatePtr);
		CreateHook(base + 0x20BF00, resetLevel, &resetLevelPtr);
		CreateHook(base + 0x1FD3D0, levelComplete, &levelCompletePtr);
		CreateHook(base + 0x01FB780, init, &initPtr);
		CreateHook(base + 0x20D810, onQuit, &onQuitPtr);
	}
}
