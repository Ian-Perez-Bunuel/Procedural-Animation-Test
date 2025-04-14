#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

class Segment
{
public:
	Segment();
	void setup(int t_size);

	void setPos(sf::Vector2f t_pos) { position = t_pos; }
	void setRot(float t_rotation) { circle.setRotation(t_rotation); }

	sf::Vector2f getPos() { return position; }
	float getRadius() { return radius; }
	float getRotationD() { return circle.getRotation(); }
	float getRotationR() { return (circle.getRotation() * PI / 180.0f); }


	void draw(sf::RenderWindow& t_window);

	void update();

	

private:

	sf::Vector2f position;

	sf::VertexArray joint;

	sf::CircleShape circle;
	float radius = 0.0f;
};

