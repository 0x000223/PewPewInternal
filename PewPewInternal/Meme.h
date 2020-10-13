#pragma once

class Meme
{
public:

	static uintptr_t engine;
	static uintptr_t client;
	
	static Entity* localEntity;
	static float viewMatrix[16];

	static void Init();
	
	static void Update();

	static bool IsValidEntity(Entity* entity);

	static bool WorldToScreen(Vector3 position, Vector2 &screen);

	static Vector3 GetBonePosition(Entity* entity, int bone);
};