#pragma once
#include "vechile.h"

class car : public vechile
{
public:
	car(int _mass = DEFAULT_MASS, double _fuel_cons = DEFAULT_CONSUMPTION, int _speed = DEFAULT_SPEED) : vechile(_mass, _speed)
	{
		set_consumption(_fuel_cons);
	}
	void set_consumption(double);
};
