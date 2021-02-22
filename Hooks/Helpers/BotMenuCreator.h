#pragma once
#include <cocos2d.h>
enum class CreationValue {
	OK_CREATED,
	ERR_TRANSITIONING,
	ERR_ALREADY_CREATED
};

CreationValue tryMenuCreation(cocos2d::CCLayer* layer, void* opaqueSelector);
