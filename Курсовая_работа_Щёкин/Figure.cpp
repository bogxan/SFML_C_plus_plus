#include"Figure.h";
bool Figure::isSelected() {
	return selected;
}

void Figure::setSelected(bool sel) {
	selected = sel;
}

int Figure::getCounterHiding()
{
	return counterHiding;
}
int Figure::getCounterTransforming()
{
	return counterTransforming;
}
Color Figure::getColor()
{
	return color;
}