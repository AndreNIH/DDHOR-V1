#include "BGDSettings.h"
#include <CCDirector.h>
BGDSettings* BGDSettings::m_instance = nullptr;
BGDSettings* BGDSettings::shared(){
    if (m_instance == nullptr) m_instance = new BGDSettings();
    return m_instance;
}
//Setters
void BGDSettings::setFPS(short val) {
    m_fps = val;
    cocos2d::CCDirector::sharedDirector()->setAnimationInterval(1.0 / val);
}

//Getters
short BGDSettings::getFPS() const { return m_fps; }

bool BGDSettings::getFrameFreeze() const {
    return false;
}

bool BGDSettings::getDisableDeltaOverride() const {
    return true;
}