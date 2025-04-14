/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Body.h"
#include "Segment.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processMouseMove(sf::Event t_event);
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupObject();

	sf::RenderWindow window; // main SFML window
	bool m_exitGame; // control exiting game

	// Mouse info
	sf::Vector2f mousePos;

	// Creatures
	Body creature;
	Segment creatureJoints[TEST_JOINTS];
	int creaturePartsSizes[TEST_JOINTS] = { 50, 45, 40, 45, 30, 25, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
};

#endif // !GAME_HPP

