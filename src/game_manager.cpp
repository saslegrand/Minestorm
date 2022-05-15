#include <raylib.h>

#include "../include/game_manager.h"
#include "../toolbox/range.h"
#include "../toolbox/maths.h"
#include "../include/floating_mine.h"
#include "../include/magnetic_mine.h"
#include "../include/fireball_mine.h"
#include "../include/magnetic_fireball_mine.h"
#include "../include/game.h"
#include "../include/game_UI.h"
#include "../include/level_select.h"
#include "../include/pause_menu.h"
#include "../include/utils.h"
#include "../toolbox/intersection2d.h"

int minesCountRound[18][4] = {
		{ 4, 0, 0, 0 },
		{ 3, 0, 1, 0 },
		{ 3, 1, 0, 0 },
		{ 3, 0, 0, 1 },
		{ 2, 1, 1, 0 },
		{ 2, 0, 1, 1 },
		{ 2, 1, 0, 1 },
		{ 3, 0, 2, 0 },
		{ 3, 2, 0, 0 },
		{ 3, 0, 0, 2 },
		{ 2, 0, 3, 0 },
		{ 2, 3, 0, 0 },
		{ 2, 0, 0, 3 },
		{ 1, 2, 1, 1 },
		{ 3, 0, 3, 0 },
		{ 2, 3, 1, 0 },
		{ 2, 0, 1, 3 },
		{ 1, 2, 1, 3 },
};

void addFloatingMine(std::vector<Mine*>& mines, Vector2D origin, const Ressources& ressources, Sounds* sounds, int index, bool isMineLayerSpawn)
{
	MineSize size = MineSize::BIG;
	int		 score = 100;
	float    scale = 2.f;

	// Mines set by the mother ship (dont divide)
	if (!isMineLayerSpawn)
	{
		size = mines[index]->m_size == MineSize::BIG ? MineSize::MEDIUM : MineSize::SMALL;
		score += size == MineSize::MEDIUM ? 35 : 100;
		scale = mines[index]->scale;
	}

	mines.push_back(new FloatingMine(scale * 0.5f, size, score, origin));
	mines.back()->setSounds(sounds);
	mines.back()->setTexture(ressources.entities);
}

void addMagneticMine(std::vector<Mine*>& mines, Vector2D origin, const Ressources& ressources, Sounds* sounds, int index, bool isMineLayerSpawn)
{
	MineSize size = MineSize::BIG;
	int		 score = 500;
	float    scale = 2.f;

	// Mines set by the mother ship (dont divide)
	if (!isMineLayerSpawn)
	{
		size = mines[index]->m_size == MineSize::BIG ? MineSize::MEDIUM : MineSize::SMALL;
		score += size == MineSize::MEDIUM ? 35 : 100;
		scale = mines[index]->scale;
	}

	mines.push_back(new MagneticMine(scale * 0.5f, size, score, origin));
	mines.back()->setSounds(sounds);
	mines.back()->setTexture(ressources.entities);
}

void addFireballMine(std::vector<Mine*>& mines, Vector2D origin, const Ressources& ressources, Sounds* sounds, int index, bool isMineLayerSpawn)
{
	MineSize size = MineSize::BIG;
	int		 score = 325;
	float    scale = 2.f;

	// Mines set by the mother ship (dont divide)
	if (!isMineLayerSpawn)
	{
		size = mines[index]->m_size == MineSize::BIG ? MineSize::MEDIUM : MineSize::SMALL;
		score += size == MineSize::MEDIUM ? 35 : 100;
		scale = mines[index]->scale;
	}

	mines.push_back(new FireballMine(scale * 0.5f, size, score, origin));
	mines.back()->setSounds(sounds);
	mines.back()->setTexture(ressources.entities);
}

void addMagneticFireballMine(std::vector<Mine*>& mines, Vector2D origin, const Ressources& ressources, Sounds* sounds, int index, bool isMineLayerSpawn)
{
	MineSize size = MineSize::BIG;
	int		 score = 750;
	float    scale = 2.f;

	// Mines set by the mother ship (dont divide)
	if (!isMineLayerSpawn)
	{
		size = mines[index]->m_size == MineSize::BIG ? MineSize::MEDIUM : MineSize::SMALL;
		score += size == MineSize::MEDIUM ? 35 : 100;
		scale = mines[index]->scale;
	}

	mines.push_back(new MagneticFireballMine(scale * 0.5f, size, score, origin));
	mines.back()->setSounds(sounds);
	mines.back()->setTexture(ressources.entities);
}

// Set random spawnpoints on map
void initSpawnPoints(SpawnMotherShip& motherShip, std::vector<Vector2D>& spawnPoints, int nbPoints)
{
	for (int i = 0; i < nbPoints; i++)
	{
		Range X = { xMinRand, xMaxRand };
		Range Y = { yMinRand, yMaxRand };

		motherShip.spawns.push_back({ manage::randRangeValue(X), manage::randRangeValue(Y) });
		motherShip.isSpawn.push_back(false);
		spawnPoints.push_back({ (float)SCREEN_WIDTH / 2.f, 0.f });
	}
}

// Get the target for magnetic and magnetic-fireball mines
Vector2D getTarget(std::vector<Player>& players, Mine* mine)
{
	Vector2D target = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };
	int index = 0;

	for (unsigned int i = 1; i < players.size(); i++)
	{
		if ((players[i].getLocalRef().origin - mine->getLocalRef().origin).squareLength() < target.squareLength() && players[i].isAlive)
			index = i;
	}

	return players[index].getLocalRef().origin;
}

// Add a minde on the map
void addMineOnMap(std::vector<Mine*>& mines, Vector2D origin, const Ressources& ressources, Sounds* sounds, int index)
{
	switch (index)
	{
	case 0:
		addFloatingMine(mines, origin, ressources, sounds, 0, true);
		break;
	case 1:
		addMagneticMine(mines, origin, ressources, sounds, 0, true);
		break;
	case 2:
		addFireballMine(mines, origin, ressources, sounds, 0, true);
		break;
	case 3:
		addMagneticFireballMine(mines, origin, ressources, sounds, 0, true);
		break;
	default:
		break;
	}
}

// Give a random value from a range
float manage::randRangeValue(const Range& range)
{
	return (float)GetRandomValue((int)range.min, (int)range.max);
}

// Draw the spawnpoints
void manage::drawSpawnPoints(const std::vector<Vector2D>& spawnPoints, const Texture2D& texture)
{
	for (unsigned int i = 0; i < spawnPoints.size(); i++)
	{
		Rectangle src = { 256.f, 0.f, 256.f, 256.f };
		Rectangle dest = { spawnPoints[i].x, spawnPoints[i].y, 40.f, 40.f };
		Vector2 origin = { 20.f, 20.f };
		DrawTexturePro(texture, src, dest, origin, 0.f, YELLOW);
	}
}

// Destroy a mine
void manage::destroyMine(std::vector<Mine*>& mines, int index)
{
	delete mines[index];
	mines[index] = mines.back();
	mines.pop_back();
}

// If the mine is BIG or MEDIUM, divide the mine. Else just destroy the mine
void manage::addDestroyMine(std::vector<Mine*>& mines, std::vector<Vector2D>& spawnPoints, const Ressources& ressources, Sounds* sounds, int index)
{
	if (mines[index]->scale >= 0.5f)
	{
		switch (mines[index]->m_type)
		{
		case MineType::FLOATING:
			addFloatingMine(mines, spawnPoints.back(), ressources, sounds, index, false);
			spawnPoints.pop_back();
			addFloatingMine(mines, spawnPoints.back(), ressources, sounds, index, false);
			PlaySoundMulti(sounds->mineAppear);
			break;
		case MineType::MAGNETIC:
			addMagneticMine(mines, spawnPoints.back(), ressources, sounds, index, false);
			spawnPoints.pop_back();
			addMagneticMine(mines, spawnPoints.back(), ressources, sounds, index, false);
			PlaySoundMulti(sounds->mineAppear);
			break;
		case MineType::FIREBALL:
			addFireballMine(mines, spawnPoints.back(), ressources, sounds, index, false);
			spawnPoints.pop_back();
			addFireballMine(mines, spawnPoints.back(), ressources, sounds, index, false);
			PlaySoundMulti(sounds->mineAppear);
			break;
		case MineType::MAGNETIC_FIREBALL:
			addMagneticFireballMine(mines, spawnPoints.back(), ressources, sounds, index, false);
			spawnPoints.pop_back();
			addMagneticFireballMine(mines, spawnPoints.back(), ressources, sounds, index, false);
			PlaySoundMulti(sounds->mineAppear);
			break;
		default:
			break;
		}
		spawnPoints.pop_back();
	}

	destroyMine(mines, index);
}

// Init a new round
void manage::initNewRound(SpawnMotherShip& motherShip, std::vector<Vector2D>& spawnPoints, GameState& curState, int round, int(&nbMines)[4])
{
	// Set the nulber of mines in function of the round
	nbMines[0] = minesCountRound[round - 1][0];
	nbMines[1] = minesCountRound[round - 1][1];
	nbMines[2] = minesCountRound[round - 1][2];
	nbMines[3] = minesCountRound[round - 1][3];

	int mines  = nbMines[0] + nbMines[1] + nbMines[2] + nbMines[3];

	std::cout << "Floating : " << nbMines[0] << " , ";
	std::cout << "Magnetic : " << nbMines[1] << " , ";
	std::cout << "Fireball : " << nbMines[2] << " , ";
	std::cout << "MagFire : " << nbMines[3] << " , " << std::endl;

	motherShip.spawns.clear();
	motherShip.isSpawn.clear();
	spawnPoints.clear();

	// Create the spawnPoints
	initSpawnPoints(motherShip, spawnPoints, mines * 7);

	curState = GameState::PLACE_SPAWNPOINTS;
}

// Placing spawnPoints at the start of each round
bool manage::updateSpawnPoints(SpawnMotherShip& motherShip, std::vector<Vector2D>& spawnPoints, float deltaTime)
{
	bool isPointPlace = true;
	motherShip.update();

	for (unsigned int i = 0; i < motherShip.spawns.size(); i++)
	{
		if (!motherShip.isSpawn[i])
		{
			if (spawnPoints[i].y < motherShip.spawns[i].y)
			{
				isPointPlace = false;
				spawnPoints[i] = motherShip.getLocalRef().origin;
			}
			else
			{
				Vector2D destination = motherShip.spawns[i] - spawnPoints[i];
				if (destination.length() > 3.f)
				{
					spawnPoints[i] += destination.normalized() * 130.f * deltaTime;
					isPointPlace = false;
				}
				else
				{
					motherShip.isSpawn[i] = true;
				}
			}
		}
	}

	return isPointPlace;
}

// Draw spawnPoints and mother ship at the start of each rounds
void manage::drawPlacingPoint(const SpawnMotherShip& motherShip, const std::vector<Vector2D>& spawnPoints, const Texture2D& texture)
{
	manage::drawSpawnPoints(spawnPoints, texture);
	motherShip.draw();
}

// Draw the players
void manage::drawPlayers(const std::vector<Player>& players)
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i].isAlive && !players[i].isTeleport)
			players[i].draw();
	}
}

// Add a fireball to the fireballs list
void manage::addFireBall(Vector2D origin, Vector2D dir, std::vector<Bullet>& bullets)
{
	Bullet b = { origin, dir, BulletType::FIREBALL, RED };
	b.setSpeed(200.f);
	b.setRadius(5.f);
	bullets.push_back(b);
}

// Add a bullet to the bullets list
void manage::addBullet(Vector2D origin, Vector2D dir, std::vector<Bullet>& bullets, BulletType type, Color color)
{
	Bullet b = { origin, dir, type, color };
	bullets.push_back(b);
}

// Update players
void manage::updatePlayers(std::vector<Player>& players, std::vector<Animation>& animations)
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i].isAlive)
			players[i].update();
		if (players[i].isTeleport)
			animations.push_back(PlayerTeleportation(players[i].getOrigin(), players[i].getColor()));
	}
}

// Update bullets
void manage::updateBullets(std::vector<Player>& players, std::vector<Bullet>& bulletsPlayer, std::vector<Bullet>& bulletsMine)
{
	// Check if player shoot to add a bullet
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i].isShooting && players[i].isAlive)
		{
			players[i].isShooting = false;
			BulletType b_type = i == 0 ? BulletType::PLAYER_1 : BulletType::PLAYER_2;

			manage::addBullet(players[i].getOrigin(), players[i].getLocalRef().unitJ, bulletsPlayer, b_type, players[i].getColor());
		}
	}

	for (unsigned int i = 0; i < bulletsPlayer.size(); i++)
	{
		bulletsPlayer[i].update();

		if (!bulletsPlayer[i].isAlive)
		{
			bulletsPlayer[i] = bulletsPlayer.back();
			bulletsPlayer.pop_back();
		}
	}

	for (unsigned int i = 0; i < bulletsMine.size(); i++)
	{
		bulletsMine[i].update();

		if (screen::checkBorderBulletsMines(bulletsMine[i]))
		{
			bulletsMine[i] = bulletsMine.back();
			bulletsMine.pop_back();
		}
	}

	// Check if bullets are out of the screen to replace them
	screen::checkBorderBulletsPlayer(bulletsPlayer);
}

// Draw bullets and fireballs
void manage::drawBullets(const std::vector<Bullet>& bulletsPlayer, const std::vector<Bullet>& bulletsMine, const Texture2D& texture)
{
	for (unsigned int i = 0; i < bulletsPlayer.size(); i++)
	{
		bulletsPlayer[i].drawBullet();
	}

	for (unsigned int i = 0; i < bulletsMine.size(); i++)
	{
		bulletsMine[i].drawFireball(texture);
	}
}

// Update mines
void manage::updateMines(std::vector<Mine*>& mines)
{
	for (unsigned int i = 0; i < mines.size(); i++)
	{
		mines[i]->update();
	}
}

// Draw mines
void manage::drawMines(const std::vector<Mine*>& mines)
{
	for (unsigned int i = 0; i < mines.size(); i++)
	{
		mines[i]->draw();
	}
}

// Update entities (mines and players)
void manage::updateEntities(std::vector<Player>& players, std::vector<Mine*>& mines, std::vector<Animation>& animations)
{
	manage::updatePlayers(players, animations);

	for (unsigned int i = 0; i < mines.size(); i++)
	{
		if (mines[i]->m_type == MineType::MAGNETIC)
			((MagneticMine*)mines[i])->setTarget(getTarget(players, mines[i]));

		if (mines[i]->m_type == MineType::MAGNETIC_FIREBALL)
			((MagneticFireballMine*)mines[i])->setTarget(getTarget(players, mines[i]));

		mines[i]->update();
	}
}

// Draw entities (players and mines)
void manage::drawEntities(const std::vector<Player>& players, const std::vector<Mine*>& mines)
{
	manage::drawPlayers(players);
	manage::drawMines(mines);
}

// Update the mineLayer
void manage::updateMineLayer(MineLayer& mineLayer, std::vector<Bullet>& playerBullets, std::vector<Vector2D>& spawnPoints, int& round, int(&nbMines)[4])
{
	mineLayer.update();

	// If the mineLayer reach his target, set a new target
	if (mineLayer.getLocalRef().origin.compareValue(mineLayer.target, 3.F))
	{
		spawnPoints.push_back(mineLayer.target);
		mineLayer.updateTarget();

		// Add a mine from the mines that spawn at the beginning (example, can't add a magnetic if not spawn at the start of the round)
		int index = GetRandomValue(0, 3);
		while (minesCountRound[round - 1][index] == 0)
		{
			index++;
			index = index % 4;
		}
		nbMines[index] += 1;
	}
}

// Add a fireball if a fireball or a magnetic-fireball mine is destroy
void manage::addPotentialBulletMine(Mine* mine, Player& player, std::vector<Bullet>& mineBullets)
{
	if (mine->m_type == MineType::FIREBALL || mine->m_type == MineType::MAGNETIC_FIREBALL)
	{
		Vector2D dir = (player.getOrigin() - mine->getOrigin()).normalized();
		manage::addFireBall(mine->getOrigin(), dir, mineBullets);
	}
}

// Check if a mine waiting to spawn and add after delay
void manage::updateWaitingMineSpawn(std::vector<Mine*>& mines, std::vector<Vector2D>& spawnPoints, const Ressources& ressources, Sounds* sounds, Timer& timer, int round, int(&nbMines)[4])
{
	if (nbMines[0] != 0 || nbMines[1] != 0 || nbMines[2] != 0 || nbMines[3] != 0)
	{
		timer.update();

		if (timer.isDelayPassed)
		{
			timer.isDelayPassed = false;
			timer.setDelay((float)GetRandomValue(1, 2));

			// Add a random mine set a the initRound
			int index = GetRandomValue(0, 3);

			while (nbMines[index] == 0)
			{
				index++;
				index = index % 4;
			}

			// Add mine
			addMineOnMap(mines, spawnPoints.back(), ressources, sounds, index);
			spawnPoints.pop_back();

			PlaySoundMulti(sounds->mineAppear);

			if (nbMines[index] != 0)
				nbMines[index] -= 1;
		}
	}
}

// Set random spawn for minelayer (only out of the screen)
void manage::setMineLayerSpawn(MineLayer& minelayer)
{
	Vector2D origin;
	int	 randSide0 = GetRandomValue(1, 4);
	int	 randSide1 = GetRandomValue(1, 4);

	if (randSide0 >= 2)
	{
		if (randSide1 >= 2)
			origin = { -(float)MINE_WIDTH, (float)GetRandomValue(0, SCREEN_HEIGHT) };
		else
			origin = { (float)SCREEN_WIDTH + (float)MINE_WIDTH, (float)GetRandomValue(0, SCREEN_HEIGHT) };
	}
	else
	{
		if (randSide1 >= 2)
			origin = { (float)GetRandomValue(0, SCREEN_WIDTH), -(float)MINE_HEIGHT / 2.f };
		else
			origin = { (float)GetRandomValue(0, SCREEN_WIDTH), (float)SCREEN_HEIGHT + (float)MINE_HEIGHT / 2.f };
	}

	minelayer.setOrigin(origin);
	minelayer.initShapes();
}

// Init the mineLayer when spawn
void manage::setMineLayer(MineLayer& minelayer, bool& mineLayerSpawn)
{
	if (!mineLayerSpawn)
	{
		manage::setMineLayerSpawn(minelayer);
		minelayer.updateTarget();

		minelayer.isAlive = true;
		mineLayerSpawn = true;
	}
}

// Update players lifes at the end of each round from the difficulty choosen
void manage::setPlayersLife(std::vector<Player>& players, Difficulty difficulty)
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (difficulty == Difficulty::EASY)
			players[i].life = 3;
		if (difficulty == Difficulty::NORMAL && players[i].life < 3)
			players[i].life += 1;
	}
}

// Check if all players are dead durieng the current round
bool manage::isAllPlayersDead(std::vector<Player>& players)
{
	int  nbDeath = 0;

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (!players[i].isAlive)
			nbDeath += 1;
	}

	return (nbDeath == players.size());
}

// Check if all players are out of life
bool manage::isGameOver(std::vector<Player>& players)
{
	int nbLifes = 0;

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (!players[i].life == 0)
			nbLifes += 1;
	}

	return (nbLifes == 0);
}

// Update animations
void manage::updateAnimations(std::vector<Animation>& animations)
{
	for (unsigned int i = 0; i < animations.size(); i++)
	{
		animations[i].update();
	}
}

// Draw animations
void manage::drawAnimations(const std::vector<Animation>& animations)
{
	for (unsigned int i = 0; i < animations.size(); i++)
	{
		animations[i].draw();
	}
}

///////////////////////////////////////////////  HANDLE EVENTS ////////////////////////////////////////////////////////
void manage::eventMainMenu(DisplayType& type, std::vector<Player>& players, UI& ui, Ressources& ressources, Sounds& sounds)
{
	if (IsKeyPressed(KEY_F))
	{
		players.push_back(Player(0, ressources.entities, &sounds));
		type = DisplayType::LEVEL_SELECT;
		ui = LevelSelect();
	}

	if (IsKeyPressed(KEY_K))
	{
		players.push_back(Player(1, ressources.entities, &sounds));
		players.push_back(Player(-1, ressources.entities, &sounds));
		type = DisplayType::LEVEL_SELECT;
		ui = LevelSelect();
	}
}

void manage::eventLevelSelect(DisplayType& type, Difficulty& difficulty, UI& ui, Sound& mainMusic)
{
	if (IsKeyPressed(KEY_F))
	{
		type = DisplayType::GAME;
		difficulty = Difficulty::EASY;
		ui = GameUI();
		StopSound(mainMusic);
	}

	if (IsKeyPressed(KEY_G))
	{
		type = DisplayType::GAME;
		difficulty = Difficulty::NORMAL;
		ui = GameUI();
		StopSound(mainMusic);
	}

	if (IsKeyPressed(KEY_H))
	{
		type = DisplayType::GAME;
		difficulty = Difficulty::HARD;
		ui = GameUI();
		StopSound(mainMusic);
	}
}

void manage::eventGame(DisplayType& type,GameState& state, UI& ui, Sounds& sounds, bool& isDebug)
{
	if (IsKeyPressed(KEY_C))
		isDebug = !isDebug;

	if (IsKeyPressed(KEY_SPACE))
	{
		if (state == GameState::PLACE_SPAWNPOINTS)
			PauseSound(sounds.spawnPoints);

		type = DisplayType::PAUSE_MENU;
		ui = PauseMenu();
	}
}

bool manage::eventPauseMenu(DisplayType& type, GameState& state, UI& ui, Sounds& sounds)
{
	if (IsKeyPressed(KEY_SPACE))
	{
		if (state == GameState::PLACE_SPAWNPOINTS)
			ResumeSound(sounds.spawnPoints);

		type = DisplayType::GAME;
		ui = GameUI();
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		type = DisplayType::MAIN_MENU;
		ui = MainMenu(sounds.mainMenuSong);
		return true;
	}

	return false;
}

bool manage::eventGameOver(DisplayType& type, UI& ui, Sounds& sounds)
{
	if (IsKeyPressed(KEY_BACKSPACE))
	{
		type = DisplayType::MAIN_MENU;
		ui = MainMenu(sounds.mainMenuSong);
		return true;
	}

	return false;
}