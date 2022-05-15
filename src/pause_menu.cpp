#include "../include/pause_menu.h"
#include "../include/game.h"

PauseMenu::PauseMenu()
{
	m_title = { "PAUSE", { (float)SCREEN_WIDTH / 2 - 70.f, (float)SCREEN_HEIGHT / 2.f - 120.f}, 40, WHITE };
	m_playerScore = { "", { (float)SCREEN_WIDTH / 2.f - 50.f, 40.f }, 25, WHITE };

	m_commands.push_back({ "Press \"Space\" :            Resume", { (float)SCREEN_WIDTH / 4.f + 10.f, (float)SCREEN_HEIGHT / 2.f - 40}, 20, SKYBLUE });
	m_commands.push_back({ "Press \"BackSpace\" :      Back To Menu", { (float)SCREEN_WIDTH / 4.f + 10.f, (float)SCREEN_HEIGHT / 2.f }, 20, GREEN });
	m_commands.push_back({ "Press \"Esc\" :               Exit", { (float)SCREEN_WIDTH / 4.f + 10.f, (float)SCREEN_HEIGHT / 2.f + 40.f}, 20, RED });

	m_isTitle			= true;
	m_isPlayerScore		= true;
	m_isPlayersControls = true;
	m_isCommands		= true;
}