#include "Performer.h"
#include <memory>
#include <utility>
#include <vector>
#include "../../Engine/SharedBot.h"
#include "../GJBaseGameLayer.h"

void tryActionOnPlayer(GT::PlayLayer* playLayer, GT::PlayerObject* player, bool p1)
{
	typedef void(__thiscall* buttonFunction)(void* thisPtr, int unknown, bool p1);
	DDHBPlayer& bot = p1
		? BotManager::shared()->players().first
		: BotManager::shared()->players().second;

	void* funcs[2] = {
		&Hook::GJBaseGameLayer::pushButtonPtr,
		&Hook::GJBaseGameLayer::releaseButtonPtr };

	if (bot.can_act(player->XPos)) {
		auto nextAction = bot.fetch();
		auto func = *reinterpret_cast<buttonFunction*>(funcs[static_cast<int>(nextAction.action)]);
		func(playLayer, 0, p1);
	}

}
