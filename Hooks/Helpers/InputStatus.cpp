#include "InputStatus.h"
#include "../../Types/PlayLayer.h"
Actions gStatus[2] = { Actions::RELEASE };
void GDIS::reportInputStatus(bool p1, Actions reportedVal){
	gStatus[!p1] = reportedVal;
}

Actions GDIS::queryInputStatus(bool p1) {
	return gStatus[!p1];
}

bool GDIS::recorderMatchesState(const DDHBRecorder& recorder, bool p1){
	if (recorder.empty()) return true;
	return recorder.last().action == GDIS::queryInputStatus(p1);
}
