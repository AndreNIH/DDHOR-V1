#pragma once
#include "../../Engine/Primitives.h"
#include "../../Engine/Recorder.h"
namespace GDIS {
	void reportInputStatus(bool p1, Actions reportedVal);
	Actions queryInputStatus(bool p1);
	bool recorderMatchesState(const DDHBRecorder& recorder, bool p1);
}