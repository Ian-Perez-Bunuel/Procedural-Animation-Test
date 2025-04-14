#include "Segment.h"

Segment::Segment()
{
	position = { SCREEN_SIZE / 2, SCREEN_SIZE / 2 };
	
	joint.setPrimitiveType(sf::Points);

	circle.setFillColor(sf::Color::White);
	circle.setPosition(position);
}

void Segment::setup(int t_size)
{
	radius = t_size;
	circle.setRadius(radius);
	circle.setOrigin(t_size, t_size);
}

void Segment::draw(sf::RenderWindow& t_window)
{
	t_window.draw(circle);
	t_window.draw(joint);
}

void Segment::update()
{
	joint.clear();


	joint.append(position);
	circle.setPosition(position);

	for (int i = 0; i < joint.getVertexCount(); i++)
	{
		joint[i].color = sf::Color::Blue;
	}
}
