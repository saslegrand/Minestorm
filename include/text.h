#pragma once

#include <raylib.h>
#include <string>
#include <iostream>

#include "..\toolbox\vector2d.h"

class Text
{
public:
	Text();
	Text(std::string str, Vector2D position, int size, Color c);
	~Text(){}
	
	void setText(std::string str) { string = str; }
	void init(std::string str, Vector2D position, int size, Color c);
	void draw() const;
	
private:
	std::string string;
	Vector2D	pos;
	int			fontSize;
	Color		color;
};