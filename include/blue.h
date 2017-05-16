/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to 
Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef BLUE_H
#define BLUE_H

#include "ennemi.h"

class Blue : public Ennemi {
public:
	Blue(std::shared_ptr<Ressources> ressources, Window& window, Runner& player);

	void update(sf::Time delta);
	void draw();

private:
	std::unordered_map<int, sf::Sprite> m_sprite;
};

#endif