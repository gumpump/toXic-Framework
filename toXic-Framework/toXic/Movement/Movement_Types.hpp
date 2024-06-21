#ifndef MOVEMENT_TYPES_IS_DEFINED
#define MOVEMENT_TYPES_IS_DEFINED

#include "../Graphic/Graphic_Window.hpp"

struct tX_Movement_Data
{
	D3DXVECTOR3 Vec;
	float Speed;
	tX_Movement_Data ()
	{
	}

	tX_Movement_Data (float X, float Y, float Z, float Speed)
	{
		this->Vec.x = X;
		this->Vec.y = Y;
		this->Vec.z = Z;
		this->Speed = Speed;
	}

	tX_Movement_Data (D3DXVECTOR3 Vec, float Speed)
	{
		this->Vec = Vec;
		this->Speed = Speed;
	}
};

#define tX_MOVE tX_Movement_Data

#endif