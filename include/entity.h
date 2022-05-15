#pragma once
#include <raylib.h>

#include "../toolbox/convexPolygon.h"
#include "../toolbox/AABB.h"
#include "../include/bullet.h"
#include "../include/collider.h"
#include "../include/sounds.h"

struct TextureStat
{
	float     width;
	float     height;
	Rectangle src;
	Rectangle dest;
	Vector2   origin;
	Color     color;
};

struct EntityStat
{

};

class Entity
{
public:
	Entity() = default;
	Entity(Sounds* sounds, const Texture2D& texture);
	~Entity() {}

	inline Referantial2D&			  getLocalRef() { return m_localRef; }
	inline Vector2D					  getOrigin() { return m_localRef.origin; }
	inline AABB&					  getAABB() { return m_collider.aabb; }
	inline std::vector<ConvexPolygon>& getShapes() { return m_collider.shapes; }
	inline Collider&				  getCollider() { return m_collider; }
	inline const Texture2D&			  getTexture() const { return m_texture; }
	inline const Rectangle&			  getSrcTexture() const { return m_statTexture.src; }

	inline void	 setOrigin(Vector2D origin) { m_localRef.origin = origin; }
	inline void	 setTexture(const Texture2D& t) { m_texture = t; }
	inline void	 setSounds(Sounds* sounds) { m_sounds = sounds; }

	void virtual draw() const;
	void virtual drawDebug() const;
	void virtual update();
	void virtual updateMovement() {}

protected:
	Texture2D	  m_texture;
	Sounds*		  m_sounds;
	TextureStat   m_statTexture;

	float		  m_deltaTime = 0.f;

	Collider	  m_collider;
	Referantial2D m_localRef;
};