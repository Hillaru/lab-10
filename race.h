#pragma once
#include "car.h"
#include "carriage.h"

struct vechiles
{
	carriage* carriage;
	car* car;
};

class race
{
public:
	race() {};
	~race()
	{
		int len = vechile_list.size();
		for (int i = 0; i < len; i++)
		{
			delete(vechile_list[i].carriage);
			delete(vechile_list[i].car);
		}
	}
	void start(double, vector<vechiles>&, vector<double>&);
	void add_car(car*);
	void add_carriage(carriage*);
	void remove_vechile(int);
	vector<vechiles> return_list();

protected:
	vector<vechiles> vechile_list;
	void BubbleSort(int, vector<vechiles>&, vector<double>&);
};

