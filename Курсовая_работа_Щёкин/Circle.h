#pragma once
#include "Figure.h"
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

	float getX() override
	{
		return circle.getPosition().x;
	}
	float getY() override
	{
		return circle.getPosition().y;
	}
	float getSize() override
	{
		return radius;
	}
	float getRadius()
	{
		return radius;
	}
	FloatRect getBoundingBox() override {
		return circle.getGlobalBounds();
	}
	void setColor(Color c) override
	{
		color = c;
		circle.setFillColor(c);
	}
	void setFillColor(Color c) override
	{
		circle.setFillColor(c);
	}

	void setRadius(float b)
	{
		radius = b;
	}
	void setPosition(float x, float y) override
	{
		circle.setPosition(x, y);
	}

	void remove(RenderWindow* window) override {
		window->clear();
	}
	void choose() override {
		if (isSelected())
		{
			circle.setOutlineThickness(5);
			circle.setOutlineColor(Color(192, 192, 192));
		}
		else {
			circle.setOutlineThickness(0);
			circle.setOutlineColor(color);
		}
	}
	void limitMoving(Vector2u size) override
	{
		if (circle.getPosition().x + radius >= size.x) circle.setPosition(size.x - radius, circle.getPosition().y);
		if (circle.getPosition().x - radius <= 0) circle.setPosition(radius, circle.getPosition().y);
		if (circle.getPosition().y + radius >= size.y) circle.setPosition(circle.getPosition().x, size.y - radius);
		if (circle.getPosition().y - radius <= 0) circle.setPosition(circle.getPosition().x, radius);
	}
	void hide() override
	{
		Color outColor = circle.getOutlineColor();
		float thick = circle.getOutlineThickness();
		switch (counterHiding)
		{
		case 1:
		{
			circle.setFillColor(Color::Transparent);
			circle.setOutlineColor(Color::Transparent);
			circle.setOutlineThickness(0);
			counterHiding++;
			break;
		}
		case 2:
		{
			circle.setFillColor(getColor());
			circle.setOutlineColor(outColor);
			circle.setOutlineThickness(thick);
			counterHiding--;
			break;
		}
		default:
			break;
		}
	}
	void move(Keyboard::Key key, float coefOfMoving, float speed = 800) override
	{
		if (Keyboard::isKeyPressed(Keyboard::D)) circle.move(10.0f * speed * coefOfMoving, 0.0f);
		if (Keyboard::isKeyPressed(Keyboard::W)) circle.move(0.0f, -10.0f * speed * coefOfMoving);
		if (Keyboard::isKeyPressed(Keyboard::A)) circle.move(-10.0f * speed * coefOfMoving, 0.0f);
		if (Keyboard::isKeyPressed(Keyboard::S)) circle.move(0.0f, 10.0f * speed * coefOfMoving);
	}
	void automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed = 150) override
	{
		switch (part)
		{
		case 0:
		{
			circle.move(1.0f * speed * coefOfMoving, 0.0f);
			if (abs(circle.getPosition().x - points[part]) <= 10) part++;
			break;
		}
		case 1:
		{
			circle.move(-1.0f * speed * coefOfMoving, 0.0f);
			if (abs(circle.getPosition().x - points[part]) <= 10) part--;
			break;
		}
		default:
			break;
		}
		limitMoving(window.getSize());
	}
	void transform() override
	{
		Color outColor = circle.getOutlineColor();
		float thick = circle.getOutlineThickness();
		switch (counterTransforming)
		{
		case 1:
		{
			radius -= 25;
			setRadius(radius);
			circle.setRadius(getRadius());
			if (isSelected())
			{
				circle.setOutlineColor(outColor);
				circle.setOutlineThickness(thick);
			}
			counterTransforming++;
			break;
		}
		case 2:
		{
			setRadius(first_radius);
			circle.setRadius(getRadius());
			if (isSelected())
			{
				circle.setOutlineColor(outColor);
				circle.setOutlineThickness(thick);
			}
			counterTransforming--;
			break;
		}
		default:
			break;
		}
	}
	void restore() override
	{
		circle.setPosition(x, y);
		setColor(fc);
		circle.setFillColor(getColor());
		setRadius(first_radius);
		circle.setRadius(getRadius());
		counterHiding = 1, counterTransforming = 1;
	}
	void draw(RenderWindow& window) override
	{
		window.draw(circle);
	}
	Circle* clone() override
	{
		Circle* circ = new Circle(getRadius(), color, circle.getPosition().x, circle.getPosition().y);
		return circ;
	}
};