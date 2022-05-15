#include "../include/floating_mine.h"
#include "../include/game.h"
#include "../include/utils.h"
#include "../toolbox/maths.h"

void initShapes(Collider& collider, Vector2D origin, float scale)
{
	float angle		= maths::TAU / 6.f;
	float radiusMax = 35.f * scale;
	float radiusMin = 11.f * scale;

	std::vector<Vector2D> shape;

	for (int i = 0; i < 6; i += 2)
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

		pt0 = pt0.rotateCenterVector(origin, -angle / 2.f);
		pt1 = pt1.rotateCenterVector(origin, -angle / 2.f);
		pt2 = pt2.rotateCenterVector(origin, -angle / 2.f);

		shape.push_back(origin);
		shape.push_back(pt0);
		shape.push_back(pt1);
		shape.push_back(pt2);

		collider.addShape(shape, 4);
		shape.clear();
	}
}

FloatingMine::FloatingMine(float _scale, MineSize _size, int score, Vector2D origin)
{
	m_localRef.origin = origin;
	//m_localRef.rotateRef(90.f);

	initShapes(m_collider, m_localRef.origin, _scale);
	m_collider.updateAABB();
	m_movement = { 120.f, 120.f, 0.f };

	m_statTexture.src = { 0.f, 256.f, 256.f, 256.f };
	m_statTexture.color = YELLOW;
	m_type = MineType::FLOATING;

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

FloatingMine::~FloatingMine()
{

}

void FloatingMine::updateMovement()
{
	m_localRef.rotateRef(2 * m_deltaTime);
	m_collider.updateShapesRotation(m_localRef.origin, 2 * m_deltaTime);

	m_movement.updateAcceleration(dir);
	m_movement.updateRotation(m_localRef, 0.f);
	m_movement.updatePosition(m_localRef, m_deltaTime);
	m_collider.updateShapesPosition(m_movement.velocity, m_deltaTime);
}

void FloatingMine::update()
{
	m_deltaTime = GetFrameTime();

	updateMovement();
	Entity::update();
}

void FloatingMine::drawDebug() const
{
	Entity::drawDebug();
}

void FloatingMine::draw() const
{
	Entity::draw();
}