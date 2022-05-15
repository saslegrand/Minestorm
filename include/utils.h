#pragma once
#include <raylib.h>
#include <vector>

#include "../toolbox/referantial2D.h"
#include "../toolbox/convexPolygon.h"
#include "../toolbox/maths.h"
#include "bullet.h"
#include "entity.h"

/*struct NbMines
{
	int floating = 0;
	int magnetic = 0;
	int fireball = 0;
	int magneticFireball = 0;
};*/

namespace utils
{
	void drawEntity(const Referantial2D& ref, const Texture2D& texture, const TextureStat& stats);
};

namespace screen
{
	void changeShapesPos(std::vector<ConvexPolygon>& shapes, float offsetX, float offsetY, float dir);
	void checkBorderEntity(Referantial2D& ref, std::vector<ConvexPolygon>& shapes, float padding);
	void checkBorderBulletsPlayer(std::vector<Bullet>& bullets);
	bool checkBorderBulletsMines(const Bullet& bullet);
};