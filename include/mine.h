/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to
Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef MINE_H
#define MINE_H

#include "unit.h"

/**
 * Inheritance from Unit. Represents a stable Mine
 **/
class Mine : public Unit {
public:
	Mine(Position position, std::shared_ptr<Ressources> ressources, Window& window);

	//Virtual inheritance
	void update(sf::Time delta);
	void draw();
private:
};

#endif