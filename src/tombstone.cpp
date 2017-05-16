/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "tombstone.h"
#include "ressource.h"
#include "window.h"

Tombstone::Tombstone(Position position, std::shared_ptr<Ressources> ressources, Window& window)
	: Unit(ressources, window, 0.0f, Unit::Tomb) {
		m_position = position;
		m_currentDirection = Immobile;
		m_sprite = m_ressources->aquireTombstone();
		m_sprite.setPosition(m_position);
}

void Tombstone::update(sf::Time delta) {
	//Nothing to update here
}

void Tombstone::draw() {
	m_sfWindow.draw(m_sprite);
}