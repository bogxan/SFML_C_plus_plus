#include<iostream>
#include "Scene_Controller.h"
#include <time.h>
#include <Windows.h> 
using namespace std;
int main()
{
	setlocale(LC_ALL, "ukr");
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	Scene_Controller* controller = Scene_Controller::getInstance();
	controller->start();
	delete controller;
	system("pause");
	return 0;
}