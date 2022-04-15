#pragma once
#include "Figure.h"
class My_Rectangle :public Figure
{
	float width, height, first_height, first_width;
	RectangleShape rectangle;
public:
	My_Rectangle(){}
	My_Rectangle(float width, float height, Color c, float x, float y) :Figure(x, y, c)
	{
		this->width = width;
		this->height = height;
		this->first_height = height;
		this->first_width = width;
		rectangle.setSize(Vector2f(width, height));
		rectangle.setFillColor(c);
		rectangle.setPosition(x, y);
		rectangle.setOrigin(width / 2, height / 2);
	}

	float getX() override;
	float getY() override;
	float getSize() override;
	void setColor(Color c) override;
	void setFillColor(Color c) override;
	FloatRect getBoundingBox()override;
	void setPosition(float x, float y) override;
	void remove(RenderWindow* window) override;
	void limitMoving(Vector2u size) override;
	void hide() override;
	void move(Keyboard::Key key, float coefOfMoving, float speed) override;
	void automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed) override;
	void transform() override;
	void restore() override;
	void draw(RenderWindow& window) override;
	My_Rectangle* clone() override;
	string serialize() override;
};


