#include "car.h"

void car::set_consumption(double fuel_cons)
{
	if (fuel_cons > 0)
		consumption = fuel_cons;
	else
		consumption = DEFAULT_CONSUMPTION;
}
