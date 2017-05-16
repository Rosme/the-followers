/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to
Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
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