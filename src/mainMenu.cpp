#include "../include/mainMenu.h"
#include "../include/game.h"

MainMenu::MainMenu(const Sound& sound)
{
	m_title = { "Start a new game", { (float)SCREEN_WIDTH / 4.f + 10.f, (float)SCREEN_HEIGHT / 2.f - 100.f}, 40, WHITE };
	m_playerScore = { "", { 0.f, 0.f }, 0, WHITE };
	m_musicScreenSelect = sound;

	m_commands.push_back({ "Press \"F\" :          Solo Mode", { (float)SCREEN_WIDTH / 4.f + 25.f, (float)SCREEN_HEIGHT / 2.f - 20.f}, 20, SKYBLUE });
	m_commands.push_back({ "Press \"K\" :          Two Players Mode", { (float)SCREEN_WIDTH / 4.f + 25.f, (float)SCREEN_HEIGHT / 2.f + 20.f }, 20, GREEN });
	m_commands.push_back({ "Press \"Esc\" :       Exit", { (float)SCREEN_WIDTH / 4.f + 25.f, (float)SCREEN_HEIGHT / 2.f + 60.f}, 20, RED });

	m_isTitle			= true;
	m_isPlayersControls = true;
	m_isCommands		= true;
	m_isTexture			= true;

	Rectangle src = { 0.f, 0.f, 2000.f, 500.f };
	Rectangle dest = { (float)SCREEN_WIDTH / 2.f, 200.f, 700.f, 200.f };
	Vector2 origin = { 350.f, 100.f };
	m_texturesStat.push_back({ 0.f, 0.f, src, dest, origin, WHITE });
}