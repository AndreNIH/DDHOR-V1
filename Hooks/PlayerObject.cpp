#include "PlayerObject.h"
#include <Minhook/MinhookExt.h>
#include <SimpleMemory/SimpleMemory.h>
void __fastcall Hook::PlayerObject::saveToCheckpoint(GT::PlayerObject* self, int edx, GT::PlayerCheckpoint* checkpoint){
	saveToCheckpointPtr(self, checkpoint);
	checkpoint->accYVelocity = self->yVelocityVec;
	checkpoint->xRotation = self->xRotation;
	checkpoint->yRotation = self->yRotation;
}

void __fastcall Hook::PlayerObject::loadFromCheckpoint(GT::PlayerObject* self, int edx, GT::PlayerCheckpoint* checkpoint)
{
	loadFromCheckpointPtr(self, checkpoint);
	self->yVelocityVec = checkpoint->accYVelocity;
	self->xRotation = checkpoint->xRotation;
	self->yRotation = checkpoint->yRotation;
}

void Hook::PlayerObject::memInit(){
	DWORD base = reinterpret_cast<DWORD>(GetModuleHandle(0));
	CreateHook(base + 0x1F9EE0, saveToCheckpoint, &saveToCheckpointPtr);
	CreateHook(base + 0X1FA080, loadFromCheckpoint, &loadFromCheckpointPtr);
	sm::internal::write<char>(base + 0x20DC65, '\x24');
	
}
