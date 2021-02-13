#pragma once
namespace GT {
#pragma pack(push, 1)
	class PlayerCheckpoint{
	public:
		char pad_0000[236]; //0x0000
		float xPos; //0x00EC
		float yPos; //0x00F0
		float yVelocity; //0x00F4
		char pad_00F8[28]; //0x00F8
		
		//These fields aren't real
		//The space is allocated by DDHOR-Bot
		//For internal usage: Extra 16 bytes
		double accYVelocity; //0x0114
		float xRotation; //0x011C
		float yRotation; //0x0120
	}; //Size: 0x0124
#pragma pack(pop)
}