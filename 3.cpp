#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>
using namespace std;

mutex mutexHouse;

void master(vector<int> &things)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(1, 100);
	while (!things.empty())
	{
		mutexHouse.lock();
		int new_thing = dis(generator);
		things.push_back(new_thing);
		cout << "В дом добавилась вещь стоимостью " << new_thing << endl;
		cout << "Стоимость вещей в доме: " << endl;
		for (const auto &t : things)
		{
			cout << t << " ";
		}
		cout << endl << endl;
		mutexHouse.unlock();
		this_thread::sleep_for(1000ms);
	}
}

void thief(vector<int>& things)
{
	while (!things.empty())
	{
		mutexHouse.lock();
		vector<int>::iterator high_price = max_element(things.begin(), things.end());
		cout << "Вор украл вещи стоимостью: " << *high_price << endl;
		things.erase(high_price);
		cout << "Остались вещи по такой цене: " << endl;
		for (const auto &n : things)
		{
			cout << n << " ";
		}
		cout << endl << endl;
		mutexHouse.unlock();
		this_thread::sleep_for(1s);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<int> things = { 95,126,42,84 };
	thread masterThread(master, ref(things));
	thread theifThread(thief, ref(things));
	masterThread.join();
	theifThread.join();
	cout << "Были украдены все вещи в доме" << endl;
	return 0;
}