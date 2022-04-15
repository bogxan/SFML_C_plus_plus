#include"Circle.h"
float Circle::getX()
{
	return circle.getPosition().x;
}
float Circle::getY()
{
	return circle.getPosition().y;
}
float Circle::getSize()
{
	return radius;
}
float Circle::getRadius()
{
	return radius;
}
FloatRect Circle::getBoundingBox() {
	return circle.getGlobalBounds();
}
void Circle::setColor(Color c)
{
	color = c;
	circle.setFillColor(c);
}
void Circle::setFillColor(Color c)
{
	circle.setFillColor(c);
}

void Circle::setRadius(float b)
{
	radius = b;
}
void Circle::setPosition(float x, float y)
{
	circle.setPosition(x, y);
}

void Circle::remove(RenderWindow* window) {
	window->clear();
}
void Circle::limitMoving(Vector2u size)
{
	if (circle.getPosition().x + radius >= size.x) circle.setPosition(size.x - radius, circle.getPosition().y);
	if (circle.getPosition().x - radius <= 0) circle.setPosition(radius, circle.getPosition().y);
	if (circle.getPosition().y + radius >= size.y) circle.setPosition(circle.getPosition().x, size.y - radius);
	if (circle.getPosition().y - radius <= 0) circle.setPosition(circle.getPosition().x, radius);
}
void Circle::hide()
{
	switch (counterHiding)
	{
	case 1:
	{
		circle.setFillColor(Color::Transparent);
		counterHiding++;
		break;
	}
	case 2:
	{
		circle.setFillColor(getColor());
		counterHiding--;
		break;
	}
	default:
		break;
	}
}
void Circle::move(Keyboard::Key key, float coefOfMoving, float speed = 800)
{
	if (Keyboard::isKeyPressed(Keyboard::D)) circle.move(10.0f * speed * coefOfMoving, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::W)) circle.move(0.0f, -10.0f * speed * coefOfMoving);
	if (Keyboard::isKeyPressed(Keyboard::A)) circle.move(-10.0f * speed * coefOfMoving, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::S)) circle.move(0.0f, 10.0f * speed * coefOfMoving);
}
void Circle::automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed = 150)
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
void Circle::transform()
{
	switch (counterTransforming)
	{
	case 1:
	{
		radius -= 25;
		setRadius(radius);
		circle.setRadius(getRadius());
		counterTransforming++;
		break;
	}
	case 2:
	{
		setRadius(first_radius);
		circle.setRadius(getRadius());
		counterTransforming--;
		break;
	}
	default:
		break;
	}
}
void Circle::restore()
{
	circle.setPosition(x, y);
	setColor(fc);
	circle.setFillColor(getColor());
	setRadius(first_radius);
	circle.setRadius(getRadius());
	counterHiding = 1, counterTransforming = 1;
}
void Circle::draw(RenderWindow& window)
{
	window.draw(circle);
}
Circle* Circle::clone()
{
	Circle* circ = new Circle(getRadius(), getColor(), circle.getPosition().x, circle.getPosition().y);
	return circ;
}
string Circle::serialize() {
	string str = "", t = "_";
	str += to_string(tp) + t + to_string(radius) + t + to_string(color.toInteger()) + t + to_string(getX()) + t + to_string(getY()) + "\n";
	return str;
}