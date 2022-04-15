#pragma once
#include "Figure.h"
#include <vector>
using namespace std;
class Composite : public Figure
{
	vector<Figure*> composites;
	float x1, y1, x2, y2;
	Color color;
public:
	Composite(Color c, float x, float y) :Figure(x, y, c) {}
	Composite(float x, float y) :Figure(x, y) {}
	Composite(){}

	float getX() override;
	float getY() override;
	float getSize() override;
	FloatRect getBoundingBox() override;
	void setColor(Color c) override;
	void setFillColor(Color c) override;
	void setPosition(float x, float y) override;
	void pushBack(Figure* fig);
	void clear();
	void limitMoving(Vector2u size) override;
	void remove(RenderWindow* window) override;
	void hide() override;
	void move(Keyboard::Key key, float coefOfMoving, float speed) override;
	void automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed) override;
	void transform() override;
	void restore();
	void draw(RenderWindow& window) override;
	Composite* clone() override;
	string serialize() override;
};