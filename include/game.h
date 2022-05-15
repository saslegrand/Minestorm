#pragma once
#include <array>

#include "game_manager.h"

#define SCREEN_WIDTH   750
#define SCREEN_HEIGHT  950
#define SCREEN_PADDING 30

#define PLAYER_WIDTH   48	
#define PLAYER_HEIGHT  48

#define MINE_WIDTH     128
#define MINE_HEIGHT    128

const float xMinRand = (float)SCREEN_PADDING;
const float xMaxRand = (float)SCREEN_WIDTH - (float)SCREEN_PADDING;

const float yMinRand = (float)SCREEN_PADDING;
const float yMaxRand = (float)SCREEN_HEIGHT - (float)SCREEN_PADDING;

enum class DisplayType
{
	MAIN_MENU,
	GAME,
	PAUSE_MENU,
	GAME_OVER,
	LEVEL_SELECT,
	WIN_GAME,
	TEST
};

class Game
{
public:
	Game();
	~Game() {}

	/// MAIN FUNCTIONS ____
	void draw() const;
	void drawDebug() const;
	void update();
	void handleEvent();
	/// ___________________

	/// OTHERS ___________________
	void updateTest();
	void drawTest() const;
	void drawBackTextures() const;
	/// __________________________

	/// FUNCTIONS GAMEPLAY LOOP
	void updateGame();
	void drawGame() const;

	void updatePlayerDeath();
	void updateSpawnPoints();
	void updateSpawnPlayers();
	void updateGameplay();
	void updateEndRound();

	void drawPlayerDeath() const;
	void drawSpawnPlayer() const;
	void drawGameplay()    const;
	void drawEndRound()    const;

	void checkCollisions();
	void startNewRound();
	void restartCurrentRound();
	/// ________________________

	/// RESET/DELETE GAME ______
	void unloadSoundsTextures();
	void deleteGame();
	void resetGame();
	/// ________________________
	

private:
	/// UTILS VARIABLES _____________
	int    m_scorePlayer	  = 0;
	int    m_round			  = 1;
	int    m_nbMines[4]		  = {};
	bool   m_isDebug		  = false;
	bool   m_isRoundStart	  = false;
	bool   m_isMineLayerSpawn = false;
	float  m_deltaTime	      = 0.f;
	Timer  m_timer;
	/// _____________________________
	
	/// RESSOURCES / SOUNDS _
	Ressources	m_ressources;
	Sounds		m_sounds;
	/// _____________________
	
	/// UI / ENUM ___________
	UI          m_curMenu;
	DisplayType	m_curType;
	GameState   m_curState;
	Difficulty  m_difficulty;
	/// _____________________

	/// ENTITIES _________________
	SpawnMotherShip       
			    m_spawnMotherShip;
	MineLayer	m_mineLayer;

	std::vector<Player>	  
				m_players;
	std::vector<Bullet>	  
				m_playersBullets;

	std::vector<Mine*>	  
				m_mines;
	std::vector<Bullet>	  
				m_minesFireballs;
	std::vector<Vector2D> 
				m_spawnPoints;
	/// __________________________
	
	std::vector<Animation> 
				m_animations;
};
