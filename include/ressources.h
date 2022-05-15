#pragma once

#include <raylib.h>

struct Ressources
{
	void loadTextures()
	{
		entities	  = LoadTexture("assets/textures/minestorm_entities.png");
		background    = LoadTexture("assets/textures/space2.png");
		titleMainMenu = LoadTexture("assets/textures/mainMenu.png");
	}

	void unload()
	{
		UnloadTexture(titleMainMenu);
		UnloadTexture(background);
		UnloadTexture(entities);
	}

	Texture2D entities;
	Texture2D background;
	Texture2D titleMainMenu;
};
