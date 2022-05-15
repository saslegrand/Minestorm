#pragma once

#include "../include/UI.h"
#include "../include/sounds.h"

class MainMenu : public UI
{
public:
	MainMenu(const Sound& sound);
	~MainMenu() {}

private:
	Sound m_musicScreenSelect;
};