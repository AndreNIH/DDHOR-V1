#pragma once
#include <cocos2d.h>
#include "../../Types/PlayLayer.h"
class InputDesyncLayer : public cocos2d::CCLayer {
private:
	GT::PlayLayer* m_playLayerDelegate = nullptr;
	cocos2d::CCLabelTTF* m_player1Label = nullptr;
	cocos2d::CCLabelTTF* m_player2Label = nullptr;
public:
	void setPlayLayerDelegate(GT::PlayLayer* playLayer);
	bool init() override;
	void update(float dt) override;
	CREATE_FUNC(InputDesyncLayer);
};