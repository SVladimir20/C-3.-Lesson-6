#include <iostream>
#include <sstream>
#include <mutex>
using namespace std;

bool isPrime(unsigned long long result)
{
	if (result == 1) return false;
	for (size_t i = 2; i < sqrt(result); i++)
	{
		if (result % i == 0)
		{
			return false;
		}
	}
	return true;
}

void Prime(long long index, unsigned long long &result, long long &counter, bool &ready)
{
	while (counter < index)
	{
		result++;
		if (isPrime(result))
		{
			counter++;
		}
	}
	ready = true;
}

long long primeNumber(long long index)
{
	unsigned long long result = 0;
	long long counter = 0;
	bool ready = false;
	thread t2{ Prime, ref(index), ref(result), ref(counter), ref(ready) };
	while (!ready)
	{
		system("cls");
		cout << "Прогресс: " << counter / (index / 100.0) << "%" << endl;
		this_thread::sleep_for(100ms);
	}
	t2.join();
	system("cls");
	cout << "Прогресс: " << counter / (index / 100.0) << "%" << endl;
	return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	long long primeNumber№ = 1000;
	unsigned long long pNumber = primeNumber(primeNumber№);
	cout << primeNumber№ << "-ое простое число = " << pNumber << endl;
	return 0;
}