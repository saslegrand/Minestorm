#include "../include/UI.h"
#include "../include/game.h"

UI::UI()
{
	m_playersControls[0] = { "PLAYER ONE",
							 {80.f, (float)SCREEN_HEIGHT - 150.f}, 15, SKYBLUE };
	m_playersControls[1] = { "PLAYER TWO",
							 {560.f, (float)SCREEN_HEIGHT - 150.f}, 15, GREEN };
	m_playersControls[2] = { "Rotate : \"D\" and \"G\"\nMove : \"R\"\nShoot : \"F\"\nTeleport : \"E\" or \"T\"", 
							 {60.f, (float)SCREEN_HEIGHT - 120.f}, 15, WHITE };
	m_playersControls[3] = { "Rotate : \"J\" and \"L\"\nMove : \"I\"\nShoot : \"K\"\nTeleport : \"U\" or \"O\"", 
							 {540.f, (float)SCREEN_HEIGHT - 120.f}, 15, WHITE };
}

UI::~UI()
{
	m_commands.clear();
	m_texturesStat.clear();
	m_textures.clear();
}

void UI::draw() const
{
	if (m_isTexture)
		drawTextures();

	if (m_isPlayerScore)
		drawPlayerScore();

	if (m_isPlayersControls)
		drawPlayersControls();

	if (m_isTitle)
		drawTitle();

	if (m_isCommands)
		drawCommands();
}

void UI::drawTextures() const
{
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		DrawTexturePro(m_textures[i], m_texturesStat[i].src, m_texturesStat[i].dest, m_texturesStat[i].origin, 0.f, WHITE);
	}
}

void UI::setPlayerScore(int score)
{
	m_playerScore.setText("Score : " + std::to_string(score));
}

void UI::drawPlayersControls() const
{
	for (int i = 0; i < m_playersControls.size(); i++)
	{
		m_playersControls[i].draw();
	}
}

void UI::drawPlayerScore() const
{
	m_playerScore.draw();
}

void UI::drawTitle() const
{
	m_title.draw();
}

void UI::drawPlayersLifes(const std::vector<Player>& players) const
{
	float offsetTexture = 50.f;
	float offsetPlayers = (float)SCREEN_WIDTH / 2.f + 170.f;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		for (int j = 0; j < players[i].life; j++)
		{
			Rectangle dest = { 50.f + offsetTexture * j + offsetPlayers * i, 50.f, 64.f, 64.f };
			Vector2 origin = { 32.f, 32.f };
			DrawTexturePro(players[i].getTexture(), players[i].getSrcTexture(), dest, origin, 0.f, WHITE);
		}
	}
}

void UI::drawCommands() const
{
	for (int i = 0; i < m_commands.size(); i++)
	{
		m_commands[i].draw();
	}
}