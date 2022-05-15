#include "../include/game_over.h"
#include "../include/game.h"

GameOver::GameOver()
{
	m_title = { "GAME OVER", { (float)SCREEN_WIDTH / 3.f, (float)SCREEN_HEIGHT / 2.f - 120.f}, 40, WHITE };
	m_playerScore = { "", { (float)SCREEN_WIDTH / 3.f + 25.f, (float)SCREEN_HEIGHT / 2.f - 70.f }, 30, RED };

	m_commands.push_back({ "Press \"BackSpace\" :      Back To Menu", { (float)SCREEN_WIDTH / 4.f - 10.f, (float)SCREEN_HEIGHT / 2.f + 40.f }, 20, SKYBLUE });

	m_isTitle			= true;
	m_isPlayerScore		= true;
	m_isPlayersControls = true;
	m_isCommands		= true;
}