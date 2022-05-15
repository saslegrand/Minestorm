#pragma once

#include "player.h"
#include "mines.h"
#include "spawn_mother_ship.h"
#include "mine_layer.h"
#include "entity.h"
#include "animation.h"
#include "mine_explosion.h"
#include "player_explosion.h"
#include "player_teleportation.h"
#include "bullet_explosion.h"
#include "fireball_explosion.h"
#include "mine_layer_explosion.h"

namespace collision
{
	bool checkBulletShapesCollision(Bullet bullet, std::vector<ConvexPolygon>& shapes);
	bool checkBulletAABBCollision(std::vector<Bullet>& bullets, AABB AABB, int& indexBullet);
	bool checkAABBSCollision(AABB aabb1, AABB aabb2);
	bool checkShapesShapesCollision(std::vector<ConvexPolygon>& shapes1, std::vector<ConvexPolygon>& shapes2);

	void isBulletMineLayerCollision(std::vector<Bullet>& bullets, MineLayer& mineLayer, int& score, Sounds& sounds, std::vector<Animation>& animations);
	bool isBulletMineCollision(std::vector<Bullet>& bullets, std::vector<Mine*>& mines, std::vector<Animation>& animations, int& indexMine, int& indexPlayer);
	bool isBulletFireballCollision(std::vector<Bullet>& bullets, std::vector<Bullet>& fireballs, std::vector<Animation>& animations, int& scorePlayer);
	bool isPlayerMineCollision(std::vector<Player>& players, std::vector<Mine*>& mines, int& indexPlayer);
	bool isPlayerFireballCollision(std::vector<Player>& players, std::vector<Bullet>& fireballs, int& indexPlayer);
	bool isPlayerBulletCollision(std::vector<Player>& players, std::vector<Bullet>& bullets, int& indexPlayer);
	bool isPlayerCollision(std::vector<Player>& players, std::vector<Mine*>& mines, std::vector<Bullet>& bullets, std::vector<Bullet>& fireballs, MineLayer& mineLayer, int& indexPlayer);
	bool isPlayerMineLayerCollision(std::vector<Player>& players, MineLayer& mineLayer, int& indexPlayer);
};