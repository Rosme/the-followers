/*
Copyright (C) - Jean-S�bastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/


#include "mine.h"
#include "window.h"

Mine::Mine(Position position, std::shared_ptr<Ressources> ressources, Window& window)
	: Unit(ressources, window, 0.f, Usable) {
		m_position = position;
}

void Mine::update(sf::Time delta) {
}

void Mine::draw() {
}