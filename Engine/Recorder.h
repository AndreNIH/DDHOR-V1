#pragma once
#include "Primitives.h"
#include <vector>
#include <ostream>


class DDHBRecorder {
	std::vector<PlayerAction> m_actions;
public:
	void add(const PlayerAction& actions) {
		if (actions.xposition > 0)
			m_actions.push_back(actions);
	}
	void reset() { m_actions.clear(); }
	void rollback(float position);
	bool empty() const { return m_actions.empty(); }

	const PlayerAction& last() const { return m_actions.back(); }
	size_t size() const { return m_actions.size(); }
	bool isDuplicated(const PlayerAction& newAction) const;

	friend std::ostream& operator<<(std::ostream& lhs, const DDHBRecorder& rhs);
};

