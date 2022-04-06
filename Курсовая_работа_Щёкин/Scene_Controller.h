#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Composite.h"
#include "Rectangle.h"
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;
class Scene_Controller {
protected:
	vector<Figure*> figures;
	int ch = 0;
	bool collisionMode;
	Scene_Controller() {
		collisionMode = false;
	}
	bool collideCheck(int& collision_index) {
		FloatRect boundingBox = figures[ch]->getBoundingBox();
		for (int i = 0; i < figures.size(); i++) {
			if (i == ch) continue;
			if (boundingBox.intersects(figures[i]->getBoundingBox())) {
				collision_index = i;
				return true;
			}
		}
		return false;
	}
	void setCollisionMode(bool b) {
		collisionMode = b;
	}
	bool getCollisionMode() {
		return collisionMode;
	}
public:
	Scene_Controller(Scene_Controller& other) = delete;
	void operator=(const Scene_Controller&) = delete;
	static Scene_Controller* getInstance();
	void start()
	{
		ContextSettings settings;
		settings.antialiasingLevel = 8;
		RenderWindow window(VideoMode(900, 900), "SFML_Course_Work_Shchokin_Bohdan", Style::Default, settings);
		int countOfFigures = 3;
		int collision_index = -1;
		int partForMoving = 0;
		float coefOfMoving, speed = 300;
		Rectangle* rectangle = new Rectangle(200.0f, 100.0f, Color::Yellow, 150, 150);
		Circle* circle = new Circle(90.0f, Color::Cyan, 250, 250);
		Rectangle* rectangle1 = new Rectangle(100.0f, 50.0f, Color::Red, 350, 350);
		figures.push_back(rectangle->clone());
		figures.push_back(circle->clone());
		figures.push_back(rectangle1->clone());
		Color colors[7] = { Color::Red,Color::Blue,Color::Green,Color::White,Color::Yellow ,Color::Magenta, Color::Cyan };
		Vector2u sizeWin = window.getSize();
		Clock* clock_for_moving = new Clock;
		Clock* clock_for_keyboard = new Clock;
		cout << "Інструкція для управління об'єктами:" << endl;
		cout << "<- або -> - вибір об'єкта." << endl;
		cout << "W - рух об'єкта нагору." << endl;
		cout << "A - рух об'єкта ліворуч." << endl;
		cout << "S - рух об'єкта донизу." << endl;
		cout << "D - рух об'єкта праворуч." << endl;
		cout << "H - приховування об'єкта." << endl;
		cout << "T - трансформація об'єкта(зміна розмірів)." << endl;
		cout << "R - повернення об'екта в початковий стан." << endl;
		cout << "M - автоматичний руч об'екта(по заданому закону)." << endl;
		cout << "C - зміна кольору об'екта." << endl;
		cout << "K - створення агрегата з двух об'ектів." << endl;
		cout << "P - зміна кольору об'екта под впливом іншого об'екта." << endl;
		cout << "Esc - вихід з програми." << endl;
		while (window.isOpen())
		{
			coefOfMoving = clock_for_moving->restart().asSeconds();
			Event event;
			while (window.pollEvent(event));
			{
				if (event.type == Event::Closed) window.close();
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					ch++;
					if (ch == countOfFigures) ch = 0;
					clock_for_keyboard->restart();
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					ch--;
					if (ch < 0)ch = countOfFigures - 1;
					clock_for_keyboard->restart();
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
				}
				int x[2] = { figures[ch]->getX() + 200, figures[ch]->getX() };
				for (int i = 0; i < countOfFigures; i++) figures[i]->setFillColor(Color::Transparent);
				if (figures[ch]->getCounterHiding() == 1) figures[ch]->setColor(figures[ch]->getColor());
				if (Keyboard::isKeyPressed(Keyboard::H))
				{
					clock_for_keyboard->restart();
					figures[ch]->hide();
					window.clear(Color::Black);
					for (int i = 0; i < countOfFigures; i++) figures[i]->draw(window);
					window.display();
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
				}
				if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S))
				{
					if (collisionMode) {
						if (collideCheck(collision_index))
						{
							figures[ch]->setColor(colors[rand() % 7]);
							figures[ch]->move(event.key.code, coefOfMoving);
							figures[ch]->limitMoving(sizeWin);
						}
						else {
							figures[ch]->move(event.key.code, coefOfMoving);
							figures[ch]->limitMoving(sizeWin);
						}
					}
					else {
						figures[ch]->move(event.key.code, coefOfMoving);
						figures[ch]->limitMoving(sizeWin);
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::T))
				{
					figures[ch]->transform();
					window.clear(Color::Black);
					for (int i = 0; i < countOfFigures; i++) figures[i]->draw(window);
					window.display();
					clock_for_keyboard->restart();
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
				}
				if (Keyboard::isKeyPressed(Keyboard::P))
				{
					if (!getCollisionMode()) setCollisionMode(true);
					else setCollisionMode(false);
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
				}
				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					figures[ch]->restore();
					window.clear(Color::Black);
					for (int i = 0; i < countOfFigures; i++) figures[i]->draw(window);
					window.display();
					clock_for_keyboard->restart();
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
				}
				if (Keyboard::isKeyPressed(Keyboard::M))
				{
					clock_for_keyboard->restart();
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 3)
					{
						figures[ch]->automove(partForMoving, x, window, coefOfMoving);
						window.clear(Color::Black);
						for (int i = 0; i < countOfFigures; i++) figures[i]->draw(window);
						window.display();
					}
					partForMoving = 0;
				}
				if (Keyboard::isKeyPressed(Keyboard::C))
				{
					int c;
				B:
					cout << "Виберіть колір для об'єкта:" << endl;
					cout << "1.Червоний  2.Синій  3.Зелений  4.Фіолетовий  5.Жовтий" << endl;
					cin >> c;
					if (c >= 1 && c <= 5) figures[ch]->setColor(colors[c - 1]);
					else goto B;
				}
				if (Keyboard::isKeyPressed(Keyboard::K))
				{
					int i1, i2;
				A:
					cout << "Введіть індекси об'ектів через пробіл від 0 до " << countOfFigures - 1 << endl;
					cin >> i1 >> i2;
					if (i1 >= 0 && i1 < countOfFigures && i2 >= 0 && i2 < countOfFigures)
					{
						Composite* composit = new Composite(figures[i1]->getColor(), figures[i1]->getX(), figures[i2]->getY());
						composit->pushBack(figures[i1]->clone());
						composit->pushBack(figures[i2]->clone());
						figures.push_back(composit->clone());
						composit->clear();
						countOfFigures++;
						delete composit;
					}
					else goto A;
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					exit(0);
				}
			}
			window.clear(Color::Black);
			for (int i = 0; i < countOfFigures; i++) figures[i]->draw(window);
			window.display();
		}
		delete clock_for_keyboard;
		delete clock_for_moving;
		delete circle;
		delete rectangle;
		delete rectangle1;
		system("pause");
	}
};