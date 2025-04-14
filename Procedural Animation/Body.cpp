#include "Body.h"

Body::Body()
{
	outline.setPrimitiveType(sf::LineStrip);
	spine.setPrimitiveType(sf::LineStrip);
}

void Body::setup(Segment t_segments[], int t_jointAmount, int t_partSizes[])
{
	jointAmount = t_jointAmount;

	for (int i = 0; i < jointAmount; i++)
	{
		segments[i] = t_segments[i];

		segmentSizes[i] = t_partSizes[i];
		segments[i].setup(t_partSizes[i]);
	}

	distBetweenJoints = getAvg(jointAmount, segmentSizes);
}

void Body::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < jointAmount; i++)
	{
		// segments[i].draw(t_window);
		t_window.draw(outline);
		t_window.draw(spine);
	}
}

void Body::move()
{
	sf::Vector2f movement = { 0.0f, 0.0f };
	int speed = 10;

	switch (direction)
	{
	case Direction::None:
		break;

	case Direction::Up:
		movement.y = -speed;
		break;

	case Direction::Down:
		movement.y = speed;
		break;

	case Direction::Left:
		movement.x = -speed;
		break;

	case Direction::Right:
		movement.x = speed;
		break;
	}
	headPosition += movement;
	segments[0].setPos(headPosition);

	for (int i = 0; i < jointAmount; i++)
	{
		sf::Vector2f newPos;
		sf::Vector2f vectorBetweenPoints;


		vectorBetweenPoints = vectorBetweenAB(segments[i].getPos(), segments[i + 1].getPos());

		newPos = scaleVectorLenght(segments[i].getPos(), segments[i + 1].getPos(), vectorBetweenPoints, distBetweenJoints);

		segments[i + 1].setPos(newPos);

		// Update to new positions
		segments[i].update();

		rotateToMouse();

	}

	makeSpine();
	findBodyOutline();
}

void Body::checkDirection()
{
	direction = Direction::None;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = Direction::Up;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = Direction::Down;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = Direction::Left;
		move();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = Direction::Right;
		move();
	}
}

void Body::findBodyOutline()
{
	sf::Vector2f edgePoint;
	float angleWanted = 90.0f * PI / 180;
	float headExtra = 45.0f * PI / 180;
	float tailExtra = 135.0f * PI / 180;
	float topPoint = 180.0f * PI / 180;

	outline.clear();

	// Right Side
	for (int i = 0; i < jointAmount; i++)
	{
		if (i == 0)
		{
			// Top point
			edgePoint.x = segments[0].getPos().x + segments[i].getRadius() * cos((segments[i].getRotationR()) + PI / 2.0f);
			edgePoint.y = segments[0].getPos().y + segments[i].getRadius() * sin((segments[i].getRotationR()) + PI / 2.0f);
			outline.append(edgePoint);


			// Middle point Right
			edgePoint.x = segments[i].getPos().x + segments[i].getRadius() * cos((segments[i].getRotationR() + headExtra) + PI / 2.0f);
			edgePoint.y = segments[i].getPos().y + segments[i].getRadius() * sin((segments[i].getRotationR() + headExtra) + PI / 2.0f);

			outline.append(edgePoint);
		}

		// Calculate the right
		edgePoint.x = segments[i].getPos().x + segments[i].getRadius() * cos((segments[i].getRotationR() + angleWanted) + PI / 2.0f);
		edgePoint.y = segments[i].getPos().y + segments[i].getRadius() * sin((segments[i].getRotationR() + angleWanted) + PI / 2.0f);

		outline.append(edgePoint);

		// End point
		if (i == jointAmount - 1)
		{
			// Extra point on right
			edgePoint.x = segments[i].getPos().x + segments[i].getRadius() * cos((segments[i].getRotationR() + tailExtra) + PI / 2.0f);
			edgePoint.y = segments[i].getPos().y + segments[i].getRadius() * sin((segments[i].getRotationR() + tailExtra) + PI / 2.0f);

			outline.append(edgePoint);

			// Extra point on middle
			edgePoint.x = segments[i].getPos().x + segments[i].getRadius() * cos((segments[i].getRotationR() - topPoint) + PI / 2.0f);
			edgePoint.y = segments[i].getPos().y + segments[i].getRadius() * sin((segments[i].getRotationR() - topPoint) + PI / 2.0f);
			
			outline.append(edgePoint);

			// Extra point on left
			edgePoint.x = segments[i].getPos().x + segments[i].getRadius() * cos((segments[i].getRotationR() - tailExtra) + PI / 2.0f);
			edgePoint.y = segments[i].getPos().y + segments[i].getRadius() * sin((segments[i].getRotationR() - tailExtra) + PI / 2.0f);

			outline.append(edgePoint);
		}

	}

	// Left Side
	for (int i = jointAmount - 1; i >= 0; i--)
	{
		// Calculate the right
		edgePoint.x = segments[i].getPos().x + segments[i].getRadius() * cos((segments[i].getRotationR() - angleWanted) + PI / 2.0f);
		edgePoint.y = segments[i].getPos().y + segments[i].getRadius() * sin((segments[i].getRotationR() - angleWanted) + PI / 2.0f);


		outline.append(edgePoint);
	}

	// Connect it back arount
	edgePoint.x = segments[0].getPos().x + segments[0].getRadius() * cos((segments[0].getRotationR() - headExtra) + PI / 2.0f);
	edgePoint.y = segments[0].getPos().y + segments[0].getRadius() * sin((segments[0].getRotationR() - headExtra) + PI / 2.0f);
	outline.append(edgePoint);
	// Top point
	edgePoint.x = segments[0].getPos().x + segments[0].getRadius() * cos((segments[0].getRotationR()) + PI / 2.0f);
	edgePoint.y = segments[0].getPos().y + segments[0].getRadius() * sin((segments[0].getRotationR()) + PI / 2.0f);
	outline.append(edgePoint);

	// Set color of outline
	for (int i = 0; i < outline.getVertexCount(); i++)
	{
		outline[i].color = sf::Color::Magenta;
	}


	
}

void Body::makeSpine()
{
	spine.clear();

	for (int i = 0; i < jointAmount; i++)
	{
		spine.append(segments[i].getPos());
	}

	// Set color of spine
	for (int i = 0; i < spine.getVertexCount(); i++)
	{
		spine[i].color = sf::Color::Blue;
	}
}

void Body::rotateToMouse()
{
	for (int i = 0; i < jointAmount; i++)
	{
		// Calculate the direction from the object to the mouse
		float dx = segments[i + 1].getPos().x - segments[i].getPos().x;
		float dy = segments[i + 1].getPos().y - segments[i].getPos().y;

		// Calculate the angle in degrees
		float angle = std::atan2(dy, dx) * 180 / 3.14159265;

		// Set the rotation of the rectangle
		segments[i].setRot(angle + 90);
	}
}




float Body::angleBetweenAB(sf::Vector2f t_a, sf::Vector2f t_b)
{
	return atan2(t_b.y - t_a.y, t_b.x - t_a.x) * (180 / PI);
}

sf::Vector2f Body::scaleVectorLenght(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, sf::Vector2f t_vecBetweenPoints, int t_distance)
{
	float angle = atan2f(t_vecBetweenPoints.y, t_vecBetweenPoints.x);

	// Calculate the total length of the line
	float totalLength = vectorLenght(t_startPoint.x, t_startPoint.y, t_endPoint.x, t_endPoint.y);

	// Calculate the ratio of the desired length to the total length of the line
	float ratio = t_distance / totalLength;

	// Calculate the coordinates of the point at the desired length along the line
	float newX = t_startPoint.x + ratio * (t_endPoint.x - t_startPoint.x);
	float newY = t_startPoint.y + ratio * (t_endPoint.y - t_startPoint.y);

	return { newX, newY };
}

sf::Vector2f Body::changeAngleMadeAB(sf::Vector2f t_vectorChanged, sf::Vector2f t_connectedVector, float t_desiredAngle)
{
	// Calculate the original angle
	float originalAngle = angleBetweenAB(t_vectorChanged, t_connectedVector);

	
	float newAngle;
	// Calculate the new angle by adding the desired angle
	if (originalAngle > 0)
	{
		newAngle = originalAngle - t_desiredAngle;
	}
	else
	{
		newAngle = originalAngle + t_desiredAngle;
	}


	// Calculate the magnitude of vector b
	float magnitude = vectorLenght(t_vectorChanged, t_connectedVector);

	// Calculate new coordinates based on the new angle
	sf::Vector2f newVector;
	newVector.x = t_vectorChanged.x + magnitude * std::cos(newAngle);
	newVector.y = t_vectorChanged.y + magnitude * std::sin(newAngle);

	return newVector;
}

float Body::getAvg(int t_amount, int t_data[])
{
	int addedUp = 0;

	for (int i = 0; i < t_amount; i++)
	{
		addedUp += t_data[i];
	}

	return addedUp / t_amount;
}
