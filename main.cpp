/*************************************************************************
	> File Name: main.cpp
	> Author: Liu Shengxi 
	> Mail: 13689209566@163.com
	> Created Time: 2018年12月19日 星期三 12时01分56秒
 ************************************************************************/

#include "Coroutine.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <mcheck.h>

using namespace std;
using namespace Tattoo;

void func1(std::shared_ptr<CoroutineSchedule> s, void *arg)
{
	cout << "1" << endl;
	cout << "2" << endl;
	cout << *(int *)arg << endl; // 6666
	s->Yield();
	cout << "3" << endl;
	s->Yield();
}
void func2(std::shared_ptr<CoroutineSchedule> s, void *arg) //9999
{
	cout << "a" << endl;
	cout << *(int *)arg << endl;

	s->Yield();
	cout << "b" << endl;
	cout << "c" << endl;
	s->Yield();
}
class TEST
{
  public:
	void func3(std::shared_ptr<CoroutineSchedule> s, void *arg)
	{
		// cout << "x" << endl;
		// cout << *(int *)arg << endl;
		// s->Yield();
		// cout << "y" << endl;
		// cout << "z" << endl;
		// s->Yield();
		for (int i = 0; i < 10; i++)
		{
			cout << "coroutine : " << s->GetCurCoID() << " : " << *(int *)arg + i << endl;
			s->Yield();
		}
	}
};

int main()
{
	std::shared_ptr<CoroutineSchedule>
		schedule = std::make_shared<CoroutineSchedule>();

	int test1 = 1;
	int test2 = 2;
	int test3 = 3;

	TEST tt;

	int id_co1 = schedule->CreateCoroutine(std::bind(&TEST::func3, &tt, schedule, &test1));
	int id_co2 = schedule->CreateCoroutine(std::bind(&TEST::func3, &tt, schedule, &test2));
	int id_co3 = schedule->CreateCoroutine(std::bind(&TEST::func3, &tt, schedule, &test3));

	printf("main start\n");
	// int flag = 1;
	// while (1)
	// {
	// 	flag = 1;
	// 	if (schedule->IsAlive(id_co1))
	// 	{
	// 		flag++;
	// 		cout << "id_cor1   true" << endl;
	// 		schedule->ResumeCoroutine(id_co1);
	// 	}

	// 	if (schedule->IsAlive(id_co2))
	// 	{
	// 		flag++;
	// 		cout << "id_cor2   true" << endl;
	// 		schedule->ResumeCoroutine(id_co2);
	// 	}
	// 	sleep(1);
	// 	if (flag == 1)
	// 		break;
	// }
	while ((schedule->IsAlive(id_co1)) && (schedule->IsAlive(id_co2)) && (schedule->IsAlive(id_co3)))
	{
		schedule->ResumeCoroutine(id_co1);
		schedule->ResumeCoroutine(id_co2);
		schedule->ResumeCoroutine(id_co3);
	}
	printf("main end\n");

	return 0;
}
