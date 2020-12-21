#include "race.h"

void race::BubbleSort(int len, vector<vechiles>& a, vector<double>& b)
{
	double tempb;
	vechiles tempa;
	bool exit = false, swap = false; 

	while (!exit) 
	{
		exit = true;
		for (int i = 0; i < (len - 1); i++)
		{
			swap = false;

			if (a[i].car != NULL && a[i + 1].car != NULL)
			{
				if (((a[i].car->get_speed() < a[i + 1].car->get_speed()) && (b[i] == b[i + 1])) || (b[i] < b[i + 1]))
				{
					exit = false;
					swap = true;
				}
					
			}
			else
			if (a[i].car != NULL && a[i + 1].carriage != NULL)
			{
				if (((a[i].car->get_speed() < a[i + 1].carriage->get_speed()) && (b[i] == b[i + 1])) || (b[i] < b[i + 1]))
				{
					exit = false;
					swap = true;
				}
			
			}
			else
			if (a[i].carriage != NULL && a[i + 1].car != NULL)
			{
				if (((a[i].carriage->get_speed() < a[i + 1].car->get_speed()) && (b[i] == b[i + 1])) || (b[i] < b[i + 1]))
				{
					exit = false;
					swap = true;
				}
			}
			else
			if (a[i].carriage != NULL && a[i + 1].carriage != NULL)
				if (((a[i].carriage->get_speed() < a[i + 1].carriage->get_speed()) && (b[i] == b[i + 1])) || (b[i] < b[i + 1]))
				{
					exit = false;
					swap = true;
				}

			if (swap)
			{
				tempa = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tempa;

				tempb = b[i];
				b[i] = b[i + 1];
				b[i + 1] = tempb;
			}
		}
	}
}

void race::start(double dist, vector<vechiles>& sorted_list, vector<double>& distance)
{
	sorted_list = vechile_list;
	distance.clear();

	int len = vechile_list.size();
	if (len < 1) return;

	for (int i = 0; i < len; i++)
		if (vechile_list[i].car != NULL)
			distance.push_back(vechile_list[i].car->move(dist));
		else
			distance.push_back(vechile_list[i].carriage->move(dist));

	BubbleSort(len, sorted_list, distance);
}

void race::add_car(car* _car)
{
	vechiles temp;
	temp.car = _car;
	temp.carriage = NULL;
	vechile_list.push_back(temp);
}

void race::add_carriage(carriage* _carriage)
{
	vechiles temp;
	temp.car = NULL;
	temp.carriage = _carriage;
	vechile_list.push_back(temp);
}

void race::remove_vechile(int ind)
{

	int len = vechile_list.size();
	if (vechile_list[ind].car != NULL)
		delete(vechile_list[ind].car);
	else
		delete(vechile_list[ind].carriage);

	for (int i = ind; i < len - 1; i++)
		vechile_list[i] = vechile_list[i + 1];	

	vechile_list.pop_back();
}

vector<vechiles> race::return_list()
{
	return(vechile_list);
}