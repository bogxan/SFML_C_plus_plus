#include<iostream>
#include "Scene_Controller.h"
#include <time.h>
using namespace std;
int main()
{
	setlocale(0, "ru");
	srand(time(NULL));
	Scene_Controller* controller = Scene_Controller::getInstance();
	controller->start();
	system("pause");
	return 0;
}