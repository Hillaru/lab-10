#pragma once
#include "vechile.h"
#include "vector"

using std::vector;

class carriage : public vechile
{
public:
	carriage(vector<double>_horses_stamina = { DEFAULT_CONSUMPTION }, int _mass = DEFAULT_MASS, int _speed = DEFAULT_SPEED) : vechile(_mass, _speed)
	{
		set_consumption(_horses_stamina);
	}
	void set_consumption(vector<double>&);
	vector<double> get_horses_stamina_list() const;

protected:
	vector<double> horses_stamina_list;
};
