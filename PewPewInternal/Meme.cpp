#include "pch.h"

uintptr_t Meme::client = 0;
uintptr_t Meme::engine = 0;

Entity* Meme::localEntity = nullptr;
float   Meme::viewMatrix[16] = { 0 };

//
void Meme::Init()
{
	client = (uintptr_t)GetModuleHandle("client.dll");
	engine = (uintptr_t)GetModuleHandle("engine.dll");
}
//
void Meme::Update()
{
	memcpy(&viewMatrix, (PBYTE*)(client + offsets::dwViewMatrix), sizeof(viewMatrix));
}

//
bool Meme::IsValidEntity(Entity* entity)
{
	if(entity == nullptr) // ????
		return false;

	if(entity == localEntity) // Local
		return false;

	if(entity->iHealth <= 0) // Dead
		return false;

	if(entity->isDormant) // Dormant
		return false;

	return true;
}

//
bool Meme::WorldToScreen(Vector3 position, Vector2 &screen)
{
	Vector4 clipcoords;
	
	clipcoords.x = position.x * viewMatrix[0]  + position.y * viewMatrix[1]  + position.z * viewMatrix[2]  + viewMatrix[3];
	clipcoords.y = position.x * viewMatrix[4]  + position.y * viewMatrix[5]  + position.z * viewMatrix[6]  + viewMatrix[7];
	clipcoords.z = position.x * viewMatrix[8]  + position.y * viewMatrix[9]  + position.z * viewMatrix[10] + viewMatrix[11];
	clipcoords.w = position.x * viewMatrix[12] + position.y * viewMatrix[13] + position.z * viewMatrix[14] + viewMatrix[15];

	if(clipcoords.w < 0.1f)
		return false;

	Vector3 NDC;

	NDC.x = clipcoords.x / clipcoords.w;
	NDC.y = clipcoords.y / clipcoords.w;
	NDC.z = clipcoords.z / clipcoords.w;

	screen.x =  (windowWidth  / 2 * NDC.x) + (NDC.x + windowWidth  / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

	return true;
}

//
Vector3 Meme::GetBonePosition(Entity* entity, int bone)
{
	uintptr_t bonePtr = entity->boneMatrix;
	Vector3 bonePos;

	bonePos.x = *(float*) (bonePtr + 0x30 * bone + 0x0C);
	bonePos.y = *(float*) (bonePtr + 0x30 * bone + 0x1C);
	bonePos.z = *(float*) (bonePtr + 0x30 * bone + 0x2C);

	return bonePos;
}