#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Segment.h"
#include "Globals.h"


enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};


class Body
{
public:
	Body();
	void setup(Segment t_segments[], int t_jointAmount, int t_partSizes[]);

	void draw(sf::RenderWindow& t_window);

	void move();
	void checkDirection();

	void findBodyOutline();
	void makeSpine();

	void rotateToMouse();

private:
	
	Direction direction;
	sf::Vector2f headPosition;
	Segment segments[MAX_JOINTS];
	int segmentSizes[MAX_JOINTS];
	int jointAmount = 0;

	// Drawing Structure
	sf::VertexArray outline;
	sf::VertexArray spine;

	int distBetweenJoints = 35;
	int angleDiffenceMaxD = 45;
	float angleDiffenceMaxR = angleDiffenceMaxD * 180 / PI;


	// Equations
	sf::Vector2f vectorBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b) { return (t_b - t_a); }
	float angleBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b);
	float vectorLenght(float ax, float ay, float bx, float by) { return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); }
	float vectorLenght(sf::Vector2f t_a, sf::Vector2f t_b) { return (sqrt((t_b.x - t_a.x) * (t_b.x - t_a.x) + (t_b.y - t_a.y) * (t_b.y - t_a.y))); }
	float vectorDotProduct(sf::Vector2f t_v0, sf::Vector2f t_v1) { return t_v0.x * t_v1.x + t_v0.y * t_v1.y; }
	float vectorCrossProduct(sf::Vector2f t_v0, sf::Vector2f t_v1) { return t_v0.x * t_v1.y - t_v0.y * t_v1.x; }

	sf::Vector2f scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance);
	sf::Vector2f changeAngleMadeAB(sf::Vector2f t_vectorChanged, sf::Vector2f t_connectedVector, float t_desiredAngle);
	float getAvg(int t_amount, int t_data[]);

};

