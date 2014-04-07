/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/


#include "unit.h"
#include "ressource.h"
#include "window.h"

Unit::Unit(std::shared_ptr<Ressources> ressources, Window& window, float velocity, Type type)
	: m_ressources(ressources), m_window(window), m_currentDirection(Immobile), m_velocity(velocity), m_type(type), m_sfWindow(window.getSFWindow()) {
		GameArea ga = m_window.getPlayableArea();
		ga.width -= ressources->widthSprite;
		ga.height -= ressources->heightSprite;
		std::uniform_int_distribution<> tempX(ga.left, ga.width);
		m_xDistribution = tempX;
		std::uniform_int_distribution<> tempY(ga.top, ga.height);
		m_yDistribution = tempY;
}

Unit::~Unit() {

}

Position& Unit::getPosition() {
	return m_position;
}

void Unit::setPosition(Position const position) {
	m_position = position;
}

Position Unit::getRandomPosition() {	
	//return Position(rand()%m_window.windowWidth+1, rand()%(m_window.windowHeight-m_window.gameFooterHeight)+1);
	return Position(m_xDistribution(m_ressources->getRNG()), m_yDistribution(m_ressources->getRNG()));
}

void Unit::setRandomPosition() {
	m_position = getRandomPosition();
}