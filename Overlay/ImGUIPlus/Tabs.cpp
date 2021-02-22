#include "Tabs.h"
#include <stdexcept>
ImGUIPlus::Tabs::Tabs(std::string const& tabName, ImGuiTabBarFlags flags) {
	if (!ImGui::BeginTabBar(tabName.c_str(), flags))
		std::runtime_error{ "Tabs ctor throw" };
	m_isActive = true;
}

ImGUIPlus::Tabs::~Tabs()
{
	finalize();
}

void ImGUIPlus::Tabs::finalize()
{
	if (m_isActive) {
		ImGui::EndTabBar();
		m_isActive = false;
	}
}

bool ImGUIPlus::Tabs::populate(const std::string& itemName, std::function<void()> callback)
{
	if (ImGui::BeginTabItem(itemName.c_str())) {
		callback();
		ImGui::EndTabItem();
		return true;
	}
	return false;
}


