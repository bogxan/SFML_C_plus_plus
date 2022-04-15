#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;
enum type
{
	Cir,
	Rec,
	Com
};
class Figure
{
protected:
	Color color, fc;
	float x, y;
	int counterHiding = 1, counterTransforming = 1;
	bool selected;
	type tp;
public:
	Figure() {}
	Figure(float x, float y, Color c)
	{
		this->x = x;
		this->y = y;
		this->color = c;
		this->fc = c;
		this->selected = false;
	}
	Figure(float x1, float y1, float x2, float y2, Color c)
	{
		this->x = x;
		this->y = y;
		this->color = c;
		this->fc = c;
		this->selected = false;
	}
	Figure(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->color = Color::Magenta;
		this->selected = false;
	}
	type getType()
	{
		return tp;
	}

	virtual void draw(RenderWindow& window) = 0;
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual float getSize() = 0;
	virtual FloatRect getBoundingBox() = 0;
	virtual void setColor(Color c) = 0;
	virtual void setFillColor(Color c) = 0;
	virtual void setPosition(float x, float y) = 0;
	virtual void limitMoving(Vector2u size) = 0;
	virtual void hide() = 0;
	virtual void move(Keyboard::Key key, float dt, float speed) = 0;
	virtual void automove(int& part, int x[2], RenderWindow& window, float dt, int speed) = 0;
	virtual void transform() = 0;
	virtual void restore() = 0;
	virtual void remove(RenderWindow* window) = 0;
	virtual Figure* clone() = 0;
	virtual string serialize() = 0;

	bool isSelected();
	void setSelected(bool sel);
	int getCounterHiding();
	int getCounterTransforming();
	Color getColor();
};