#include "../include/level_select.h"
#include "../include/game.h"

LevelSelect::LevelSelect()
{
	m_title = { "LEVEL SELECT", { (float)SCREEN_WIDTH / 3.f - 30.f, (float)SCREEN_HEIGHT / 2.f - 120.f}, 40, WHITE };
	m_playerScore = { "", { (float)SCREEN_WIDTH / 2.f - 50.f, (float)SCREEN_HEIGHT / 2.f }, 40, RED };

	m_commands.push_back({ "Press \"F\" :      Easy", { (float)SCREEN_WIDTH / 4.f + 70.f, (float)SCREEN_HEIGHT / 2.f - 40.f}, 20, SKYBLUE });
	m_commands.push_back({ "(You regain you 3 lifes at the start of each round)", { (float)SCREEN_WIDTH / 4.f + 3.f, (float)SCREEN_HEIGHT / 2.f - 15.f }, 14, SKYBLUE });
	m_commands.push_back({ "Press \"G\" :      Normal", { (float)SCREEN_WIDTH / 4.f + 70.f, (float)SCREEN_HEIGHT / 2.f + 20.f }, 20, GREEN });
	m_commands.push_back({ "(You regain 1 life at the start of each round)", { (float)SCREEN_WIDTH / 4.f + 27.f, (float)SCREEN_HEIGHT / 2.f + 45.f }, 14, GREEN });
	m_commands.push_back({ "Press \"H\" :      Hard", { (float)SCREEN_WIDTH / 4.f + 70.f, (float)SCREEN_HEIGHT / 2.f + 80.f }, 20, RED });
	m_commands.push_back({ "(You only have 3 lifes. Good Luck !!)", { (float)SCREEN_WIDTH / 4.f + 57.f, (float)SCREEN_HEIGHT / 2.f + 105.f }, 14, RED });

	m_isTitle			= true;
	m_isPlayersControls = true;
	m_isCommands		= true;
}