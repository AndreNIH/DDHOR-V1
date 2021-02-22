#pragma once
#include <imgui/imgui.h>
#include <functional>
#include <string>
namespace ImGUIPlus {
	class Tabs {
	private:
		bool m_isActive = false;
	public:
		Tabs(std::string const& tabName, ImGuiTabBarFlags flags=0);
		~Tabs();
		
		void finalize();
		bool populate(const std::string& itemName, std::function<void()> callback);
	};
}