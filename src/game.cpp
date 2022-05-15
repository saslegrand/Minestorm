#include <iostream>
#include <string>

#include "../include/game.h"
#include "../toolbox/range.h"
#include "../toolbox/intersection2d.h"
#include "../include/utils.h"
#include "../include/floating_mine.h"
#include "../include/magnetic_fireball_mine.h"
#include "../include/game_UI.h"
#include "../include/level_select.h"
#include "../include/game_over.h"
#include "../include/pause_menu.h"
#include "../include/end_game.h"
#include "../include/collision.h"

// Constructor
Game::Game()
{
	m_ressources.loadTextures();
	m_sounds.load();

	// Init game at the main menu (difficulty set by the player)
	m_curType	 = DisplayType::MAIN_MENU;
	m_curState	 = GameState::INIT_ROUND;
	m_difficulty = Difficulty::EASY;
	m_curMenu	 = MainMenu(m_sounds.mainMenuSong);
	m_curMenu.setTexture(m_ressources.titleMainMenu);

	// Init ressources for motherShip
	m_spawnMotherShip.setTexture(m_ressources.entities);
	m_mineLayer.setTexture(m_ressources.entities);
	m_mineLayer.setSounds(&m_sounds);
	//m_players.push_back(Player(-1, m_ressources.entities, &m_sounds));
}

void Game::unloadSoundsTextures()
{
	m_sounds.stop();
	m_sounds.unload();
	m_ressources.unload();
}

// Get inputs event
void Game::handleEvent()
{
	if (m_curType == DisplayType::MAIN_MENU)
	{
		manage::eventMainMenu(m_curType, m_players, m_curMenu, m_ressources, m_sounds);
		return;
	}

	if (m_curType == DisplayType::LEVEL_SELECT)
	{
		manage::eventLevelSelect(m_curType, m_difficulty, m_curMenu, m_sounds.mainMenuSong);
		return;
	}

	if (m_curType == DisplayType::GAME || m_curType == DisplayType::TEST)
	{
		manage::eventGame(m_curType, m_curState, m_curMenu, m_sounds, m_isDebug);
		return;
	}

	if (m_curType == DisplayType::PAUSE_MENU)
	{
		if (manage::eventPauseMenu(m_curType, m_curState, m_curMenu, m_sounds))
		{
			resetGame();
			m_curMenu.setTexture(m_ressources.titleMainMenu);
		}
		return;
	}

	if (m_curType == DisplayType::GAME_OVER || m_curType == DisplayType::WIN_GAME)
	{
		if (manage::eventGameOver(m_curType, m_curMenu, m_sounds))
		{
			resetGame();
			m_curMenu.setTexture(m_ressources.titleMainMenu);
		}
		return;
	}
}

// Placing spawn-points on map
void Game::updateSpawnPoints()
{
	// update the spawnMotherShip and place spawnPoints on the map
	static bool isSoundPlay = false;
	bool isPointsPlaced = manage::updateSpawnPoints(m_spawnMotherShip, m_spawnPoints, m_deltaTime);

	if (!isSoundPlay)
	{
		PlaySound(m_sounds.spawnPoints);
		isSoundPlay = true;
	}

	if (isPointsPlaced && !IsSoundPlaying(m_sounds.spawnPoints))
	{
		isSoundPlay = false;
		m_timer.reset();
		m_curState = GameState::SPAWN_PLAYERS;
	}
}

// Spawn of player(s) and text for current round (on draw)
void Game::updateSpawnPlayers()
{
	m_timer.setDelay(3.f);
	m_timer.update();

	manage::updatePlayers(m_players, m_animations);
	manage::updateBullets(m_players, m_playersBullets, m_minesFireballs);

	if (m_timer.isDelayPassed)
	{
		m_timer.reset();

		// Set delay for mines spawn
		m_timer.setDelay((float)GetRandomValue(0, 1));

		// Start gameplay
		m_curState = GameState::GAMEPLAY;
	}
}

// Check all collisions
void Game::checkCollisions()
{
	int indexMine, indexPlayer;

	// Check collision with player(s)
	if (collision::isPlayerCollision(m_players, m_mines, m_playersBullets, m_minesFireballs, m_mineLayer, indexPlayer))
	{
		m_animations.push_back(PlayerExplosion(m_players[indexPlayer].getOrigin(), m_players[indexPlayer].getColor()));
		PlaySoundMulti(m_sounds.shipExplosion);

		// Check if all players are dead during the current round
		if (manage::isAllPlayersDead(m_players))
		{
			m_timer.reset();
			m_curState = GameState::PLAYER_DEATH;
			return;
		}
	}

	if (m_mineLayer.isAlive)
		collision::isBulletMineLayerCollision(m_playersBullets, m_mineLayer, m_scorePlayer, m_sounds, m_animations);

	// Check colliion with bullets
	if (collision::isBulletMineCollision(m_playersBullets, m_mines, m_animations, indexMine, indexPlayer))
	{
		m_animations.push_back(MineExplosion(m_mines[indexMine]->getOrigin()));

		PlaySoundMulti(m_sounds.mineExplosion);
		// Add the deathScore of the mine to the general score
		m_scorePlayer += m_mines[indexMine]->deathScore;

		// Add a bullet for fireball/magnetic_fireball mines
		manage::addPotentialBulletMine(m_mines[indexMine], m_players[indexPlayer], m_minesFireballs);

		// Divide the mine if BIG or MEDIUM. If motherShip has spawn, only destroy mines
		if (!m_isMineLayerSpawn)
			manage::addDestroyMine(m_mines, m_spawnPoints, m_ressources, &m_sounds, indexMine);
		else
			manage::destroyMine(m_mines, indexMine);
	}

	if (collision::isBulletFireballCollision(m_playersBullets, m_minesFireballs, m_animations, m_scorePlayer))
		PlaySoundMulti(m_sounds.mineExplosion);
}

// Update the gameplay
void Game::updateGameplay()
{
	// Update entities then check for collisions
	manage::updateEntities(m_players, m_mines, m_animations);
	manage::updateBullets(m_players, m_playersBullets, m_minesFireballs);

	// Initial Mine set at init_round or mines add by the mine_layer
	manage::updateWaitingMineSpawn(m_mines, m_spawnPoints, m_ressources, &m_sounds, m_timer, m_round, m_nbMines);

	// Update MineLayer if alive
	if (m_mineLayer.isAlive)
	{
		if (!IsSoundPlaying(m_sounds.mineLayerMove))
			PlaySound(m_sounds.mineLayerMove);

		manage::updateMineLayer(m_mineLayer, m_playersBullets, m_spawnPoints, m_round, m_nbMines);
	}

	checkCollisions();

	// Check for minelayer spawn or end of the round
	if (m_spawnPoints.size() == 0)
	{
		manage::setMineLayer(m_mineLayer, m_isMineLayerSpawn);

		if (m_mines.size() == 0 && m_isMineLayerSpawn && !m_mineLayer.isAlive)
		{
			m_timer.reset();
			m_curState = GameState::END_ROUND;
		}
	}
}

// Start a new round
void Game::startNewRound()
{
	// Clear all lists and reset values
	m_isMineLayerSpawn = false;
	m_isDebug = false;
	m_round += 1;

	// Set players lifes from difficulty
	manage::setPlayersLife(m_players, m_difficulty);
	m_spawnMotherShip.setOrigin({ (float)SCREEN_WIDTH / 2.f, 0.f });

	m_playersBullets.clear();
	m_minesFireballs.clear();

	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		m_players[i].resetPlayer();
	}

	// Restart the gameplay loop
	m_curState = GameState::INIT_ROUND;
}

// Round fail, restart the current round
void Game::restartCurrentRound()
{
	// Clear all lists and reset values
	m_isMineLayerSpawn = false;
	m_isDebug = false;

	m_spawnMotherShip.setOrigin({ (float)SCREEN_WIDTH / 2.f, 0.f });

	m_spawnPoints.clear();
	m_minesFireballs.clear();

	// delete mines
	for (int i = (int)(m_mines.size() - 1); i >= 0; i--)
	{
		delete m_mines[i];
		m_mines.pop_back();
	}

	m_playersBullets.clear();

	// reset players
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		m_players[i].resetPlayer();
	}

	m_curState = GameState::INIT_ROUND;
}

// Round finish, delay before new round
void Game::updateEndRound()
{
	// Delay of 3 seconds before a new round start
	manage::updatePlayers(m_players, m_animations);
	manage::updateBullets(m_players, m_playersBullets, m_minesFireballs);
	m_timer.setDelay(3.f);
	m_timer.update();

	if (m_timer.isDelayPassed)
	{
		if (m_round == 18)
		{
			m_curMenu = EndGame();
			m_curMenu.setPlayerScore(m_scorePlayer);
			m_curState = GameState::INIT_ROUND;
			m_curType = DisplayType::WIN_GAME;
		}
		startNewRound();
	}
}

// Check if game is finish or if the round restart
void Game::updatePlayerDeath()
{
	m_timer.setDelay(2.f);
	m_timer.update();

	manage::updateMines(m_mines);
	manage::updateBullets(m_players, m_playersBullets, m_minesFireballs);

	if (m_timer.isDelayPassed)
	{
		// Check if all players are out of lifes
		if (manage::isGameOver(m_players))
		{
			// Game Over screen
			m_curMenu = GameOver();
			m_curMenu.setPlayerScore(m_scorePlayer);
			m_curType = DisplayType::GAME_OVER;
		}
		else
			restartCurrentRound();
	}
}

// State machine for gameplay loop
void Game::updateGame()
{
	m_deltaTime = GetFrameTime();
	m_curMenu.setPlayerScore(m_scorePlayer);
	manage::updateAnimations(m_animations);

	switch (m_curState)
	{
	case GameState::INIT_ROUND:
		manage::initNewRound(m_spawnMotherShip, m_spawnPoints, m_curState, m_round, m_nbMines);
		break;
	case GameState::PLACE_SPAWNPOINTS:
		updateSpawnPoints();
		break;
	case GameState::SPAWN_PLAYERS:
		updateSpawnPlayers();
		break;
	case GameState::GAMEPLAY:
		updateGameplay();
		break;
	case GameState::END_ROUND:
		updateEndRound();
		break;
	case GameState::PLAYER_DEATH:
		updatePlayerDeath();
		break;
	default:
		break;
	}
}

// Test new additions
void Game::updateTest()
{
	/*static bool isStart = false;
	Vector2D origin1 = { (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEIGHT / 2.f };
	Vector2D origin2 = { (float)SCREEN_WIDTH / 4.f, (float)SCREEN_HEIGHT / 4.f };
	Vector2D origin3 = { (float)SCREEN_WIDTH - (float)SCREEN_WIDTH / 4.f, (float)SCREEN_HEIGHT - (float)SCREEN_HEIGHT / 4.f };

	if (!isStart)
	{
		m_mines.push_back(new MagneticFireballMine(1.f, MineSize::BIG, 100, origin1));
		m_mines.back()->setTexture(m_ressources.entities);
		m_mines.back()->setSounds(&m_sounds);
		m_mines.push_back(new MagneticFireballMine(1.f, MineSize::BIG, 100, origin2));
		m_mines.back()->setTexture(m_ressources.entities);
		m_mines.back()->setSounds(&m_sounds);
		m_mines.push_back(new MagneticFireballMine(1.f, MineSize::BIG, 100, origin3));
		m_mines.back()->setTexture(m_ressources.entities);
		m_mines.back()->setSounds(&m_sounds);
		isStart = true;
	}

	manage::updatePlayers(m_players, m_animations);
	manage::updateBullets(m_players, m_playersBullets, m_minesFireballs);
	
	for (unsigned int i = 0; i < m_animations.size(); i++)
	{
		m_animations[i].update();
	}

	int indexMine, indexPlayer;

	if (manage::isBulletMineCollision(m_playersBullets, m_mines, indexMine, indexPlayer))
	{
		m_animations.push_back(MineExplosion(m_mines[indexMine]->getOrigin()));
		manage::destroyMine(m_mines, indexMine);
	}

	m_mineLayer.setOrigin({ (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEIGHT / 2.f });
	m_mineLayer.initShapes();*/
}

void Game::drawTest() const
{
	manage::drawEntities(m_players, m_mines);
	manage::drawBullets(m_playersBullets, m_minesFireballs, m_ressources.entities);

	for (unsigned int i = 0; i < m_animations.size(); i++)
	{
		m_animations[i].draw();
	}

	if (m_isDebug)
		m_mineLayer.drawDebug();
}

// State machine for current display (menus, gameplay)
void Game::update()
{
	handleEvent();

	switch (m_curType)
	{
	case DisplayType::MAIN_MENU:
		if (!IsSoundPlaying(m_sounds.mainMenuSong))
			PlaySound(m_sounds.mainMenuSong);
		break;
	case DisplayType::LEVEL_SELECT:
		if (!IsSoundPlaying(m_sounds.mainMenuSong))
			PlaySound(m_sounds.mainMenuSong);
		break;
	case DisplayType::PAUSE_MENU:
		m_curMenu.setPlayerScore(m_scorePlayer);
		break;
	case DisplayType::GAME:
		updateGame();
		break;
	case DisplayType::GAME_OVER:
		break;
	case DisplayType::WIN_GAME:
		break;
	case DisplayType::TEST:
		updateTest();
		break;
	default:
		break;
	}
}

// Draw the background textures
void Game::drawBackTextures() const
{
	Rectangle srcRect = { 0.f, 0.f, 640, 800 };
	Rectangle destRect = { 0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };
	DrawTexturePro(m_ressources.background, srcRect, destRect, { 0.f, 0.f }, 0.f, WHITE);
}

// Draw entities debug
void Game::drawDebug() const
{
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		m_players[i].drawDebug();
	}

	for (unsigned int i = 0; i < m_mines.size(); i++)
	{
		m_mines[i]->drawDebug();
	}

	if (m_mineLayer.isAlive)
		m_mineLayer.drawDebug();
}

// Draw spawn, players and round text before launch gameplay
void Game::drawSpawnPlayer() const
{
	manage::drawSpawnPoints(m_spawnPoints, m_ressources.entities);
	manage::drawPlayers(m_players);
	manage::drawBullets(m_playersBullets, m_minesFireballs, m_ressources.entities);
	manage::drawAnimations(m_animations);

	// Text round start
	std::string roundText = "Round : " + std::to_string(m_round);
	DrawText(roundText.c_str(), SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 4, 40, RED);
	DrawText("Get Ready !!", SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 4 + 40, 40, RED);
}

// Draw all the gameplay
void Game::drawGameplay() const
{
	manage::drawSpawnPoints(m_spawnPoints, m_ressources.entities);
	manage::drawEntities(m_players, m_mines);
	manage::drawBullets(m_playersBullets, m_minesFireballs, m_ressources.entities);
	manage::drawAnimations(m_animations);

	if (m_mineLayer.isAlive)
	{
		m_mineLayer.draw();
	}

	if (m_isDebug)
		drawDebug();
}

// Draw players and text round before start a new round
void Game::drawEndRound() const
{
	manage::drawPlayers(m_players);
	manage::drawBullets(m_playersBullets, m_minesFireballs, m_ressources.entities);
	manage::drawAnimations(m_animations);

	std::string roundText = "Round : " + std::to_string(m_round) + " complete !!!";
	DrawText(roundText.c_str(), SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2, 40, RED);
}

// Draw gameplay before current round restart
void Game::drawPlayerDeath() const
{
	drawGameplay();
}

// State machine for draw gameplay loop
void Game::drawGame() const
{
	m_curMenu.drawPlayersLifes(m_players);
	m_curMenu.draw();

	switch (m_curState)
	{
	case GameState::INIT_ROUND:
		break;
	case GameState::PLACE_SPAWNPOINTS:
		manage::drawPlacingPoint(m_spawnMotherShip, m_spawnPoints, m_ressources.entities);
		break;
	case GameState::SPAWN_PLAYERS:
		drawSpawnPlayer();
		break;
	case GameState::GAMEPLAY:
		drawGameplay();
		break;
	case GameState::END_ROUND:
		drawEndRound();
		break;
	case GameState::PLAYER_DEATH:
		drawPlayerDeath();
		break;
	default:
		break;
	}
}

// Draw the current displayType (game, menus)
void Game::draw() const
{
	drawBackTextures();

	switch (m_curType)
	{
	case DisplayType::MAIN_MENU:
		m_curMenu.draw();
		break;
	case DisplayType::LEVEL_SELECT:
		m_curMenu.draw();
		break;
	case DisplayType::PAUSE_MENU:
		m_curMenu.drawPlayersLifes(m_players);
		m_curMenu.draw();
		break;
	case DisplayType::GAME:
		drawGame();
		break;
	case DisplayType::GAME_OVER:
		m_curMenu.draw();
		break;
	case DisplayType::WIN_GAME:
		m_curMenu.draw();
		break;
	case DisplayType::TEST:
		drawTest();
		break;
	default:
		break;
	}
}

// Reset the game (game over or return main menu by pause menu)
void Game::resetGame()
{
	m_spawnPoints.clear();
	m_minesFireballs.clear();

	for (int i = (int)(m_mines.size() - 1); i >= 0; i--)
	{
		delete m_mines[i];
		m_mines.pop_back();
	}

	m_playersBullets.clear();
	m_players.clear();
	m_spawnMotherShip.reset();

	m_round = 1;
	m_scorePlayer = 0;
	m_isMineLayerSpawn = false;

	m_curState = GameState::INIT_ROUND;
}

// Delete the game when closing
void Game::deleteGame()
{
	m_animations.clear();
	m_spawnPoints.clear();
	m_minesFireballs.clear();

	for (int i = (int)(m_mines.size() - 1); i >= 0; i--)
	{
		delete m_mines[i];
		m_mines.pop_back();
	}

	m_playersBullets.clear();
	m_players.clear();

	unloadSoundsTextures();
}