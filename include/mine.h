/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
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