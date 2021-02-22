#include "BotMenuCreator.h"
#include "../../Classes/Layers/BotMenuLayer.h"
#include <optional>
using namespace cocos2d;
CreationValue tryMenuCreation(cocos2d::CCLayer* layer, void* opaqueSelector)
{
	CCDirector* director = CCDirector::sharedDirector();
	CCScene* scene = director->getRunningScene();
	if (director->getIsTransitioning()) return CreationValue::ERR_TRANSITIONING;
	CCNode* createdMenu = scene->getChildByTag(1001);
	if (createdMenu == nullptr) {
		auto botMenu = BotMenuLayer::create();
		botMenu->setTag(1001);
		botMenu->addMenuLayerDelegate(layer);
		botMenu->addPlayMenuSelector(opaqueSelector);
		scene->addChild(botMenu, 1);
		
	
		return CreationValue::OK_CREATED;
	}
	else {
		return CreationValue::ERR_ALREADY_CREATED;
	}
}
