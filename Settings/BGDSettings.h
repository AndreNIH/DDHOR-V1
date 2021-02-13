#pragma once
#define ATTRIBUTE(varType,varName,functName)\
private: varType varName;\
public:  varType get##functName() const;\
public:  void set##functName(varType var)

class BGDSettings {
private:
	static BGDSettings* m_instance;
	BGDSettings() {};
public:
	ATTRIBUTE(bool, m_frameFreeze, FrameFreeze);
	ATTRIBUTE(bool, m_safeMode, SafeMode);
	ATTRIBUTE(bool, m_watermark, Watermark);
	ATTRIBUTE(bool, m_deltaOverrideDisabled, DisableDeltaOverride);
	ATTRIBUTE(double, m_speedMultiplier, SpeedMultiplier);
	ATTRIBUTE(short, m_fps, FPS);
	
	static BGDSettings* shared();

};
