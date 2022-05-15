#pragma once

#include "../toolbox/vector2d.h"

class Referantial2D
{
public:
	Referantial2D();
	~Referantial2D();

	void     reset();
	void	 init_ref(Vector2D o);
	void	 rotateRef(float _angle);
	Vector2D local_to_global(Referantial2D global, Vector2D localPos);
	Vector2D global_to_local(Vector2D globalPos);
	Vector2D local_to_global_vect(Vector2D localPos);
	Vector2D global_to_local_vect(Vector2D globalPos);

	void     drawVectors() const;

	Vector2D origin;
	Vector2D unitI;
	Vector2D unitJ;
	float	 angle;
};
