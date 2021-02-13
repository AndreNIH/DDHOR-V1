#pragma once

enum class Actions : char {
	HOLD,
	RELEASE
};

struct PlayerAction {
	float xposition;
	Actions action;
};
