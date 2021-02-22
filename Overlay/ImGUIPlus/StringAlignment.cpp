#include "StringAlignment.h"
#include <vector>
#include <imgui/imgui.h>

std::vector<std::string> atomize(std::string source, const char delim, bool includeDelim=false) {
	if (source.empty()) return {};
	if (source.back() != delim) source += delim;
	size_t offset = 0;
	std::vector<std::string>buffer;
	for (;;) {
		size_t newOffset = source.find(delim, offset);
		if (newOffset == std::string::npos)
			break;
		size_t charCount = newOffset - offset;
		buffer.push_back(source.substr(offset, charCount + includeDelim));
		offset = newOffset + 1;
	}
	return buffer;
}

void ImGUIPlus::String::centerText(std::string const& text)
{
	auto lines = atomize(text, '\n');
	for (auto& line : lines) {
		ImGui::Dummy(ImVec2(0, 0));
		float font_size = ImGui::GetFontSize() * line.size() / 2;
		ImGui::SameLine(
			ImGui::GetWindowSize().x / 2 -
			font_size + (font_size / 2)
		);
		ImGui::Text(line.c_str());
	}
}
