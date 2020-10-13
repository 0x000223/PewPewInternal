#include "pch.h"
#include "Sdk.h"

//
void Render::Text(int x, int y, ImColor color, const char* text, float outline)
{
	ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(x, y), color, text, text + strlen(text), outline);
}

//
void Render::Line(int x1, int y1, int x2, int y2, ImColor color, float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thickness);
}

//
void Render::Menu()
{
	ImGui::SetNextWindowPos(ImVec2(50, 10));
	ImGui::SetNextWindowSize(ImVec2(100, 100));

	ImGui::Begin("Menu");

	ImGui::Text("This is my menu");

	ImGui::End();
}

//
void Render::Meme()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_Always);
	
	ImGui::Begin(" ", 
				nullptr, 
				ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration);

	
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	
	auto *ClientEntityList = (IClientEntityList*)GetInterface("client.dll", "VClientEntityList003");

	// Player iteration
	for(int i = 1; i < ClientEntityList->GetHighestEntityIndex(); i++)
	{
		auto *currentEntity = (Entity*)(ClientEntityList->GetClientEntity(i));
		
		if(!Meme::IsValidEntity(currentEntity))
			continue;

		Vector2 position2d;

		// Snapline
		if(Meme::WorldToScreen(currentEntity->vecOrigin, position2d))
			Line(position2d.x, position2d.y, windowWidth / 2, windowHeight, ImColor(255, 0, 0, 255), 0.2f);

		Text(position2d.x, position2d.y, ImColor(255,255,255,255), "test", 1.0f);
	}

	ImGui::End();
}

