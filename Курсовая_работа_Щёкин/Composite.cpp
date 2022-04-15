#include"Composite.h";
float Composite::getX()
{
	return composites[0]->getX();
}
float Composite::getY()
{
	return composites[0]->getY();
}
float Composite::getSize()
{
	return composites[0]->getSize();
}
FloatRect Composite::getBoundingBox() {
	return composites[0]->getBoundingBox();
}
void Composite::setColor(Color c)
{
	color = c;
	for (int i = 0; i < composites.size(); i++) composites[i]->setColor(c);
}
void Composite::setFillColor(Color c)
{
	for (int i = 0; i < composites.size(); i++) composites[i]->setFillColor(c);
}
void Composite::setPosition(float x, float y)
{
	for (int i = 0; i < composites.size(); i++) composites[i]->setPosition(x, y);
}
void Composite::pushBack(Figure* fig)
{
	composites.push_back(fig);
}
void Composite::clear()
{
	composites.clear();
}
void Composite::limitMoving(Vector2u size)
{
	for (int i = 0; i < composites.size(); i++) composites[i]->limitMoving(size);
}
void Composite::remove(RenderWindow* window) {
	for (int i = 0; i < composites.size(); i++) {
		composites[i]->remove(window);
	}
}
void Composite::hide()
{
	switch (counterHiding)
	{
	case 1:
	{
		for (int i = 0; i < composites.size(); i++) {
			composites[i]->setFillColor(Color::Transparent);
		}
		counterHiding++;
		break;
	}
	case 2:
	{
		for (int i = 0; i < composites.size(); i++) {
			composites[i]->setFillColor(composites[i]->getColor());
		}
		counterHiding--;
		break;
	}
	default:
		break;
	}
}
void Composite::move(Keyboard::Key key, float coefOfMoving, float speed = 200)
{
	for (int i = 0; i < composites.size(); i++) composites[i]->move(key, coefOfMoving ,speed);
}
void Composite::automove(int& part, int points[2], RenderWindow& window, float coefOfMoving, int speed = 150)
{
	for (int i = 0; i < composites.size(); i++) composites[i]->automove(part, points, window, coefOfMoving, speed);
	limitMoving(window.getSize());
}
void Composite::transform()
{
	switch (counterTransforming)
	{
	case 1:
	{
		for (int i = 0; i < composites.size(); i++) {
			composites[i]->transform();
		}
		counterTransforming++;
		break;
	}
	case 2:
	{
		for (int i = 0; i < composites.size(); i++) {
			composites[i]->transform();
		}
		counterTransforming--;
		break;
	}
	default:
		break;
	}
}
void Composite::restore()
{
	for (int i = 0; i < composites.size(); i++)
	{
		composites[i]->restore();
	}
}
void Composite::draw(RenderWindow& window)
{
	for (int i = 0; i < composites.size(); i++) composites[i]->draw(window);
}
Composite* Composite::clone()
{
	Composite* comp = new Composite(composites[0]->getColor(), composites[0]->getX(), composites[0]->getY());
	for (int i = 0; i < composites.size(); i++) comp->pushBack(composites[i]->clone());
	return comp;
}
string Composite::serialize() {
	string str, t = "_";
	str += to_string(tp) + t + to_string(composites.size()) + '\n';

	for (int i = 0; i < composites.size(); i++)
	{
		str += composites[i]->serialize();
	}
	return str;
}