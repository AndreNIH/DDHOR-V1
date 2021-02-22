#include "BotMenuLayer.h"
#include <cocos-ext.h>
#include <array>
#include <algorithm>
using namespace cocos2d;
//Layer setup

typedef void(__thiscall* menuSelectorPtr)(CCLayer*, CCObject*);
void BotMenuLayer::decorateWithCorners()
{
    std::array<CCSprite*, 2>corners;
    enum Corner {
        BOTTOM_LEFT,
        BOTTOM_RIGHT,
    };
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    std::generate(
        corners.begin(), 
        corners.end(), 
        [] {return CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png"); });
    corners[Corner::BOTTOM_LEFT]->setPosition({
        corners[Corner::BOTTOM_LEFT]->getContentSize().width / 2,
        corners[Corner::BOTTOM_LEFT]->getContentSize().height / 2
        }
    );
    corners[Corner::BOTTOM_RIGHT]->setFlipX(true);
    corners[Corner::BOTTOM_RIGHT]->setPosition({
        winSize.width - corners[Corner::BOTTOM_RIGHT]->getContentSize().width / 2,
        corners[Corner::BOTTOM_RIGHT]->getContentSize().height / 2
        });
    
    auto topBar = CCSprite::createWithSpriteFrameName("GJ_topBar_001.png");
    topBar->setPosition({
        winSize.width / 2,
        winSize.height - topBar->getContentSize().height / 2
        });
    for (auto& corner : corners) addChild(corner);
    addChild(topBar);
}

void BotMenuLayer::populateMenu() {
    auto generateBtn = [&](CCSprite* sprite, SEL_MenuHandler menu) {
        return CCMenuItemSpriteExtra::create(sprite, sprite, this, menu);
    };
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* normalBtnSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
    CCSprite* recordBtnSprite = CCSprite::createWithSpriteFrameName("D2B_RecordBtn_001.png");
    CCSprite* loadBtnSprite = CCSprite::createWithSpriteFrameName("D2B_LoadBtn_001.png");
    CCMenuItemSpriteExtra* normalBtn = generateBtn(normalBtnSprite, menu_selector(BotMenuLayer::onPlayNormal));
    CCMenuItemSpriteExtra* recordBtn = generateBtn(recordBtnSprite, menu_selector(BotMenuLayer::onRecordMacro));
    CCMenuItemSpriteExtra* loadBtn   = generateBtn(loadBtnSprite, menu_selector(BotMenuLayer::onLoadMacro));
    CCMenu* buttonMenu = CCMenu::create();
    buttonMenu->addChild(normalBtn);
    //buttonMenu->addChild(recordBtn); 
    //buttonMenu->addChild(loadBtn);
    buttonMenu->alignItemsHorizontallyWithPadding(25.0f);
    buttonMenu->setPosition({ winSize.width / 2, winSize.height / 2 });
    buttonMenu->setTouchPriority(-400);

    auto background = extension::CCScale9Sprite::create("square01_001-uhd.png");
    background->setContentSize({ 371,160 });
    background->setPosition({ winSize.width / 2 ,winSize.height / 2 });
    addChild(background, 0);
    addChild(buttonMenu);
}

void BotMenuLayer::registerWithTouchDispatcher(){
    auto director = CCDirector::sharedDirector();
    director->getTouchDispatcher()->incrementForcePrio(-1);
    director->getTouchDispatcher()->addTargetedDelegate(this, -399, true);
}

void BotMenuLayer::onEnter()
{
    assert(m_menuLayerDelegate != nullptr, "BotMenu::onEnter layer delegate is nullptr");
    m_menuLayerDelegate->setKeypadEnabled(false);
    auto window = CCDirector::sharedDirector()->getWinSize();
    setPositionX(-getContentSize().height);
    runAction(CCMoveTo::create(0.3, ccp(0, 0)));
    CCLayerGradient::onEnter();
}

bool BotMenuLayer::init(){
    const ccColor4B startGradient = { 0, 101, 253, 255 };
    const ccColor4B endGradient = { 0, 46, 115, 255 };
    if (!CCLayerGradient::initWithColor(startGradient, endGradient))
        return false;
    
    setTouchEnabled(true);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    decorateWithCorners();
    populateMenu();
    
    
    return true;
}


//Button Callbacks
void BotMenuLayer::onPlayNormal(CCObject* sender)
{
    assert(m_menuLayerDelegate != nullptr, "BotMenuLayer::m_menuLayerDelegate is nullptr");
    reinterpret_cast<menuSelectorPtr>(m_realOnPlaySelector)(m_menuLayerDelegate, 0);
}