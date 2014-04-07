/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef ENNEMI_H
#define ENNEMI_H

#include "unit.h"
#include <unordered_map>

//Forward declaration
class Runner;

/**
 * Ennemi class, that inherits from Unit, that puts the minimum for the differents kinds of ennemis
 **/
class Ennemi : public Unit {
public:
	Ennemi(std::shared_ptr<Ressources> ressources, Window& window, Runner& player, float velocity);

	//Going forward to virtual inheritance and pure virtual method -> Abstract Class
	virtual void update(sf::Time delta) = 0;
	virtual void draw() = 0;

protected:
	Runner& m_player; //The player for easier access and possibility to get to him easily
	sf::Clock m_clock;
};

#endif