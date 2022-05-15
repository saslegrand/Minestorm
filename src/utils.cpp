#include "../include/utils.h"
#include "../include/game.h"

const float offsetX = (float)SCREEN_WIDTH + (float)SCREEN_PADDING * 2.f;
const float offsetY = (float)SCREEN_HEIGHT + (float)SCREEN_PADDING * 2.f;

void utils::drawEntity(const Referantial2D& ref, const Texture2D& texture, const TextureStat& stats)
{
	Rectangle rectDest = { ref.origin.x, ref.origin.y, stats.width, stats.height };
	Vector2 origin = { stats.width / 2.f, stats.height / 2.f };

	DrawTexturePro(texture, stats.src, rectDest, origin, ref.angle * 360 / maths::TAU, WHITE);
}

void screen::changeShapesPos(std::vector<ConvexPolygon>& shapes, float offsetX, float offsetY, float dir)
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		for (unsigned int j = 0; j < shapes[i].pointsList.size(); j++)
		{
			if (offsetX != 0.f)
				shapes[i].pointsList[j].x += offsetX * dir;
			if (offsetY != 0.f)
				shapes[i].pointsList[j].y += offsetY * dir;
		}
	}
}

void screen::checkBorderEntity(Referantial2D& ref, std::vector<ConvexPolygon>& shapes, float padding)
{
	if (ref.origin.x > (float)SCREEN_WIDTH + padding)
	{
		ref.origin.x -= offsetX;
		screen::changeShapesPos(shapes, offsetX, 0.f, -1.f);
	}

	if (ref.origin.x < 0.f - padding)
	{
		ref.origin.x += offsetX;
		screen::changeShapesPos(shapes, offsetX, 0.f, 1.f);
	}

	if (ref.origin.y > (float)SCREEN_HEIGHT + padding)
	{
		ref.origin.y -= offsetY;
		screen::changeShapesPos(shapes, 0.f, offsetY, -1.f);
	}

	if (ref.origin.y < 0.f - padding)
	{
		ref.origin.y += offsetY;
		screen::changeShapesPos(shapes, 0.f, offsetY, 1.f);
	}
}

void screen::checkBorderBulletsPlayer(std::vector<Bullet>& bullets)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].circle.center.x > (float)SCREEN_WIDTH + (float)SCREEN_PADDING)
		{
			bullets[i].circle.center.x -= offsetX;
		}

		if (bullets[i].circle.center.x < 0.f - SCREEN_PADDING)
		{
			bullets[i].circle.center.x += offsetX;
		}

		if (bullets[i].circle.center.y > (float)SCREEN_HEIGHT + (float)SCREEN_PADDING)
		{
			bullets[i].circle.center.y -= offsetY;
		}

		if (bullets[i].circle.center.y < 0.f - SCREEN_PADDING)
		{
			bullets[i].circle.center.y += offsetY;
		}
	}
}

bool screen::checkBorderBulletsMines(const Bullet& bullet)
{
	if ((bullet.circle.center.x > (float)SCREEN_WIDTH + (float)SCREEN_PADDING) ||
		(bullet.circle.center.x < 0.f - SCREEN_PADDING) ||
		(bullet.circle.center.y > (float)SCREEN_HEIGHT + (float)SCREEN_PADDING) ||
		(bullet.circle.center.y < 0.f - SCREEN_PADDING))
		return true;

	return false;
}