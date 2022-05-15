#include "../include/collision.h"
#include "../toolbox/intersection2d.h"

void destroyMineLayer(MineLayer& mineLayer)
{
	mineLayer.isAlive = false;
}

void destroyBullet(std::vector<Bullet>& bullets, int index)
{
	bullets[index] = bullets.back();
	bullets.pop_back();
}

// Check collision between a bullet (circle) and shapes (AABB + convexPolygon)
bool collision::checkBulletShapesCollision(Bullet bullet, std::vector<ConvexPolygon>& shapes)
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		// is bullet intersect with AABB of cur shape
		if (circle_box_intersect(bullet.circle, shapes[i].AABB))
		{
			// is bullet and shape intersect
			return convPol_circle_intersect(bullet.circle, shapes[i]);
		}
	}

	return false;
}

// Check collision between bullet (circle) and AABB
bool collision::checkBulletAABBCollision(std::vector<Bullet>& bullets, AABB AABB, int& indexBullet)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (circle_box_intersect(bullets[i].circle, AABB))
		{
			indexBullet = i;
			return true;
		}
	}

	return false;
}

// Check collision between two AABB
bool collision::checkAABBSCollision(AABB aabb1, AABB aabb2)
{
	return box_box_intersect(aabb1, aabb2);
}

// Check collision between two lists of shapes
bool collision::checkShapesShapesCollision(std::vector<ConvexPolygon>& shapes1, std::vector<ConvexPolygon>& shapes2)
{
	for (unsigned int i = 0; i < shapes1.size(); i++)
	{
		for (unsigned int j = 0; j < shapes2.size(); j++)
		{
			// is AABB of shapes intersect
			if (checkAABBSCollision(shapes1[i].AABB, shapes2[j].AABB))
			{
				// is shapes intersect
				return convPol_convPol_intersect(shapes1[i], shapes2[j]);
			}
		}
	}

	return false;
}

// Check collision between bullets of player and mines
bool collision::isBulletMineCollision(std::vector<Bullet>& bullets, std::vector<Mine*>& mines, std::vector<Animation>& animations, int& indexMine, int& indexPlayer)
{
	int  indexBullet, i = 0;

	for (unsigned int i = 0; i < mines.size(); i++)
	{
		if (checkBulletAABBCollision(bullets, mines[i]->getAABB(), indexBullet))
		{
			if (checkBulletShapesCollision(bullets[indexBullet], mines[i]->getShapes()))
			{
				animations.push_back(BulletExplosion(bullets[indexBullet].getPos(), bullets[indexBullet].getColor()));
				indexMine = i;
				indexPlayer = (int)bullets[indexBullet].type;
				destroyBullet(bullets, indexBullet);
				return true;
			}
		}
	}

	return false;
}

// Check collision between player bullets and the mineLayer
void collision::isBulletMineLayerCollision(std::vector<Bullet>& bullets, MineLayer& mineLayer, int& score, Sounds& sounds, std::vector<Animation>& animations)
{
	int indexBullet = 0;

	if (checkBulletAABBCollision(bullets, mineLayer.getAABB(), indexBullet))
	{
		if (checkBulletShapesCollision(bullets[indexBullet], mineLayer.getShapes()))
		{
			destroyBullet(bullets, indexBullet);
			animations.push_back(MineLayerExplosion(mineLayer.getOrigin()));
			PlaySound(sounds.mineExplosion);
			score += mineLayer.deathScore;
			destroyMineLayer(mineLayer);
		}
	}
}

// Check collision between players and mines
bool collision::isPlayerMineCollision(std::vector<Player>& players, std::vector<Mine*>& mines, int& indexPlayer)
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		for (unsigned int j = 0; j < mines.size(); j++)
		{
			if (players[i].isAlive && !players[i].isTeleport)
			{
				if (checkAABBSCollision(players[i].getAABB(), mines[j]->getAABB()))
				{
					if (checkShapesShapesCollision(players[i].getShapes(), mines[j]->getShapes()))
					{
						players[i].isAlive = false;
						players[i].life -= 1;
						indexPlayer = i;
						return true;
					}
				}
			}
		}
	}

	return false;
}

// Check collision between players and fireballs
bool collision::isPlayerFireballCollision(std::vector<Player>& players, std::vector<Bullet>& fireballs, int& indexPlayer)
{
	int indexBullet = 0;

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (checkBulletAABBCollision(fireballs, players[i].getAABB(), indexBullet) && !players[i].isTeleport)
		{
			if (checkBulletShapesCollision(fireballs[indexBullet], players[i].getShapes()))
			{
				destroyBullet(fireballs, indexBullet);
				players[i].isAlive = false;
				players[i].life -= 1;
				indexPlayer = i;
				return true;
			}
		}
	}

	return false;
}

// Check collision between player bullets and fireballs
bool collision::isBulletFireballCollision(std::vector<Bullet>& bullets, std::vector<Bullet>& fireballs, std::vector<Animation>& animations, int& scorePlayer)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		for (unsigned int j = 0; j < fireballs.size(); j++)
		{
			if (circles_intersect(bullets[i].circle, fireballs[j].circle))
			{
				scorePlayer += 110;
				animations.push_back(BulletExplosion(bullets[i].getPos(), bullets[i].getColor()));
				animations.push_back(FireballExplosion(fireballs[j].getPos()));
				destroyBullet(bullets, i);
				destroyBullet(fireballs, j);
				return true;
			}
		}
	}

	return false;
}

// Check collision between players and players bullets (if bullet is not from the current player)
bool collision::isPlayerBulletCollision(std::vector<Player>& players, std::vector<Bullet>& bullets, int& indexPlayer)
{
	if (players.size() > 1)
	{
		int indexBullet = 0;

		for (unsigned int i = 0; i < bullets.size(); i++)
		{
			for (unsigned int j = 0; j < players.size(); j++)
			{
				if ((bullets[i].type == BulletType::PLAYER_1 && j == 1) ||
					(bullets[i].type == BulletType::PLAYER_2 && j == 0))
				{
					if (circle_box_intersect(bullets[i].circle, players[j].getAABB()) && !players[j].isTeleport)
					{
						if (checkBulletShapesCollision(bullets[i], players[j].getShapes()))
						{
							destroyBullet(bullets, i);
							players[j].isAlive = false;
							players[j].life -= 1;
							indexPlayer = i;
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

// Check collision between the mineLayer and the players
bool collision::isPlayerMineLayerCollision(std::vector<Player>& players, MineLayer& mineLayer, int& indexPlayer)
{
	if (!mineLayer.isAlive)
		return false;

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (checkAABBSCollision(players[i].getAABB(), mineLayer.getAABB()) && !players[i].isTeleport)
		{
			if (checkShapesShapesCollision(players[i].getShapes(), mineLayer.getShapes()))
			{
				players[i].isAlive = false;
				players[i].life -= 1;
				destroyMineLayer(mineLayer);
				indexPlayer = i;
				return true;
			}
		}
	}

	return false;
}

// Check all players collision (allow kill the player)
bool collision::isPlayerCollision(std::vector<Player>& players, std::vector<Mine*>& mines, std::vector<Bullet>& bullets, std::vector<Bullet>& fireballs, MineLayer& mineLayer, int& indexPlayer)
{
	return (collision::isPlayerMineCollision(players, mines, indexPlayer) ||
		collision::isPlayerFireballCollision(players, fireballs, indexPlayer) ||
		collision::isPlayerBulletCollision(players, bullets, indexPlayer) ||
		collision::isPlayerMineLayerCollision(players, mineLayer, indexPlayer));
}