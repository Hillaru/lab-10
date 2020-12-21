#pragma once
#include <iostream>
#include <string>

using std::string;

static const int DEFAULT_MASS = 1;
static const int DEFAULT_SPEED = 1;
static const double DEFAULT_CONSUMPTION = 0.01;

class vechile
{
protected:
	double consumption = DEFAULT_CONSUMPTION; //суммарное потребление выносливости/топлива транспортным средством
	int speed = DEFAULT_SPEED;
	int mass = DEFAULT_MASS;

public:
	vechile(int _mass = DEFAULT_MASS, int _speed = DEFAULT_SPEED)
	{
		set_mass(_mass);
		set_speed(_speed);
	}
	void set_mass(int);
	void set_speed(int);
	double move(double) const; 
	int get_mass() const;
	int get_speed() const;
	double get_consumption() const;
};
