#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <string>

#include "../include/text.h"
#include "../include/ressources.h"
#include "../include/player.h"


class UI
{
public:
	UI();
	~UI();

	void		setPlayerScore(int score);
	inline void setTexture(Texture2D& texture) { m_textures.push_back(texture); }

	void draw() const;
	void drawTextures() const;
	void drawPlayerScore() const;
	void drawPlayersControls() const;
	void drawPlayersLifes(const std::vector<Player>& players) const;
	void drawTitle() const;
	void drawCommands() const;

protected:
	std::vector<Texture2D>   m_textures;
	std::vector<TextureStat> m_texturesStat;
	std::array<Text, 4>      m_playersControls;
	Text				     m_playerScore;
	Text				     m_title;
	std::vector<Text>        m_commands;

	bool m_isPlayerScore     = false;
	bool m_isPlayersControls = false;
	bool m_isTitle           = false;
	bool m_isCommands        = false;
	bool m_isTexture		 = false;
	//DisplayType            m_type;
};