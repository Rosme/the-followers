/*
Copyright (C) - Jean-S�bastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef BROWN_H
#define BROWN_H

#include <unordered_map>

#include "ennemi.h"

//Forward Declaration
class Ressources;
class Runner;

/**
 * Inheritance from Ennemi. The Brown kind of ennemi. Slower than player, dumb as hell
 **/
class Brown : public Ennemi {
public:
	Brown(std::shared_ptr<Ressources> ressources, Window& window, Runner& player);

	//Virtual inheritance
	void update(sf::Time delta);
	void draw();

private:
	std::unordered_map<int, sf::Sprite> m_sprite;
};

#endif