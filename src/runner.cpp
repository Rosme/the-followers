/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/


#include "runner.h"
#include "ressource.h"
#include "mine.h"
#include "window.h"

Runner::Runner(Position position, std::shared_ptr<Ressources> ressources, Window& window)
	: Unit(ressources, window, 0.1f, Alive), m_qteZapper(0), m_qteMine(0), m_timer(sf::milliseconds(10)), m_drawZapper(false), m_currentZapSprite(0), m_joystickId(0) {

	m_sprite = ressources->aquirePlayer();
	m_currentDirection = Down; //Default position is down
	m_position = position;

	//Set position of all sprite
	for(std::unordered_map<int, sf::Sprite>::iterator it = m_sprite.begin(); it != m_sprite.end(); ++it) {
		it->second.setPosition(position);
	}

	m_zapperSprite = m_ressources->aquireZapperInUse();

	for(int i = 0; i < 8; ++i) {
		if(sf::Joystick::isConnected(i)) {
			m_joystickId = i;
			break;
		}
	}
}

void Runner::update(sf::Time delta) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::getAxisPosition(m_joystickId, sf::Joystick::X) < -15) {
		m_currentDirection = Left;
		m_position.x -= m_velocity*delta.asMilliseconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::getAxisPosition(m_joystickId, sf::Joystick::X) > 15) {
		m_currentDirection = Right;
		m_position.x += m_velocity*delta.asMilliseconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::getAxisPosition(m_joystickId, sf::Joystick::Y) > 15) {
		m_currentDirection = Down;
		m_position.y += m_velocity*delta.asMilliseconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::getAxisPosition(m_joystickId, sf::Joystick::Y) < -15) {
		m_currentDirection = Up;
		m_position.y -= m_velocity*delta.asMilliseconds();
	}

	//Reset the position to the new
	for(std::unordered_map<int, sf::Sprite>::iterator it = m_sprite.begin(); it != m_sprite.end(); ++it) {
		it->second.setPosition(m_position);
	}

	if(m_drawZapper) {
		//hard coded, dislike this, might change it later
		m_zapperSprite.at(0).setPosition(m_position.x-m_ressources->widthSprite, m_position.y-m_ressources->heightSprite); //Top Left Corner
		m_zapperSprite.at(1).setPosition(m_position.x, m_position.y-m_ressources->heightSprite); //Above player
		m_zapperSprite.at(2).setPosition(m_position.x+(m_ressources->widthSprite*2), m_position.y-m_ressources->heightSprite); //Top Right Corner
		m_zapperSprite.at(7).setPosition(m_position.x-m_ressources->widthSprite, m_position.y+m_ressources->heightSprite); //Left of player
		m_zapperSprite.at(4).setPosition(m_position.x+(m_ressources->widthSprite*2), m_position.y+(m_ressources->heightSprite*2)); //Bottom Right Corner
		m_zapperSprite.at(3).setPosition(m_position.x+(m_ressources->widthSprite*2), m_position.y); //Right of player
		m_zapperSprite.at(6).setPosition(m_position.x-m_ressources->widthSprite, m_position.y+(m_ressources->heightSprite*2)); //Bottom left Corner
		m_zapperSprite.at(5).setPosition(m_position.x+m_ressources->widthSprite, m_position.y+(m_ressources->heightSprite*2)); //Under player
	}
	if(m_drawZapper) {
		if(m_timer.isExpired()) {
			++m_currentZapSprite;
			m_timer.restart(true);
		}
		if(m_currentZapSprite >= m_zapperSprite.size()) {
			m_drawZapper = false;
			m_currentZapSprite = 0;
		}
	}
}

void Runner::draw() {
	if(m_drawZapper) {
		if(m_currentZapSprite < m_zapperSprite.size())
			m_sfWindow.draw(m_zapperSprite.at(m_currentZapSprite));
	}
	m_sfWindow.draw(m_sprite[m_currentDirection]);
}

bool Runner::useZapper() {
	if(m_qteZapper > 0) {
		--m_qteZapper;
		m_drawZapper = true;
		m_timer.restart(true);
		return true;
	} else
		return false;
}

Mine* Runner::useMine() {
	if(m_qteMine > 0) {
		--m_qteMine;
		return new Mine(m_position, m_ressources, m_window);
	} else
		return nullptr;
}

//Bomb* Runner::useBomb() {
//	if(m_qteBomb > 0) {
//		--m_qteBomb;
//		return new Bomb(m_position, m_ressources, m_window);
//	} else
//		return nullptr;
//}

void Runner::addZapper(int qte) {
	m_qteZapper += qte;
}

void Runner::addMine(int qte) {
	m_qteMine += qte;
}

//void Runner::addBomb(int qte) {
//	m_qteBomb += qte;
//}

void Runner::useTeleport() {
	m_position = getRandomPosition();
}

int Runner::getNbreZapper() const {
	return m_qteZapper;
}

void Runner::setZapper(int n) {
	m_qteZapper = n;
}

sf::FloatRect Runner::getSafeZone() {
	return sf::FloatRect(m_position.x-(m_ressources->widthSprite*3), m_position.y-(m_ressources->heightSprite*3), m_ressources->widthSprite*6, m_ressources->heightSprite*6);
}

sf::FloatRect Runner::getZapperZone() {
	return sf::FloatRect(m_position.x-m_ressources->widthSprite, m_position.y-m_ressources->heightSprite, m_ressources->widthSprite*3, m_ressources->heightSprite*3);
}