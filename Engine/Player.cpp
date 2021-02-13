#include "Player.h"
#include <cassert>
#include <streamx.h>

void DDHBPlayer::rewind(float position) {
	auto match = std::find_if(
		m_actions.rbegin(),
		m_actions.rend(),
		[position](const PlayerAction& action) {return action.xposition <= position; }
	);
	m_currentAction = match != m_actions.rend()
		? std::distance(match, m_actions.rend()) - 1
		: 0;
}

bool DDHBPlayer::can_act(float position) {
	if (m_currentAction == m_actions.size()) return false;
	return position >= m_actions[m_currentAction].xposition;
}

void DDHBPlayer::reset() {
	m_actions.clear();
	m_currentAction = 0;
}

const PlayerAction& DDHBPlayer::fetch() {
	assert(
		m_currentAction != m_actions.size(), 
		"Trying to FETCH from an exhausted Player object");
	return m_actions[m_currentAction++];
}

std::istream& operator>>(std::istream& lhs, DDHBPlayer& rhs) {
	rhs.m_actions.push_back({
		stdx::binary_read<float>(lhs),
		stdx::binary_read<Actions>(lhs)
		}
	);
	return lhs;
}
