#include "RecorderSelector.h"

bool isPlayer1(GT::GJBaseGameLayer* pl, bool leftTouch)
{
	bool is2PM = pl->effectManager->is2PMode;
	if (!is2PM) return true;
	else if (is2PM && !pl->isDualMode) return true;
	else if (is2PM && pl->isDualMode && leftTouch) return true;
	return false;
}

DDHBRecorder& selectRecorder(GT::GJBaseGameLayer* pl, bool leftTouch){
	auto manager = BotManager::shared();
	return isPlayer1(pl, leftTouch)
		? manager->recorders().first
		: manager->recorders().second;
}
