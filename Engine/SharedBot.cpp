#include "SharedBot.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <streamx.h>
#include "../Settings/BGDSettings.h"

BotManager* BotManager::m_instance = nullptr;

//Debug
void BotManager::printMacroInputs()
{
	std::cout << "Loaded Debug output:\n";
	std::cout << "P1:\n";
	for (int i = 0; i < m_players.first.size(); i++)
		std::cout << m_players.first[i].xposition << ", " << (int)m_players.first[i].action << "\n";
	std::cout << "\n\nP2:\n";
	for (int i = 0; i < m_players.second.size(); i++)
		std::cout << m_players.second[i].xposition << ", " << (int)m_players.second[i].action << "\n";
}

BotManager* BotManager::shared(){
    if (!m_instance) m_instance = new BotManager();
    return m_instance;
}

std::pair<DDHBRecorder, DDHBRecorder>& BotManager::recorders() {
	assert(m_stage == BotStage::RECORDING, "[WRONG STAGE] Illegal access to bot Recorder objects");
	return m_recorders;
}

std::pair<DDHBPlayer, DDHBPlayer>& BotManager::players() {
	assert(m_stage == BotStage::PLAYING, "[WRONG STAGE] Illegal access to bot Playback objects");
	return m_players;
}

bool BotManager::saveRecording(const std::string filename) {
	setStage(BotStage::IDLE);
	std::ofstream output(filename, std::ios::binary);
	if (!output.is_open()) return false;
	output.write("DDHR", 4); 
	stdx::binary_write<uint16_t>(output, BGDSettings::shared()->getFPS());
	stdx::binary_write<uint32_t>(output, m_recorders.first.size());
	stdx::binary_write<uint32_t>(output, m_recorders.second.size());
	for (auto& recorder : { m_recorders.first, m_recorders.second })
		output << recorder; 
	m_recorders.first.reset();
	m_recorders.second.reset();
	return true;
}

bool BotManager::loadRecording(const std::string filename) {
	setStage(BotStage::IDLE);
	m_players.first.reset();
	m_players.second.reset();
	std::ifstream input(filename, std::ios::binary);
	if (!input.is_open()) return false;

#pragma pack(push, 1)
	struct MacroHeader {
		const char magic[4] = { 0 };
		uint16_t fps;
		uint32_t p1ActionCount;
		uint32_t p2ActionCount;
	}header;
#pragma pack(pop)

	input.read(reinterpret_cast<char*>(&header), sizeof(MacroHeader));
	if (memcmp(header.magic, "DDHR", 4) != 0) return false;
	for (size_t i = 0; i < header.p1ActionCount; i++) input >> m_players.first;
	for (size_t i = 0; i < header.p2ActionCount; i++) input >> m_players.second;
	printMacroInputs();
	return true;
}
