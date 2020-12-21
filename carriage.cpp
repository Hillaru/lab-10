#include "carriage.h"

void carriage::set_consumption(vector<double>& _horses_stamina)
{
	int horse_count = 1;

	if (_horses_stamina.size() > 0)
		horse_count = _horses_stamina.size();
	else
		horse_count = 1;

	consumption = 0;

	for (int i = 0; i < horse_count; i++)
	{
		if (_horses_stamina[i] <= 0)
		{
			consumption = DEFAULT_CONSUMPTION;
			horse_count = 1;
			horses_stamina_list = { DEFAULT_CONSUMPTION };
			return;
		}

		if (i == 1 || _horses_stamina[i] > consumption)
			consumption = _horses_stamina[i];
	}

	consumption /= horse_count;
	horses_stamina_list = _horses_stamina;
}

vector<double> carriage::get_horses_stamina_list() const
{
	return horses_stamina_list;
}