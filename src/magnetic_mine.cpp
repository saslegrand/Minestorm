#include "../include/magnetic_mine.h"
#include "../include/game.h"
#include "../include/utils.h"
#include "../toolbox/maths.h"

void initShapes2(Collider& collider, Vector2D origin, float scale)
{
	float angle = maths::TAU / 8.f;
	float radiusMax = 35.f * scale;
	float radiusMin = 11.f * scale;

	std::vector<Vector2D> shape;

	for (int i = 0; i < 8; i += 2)
	{
		Vector2D pt0 = origin;
		Vector2D pt1 = origin;
		Vector2D pt2 = origin;

		pt0.x += radiusMin * cosf(angle * i);
		pt0.y += radiusMin * sinf(angle * i);

		pt1.x += radiusMax * cosf(angle * (i + 1));
		pt1.y += radiusMax * sinf(angle * (i + 1));

		pt2.x += radiusMin * cosf(angle * (i + 2));
		pt2.y += radiusMin * sinf(angle * (i + 2));

		shape.push_back(origin);
		shape.push_back(pt0);
		shape.push_back(pt1);
		shape.push_back(pt2);

		collider.addShape(shape, 4);
		shape.clear();
	}
}

MagneticMine::MagneticMine(float _scale, MineSize _size, int score, Vector2D origin)
{
	m_localRef.origin = origin;
	//m_localRef.rotateRef(90.f);

	initShapes2(m_collider, m_localRef.origin, _scale);
	m_collider.updateAABB();
	m_movement = { 120.f, 120.f, 0.f };

	m_statTexture.src = { 256.f, 256.f, 256.f, 256.f };
	m_statTexture.color = GREEN;
	m_type = MineType::MAGNETIC;

	m_size = _size;
	m_statTexture.width = (float)MINE_WIDTH * _scale;
	m_statTexture.height = (float)MINE_HEIGHT * _scale;

	deathScore = score;
	scale = _scale;
}

MagneticMine::~MagneticMine()
{

}

void MagneticMine::updateMovement()
{
	dir = m_target - m_localRef.origin;

	if (fabsf(dir.x) > ((float)SCREEN_WIDTH * 0.5f))
	{
		dir.x *= -1.f;
		dir.x = maths::sign(dir.x) * ((float)SCREEN_WIDTH - dir.x * maths::sign(dir.x));
	}

	if (fabsf(dir.y) > ((float)SCREEN_HEIGHT * 0.5f))
	{
		dir.y *= -1.f;
		dir.y = maths::sign(dir.y) * ((float)SCREEN_HEIGHT - dir.y * maths::sign(dir.y));
	}

	m_localRef.rotateRef(2 * m_deltaTime);
	m_collider.updateShapesRotation(m_localRef.origin, 2 * m_deltaTime);

	m_movement.updateAcceleration(dir.normalized());
	m_movement.updateRotation(m_localRef, 0.f);
	m_movement.updatePosition(m_localRef, m_deltaTime);
	m_collider.updateShapesPosition(m_movement.velocity, m_deltaTime);
}

void MagneticMine::update()
{
	m_deltaTime = GetFrameTime();

	updateMovement();
	Entity::update();
}

void MagneticMine::drawDebug() const
{
	Entity::drawDebug();
}

void MagneticMine::draw() const
{
	Entity::draw();
}