#include "../include/fireball_mine.h"
#include "../include/game.h"
#include "../include/utils.h"
#include "../toolbox/maths.h"

void initFireballMineShapes(Collider& collider, Vector2D origin, float scale)
{
	float angle = maths::TAU / 8.f;
	float radiusMax = 35.f * scale;
	float radiusMin = 20.f * scale;

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

FireballMine::FireballMine(float _scale, MineSize _size, int score, Vector2D origin)
{
	m_localRef.origin = origin;
	//m_localRef.rotateRef(90.f);

	initFireballMineShapes(m_collider, m_localRef.origin, _scale);
	m_collider.updateAABB();
	m_movement = { 120.f, 120.f, 0.f };

	m_statTexture.src = { 768.f, 256.f, 256.f, 256.f };
	m_statTexture.color = ORANGE;
	m_type = MineType::FIREBALL;

	Range _angle = { 0.f, maths::TAU };
	float angle = maths::randRange(_angle);
	dir = { 0.f, 1.f };
	dir = dir.rotateVector(angle).normalized();

	m_size = _size;
	m_statTexture.width = (float)MINE_WIDTH * _scale;
	m_statTexture.height = (float)MINE_HEIGHT * _scale;

	deathScore = score;
	scale = _scale;
}

FireballMine::~FireballMine()
{

}

void FireballMine::updateMovement()
{
	float angle = -2.f * m_deltaTime;

	m_localRef.rotateRef(angle);
	m_collider.updateShapesRotation(m_localRef.origin, angle);

	m_movement.updateAcceleration(dir);
	m_movement.updateRotation(m_localRef, 0.f);
	m_movement.updatePosition(m_localRef, m_deltaTime);
	m_collider.updateShapesPosition(m_movement.velocity, m_deltaTime);
}

void FireballMine::update()
{
	m_deltaTime = GetFrameTime();

	updateMovement();
	Entity::update();
}

void FireballMine::drawDebug() const
{
	Entity::drawDebug();
}

void FireballMine::draw() const
{
	Entity::draw();
}