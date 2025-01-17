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
	bool traceMode;
	Color colors[7] = { Color::Red,Color::Blue,Color::Green,Color::White,Color::Yellow ,Color::Magenta, Color::Cyan };
	RenderWindow* window;
	Scene_Controller() {
		collisionMode = false;
		traceMode = false;
		ContextSettings settings;
		settings.antialiasingLevel = 8;
		ch = 0;
		window = new RenderWindow(VideoMode(1000, 1000), "SFML_Course_Work_Shchokin_Bohdan", Style::Default, settings);
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
	void setTraceMode(bool b) {
		traceMode = b;
	}
	bool getTraceMode() {
		return traceMode;
	}
	void setCollisionMode(bool b) {
		collisionMode = b;
	}
	bool getCollisionMode() {
		return collisionMode;
	}
	vector<Figure*> getFigures() {
		return figures;
	}
	RenderWindow* getWindow() {
		return window;
	}
	void setWindow(RenderWindow* wind) {
		window = wind;
	}
	void setFigures(Figure* fig) {
		figures.push_back(fig);
	}
public:
	Scene_Controller(Scene_Controller& other) = delete;
	void operator=(const Scene_Controller&) = delete;
	static Scene_Controller* getInstance();
	void start()
	{
		ContextSettings settings;
		settings.antialiasingLevel = 8;
		RenderWindow* window = getWindow();
		Vector2u sizeWin = window->getSize();
		int countOfFigures = 3;
		int collision_index = -1;
		int partForMoving = 0;
		int i1 = -1, i2 = -1;
		float coefOfMoving, speed = 300;
		Clock* clock_for_moving = new Clock;
		Clock* clock_for_keyboard = new Clock;
		My_Rectangle* rectangle = new My_Rectangle(200.0f, 100.0f, Color::Yellow, 150, 150);
		Circle* circle = new Circle(90.0f, Color::Cyan, 450, 450);
		My_Rectangle* rectangle1 = new My_Rectangle(100.0f, 50.0f, Color::Red, 750, 750);
		setFigures(rectangle->clone());
		setFigures(circle->clone());
		setFigures(rectangle1->clone());
		delete circle;
		delete rectangle;
		delete rectangle1;
		int choice;
		cout << "���������� ��� ��������� ��'������:" << endl;
		cout << "��� - ���� ��'����." << endl;
		cout << "WASD - ��� ��'����." << endl;
		cout << "K - ��������� ��������." << endl;
		cout << "0 - ��������� ��'����." << endl;
		cout << "1 - ��������� ��'����." << endl;
		cout << "2 - ��������� ��'����." << endl;
		cout << "3 - ������������ ��'����." << endl;
		cout << "4 - ������������� ��'����(���� ������)." << endl;
		cout << "5 - ���������� ��'���� � ���������� ����." << endl;
		cout << "6 - ������������ ��� ��'����(�� �������� ������)." << endl;
		cout << "7 - ���� ������� ��'����." << endl;
		cout << "8 - ��� ��'���� � �����/��� ��'���� ��� ����" << endl;
		cout << "9 - ��� ��'���� � ����� ������� �� ������� ������ ��'����/��� ��'���� ��� ���� �������." << endl;
		cout << "Esc - ����� � ��������." << endl;
		while (window->isOpen())
		{
			coefOfMoving = 0.002;
			for (int i = 0; i < getFigures().size(); i++) {
				getFigures()[i]->draw(*window);
			}
			window->display();
			Event event;
			while (window->pollEvent(event)) {
				if (event.type == Event::Closed) {
					window->close();
				}
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					auto mouse_pos = sf::Mouse::getPosition(*window);
					auto translated_pos = window->mapPixelToCoords(mouse_pos);
					for (int i = 0; i < figures.size(); i++)
					{
						if (figures[i]->getBoundingBox().contains(translated_pos)) {
							ch = i;
							figures[i]->setSelected(true);
						}
					}
				}
				if (figures[ch] != nullptr)
				{
					if (Keyboard::isKeyPressed(Keyboard::Num1))
					{
						if (figures[ch]->isSelected())
						{
							setFigures(figures[ch]->clone());
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
						}
						else {
							cout << "������� ������!" << endl;
							break;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D))
					{
						if (figures[ch]->isSelected())
						{
							if (collisionMode) {
								if (collideCheck(collision_index))
								{
									figures[ch]->remove(window);
									figures[ch]->setColor(colors[rand() % 7]);
									figures[ch]->move(event.key.code, coefOfMoving, 200);
									figures[ch]->limitMoving(sizeWin);
								}
								else if (collideCheck(collision_index) && traceMode) {
									figures[ch]->setColor(colors[rand() % 7]);
									figures[ch]->move(event.key.code, coefOfMoving, 200);
									figures[ch]->limitMoving(sizeWin);
								}
								else if (traceMode) {
									figures[ch]->move(event.key.code, coefOfMoving, 200);
									figures[ch]->limitMoving(sizeWin);
								}
								else {
									figures[ch]->remove(window);
									figures[ch]->move(event.key.code, coefOfMoving, 200);
									figures[ch]->limitMoving(sizeWin);
								}
							}
							else if (traceMode) {
								figures[ch]->move(event.key.code, coefOfMoving, 200);
								figures[ch]->limitMoving(sizeWin);
							}
							else {
								figures[ch]->remove(window);
								figures[ch]->move(event.key.code, coefOfMoving, 200);
								figures[ch]->limitMoving(sizeWin);
							}
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
						}
						else {
							cout << "������� ������!" << endl;
							break;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num2))
					{
						if (figures[ch]->isSelected())
						{
							if (figures.size()>1)
							{
								figures[ch]->remove(window);
								figures.erase(figures.begin()+ch);
								ch--;
								countOfFigures--;
								if (ch<0)
								{
									ch = figures.size() - 1;
								}
							}
							else {
								cout << "�� �� ������ �������� ������� ��� �� �� ������ ������� ���� ���� � ���� �������!" << endl;
							}
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
						}
						else {
							cout << "������� ������!" << endl;
							break;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num3))
					{
						if (figures[ch]->isSelected())
						{
							figures[ch]->hide();
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
							
						}
						else {
							cout << "������� ������!" << endl;
							break;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num4))
					{
						if (figures[ch]->isSelected())
						{
							figures[ch]->transform();
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
						}
						else {
							cout << "������� ������!" << endl;
							break;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num5))
					{
						
						if (figures[ch]->isSelected())
						{
							figures[ch]->restore();
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
						}
						else {
							cout << "������� ������!" << endl;
							break;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num6))
					{
						
						if (figures[ch]->isSelected())
						{
							clock_for_keyboard->restart();
							int x[2] = { figures[ch]->getX() + 200, figures[ch]->getX() };
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 3)
							{
								figures[ch]->automove(partForMoving, x, *window, coefOfMoving, 200);
								window->clear(Color::Black);
								for (int i = 0; i < figures.size(); i++)
								{
									figures[i]->draw(*window);
								}
								window->display();
							}
							partForMoving = 0;
						}
						else {
							cout << "������� ������!" << endl;
							break;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num7))
					{
						if (figures[ch]->isSelected())
						{
							int c;
							B:
							cout << "������� ���� ��� ��'����:" << endl;
							cout << "1.��������  2.�����  3.�������  4.Գ��������  5.������" << endl;
							cin >> c;
							if (c >= 1 && c <= 5) figures[ch]->setColor(colors[c - 1]);
							else goto B;
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
						}
						else {
							cout << "������� ������!" << endl;
							break;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num8))
					{
						if (figures[ch]->isSelected())
						{
							if (!getTraceMode()) {
								setTraceMode(true);
								cout << "��� ��'���� � �����.\n";
							}
							else {
								setTraceMode(false);
								cout << "��� ��'���� ��� ����.\n";
							}
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num9))
					{
						if (!getCollisionMode()) {
							setCollisionMode(true);
							cout << "��� ��'���� � ����� ������� �� ������� ������ ��'����.\n";
						}
						else {
							setCollisionMode(false);
							cout << "��� ��'���� ��� ���� �������.\n";
						}
						window->clear(Color::Black);
						for (int i = 0; i < figures.size(); i++)
						{
							figures[i]->draw(*window);
						}
						window->display();
						clock_for_keyboard->restart();
						while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
					}
					for (int i = 0; i < getFigures().size(); i++) {
						getFigures()[i]->draw(*window);
					}
					window->display();
				}
				if (Keyboard::isKeyPressed(Keyboard::K))
				{
					Composite* composit = new Composite(Color::Red, 5, 5);
					int i2, count = 0;
					S:
					cout << "������ ������� ��'����:" << endl;
					cin >> count;
					if (count > figures.size())
					{
						goto S;
					}
					else {
						H:
						cout << "������ ������� ����� �� 0 �� " << figures.size() - 1 << endl;
						for (int i1 = 0; i1 < count; i1++)
						{
							cin >> i2;
							if (i2 > figures.size()-1)
							{
								goto H;
								break;
							}
							else {
								composit->pushBack(figures[i2]->clone());
							}
						}
						figures.push_back(composit->clone());
						composit->clear();
					}
					window->clear(Color::Black);
					for (int i = 0; i < getFigures().size(); i++) {
						getFigures()[i]->draw(*window);
					}
					window->display();
					clock_for_keyboard->restart();
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num0))
				{
					Figure* new_circle = new Circle();
					Figure* new_rect = new My_Rectangle();
					float radius, width, height, x = 0, y = 0;
					cout << "������ ���������� ���� ������ ����� �����: " << endl;
					cin >> x >> y;
					int colorInd = -1, shapeInd = -1;
					A:
					cout << "������ ���� ���� ������: " << endl;
					cout << "0 - Red, 1 - Blue, 2 - Green, 3 - White, 4 - Yellow , 5 - Magenta, 6 - Cyan" << endl;
					cin >> colorInd;
					if (colorInd > 6 || colorInd < 0)
					{
						goto A;
					}
					cout << "������ ��� ������: " << endl;
					cout << "1 - ����" << endl;
					cout << "2 - �����������" << endl;
					cin >> shapeInd;
					switch (shapeInd)
					{
					case 1:
						D:
						cout << "������ ����� ����: " << endl;
						cin >> radius;
						if (radius<=0)
						{
							goto D;
						}
						new_circle = new Circle(radius, colors[colorInd], x, y);
						countOfFigures--;
						setFigures(new_circle->clone());
						break;
					case 2:
						C:
						cout << "������ ������ �� ������ ������������ ����� �����: " << endl;
						cin >> width >> height;
						if (width<=0 || height<=0 || (width <= 0 && height <= 0))
						{
							goto C;
						}
						new_rect = new My_Rectangle(width, height, colors[colorInd], x, y);
						countOfFigures++;
						setFigures(new_rect->clone());
						break;
					default:
						cout << "����������� ������� ��� ������!" << endl;
						break;
					}
					for (int i = 0; i < getFigures().size(); i++) {
						getFigures()[i]->draw(*window);
					}
					window->display();
					clock_for_keyboard->restart();
					while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					exit(0);
				}
				window->display();
			}
		}
	}
};