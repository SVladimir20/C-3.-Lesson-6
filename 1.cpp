#include <iostream>
#include <sstream>
#include <mutex>
using namespace std;

class pcout:
    public ostringstream
{
private:
    static mutex mCout;

public:
    ~pcout()
    {
        lock_guard<mutex> guard(mCout);
        cout << this->str();
    }
};

mutex pcout::mCout;

void Thread1()
{
    pcout{} << "Поток 1" << endl;
}
void Thread2()
{
    pcout{} << "Поток 2" << endl;
}
void Thread3(size_t num)
{
	pcout{} << "Поток 3. Проход №" << num << endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	for (size_t i = 0, length = 6; i < length; i++)
	{
		thread t1{ Thread1 };
		thread t2{ Thread2 };
		thread t3{ Thread3, ref(i) };
		t1.join();
		t2.join();
		t3.join();
		pcout{} << endl;
	}
	return 0;
}