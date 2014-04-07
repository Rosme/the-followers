/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef TOMBSTONE_H
#define TOMBSTONE_H

#include "unit.h"

class Tombstone : public Unit {
public:
	Tombstone(Position position, std::shared_ptr<Ressources> ressources, Window& window);

	void draw();
	void update(sf::Time delta);

private:
	sf::Sprite m_sprite;
};

#endif