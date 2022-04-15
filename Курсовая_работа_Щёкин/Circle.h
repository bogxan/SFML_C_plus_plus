#pragma once
#include "Figure.h"
#include <string>
class Circle :public Figure
{
	float radius, first_radius;
	CircleShape circle;
public:
	Circle(){}
	Circle(float r, Color c, float x, float y) :Figure(x, y, c)
	{
		this->radius = r;
		this->first_radius = r;
		circle.setRadius(r);
		circle.setFillColor(c);
		circle.setPosition(x, y);
		circle.setOrigin(r, r);
	}
	float getX() override;
	float getY() override;
	float getSize() override;
	float getRadius();
	FloatRect getBoundingBox() override;
	void setColor(Color c) override;
	void setFillColor(Color c) override;
	void setRadius(float b);
	void setPosition(float x, float y) override;
	void remove(RenderWindow* window) override;
	void limitMoving(Vector2u size) override;
	void hide() override;
	void move(Keyboard::Key key, float coefOfMoving, float speed) override;
	void automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed) override;
	void transform() override;
	void restore() override;
	void draw(RenderWindow& window) override;
	Circle* clone() override;
	string serialize() override;
};