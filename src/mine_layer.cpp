#include "../include/mine_layer.h"
#include "../include/game.h"
#include "../include/utils.h"
#include "../toolbox/maths.h"

void initShapesMineLayer(Collider& collider, Vector2D origin)
{
	collider.shapes.clear();
	std::vector<Vector2D> shape;

	shape.push_back({ origin.x - 8.f, origin.y - 4.f });
	shape.push_back({ origin.x, origin.y - 10.f });
	shape.push_back({ origin.x + 8.f, origin.y - 4.f });

	collider.addShape(shape, 3);
	shape.clear();

	shape.push_back({ origin.x - 26.f, origin.y - 4.f });
	shape.push_back({ origin.x + 26.f, origin.y - 4.f });
	shape.push_back({ origin.x + 26.f, origin.y + 4.f });
	shape.push_back({ origin.x - 26.f, origin.y + 4.f });

	collider.addShape(shape, 4);
	shape.clear();

	shape.push_back({ origin.x - 26.f, origin.y - 4.f });
	shape.push_back({ origin.x - 35.f, origin.y + 12.f });
	shape.push_back({ origin.x - 26.f, origin.y + 4.f });

	collider.addShape(shape, 3);
	shape.clear();

	shape.push_back({ origin.x + 26.f, origin.y - 4.f });
	shape.push_back({ origin.x + 35.f, origin.y + 12.f });
	shape.push_back({ origin.x + 26.f, origin.y + 4.f });

	collider.addShape(shape, 3);
	shape.clear();
}

MineLayer::MineLayer()
{
	m_movement = { 250.f, 250.f, 0.f };

	m_statTexture.src = { 512.f, 0.f, 256.f, 256.f };
	m_statTexture.color = RED;
	m_statTexture.width = 64.f;
	m_statTexture.height = 64.f;

	deathScore = 1000;
}

void MineLayer::updateMovement()
{
	m_dir = (target - m_localRef.origin).normalized();

	m_movement.updateAcceleration(m_dir);
	m_movement.updatePosition(m_localRef, m_deltaTime);
	m_collider.updateShapesPosition(m_movement.velocity, m_deltaTime);
}

void MineLayer::update()
{
	m_deltaTime = GetFrameTime();

	updateMovement();
	m_collider.updateAABB();
}

void MineLayer::updateTarget()
{
	Range X = { xMinRand, xMaxRand };
	Range Y = { yMinRand, yMaxRand };
	target = { manage::randRangeValue(X), manage::randRangeValue(Y) };
	setMaxSpeed((float)GetRandomValue(250, 300));
	m_movement.velocity = { 0.f, 0.f };
}

void MineLayer::initShapes()
{
	initShapesMineLayer(m_collider, m_localRef.origin);
	m_collider.updateAABB();
}