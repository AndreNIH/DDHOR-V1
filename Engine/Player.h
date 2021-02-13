#pragma once
#include <vector>
#include <istream>
#include "Primitives.h"


class DDHBPlayer {
	std::vector<PlayerAction> m_actions;
	uint32_t m_currentAction = 0;
public:
	friend struct PlayersPlayback;
	void rewind(float position);
	bool can_act(float position);
	void reset();

	
	const PlayerAction& fetch();
	friend std::istream& operator>>(std::istream& lhs, DDHBPlayer& rhs);

	size_t size() const { return m_actions.size(); }
	PlayerAction operator[](int index) { return m_actions[index]; };
};

