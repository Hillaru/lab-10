#include "vechile.h"
#include <algorithm>

double vechile::move(double distance) const
{
	if (distance <= 0)
		return 0;

	double actual_distance = speed / (mass * consumption);

	return std::min(actual_distance, distance);
}

void vechile::set_mass(int _mass)
{
	if (_mass > 0)
		mass = _mass;
	else
		mass = 1;
}

void vechile::set_speed(int _speed)
{
	if (_speed > 0)
		speed = _speed;
	else
		speed = 1;
}

int vechile::get_mass() const
{
	return mass;
}

int vechile::get_speed() const
{
	return speed;
}

double vechile::get_consumption() const
{
	return consumption;
}
