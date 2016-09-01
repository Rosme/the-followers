/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/


#include "eventmanager.h"
#include "runner.h"
#include "ressource.h"
#include "brown.h"
#include "window.h"
#include "level.h"
#include "tombstone.h"
#include "score.h"

#include <algorithm>

EventManager::EventManager(Window& window, std::shared_ptr<Ressources> ressources, Level& level, std::shared_ptr<Score> score)
	: m_window(window), m_playerAlive(true), m_playerPos(0), m_ressources(ressources), m_paused(false), m_sfWindow(window.getSFWindow()), m_level(level), m_nbreEnemies(0), m_score(score), m_joystickId(0) {
	for(int i = 0; i < 8; ++i) {
		if(sf::Joystick::isConnected(i)) {
			m_joystickId = i;
			break;
		}
	}
}

EventManager::~EventManager() {
	std::for_each(m_units.begin(), m_units.end(), Deallocator());
}

void EventManager::handlePlayingEvents() {
	//Managin the global event of the window
	sf::Event event;
	while(m_sfWindow.pollEvent(event)) {
		if(event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
				m_window.setGameStatus(Window::Pause);
				break;
			case sf::Keyboard::T: {
				m_player->useTeleport();
				break;
								  }				
			case sf::Keyboard::Z:
				playerZapper();
				break;
			case sf::Keyboard::F:
				m_window.drawFps();
				break;
			}
		}
	}

	if(sf::Joystick::isButtonPressed(m_joystickId, 0)) {
		m_joystickTeleportPressed = true;
	} else if(sf::Joystick::isButtonPressed(m_joystickId, 1)) {
		m_joystickZapperPressed = true;
	}

	if(m_joystickTeleportPressed && !sf::Joystick::isButtonPressed(m_joystickId, 0)) {
		m_joystickTeleportPressed = false;
		m_player->useTeleport();
	}

	if(m_joystickZapperPressed && !sf::Joystick::isButtonPressed(m_joystickId, 1)) {
		m_joystickZapperPressed = false;
		playerZapper();
	}

	handleBorderCollision();
	handleUnitCollision();
	handleUnitsDeath();

	//Call to update of all units registered
	unit_list::iterator it = m_units.begin();
	sf::Time delta = m_clock.restart();
	for(; it != m_units.end(); ++it) {
		it->second->update(delta);
	}

	if(m_nbreEnemies == 0) {
		newLevel();
	}

	m_window.getFooterMenu().setEnemies(m_nbreEnemies);
	m_window.getFooterMenu().setScore(m_score->getCurrentScore());
}

bool EventManager::isPlayerAlive() const {
	return m_playerAlive;
}

bool EventManager::isPaused() const {
	return m_paused;
}

void EventManager::handleBorderCollision() {
	//Simply verify all units if they are on outside the margin given for the given. If so, we replace them to those margin
	unit_list::iterator it = m_units.begin(), ite = m_units.end();
	for(; it != ite; ++it) {
		Unit* current = it->second;
		Position pos = current->getPosition();
		if(pos.x < 0)
			pos.x = 0;
		if(pos.y < 0)
			pos.y = 0;
		if(pos.x > (m_sfWindow.getSize().x - m_ressources->widthSprite))
			pos.x = m_sfWindow.getSize().x - m_ressources->widthSprite;
		if(pos.y > (m_window.getGameFooterMargin() - m_ressources->heightSprite))
			pos.y = m_window.getGameFooterMargin() - m_ressources->heightSprite;
		current->setPosition(pos);
	}
}

void EventManager::handleUnitCollision() {
	//Handling units between the differents units.
	unit_list::iterator it = m_units.begin(), ite = m_units.end();
	for(;it != ite; ++it) {
		sf::FloatRect currentVerifyBorder = getVerifyMargin(*it->second); //We get the margin to verify for the first one, and the second, etc.

		for(unit_list::iterator sit = m_units.begin(); sit != ite; ++sit) { //We'll check margin of all others units with the first one
			if(it != sit) {
				sf::FloatRect otherVerifyBorder = getVerifyMargin(*sit->second); //Margin for other one
				if(currentVerifyBorder.intersects(otherVerifyBorder)) { //If the margins intersects, we put them for removal
					if(it->first == 0 && sit->second->m_type == Unit::Tomb)
						handleTombstoneCollision(sit->first);
					else if(it->second->m_type != Unit::Tomb) { //If it's not a Tomb(dead) unit, we put it to rest in the toDelete vector
						registerDelete(it->first);
					}
				}
			}
		}

	}

	//And we call the units delete function
	//handleUnitsDelete();
}

sf::FloatRect EventManager::getVerifyMargin(Unit& u) {
	sf::FloatRect verifyBorder; //The border that we'll obtain
	sf::FloatRect currentBorder(u.getPosition(), sf::Vector2f(m_ressources->widthSprite, m_ressources->heightSprite));

	float quarterSizeWidth = m_ressources->widthSprite/4; //To get the quarter of the width
	verifyBorder.left = currentBorder.left+(quarterSizeWidth*2); //Places the X near the middle
	verifyBorder.width = quarterSizeWidth*2; //Width is half the size of widthSprite
	
	float quarterSizeHeight = m_ressources->heightSprite/4; //To get the quarter of the height
	verifyBorder.top = currentBorder.top+(quarterSizeHeight*2); //Places the Y near the middle
	verifyBorder.height = quarterSizeHeight*2; //Height is half the size of heightSprite

	return verifyBorder;
}

void EventManager::registerDelete(int n) {
	m_toDelete.insert(n);
}

void EventManager::playerZapper() {
	std::set<ID> toDelete;
	if(m_player->useZapper()) { //Verification for use of the Zapper, if so, we continue, otherwise nothing to do
		//We want the zapper margin to be 3 times the width and three time the height, and to an x and y at one sprite of the player's position
		sf::FloatRect zapperBorderMargin = m_player->getZapperZone();

		unit_list::iterator it = m_units.begin();
		++it; //By doing this, I remove the player from the verification of intersects
		//No matter what intersects, it is destroyed(Tomb stone as well)
		for(unit_list::iterator ite = m_units.end(); it != ite; ++it) {
			sf::FloatRect otherVerifyBorder = getVerifyMargin(*it->second);
			if(zapperBorderMargin.intersects(otherVerifyBorder)) {
				toDelete.insert(it->first);
			}
		}
	}

	for(std::set<ID>::iterator it = toDelete.begin(); it != toDelete.end(); ++it) {
		ID id = *it;
		if(m_units[id]->m_type != Unit::Tomb) {
			--m_nbreEnemies;
			m_score->addPoints(5);
		}
		delete m_units[id];
		m_units.erase(id);
	}

	m_window.getFooterMenu().setZapper(m_player->getNbreZapper());
}

void EventManager::handleUnitsDeath() {
	//If the player is not found, he's dead
	std::set<ID>::iterator playerIt = m_toDelete.find(0);
	if(playerIt != m_toDelete.end()) {
		m_playerAlive = false;
		return;
	}

	//We sort the Delete set. And we call unique to remove doubles. We don't want to remove twice the same units->Segfault otherwise.
	for(std::set<ID>::iterator it = m_toDelete.begin(); it != m_toDelete.end(); ++it) {
		ID id = *it;
		m_units[m_nbreUnits+1] = new Tombstone(m_units[id]->getPosition(), m_ressources, m_window);
		++m_nbreUnits;
		delete m_units[id];
		m_units.erase(id);
		--m_nbreEnemies;
		m_score->addPoints();
	}

	//We reset the set so it's ready for a new list of ID to delete
	m_toDelete.erase(m_toDelete.begin(), m_toDelete.end());
}

void EventManager::handlePausedEvents() {
	sf::Event event;
	while(m_sfWindow.pollEvent(event)) {
		if(event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
				unpause();
				break;
			case sf::Keyboard::Up:
				m_window.getPauseMenu().changeMenuPosition(PauseMenu::Up);
				break;
			case sf::Keyboard::Down:
				m_window.getPauseMenu().changeMenuPosition(PauseMenu::Down);
				break;
			case sf::Keyboard::Return: {
				PauseMenu::TextMenuPosition pos = m_window.getPauseMenu().getCurrentMenuPosition();
				switch(pos) {
				case PauseMenu::ReturnGame:
					unpause();
					break;
				case PauseMenu::ReturnMain:
					exitGame();
					m_window.setGameStatus(Window::Main);
					break;
				case PauseMenu::End:
					m_window.setGameStatus(Window::Exiting);
					break;
				}
				break;
									   }
			case sf::Keyboard::F:
				m_window.drawFps();
				break;
			}
		}
	}
}

void EventManager::unpause() {
	m_paused = !m_paused;
	m_clock.restart();
	m_window.setGameStatus(Window::Playing);
}

void EventManager::handleMainMenuEvents() {
	sf::Event event;
	while(m_sfWindow.pollEvent(event)) {
		if(event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
			case sf::Keyboard::Escape:
				m_window.setGameStatus(Window::Exiting);
				break;
			case sf::Keyboard::Up:
				m_window.getMainMenu().changeMenuPosition(MainMenu::Up);
				break;
			case sf::Keyboard::Down:
				m_window.getMainMenu().changeMenuPosition(MainMenu::Down);
				break;
			case sf::Keyboard::Return: {
				MainMenu::MenuPosition pos = m_window.getMainMenu().getCurrentMenuPosition();
				switch(pos) {
				case MainMenu::PlayGame:
					newGame();
					m_window.getPauseMenu().reset();
					m_window.setGameStatus(Window::Playing);
					break;
				case MainMenu::Instructions:
					m_window.setGameStatus(Window::Instructions);
					break;
				case MainMenu::Credits:
					m_window.setGameStatus(Window::Credits);
					break;
				case MainMenu::QuitGame:
					m_window.setGameStatus(Window::Exiting);
					break;
				case MainMenu::HighScore:
					m_window.setGameStatus(Window::HighScore);
					break;
				}
				break;
									   }
			case sf::Keyboard::F:
				m_window.drawFps();
				break;
			}
		}
		if (event.type == sf::Event::JoystickButtonReleased) {
			switch (event.joystickButton.button) {
			case 0:
				newGame();
				m_window.getPauseMenu().reset();
				m_window.setGameStatus(Window::Playing);
				break;
			case 1:
				m_window.setGameStatus(Window::Exiting);
				break;
			}
		}
	}
}

void EventManager::newGame() {
	m_playerAlive = true;
	m_player = new Runner(Position(m_window.windowWidth/2-m_ressources->widthSprite/2, m_window.windowHeight/2-m_ressources->heightSprite/2), m_ressources, m_window);
	m_window.registerPlayer(*m_player);
	m_level.setLevel(0);
	m_score->reset();
	m_window.getWinningMenu().reset();
	newLevel();
}


void EventManager::exitGame() {
	for(unit_list::iterator it = m_units.begin(); it != m_units.end(); ++it) {
		if(m_units[it->first])
			delete m_units[it->first];
	}
	m_units.erase(m_units.begin(), m_units.end());
	handleUnitsDeath();
}

void EventManager::handleInstructions() {
	sf::Event event;
	while(m_sfWindow.pollEvent(event)) {
		if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape))
			m_window.setGameStatus(Window::Main);
	}
}

unit_list& EventManager::getUnits() {
	return m_units;
}

void EventManager::newLevel() {
	if(m_level.levelUp()) {
		if(m_units.size() > 0 ) {
			for(unit_list::iterator it = m_units.begin(); it != m_units.end(); ++it) {
				if(it->second->m_type == Unit::Tomb) {
					delete m_units[it->first];
				}
			}
			m_units.erase(m_units.begin(), m_units.end());
		}
		//We reset the set so it's ready for a new list of ID to delete
		m_toDelete.erase(m_toDelete.begin(), m_toDelete.end());

		m_player->addZapper();
		m_units = m_level.getLevelUnits(m_ressources, m_window, *m_player);
		m_nbreEnemies = m_units.size()-1;
		m_nbreUnits = m_units.size();
		m_window.getFooterMenu().setEnemies(m_nbreEnemies);
		m_window.getFooterMenu().setLevel(m_level.getCurrentLevel());
		verifyMobSpawn();
		m_window.getFooterMenu().setZapper(m_player->getNbreZapper());
	} else { //we won
		m_window.getWinningMenu().setScore(m_score->getCurrentScore());
		m_window.setGameStatus(Window::Won);
		//m_window.setGameStatus(Window::Main);
	}
}

void EventManager::verifyMobSpawn() {
	unit_list::iterator it = m_units.begin();
	++it; //we don't want to verify the player's position
	for(unit_list::iterator end = m_units.end(); it != end; ++it) {
		sf::FloatRect borderUnit = sf::FloatRect(it->second->getPosition(), sf::Vector2f(m_ressources->widthSprite, m_ressources->heightSprite));
		while(borderUnit.intersects(m_player->getSafeZone()) || !verifyCorner(it->second)) {
			it->second->setRandomPosition();
			borderUnit.left = it->second->getPosition().x;
			borderUnit.top = it->second->getPosition().y;
		}
	}
}

void EventManager::handleTombstoneCollision(ID tomb) {
	sf::FloatRect player = getVerifyMargin(*m_player), tombstone = getVerifyMargin(*m_units[tomb]);
	switch(m_player->m_currentDirection) {
	case Left:
		m_player->setPosition(Position(m_units[tomb]->getPosition().x+tombstone.width+1, m_player->getPosition().y));
		break;
	case Right:
		m_player->setPosition(Position(m_units[tomb]->getPosition().x-tombstone.width-1, m_player->getPosition().y));
		break;
	case Up:
		m_player->setPosition(Position(m_player->getPosition().x, m_units[tomb]->getPosition().y+tombstone.height+1));
		break;
	case Down:
		m_player->setPosition(Position(m_player->getPosition().x, m_units[tomb]->getPosition().y-tombstone.height-1));
		break;
	}
}

void EventManager::handleGameOver() {
	sf::Event event;
	while(m_sfWindow.pollEvent(event)) {
		if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Return)) {
			m_score->addHighScore(m_window.getGameOverMenu().getName()+"(Died)", m_score->getCurrentScore());
			m_window.getScoreMenu().update();
			m_window.setGameStatus(Window::Main);
		}
		if(event.type == sf::Event::TextEntered)
			m_window.getGameOverMenu().addLetter(event.text.unicode);
		if(event.type == sf::Event::JoystickButtonReleased) {
			m_score->addHighScore(m_window.getGameOverMenu().getName() + "(Died)", m_score->getCurrentScore());
			m_window.getScoreMenu().update();
			m_window.setGameStatus(Window::Main);
		}
	}
}

void EventManager::handleWinning() {
	sf::Event event;
	while(m_sfWindow.pollEvent(event)) {
		if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Return)) {
			m_score->addHighScore(m_window.getWinningMenu().getName()+"(Survived)", m_score->getCurrentScore());
			m_window.getScoreMenu().update();
			m_window.setGameStatus(Window::Main);
		}
		if(event.type == sf::Event::TextEntered)
			m_window.getWinningMenu().addLetter(event.text.unicode);
		if (event.type == sf::Event::JoystickButtonReleased) {
			m_score->addHighScore(m_window.getGameOverMenu().getName() + "(Died)", m_score->getCurrentScore());
			m_window.getScoreMenu().update();
			m_window.setGameStatus(Window::Main);
		}
	}
}

bool EventManager::verifyCorner(Unit* u) {
	if(u->getPosition().x == 0 && u->getPosition().y == 0)
		return false;
	if(u->getPosition().x == 0 && u->getPosition().y >= (m_window.getPlayableArea().height-m_ressources->heightSprite))
		return false;
	if(u->getPosition().x >= (m_window.getPlayableArea().width-m_ressources->widthSprite) && u->getPosition().y == 0)
		return false;
	if(u->getPosition().x >= (m_window.getPlayableArea().width-m_ressources->widthSprite) && u->getPosition().y >= (m_window.getPlayableArea().height-m_ressources->heightSprite))
		return false;
	return true;
}