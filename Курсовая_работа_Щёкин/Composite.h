#pragma once
#include "Figure.h"
#include <vector>
using namespace std;
class Composite : public Figure
{
	vector<Figure*> composites;
public:
	Composite(Color c, float x, float y) :Figure(x, y, c) {}
	Composite(float x, float y) :Figure(x, y) {}

	float getX() override
	{
		return composites[0]->getX();
	}
	float getY() override
	{
		return composites[0]->getY();
	}
	float getSize() override
	{
		return composites[0]->getSize();
	}
	FloatRect getBoundingBox() {
		return composites[0]->getBoundingBox();
	}
	void setColor(Color c) override
	{
		color = c;
		for (int i = 0; i < composites.size(); i++) composites[i]->setColor(c);
	}
	void setFillColor(Color c) override
	{
		for (int i = 0; i < composites.size(); i++) composites[i]->setFillColor(c);
	}
	void setPosition(float x, float y) override
	{
		for (int i = 0; i < composites.size(); i++) composites[i]->setPosition(x, y);
	}

	void pushBack(Figure* fig)
	{
		composites.push_back(fig);
	}
	void clear()
	{
		composites.clear();
	}
	void limitMoving(Vector2u size) override
	{
		for (int i = 0; i < composites.size(); i++) composites[i]->limitMoving(size);
	}
	void hide() override
	{
		switch (counterHiding)
		{
		case 1:
		{
			for (int i = 0; i < composites.size(); i++) composites[i]->setFillColor(Color::Transparent);
			counterHiding++;
			break;
		}
		case 2:
		{
			for (int i = 0; i < composites.size(); i++) composites[i]->setFillColor(getColor());
			counterHiding--;
			break;
		}
		default:
			break;
		}
	}
	void move(Keyboard::Key key, float coefOfMoving, float speed = 200) override
	{
		for (int i = 0; i < composites.size(); i++) composites[i]->move(key, coefOfMoving);
	}
	void automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed = 150) override
	{
		for (int i = 0; i < composites.size(); i++) composites[i]->automove(part, points, window, coefOfMoving);
		limitMoving(window.getSize());
	}
	void transform() override
	{
		switch (counterTransforming)
		{
		case 1:
		{
			for (int i = 0; i < composites.size(); i++) composites[i]->transform();
			counterTransforming++;
			break;
		}
		case 2:
		{
			for (int i = 0; i < composites.size(); i++) composites[i]->transform();
			counterTransforming--;
			break;
		}
		default:
			break;
		}
	}
	void restore()
	{
		for (int i = 0; i < composites.size(); i++) composites[i]->restore();
	}
	void draw(RenderWindow& window) override
	{
		for (int i = 0; i < composites.size(); i++) composites[i]->draw(window);
	}
	Composite* clone() override
	{
		Composite* comp = new Composite(composites[0]->getColor(), composites[0]->getX(), composites[0]->getY());
		for (int i = 0; i < composites.size(); i++) comp->pushBack(composites[i]);
		return comp;
	}
};