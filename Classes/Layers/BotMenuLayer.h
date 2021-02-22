#pragma once
#include <cocos2d.h>

class BotMenuLayer : public cocos2d::CCLayerGradient {
private:
	void* m_realOnPlaySelector = nullptr;
	cocos2d::CCLayer* m_menuLayerDelegate  = nullptr;

	void decorateWithCorners();
	void populateMenu();

	//Button Callbacks;
	void onLoadMacro(CCObject* sender) {};
	void onRecordMacro(CCObject* sender) {};
	void onPlayNormal(CCObject* sender);
public:
	void registerWithTouchDispatcher() override;
	void onEnter() override;
	
	void addMenuLayerDelegate(cocos2d::CCLayer* layer) { m_menuLayerDelegate = layer; }
	void addPlayMenuSelector(void* selector) {m_realOnPlaySelector = selector;}
	
	bool init() override;
	CREATE_FUNC(BotMenuLayer);
};