#include "../include/text.h"

Text::Text()
{
	string = "";
	pos = { 0.f, 0.f };
	fontSize = 0;
	color = WHITE;
}

Text::Text(std::string str, Vector2D position, int size, Color c)
{
	string = str;
	pos = position;
	fontSize = size;
	color = c;
}

void Text::init(std::string str, Vector2D position, int size, Color c)
{
	string = str;
	pos = position;
	fontSize = size;
	color = c;
}

void Text::draw() const
{
	if (string != "")
		DrawText(string.c_str(), (int)pos.x, (int)pos.y, fontSize, color);
}