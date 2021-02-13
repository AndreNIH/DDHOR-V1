#include "InputDesycLayer.h"
#include "../../Hooks/PlayLayer.h"
#include "../../Engine/SharedBot.h"
#include "../../Hooks/Helpers/InputStatus.h"
#include "../../../Types/PlayerCheckpoint.h"
#include "../../../Types/CheckpointObject.h"
#include <formatx.h>

using namespace cocos2d;
//Duplicate Function

void InputDesyncLayer::setPlayLayerDelegate(GT::PlayLayer* playLayer)
{
    m_playLayerDelegate = playLayer;
}

bool InputDesyncLayer::init()
{
    if(!CCLayer::init())
        return false;
    auto createStatusLabel = [](DDHBRecorder& b) {
        return b.empty() || b.last().action == Actions::RELEASE
            ? "RELEASE"
            : "HOLD";
    };
    
    CCScheduler* scheduler =CCDirector::sharedDirector()->getScheduler();
    scheduler->scheduleUpdateForTarget(this, 0, false);
    
    auto bot = BotManager::shared();
    auto menu = CCMenu::create();
    m_player1Label = CCLabelTTF::create("", "Arial", 12);
    m_player2Label = CCLabelTTF::create("", "Arial", 12);
    m_player1Label->setString(stdx::format("Player 1: %s to respawn", createStatusLabel(bot->recorders().first)).c_str());
    m_player2Label->setString(stdx::format("Player 2: %s to respawn", createStatusLabel(bot->recorders().second)).c_str());
    menu->addChild(CCMenuItemLabel::create(m_player1Label));
    menu->addChild(CCMenuItemLabel::create(m_player2Label));
    menu->alignItemsVertically();
    
    addChild(menu);
    return true;
}

void InputDesyncLayer::update(float dt) {
    assert(m_playLayerDelegate != nullptr, "InputDesyncLayer::has no attached delegate");
    std::cout << "Querrying mouse status\n";
    auto bot = BotManager::shared();
    
    float lastCheckpointXpos = m_playLayerDelegate->checkpointArray->count()
        ? reinterpret_cast<GT::CheckpointObject*>(m_playLayerDelegate->checkpointArray->lastObject())->playerCheckpoint->xPos
        : 0;
    bot->recorders().first.rollback(lastCheckpointXpos);
    bot->recorders().second.rollback(lastCheckpointXpos);
    
    const bool p1Match = GDIS::recorderMatchesState(bot->recorders().first, true);
    const bool p2Match = GDIS::recorderMatchesState(bot->recorders().second, false);
 
    if (p1Match && p2Match) {
        Hook::PlayLayer::resetLevelPtr(m_playLayerDelegate);
        const float position = m_playLayerDelegate->player1->XPos;
        BotManager::shared()->recorders().first.rollback(position);
        BotManager::shared()->recorders().second.rollback(position);
        removeFromParentAndCleanup(true);
    }
}