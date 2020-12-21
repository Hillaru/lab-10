#include <iostream>
#include <fstream>
#include "car.h"
#include "carriage.h"
#include "race.h"
#include <Windows.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

void printJSON(const Document& d)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	cout << buffer.GetString() << endl;
}

string JSON2String(const Document& d) 
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	return buffer.GetString();
}

Document ToJSON(vechiles vech)
{
	Document d;
	Document::AllocatorType& allocator = d.GetAllocator();

	d.SetObject();

	Value Type;
	if (vech.car != NULL)
	{
		string buf = "Машина";
		Type.SetString(buf.data(), buf.length(), allocator);
		d.AddMember("Тип", Type, allocator);

		Value Speed;
		Speed.SetInt(vech.car->get_speed());
		d.AddMember("Скорость", Speed, allocator);

		Value Mass;
		Mass.SetInt(vech.car->get_mass());
		d.AddMember("Масса", Mass, allocator);

		Value Consumption;
		Consumption.SetDouble(vech.car->get_consumption());
		d.AddMember("Потребление", Consumption, allocator);

		return d;
	}
	else
		if (vech.carriage != NULL)
		{
			string buf = "Повозка";
			Type.SetString(buf.data(), buf.length(), allocator);
			d.AddMember("Тип", Type, allocator);

			Value Speed;
			Speed.SetInt(vech.carriage->get_speed());
			d.AddMember("Скорость", Speed, allocator);

			Value Mass;
			Mass.SetInt(vech.carriage->get_mass());
			d.AddMember("Масса", Mass, allocator);

			Value Horses_list;
			Horses_list.SetArray();
			for (double s : vech.carriage->get_horses_stamina_list())
			{
				Value val;
				val.SetDouble(s);
				Horses_list.PushBack(val, allocator);
			}
			d.AddMember("Потребление лошадьми", Horses_list, allocator);

			return d;
		}
}

Document RaceToJSON(race& r)
{
	Document d;
	Document::AllocatorType& allocator = d.GetAllocator();

	d.SetObject();

	Value Vechile_list;
	Vechile_list.SetArray();
	for (vechiles v : r.return_list())
	{
		Value val;
		val.CopyFrom(ToJSON(v), allocator);
		Vechile_list.PushBack(val, allocator);
	}
	d.AddMember("Список транспортных средств", Vechile_list, allocator);

	return d;
}

vechiles VechileFromJSON(Document& d)
{
	vechiles result;
	string type = d["Тип"].GetString();

	int Speed = d["Скорость"].GetInt();

	int Mass = d["Масса"].GetInt();

	if (type == "Машина")
	{
		double Consumption = d["Потребление"].GetDouble();

		result.car = new car(Mass, Consumption, Speed);
		result.carriage = NULL;
		return result;
	}

	if (type == "Повозка")
	{
		vector<double> Horses_list;
		Value& horses_list_json = d["Потребление лошадьми"];

		for (SizeType i = 0; i < horses_list_json.Size(); ++i)
		{
			Value& stamina = horses_list_json[i];
			Horses_list.push_back(stamina.GetDouble());
		}

		result.carriage = new carriage(Horses_list, Mass, Speed);
		result.car = NULL;
		return result;
	}
}


void RaceFromJSON(Document& d, race& r)
{	
	const Value& vech_list_json = d["Список транспортных средств"];

	for (SizeType i = 0; i < vech_list_json.Size(); ++i)
	{
		const Value& vech = vech_list_json[i];
		string Type;

		Type = vech["Тип"].GetString();

		int Speed = vech["Скорость"].GetInt();

		int Mass = vech["Масса"].GetInt();

		if (Type == "Машина")
		{
			double Consumption = vech["Потребление"].GetDouble();

			r.add_car(new car(Mass, Consumption, Speed));
		}
		else
		if (Type == "Повозка")
		{
			vector<double> Horses_list;
			const Value& horses_list_json = vech["Потребление лошадьми"];

			for (SizeType i = 0; i < horses_list_json.Size(); ++i)
			{
				const Value& stamina = horses_list_json[i];
				Horses_list.push_back(stamina.GetDouble());
			}

			r.add_carriage(new carriage(Horses_list, Mass, Speed));
		}
	}
}

int enter_mass()
{
	int mass = 1;
	cout << "Введите массу транспортного средства" << endl;
	cin >> mass;
	cin.clear();
	while (cin.get() != '\n');
	return(mass);
}

int enter_speed()
{
	int speed = 1;
	cout << "Введите скорость транспортного средства" << endl;
	cin >> speed;
	cin.clear();
	while (cin.get() != '\n');
	return(speed);
}

double enter_fuel()
{
	double fuel_cons = 0.01;
	cout << "Введите потребление топлива на единицу массы" << endl;
	cin >> fuel_cons;
	cin.clear();
	while (cin.get() != '\n');
	return(fuel_cons);
}

vector<double> enter_horses()
{
	int horse_count;
	double stamina_cons;
	vector<double> horses_stamina;

	cout << "Введите количество лошадей в повозке" << endl;
	cin >> horse_count;

	cin.clear();
	while (cin.get() != '\n');

	if (horse_count <= 0)
		horse_count = 1;

	horses_stamina.clear();
	for (int i = 1; i <= horse_count; i++)
	{
		cout << "Введите потребеление выносливости лошади №" << i << endl;
		cin >> stamina_cons;
		cin.clear();
		while (cin.get() != '\n');
		horses_stamina.push_back(stamina_cons);
	}

	return(horses_stamina);
}

car* carptr()
{
	car* c = new car(enter_mass(), enter_fuel(), enter_speed());
	return c;
}

carriage* carriageptr()
{
	carriage* c = new carriage(enter_horses(), enter_mass(), enter_speed());
	return c;
}

void print_vechile_list(vector<vechiles> vec, vector<double> dist = {NULL})
{
	int len = vec.size();
	bool print_dist = false;
	if (dist[0] != NULL)
		print_dist = true;

	for (int i = 0; i < len; i++)
		if (vec[i].car != NULL)
		{
			cout << "№" << i + 1 << " ----- Машина, скорость:" << vec[i].car->get_speed() << " масса:" << vec[i].car->get_mass();
			cout << " потребление:" << vec[i].car->get_consumption() << endl;
			if (print_dist)
				cout << "Пройденное расстояние: " << dist[i] << endl;
		}
		else
		{
			cout << "№" << i + 1 << " ----- Повозка, скорость:" << vec[i].carriage->get_speed() << " масса:" << vec[i].carriage->get_mass() << endl;
			cout << "потребление выносливости лошадьми: ";
			vector<double> horses_stamina_list = vec[i].carriage->get_horses_stamina_list();
			int horse_count = horses_stamina_list.size();

			for (int j = 0; j < horse_count; j++)
				cout << horses_stamina_list[j] << " ";
			cout << endl;
			if (print_dist)
				cout << "Пройденное расстояние: " << dist[i] << endl;
		}
}

void unit_test_carriage()
{
	cout << "Юнит тестирование класса carriage" << endl;
	cout << "----------------------------" << endl;

	const int MOVE_DIST = 50;
	ifstream inFile("unit_tests_carriage.txt");
	Document d;
	const int N = 1000;
	char inString[N];
	carriage* carriage;

	for (int i = 0; i < 3; i++)
	{
		inFile.getline(inString, N);
		d.Parse(inString);
		carriage = VechileFromJSON(d).carriage;

		cout << " ----- Повозка, скорость:" << carriage->get_speed() << " масса:" << carriage->get_mass() << endl;
		cout << "потребление выносливости лошадьми: ";
		vector<double> horses_stamina_list = carriage->get_horses_stamina_list();
		int horse_count = horses_stamina_list.size();

		for (int j = 0; j < horse_count; j++)
			cout << horses_stamina_list[j] << " ";
		cout << endl;

		cout << "тест метода move " << carriage->move(MOVE_DIST) << endl;
	}
	cout << endl;
	inFile.close();
}

void unit_test_car()
{
	cout << "Юнит тестирование класса car" << endl;
	cout << "----------------------------" << endl;

	const int MOVE_DIST = 50;
	ifstream inFile("unit_tests_car.txt");
	Document d;
	const int N = 1000;
	char inString[N];
	car* car;

	for (int i = 0; i < 2; i++)
	{
		inFile.getline(inString, N);
		d.Parse(inString);
		car = VechileFromJSON(d).car;

		cout << " ----- Машина, скорость:" << car->get_speed() << " масса:" << car->get_mass();
		cout << " потребление:" << car->get_consumption() << endl;

		cout << "тест метода move " << car->move(MOVE_DIST) << endl;
	}
	cout << endl;
	inFile.close();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unit_test_carriage();
	unit_test_car();

	cout << "Лабораторная работа 10, вариант 2" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "Потребление выносливости лошадьми и потребление топлива машиной\nуказываются в % от максимума на единицу массы" << endl << endl;
	cout << "(Например: 0.01 - это 1% от максимального количества\nтоплива/выносливости за каждую единицу массы.\nТогда при массе 10 машина будет тратить 10% топлива за каждый пройденный км)" << endl << endl;
	cout << "Потребление выносливости каждой лошадью будет поделено\nна количество лошадей в повозке" << endl;
	cout << "---------------------------------------------------------------" << endl;

	race r;
	char ch;
	int num, len;

	cout << "Для того чтобы начать гонку, добавьте нескольких участников" << endl;

	while (true)
	{
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Введите 1 - чтобы добавить машину, 2 - повозку, 0 - начать гонку" << endl;
		cout << "Введите 3 - чтобы удалить транспортное средство" << endl;
		cout << "Введите 4 - чтобы вывести список транспортных средств" << endl;
		cout << "Введите 5 - чтобы загрузить список участников гонки В файл" << endl;
		cout << "Введите 6 - чтобы загрузить список участников гонки ИЗ файла" << endl;
		cout << "Введите 7 - чтобы вывести сериализацию определенного транспортного средства" << endl << endl;
		cin >> ch;
		while (cin.get() != '\n');
		cin.clear();

		switch (ch)
		{
		case '1':
			r.add_car(carptr());
			break;

		case '2':
			r.add_carriage(carriageptr());
			break;

		case '3':
			cout << "Введите номер транспортного средства для удаления в списке" << endl;
			cin >> num;
			while (cin.get() != '\n');
			cin.clear();

			if (r.return_list().size() < num || num <= 0)
				continue;

			r.remove_vechile(num - 1);
			break;

		case '4':
			print_vechile_list(r.return_list());
			break;

		case '5':
		{
			if (r.return_list().size() == 0)
				continue;

			Document d = RaceToJSON(r);
			printJSON(d);

			ofstream outFile("file.txt");
			outFile << JSON2String(d);
			outFile.close();
		} break;

		case '6':
		{
			ifstream inFile("file.txt");
			Document d;
			const int N = 1000;
			char inString[N];

			inFile.getline(inString, N);
			d.Parse(inString);
			inFile.close();

			RaceFromJSON(d, r);

			print_vechile_list(r.return_list());
		} break;

		case '7':
		{
			Document d;
			cout << "Введите номер транспортного средства для вывода сериализации" << endl;
			cin >> num;
			while (cin.get() != '\n');
			cin.clear();

			if (r.return_list().size() < num || num <= 0)
				continue;

			vechiles vech = r.return_list()[num - 1];
			d = ToJSON(vech);
			printJSON(d);
		} break;

		case '0':
			vector<vechiles> vec;
			vector<double> distances;
			double dist;

			cout << "Введите дистанцию гонки" << endl;
			cin >> dist;
			while (cin.get() != '\n');
			cin.clear();

			r.start(dist, vec, distances);
			print_vechile_list(vec, distances);
		}
	}
}