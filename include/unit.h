/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>

//For easier use of position
typedef sf::Vector2f Position;

//The different direction of a sprite. Immobile is for non-mobile unit such as Mine, bomb, etc.
enum Direction {
	Up,
	Down,
	Left,
	Right,
	Immobile
};

//Forward Declaration
class Ressources;
class Window;

/**
 * Unit class. Must be inherited by all unit class.
 **/
class Unit {
public:
	//Type of units
	enum Type {
		Alive, //Living units
		Usable, //Objects units
		Tomb //Dead units
	};

	Unit(std::shared_ptr<Ressources> ressources, Window& window, float velocity, Type type);
	virtual ~Unit();

	Position& getPosition(); //Get the current position of the unit
	void setPosition(Position const position); //Set the unit position
	void setRandomPosition(); //Generate a random position

	//Virtual inheritance. Pure Virtual -> Abstract class
	virtual void update(sf::Time delta) = 0;
	virtual void draw() = 0;

	//Freely accessible of the class
	Direction m_currentDirection; //current Direction of the player(immobile in case of most objects)
	const Type m_type; //The type of units it is.

protected:
	Position getRandomPosition();

	Position m_position;
	std::shared_ptr<Ressources> m_ressources;
	Window& m_window;
	sf::RenderWindow& m_sfWindow;
	float m_velocity;
	std::uniform_int_distribution<> m_xDistribution,
		m_yDistribution;
};

#endif