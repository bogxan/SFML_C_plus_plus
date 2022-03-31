#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Figure
{
protected:
	float x, y;
	Color color, fc;
	int counterHiding = 1, counterTransforming = 1;
public:
	Figure(float x, float y, Color c)
	{
		this->x = x;
		this->y = y;
		this->color = c;
		this->fc = c;
	}
	Figure(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->color = Color::Magenta;
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
	virtual void move(Keyboard::Key key, float dt, float speed = 200) = 0;
	virtual void automove(int& part, int x[2], RenderWindow& window, float dt, int speed = 150) = 0;
	virtual void transform() = 0;
	virtual void restore() = 0;
	virtual Figure* clone() = 0;

	int getCounterHiding()
	{
		return counterHiding;
	}
	int getCounterTransforming()
	{
		return counterTransforming;
	}
	Color getColor()
	{
		return color;
	}
};