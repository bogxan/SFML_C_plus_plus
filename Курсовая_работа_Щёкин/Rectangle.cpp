#include"Rectangle.h";
float My_Rectangle::getX()
{
	return rectangle.getPosition().x;
}
float My_Rectangle::getY()
{
	return rectangle.getPosition().y;
}
float My_Rectangle::getSize()
{
	return (width + height) / 2;
}
void My_Rectangle::setColor(Color c)
{
	color = c;
	rectangle.setFillColor(c);
}
void My_Rectangle::setFillColor(Color c)
{
	rectangle.setFillColor(c);
}
FloatRect My_Rectangle::getBoundingBox() {
	return rectangle.getGlobalBounds();
}
void My_Rectangle::setPosition(float x, float y)
{
	rectangle.setPosition(x, y);
}

void My_Rectangle::remove(RenderWindow* window) {
	window->clear();
}
void My_Rectangle::limitMoving(Vector2u size)
{
	if (rectangle.getPosition().x + width / 2 >= size.x) rectangle.setPosition(size.x - width / 2, rectangle.getPosition().y);
	if (rectangle.getPosition().x - width / 2 <= 0) rectangle.setPosition(width / 2, rectangle.getPosition().y);
	if (rectangle.getPosition().y + height / 2 >= size.y) rectangle.setPosition(rectangle.getPosition().x, size.y - height / 2);
	if (rectangle.getPosition().y - height / 2 <= 0) rectangle.setPosition(rectangle.getPosition().x, height / 2);
}
void My_Rectangle::hide()
{
	Color outColor = rectangle.getOutlineColor();
	float thick = rectangle.getOutlineThickness();
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
void My_Rectangle::move(Keyboard::Key key, float coefOfMoving, float speed = 800)
{
	if (Keyboard::isKeyPressed(Keyboard::D)) rectangle.move(10.0f * speed * coefOfMoving, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::W)) rectangle.move(0.0f, -10.0f * speed * coefOfMoving);
	if (Keyboard::isKeyPressed(Keyboard::A)) rectangle.move(-10.0f * speed * coefOfMoving, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::S)) rectangle.move(0.0f, 10.0f * speed * coefOfMoving);
}
void My_Rectangle::automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed = 150)
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
void My_Rectangle::transform()
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
void My_Rectangle::restore()
{
	rectangle.setPosition(x, y);
	setColor(fc);
	rectangle.setFillColor(getColor());
	width = first_width;
	height = first_height;
	rectangle.setSize(Vector2f(width, height));
	counterHiding = 1, counterTransforming = 1;
}
void My_Rectangle::draw(RenderWindow& window)
{
	window.draw(rectangle);
}
My_Rectangle* My_Rectangle::clone()
{
	My_Rectangle* circ = new My_Rectangle(width, height, getColor(), rectangle.getPosition().x, rectangle.getPosition().y);
	return circ;
}
string My_Rectangle::serialize() {
	string str = "", t = "_";
	str += to_string(tp) + t + to_string(width) + t + to_string(height) + t + to_string(color.toInteger()) + t + to_string(getX()) + t + to_string(getY()) + "\n";
	return str;
}