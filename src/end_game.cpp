#include "../include/end_game.h"
#include "../include/game.h"

EndGame::EndGame()
{
	m_title = { "CONGRATULATION !!", { (float)SCREEN_WIDTH / 4.f - 10.f, (float)SCREEN_HEIGHT / 2.f - 120.f}, 40, WHITE };
	m_playerScore = { "", { (float)SCREEN_WIDTH / 3.f + 25.f, (float)SCREEN_HEIGHT / 2.f - 30.f }, 30, RED };

	m_commands.push_back({ "You complete the game", { (float)SCREEN_WIDTH / 3.f + 5.f, (float)SCREEN_HEIGHT / 2.f - 80.f }, 20, WHITE });
	m_commands.push_back({ "Press \"BackSpace\" :      Back To Menu", { (float)SCREEN_WIDTH / 4.f - 10.f, (float)SCREEN_HEIGHT / 2.f + 50.f }, 20, SKYBLUE });

	m_isTitle			= true;
	m_isPlayerScore		= true;
	m_isCommands		= true;
}