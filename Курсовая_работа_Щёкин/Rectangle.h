#pragma once
#include "Figure.h"
class Rectangle :public Figure
{
	float width, height, first_height, first_width;
	RectangleShape rectangle;
public:
	Rectangle(float width, float height, Color c, float x, float y) :Figure(x, y, c)
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

	float getX() override
	{
		return rectangle.getPosition().x;
	}
	float getY() override
	{
		return rectangle.getPosition().y;
	}
	float getSize() override
	{
		return (width + height) / 2;
	}
	void setColor(Color c) override
	{
		color = c;
		rectangle.setFillColor(c);
	}
	void setFillColor(Color c) override
	{
		rectangle.setFillColor(c);
	}
	FloatRect getBoundingBox() override {
		return rectangle.getGlobalBounds();
	}
	void setPosition(float x, float y) override
	{
		rectangle.setPosition(x, y);
	}

	void limitMoving(Vector2u size) override
	{
		if (rectangle.getPosition().x + width / 2 >= size.x) rectangle.setPosition(size.x - width / 2, rectangle.getPosition().y);
		if (rectangle.getPosition().x - width / 2 <= 0) rectangle.setPosition(width / 2, rectangle.getPosition().y);
		if (rectangle.getPosition().y + height / 2 >= size.y) rectangle.setPosition(rectangle.getPosition().x, size.y - height / 2);
		if (rectangle.getPosition().y - height / 2 <= 0) rectangle.setPosition(rectangle.getPosition().x, height / 2);
	}
	void hide() override
	{
		switch (counterHiding)
		{
		case 1:
		{
			rectangle.setFillColor(Color::Transparent);
			counterHiding++;
			break;
		}
		case 2:
		{
			rectangle.setFillColor(getColor());
			counterHiding--;
			break;
		}
		default:
			break;
		}
	}
	void move(Keyboard::Key key, float coefOfMoving, float speed = 200) override
	{
		if (Keyboard::isKeyPressed(Keyboard::D)) rectangle.move(1.0f * speed * coefOfMoving, 0.0f);
		if (Keyboard::isKeyPressed(Keyboard::W)) rectangle.move(0.0f, -1.0f * speed * coefOfMoving);
		if (Keyboard::isKeyPressed(Keyboard::A)) rectangle.move(-1.0f * speed * coefOfMoving, 0.0f);
		if (Keyboard::isKeyPressed(Keyboard::S)) rectangle.move(0.0f, 1.0f * speed * coefOfMoving);
	}
	void automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed = 150) override
	{
		switch (part)
		{
		case 0:
		{
			rectangle.move(1.0f * speed * coefOfMoving, 0.0f);
			if (abs(rectangle.getPosition().x - points[part]) <= 10) part++;
			break;
		}
		case 1:
		{
			rectangle.move(-1.0f * speed * coefOfMoving, 0.0f);
			if (abs(rectangle.getPosition().x - points[part]) <= 10) part--;
			break;
		}
		default:
			break;
		}
		limitMoving(window.getSize());
	}
	void transform() override
	{
		switch (counterTransforming)
		{
		case 1:
		{
			width -= 25;
			height -= 25;
			rectangle.setSize(Vector2f(width, height));
			counterTransforming++;
			break;
		}
		case 2:
		{
			width = first_width;
			height = first_height;
			rectangle.setSize(Vector2f(width, height));
			counterTransforming--;
			break;
		}
		default:
			break;
		}
	}
	void restore() override
	{
		rectangle.setPosition(x, y);
		setColor(fc);
		rectangle.setFillColor(getColor());
		width = first_width;
		height = first_height;
		rectangle.setSize(Vector2f(width, height));
		counterHiding = 1, counterTransforming = 1;
	}
	void draw(RenderWindow& window) override
	{
		window.draw(rectangle);
	}
	Rectangle* clone() override
	{
		Rectangle* circ = new Rectangle(width, height, color, rectangle.getPosition().x, rectangle.getPosition().y);
		return circ;
	}
};


