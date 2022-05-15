#include "../include/game_UI.h"
#include "../include/game.h"

GameUI::GameUI()
{
	m_title       = { "", { 0.f, 0.f }, 0, WHITE };
	m_playerScore = { "", { (float)SCREEN_WIDTH / 2.f - 50.f, 40.f }, 25, WHITE };

	m_commands.push_back({ "Pause : \"SPACE\"", { (float)SCREEN_WIDTH - 200.f, (float)SCREEN_HEIGHT - 30.f }, 20, YELLOW });
	m_commands.push_back({ "Debug : \"C\"", { 30.f, (float)SCREEN_HEIGHT - 30.f }, 20, YELLOW });

	m_isPlayerScore		= true;
	m_isCommands		= true;
}