#pragma once
#include <utility>
#include <string>
#include "Player.h"
#include "Recorder.h"

enum class BotStage {
	IDLE,
	PLAYING,
	RECORDING
};

class BotManager {
private:
	template<typename T>
	using HomogenusPair = std::pair<T,T>;
	
	HomogenusPair<DDHBRecorder> m_recorders;
	HomogenusPair<DDHBPlayer> m_players;
	BotStage m_stage = BotStage::IDLE;

	static BotManager* m_instance;
	
	BotManager() {};

	//Debug:
	void printMacroInputs();
public:
	static BotManager* shared();
	
	BotStage getStage() const { return m_stage; }
	void setStage(BotStage stage) { m_stage = stage; }
	HomogenusPair<DDHBRecorder>& recorders();
	HomogenusPair<DDHBPlayer>& players();
	bool saveRecording(const std::string filename);
	bool loadRecording(const std::string filename);
};