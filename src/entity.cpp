#include "../include/entity.h"
#include "../include/utils.h"

Entity::Entity(Sounds* sounds, const Texture2D& texture)
{
	m_statTexture.color = WHITE;
	m_statTexture.width = 0.f;
	m_statTexture.height = 0.f;
	m_statTexture.src = { 0.f, 0.f, 0.f, 0.f };

	setTexture(texture);
	setSounds(sounds);
}

void Entity::draw() const
{
	utils::drawEntity(m_localRef, m_texture, m_statTexture);
}

void Entity::drawDebug() const
{
	m_localRef.drawVectors();
	m_collider.drawShapesAABB();
}

void Entity::update()
{
	screen::checkBorderEntity(m_localRef, m_collider.shapes, m_statTexture.width * 0.2f);
	m_collider.updateAABB();
}