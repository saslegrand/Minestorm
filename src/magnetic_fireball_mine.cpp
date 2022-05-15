#include "../include/magnetic_fireball_mine.h"
#include "../include/game.h"
#include "../include/utils.h"
#include "../toolbox/maths.h"

void initShapesMagneticFireball(Collider& collider, Vector2D origin, float scale)
{
	float rectHalfWidth  = 23.f * scale;
	float rectHalfHeight = 23.f * scale;
	float triangleHeight = 16.f * scale;
	float triangleWidth = 8.f * scale;
	
	collider.shapes.clear();
	std::vector<Vector2D> shape;

	shape.push_back({ origin.x - rectHalfWidth, origin.y - rectHalfHeight});
	shape.push_back({ origin.x + rectHalfWidth, origin.y - rectHalfHeight });
	shape.push_back({ origin.x + rectHalfWidth, origin.y + rectHalfHeight });
	shape.push_back({ origin.x - rectHalfWidth, origin.y + rectHalfHeight });

	collider.addShape(shape, 4);
	shape.clear();

	shape.push_back({ origin.x - rectHalfWidth, origin.y - rectHalfHeight });
	shape.push_back({ origin.x - rectHalfWidth, origin.y - rectHalfHeight - triangleHeight });
	shape.push_back({ origin.x - rectHalfWidth + triangleWidth, origin.y - rectHalfHeight });

	collider.addShape(shape, 3);
	shape.clear();

	shape.push_back({ origin.x + rectHalfWidth, origin.y - rectHalfHeight });
	shape.push_back({ origin.x + rectHalfWidth + triangleHeight, origin.y - rectHalfHeight });
	shape.push_back({ origin.x + rectHalfWidth, origin.y - rectHalfHeight + triangleWidth });

	collider.addShape(shape, 3);
	shape.clear();

	shape.push_back({ origin.x + rectHalfWidth, origin.y + rectHalfHeight });
	shape.push_back({ origin.x + rectHalfWidth, origin.y + rectHalfHeight + triangleHeight });
	shape.push_back({ origin.x + rectHalfWidth - triangleWidth, origin.y + rectHalfHeight });

	collider.addShape(shape, 3);
	shape.clear();

	shape.push_back({ origin.x - rectHalfWidth, origin.y + rectHalfHeight });
	shape.push_back({ origin.x - rectHalfWidth - triangleHeight, origin.y + rectHalfHeight });
	shape.push_back({ origin.x - rectHalfWidth, origin.y + rectHalfHeight - triangleWidth });

	collider.addShape(shape, 3);
	shape.clear();
}

MagneticFireballMine::MagneticFireballMine(float _scale, MineSize _size, int score, Vector2D origin)
{
	m_localRef.origin = origin;
	//m_localRef.rotateRef(90.f);

	initShapesMagneticFireball(m_collider, m_localRef.origin, _scale);
	m_collider.updateAABB();
	m_movement = { 120.f, 120.f, 0.f };

	m_statTexture.src = { 512.f, 256.f, 256.f, 256.f };
	//m_statTexture.color = GREEN;
	m_type = MineType::MAGNETIC_FIREBALL;

	m_size = _size;
	m_statTexture.width = (float)MINE_WIDTH * _scale;
	m_statTexture.height = (float)MINE_HEIGHT * _scale;

	deathScore = score;
	scale = _scale;
}

MagneticFireballMine::~MagneticFireballMine()
{

}

void MagneticFireballMine::updateMovement()
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

void MagneticFireballMine::update()
{
	m_deltaTime = GetFrameTime();

	updateMovement();
	Entity::update();
}

void MagneticFireballMine::drawDebug() const
{
	Entity::drawDebug();
}

void MagneticFireballMine::draw() const
{
	Entity::draw();
}