/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "brown.h"
#include "ressource.h"
#include "runner.h"
#include "window.h"

Brown::Brown(std::shared_ptr<Ressources> ressources, Window& window, Runner& player)
	: Ennemi(ressources, window, player, 0.08f) {
		m_sprite = ressources->aquireBrownFollower();
		m_currentDirection = Down;
		m_position = getRandomPosition();

		//Set all the sprites to the right position
		for(std::unordered_map<int, sf::Sprite>::iterator it = m_sprite.begin(); it != m_sprite.end(); ++it) {
			it->second.setPosition(m_position);
		}
}

void Brown::update(sf::Time delta) {
	//sf::Time delta = m_clock.restart();//Restart the clock and get the time. Use for position moving
	Position playerPos = m_player.getPosition();
	
	/**
	 * Algorithm to find the player and go in it's direction.
	 * The -1 and +1 is to give a margin with the float so the units aren't jumping all the time
	 **/
	if(playerPos.x < m_position.x-1) { 
		m_position.x -= m_velocity*delta.asMilliseconds();
		m_currentDirection = Left;
	}
	else if(playerPos.x > m_position.x+1) {
		m_position.x += m_velocity*delta.asMilliseconds();
		m_currentDirection = Right;
	}

	if(playerPos.y < m_position.y-1) {
		m_position.y -= m_velocity*delta.asMilliseconds();
		m_currentDirection = Up;
	}
	else if(playerPos.y > m_position.y+1) {
		m_position.y += m_velocity*delta.asMilliseconds();
		m_currentDirection = Down;
	}

	//Set all sprite to the new position
	for(std::unordered_map<int, sf::Sprite>::iterator it = m_sprite.begin(); it != m_sprite.end(); ++it) {
		it->second.setPosition(m_position);
	}
}

void Brown::draw() { 
	m_sfWindow.draw(m_sprite[m_currentDirection]); //Drawing the current Sprite
}