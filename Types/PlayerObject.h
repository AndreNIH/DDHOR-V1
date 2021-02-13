#pragma once
namespace GT {
	/*class PlayerObject {
	public:
		char pad_0000[32]; //0x0000
		float xRotation; //0x0020
		float yRotation; //0x0024
		char pad_0028[1536]; //0x0028
		double yVelocityVec; //0x0628
		char pad_0630[76]; //0x0630
		float XPos; //0x067C
		float YPos; //0x0680
	}; //Size: 0x0684*/
	class PlayerObject
	{
	public:
		char pad_0000[32]; //0x0000
		float xRotation; //0x0020
		float yRotation; //0x0024
		char pad_0028[1536]; //0x0028
		double yVelocityVec; //0x0628
		char pad_0630[15]; //0x0630
		bool isDead; //0x063F
		char pad_0640[60]; //0x0640
		float XPos; //0x067C
		float YPos; //0x0680
	}; //Size: 0x0684
}