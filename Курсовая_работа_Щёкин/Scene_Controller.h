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
	int ch;
	bool collisionMode;
	Color colors[7] = { Color::Red,Color::Blue,Color::Green,Color::White,Color::Yellow ,Color::Magenta, Color::Cyan };
	RenderWindow* window;
	Scene_Controller() {
		collisionMode = false;
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
		cout << "Інструкція для управління об'єктами:" << endl;
		cout << "ЛКМ - вибір об'єкта." << endl;
		cout << "WASD - рух об'єкта." << endl;
		cout << "0 - копіювання об'єкта." << endl;
		cout << "1 - додавання об'єкта." << endl;
		cout << "!!! 2 - видалення об'єкта." << endl;
		cout << "3 - приховування об'єкта." << endl;
		cout << "4 - трансформація об'єкта(зміна розмірів)." << endl;
		cout << "5 - повернення об'екта в початковий стан." << endl;
		cout << "6 - автоматичний рух об'екта(по заданому закону)." << endl;
		cout << "7 - зміна кольору об'екта." << endl;
		cout << "!!! 8 - створення агрегата з двух об'ектів." << endl;
		cout << "!!! 9 - зміна кольору об'екта под впливом іншого об'екта." << endl;
		cout << "Esc - вихід з програми." << endl;
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
						figures[i]->setSelected(false);
						figures[i]->choose();
						if (figures[i]->getBoundingBox().contains(translated_pos)) {
							ch = i;
							figures[ch]->setSelected(true);
							figures[ch]->choose();
						}
					}
				}
				if (figures[ch] != nullptr)
				{
					if (Keyboard::isKeyPressed(Keyboard::Num0))
					{
						if (figures[ch]->isSelected())
						{
							Figure* new_figure = figures[ch]->clone();
							new_figure->setPosition(figures[ch]->getX()+50, figures[ch]->getY() + 50);
							setFigures(new_figure->clone());
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
							figures[ch]->setSelected(false);
						}
						else {
							cout << "Виберіть фігуру!" << endl;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D))
					{
						if (figures[ch]->isSelected())
						{
							figures[ch]->remove(window);
							figures[ch]->move(event.key.code, coefOfMoving);
							figures[ch]->limitMoving(sizeWin);
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num2))
					{
						
						if (figures[ch]->isSelected())
						{
							figures[ch]->remove(window);
							for (auto ele = figures.begin(); ele != figures.end(); ele++)
							{
								if (*ele == figures[ch])
								{
									ele = figures.erase(ele);
								}
								else {
									++ele;
								}
							}
							window->clear(Color::Black);
							for (int i = 0; i < figures.size(); i++)
							{
								figures[i]->draw(*window);
							}
							window->display();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
							figures[ch]->setSelected(false);
						}
						else {
							cout << "Виберіть фігуру!" << endl;
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
							figures[ch]->setSelected(false);
						}
						else {
							cout << "Виберіть фігуру!" << endl;
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
							figures[ch]->setSelected(false);
						}
						else {
							cout << "Виберіть фігуру!" << endl;
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
							figures[ch]->setSelected(false);
						}
						else {
							cout << "Виберіть фігуру!" << endl;
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
								figures[ch]->automove(partForMoving, x, *window, coefOfMoving);
								window->clear(Color::Black);
								for (int i = 0; i < figures.size(); i++)
								{
									figures[i]->draw(*window);
								}
								window->display();
							}
							partForMoving = 0;
							figures[ch]->setSelected(false);
						}
						else {
							cout << "Виберіть фігуру!" << endl;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num7))
					{
						if (figures[ch]->isSelected())
						{
							int c;
							B:
							cout << "Виберіть колір для об'єкта:" << endl;
							cout << "1.Червоний  2.Синій  3.Зелений  4.Фіолетовий  5.Жовтий" << endl;
							cin >> c;
							if (c >= 1 && c <= 5) figures[ch]->setColor(colors[c - 1]);
							else goto B;
							figures[ch]->setSelected(false);
						}
						else {
							cout << "Виберіть фігуру!" << endl;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num8))
					{
						if (figures[ch]->isSelected())
						{
							clock_for_keyboard->restart();
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
							figures[ch]->setSelected(false);
						}
						else {
							cout << "Виберіть фігуру!" << endl;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Num9))
					{
						if (figures[ch]->isSelected())
						{
							if (!getCollisionMode()) {
								setCollisionMode(true);
								cout << "Collision deformating enabled\n";
							}
							else {
								setCollisionMode(false);
								cout << "Collision deformating disabled\n";
							}
							clock_for_keyboard->restart();
							while (clock_for_keyboard->getElapsedTime().asSeconds() < 1) {}
							figures[ch]->setSelected(false);
						}
						
					}
					for (int i = 0; i < getFigures().size(); i++) {
						getFigures()[i]->draw(*window);
					}
					window->display();
				}
				if (Keyboard::isKeyPressed(Keyboard::Num1))
				{
					Figure* new_circle = new Circle();
					Figure* new_rect = new My_Rectangle();
					float radius, width, height, x = 0, y = 0;
					cout << "Введіть координати нової фігури через пробіл: " << endl;
					cin >> x >> y;
					int colorInd = -1, shapeInd = -1;
					A:
					cout << "Введіть колір нової фігури: " << endl;
					cout << "0 - Red, 1 - Blue, 2 - Green, 3 - White, 4 - Yellow , 5 - Magenta, 6 - Cyan" << endl;
					cin >> colorInd;
					if (colorInd > 6 || colorInd < 0)
					{
						goto A;
					}
					cout << "Введіть тип фігури: " << endl;
					cout << "1 - Коло" << endl;
					cout << "2 - Прямокутник" << endl;
					cin >> shapeInd;
					switch (shapeInd)
					{
					case 1:
						D:
						cout << "Введіть радіус кола: " << endl;
						cin >> radius;
						if (radius<=0)
						{
							goto D;
						}
						new_circle = new Circle(radius, colors[colorInd], x, y);
						setFigures(new_circle->clone());
						break;
					case 2:
						C:
						cout << "Введіть ширину та висоту прямокутника через пробіл: " << endl;
						cin >> width >> height;
						if (width<=0 || height<=0 || (width <= 0 && height <= 0))
						{
							goto C;
						}
						new_rect = new My_Rectangle(width, height, colors[colorInd], x, y);
						setFigures(new_rect->clone());
						break;
					default:
						cout << "Неправильно введено тип фігури!" << endl;
						break;
					}
					window->clear(Color::Black);
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