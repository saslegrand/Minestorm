#pragma once

#include <raylib.h>

struct Sounds
{
	void load()
	{
		playerShoot    = LoadSound("assets/sounds/playerShoot2.wav");
		playerShip	   = LoadSound("assets/sounds/SpaceShip.wav");
		mainMenuSong   = LoadSound("assets/sounds/mainMusic.wav");
		mineLayerMove  = LoadSound("assets/sounds/mineLayer.wav");
		mineExplosion  = LoadSound("assets/sounds/ExploMine.wav");
		mineAppear	   = LoadSound("assets/sounds/MineAppear.wav");
		spawnPoints    = LoadSound("assets/sounds/minestorm.wav");
		shipExplosion  = LoadSound("assets/sounds/ExploSpaceShip.wav");
		playerTeleport = LoadSound("assets/sounds/teleportationPlayer.wav");
	}

	void unload()
	{
		UnloadSound(playerTeleport);
		UnloadSound(shipExplosion);
		UnloadSound(spawnPoints);
		UnloadSound(mineAppear);
		UnloadSound(mineExplosion);
		UnloadSound(mineLayerMove);
		UnloadSound(mainMenuSong);
		UnloadSound(playerShip);
		UnloadSound(playerShoot);
	}

	void stop()
	{
		StopSound(playerTeleport);
		StopSound(shipExplosion);
		StopSound(spawnPoints);
		StopSound(mineAppear);
		StopSound(mineExplosion);
		StopSound(mineLayerMove);
		StopSound(mainMenuSong);
		StopSound(playerShip);
		StopSound(playerShoot);
	}

	Sound playerShoot;
	Sound playerShip;
	Sound mainMenuSong;
	Sound mineLayerMove;
	Sound mineExplosion;
	Sound mineAppear;
	Sound spawnPoints;
	Sound shipExplosion;
	Sound playerTeleport;
};
