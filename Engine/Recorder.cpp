#include "Recorder.h"
#include <streamx.h>
#include <cassert>
#include <algorithm>

void DDHBRecorder::rollback(float position) {
	m_actions.erase(std::remove_if(
		m_actions.begin(),
		m_actions.end(),
		[position](const PlayerAction& action) {return action.xposition > position; }
	), m_actions.end());
}

bool DDHBRecorder::isDuplicated(const PlayerAction& newAction) const
{
	return std::find_if(
		m_actions.cbegin(),
		m_actions.cend(),
		[&newAction](const PlayerAction& myAction) {
		return (myAction.xposition == newAction.xposition) &&
			(myAction.action == newAction.action);
	}) != m_actions.cend();

}

std::ostream& operator<<(std::ostream& lhs, const DDHBRecorder& rhs) {
	for (const auto& action : rhs.m_actions) {
		stdx::binary_write(lhs, action.xposition);
		stdx::binary_write(lhs, action.action);
	}
	return lhs;
}
