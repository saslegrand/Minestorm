#pragma once

#include "player.h"
#include "mines.h"
#include "spawn_mother_ship.h"
#include "mine_layer.h"
#include "entity.h"
#include "ressources.h"
#include "sounds.h"
#include "mainMenu.h"
#include "animation.h"
#include "mine_explosion.h"
#include "player_explosion.h"
#include "player_teleportation.h"
#include "bullet_explosion.h"
#include "fireball_explosion.h"
#include "mine_layer_explosion.h"
#include "../toolbox/range.h"

enum class GameState
{
	INIT_ROUND,
	PLACE_SPAWNPOINTS,
	SPAWN_PLAYERS,
	GAMEPLAY,
	END_ROUND,
	PLAYER_DEATH
};

enum class Difficulty
{
	EASY,
	NORMAL,
	HARD
};

class Game;
enum class DisplayType;

namespace manage
{
	void initNewRound(SpawnMotherShip& motherShip, std::vector<Vector2D>& spawnPoints, GameState& curState, int round, int(&nbMines)[4]);
	void addDestroyMine(std::vector<Mine*>& mines, std::vector<Vector2D>& spawnPoints, const Ressources& ressources, Sounds* sounds, int index);

	// SpawnPoints
	bool updateSpawnPoints(SpawnMotherShip& motherShip, std::vector<Vector2D>& spawnPoints, float deltaTime);
	void drawPlacingPoint(const SpawnMotherShip& motherShip, const std::vector<Vector2D>& spawnPoints, const Texture2D& texture);
	void drawSpawnPoints(const std::vector<Vector2D>& spawnPoints, const Texture2D& texture);

	// Bullets / Fireballs
	void addBullet(Vector2D origin, Vector2D dir, std::vector<Bullet>& bullets, BulletType type, Color color);
	void addFireBall(Vector2D origin, Vector2D dir, std::vector<Bullet>& bullets);
	void updateBullets(std::vector<Player>& players, std::vector<Bullet>& bulletsPlayer, std::vector<Bullet>& bulletsMine);
	void drawBullets(const std::vector<Bullet>& bulletsPlayer, const std::vector<Bullet>& bulletsMine, const Texture2D& texture);
	void addPotentialBulletMine(Mine* mine, Player& player, std::vector<Bullet>& mineBullets);

	// Entities
	void drawPlayers(const std::vector<Player>& players);
	void updatePlayers(std::vector<Player>& players, std::vector<Animation>& animations);
	void drawMines(const std::vector<Mine*>& mines);
	void updateMines(std::vector<Mine*>& mines);
	void drawEntities(const std::vector<Player>& players, const std::vector<Mine*>& mines);
	void updateEntities(std::vector<Player>& players, std::vector<Mine*>& mines, std::vector<Animation>& animations);
	void updateMineLayer(MineLayer& mineLayer, std::vector<Bullet>& playerBullets, std::vector<Vector2D>& spawnPoints, int& round, int(&nbMines)[4]);
	float randRangeValue(const Range& range);

	void updateWaitingMineSpawn(std::vector<Mine*>& curMines, std::vector<Vector2D>& spawnPoints, const Ressources& ressources, Sounds* sounds, Timer& timer, int round, int(&nbMines)[4]);
	void destroyMine(std::vector<Mine*>& mines, int index);

	// Minelayer
	void setMineLayerSpawn(MineLayer& minelayer);
	void setMineLayer(MineLayer& mineLayer, bool& mineLayerSpawn);

	void setPlayersLife(std::vector<Player>& players, Difficulty difficulty);

	bool isGameOver(std::vector<Player>& players);
	bool isAllPlayersDead(std::vector<Player>& players);

	// Events
	void eventMainMenu(DisplayType& type, std::vector<Player>& players, UI& ui, Ressources& ressources, Sounds& sounds);
	void eventLevelSelect(DisplayType& type, Difficulty& difficulty, UI& ui, Sound& mainMusic);
	void eventGame(DisplayType& type, GameState& state, UI& ui, Sounds& sounds, bool& isDebug);
	bool eventPauseMenu(DisplayType& type, GameState& state, UI& ui, Sounds& sounds);
	bool eventGameOver(DisplayType& type, UI& ui, Sounds& sounds);

	void updateAnimations(std::vector<Animation>& animations);
	void drawAnimations(const std::vector<Animation>& animations);
}