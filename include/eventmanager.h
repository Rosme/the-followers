/*
Copyright (C) - Jean-S�bastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <set>
#include <memory>

#include "unit.h"

//Typedef to determine the player ID
typedef int ID;
//Typedef for Unit list
typedef std::map<ID, Unit*> unit_list;

//Forward declaration
class Ressources;
class Window;
class Level;
class Runner;
class Score;

/**
 * Event manager class that verify collision, and the use of events.
 **/
class EventManager {
public:
	EventManager(Window& window, std::shared_ptr<Ressources> ressources, Level& level, std::shared_ptr<Score> score);
	~EventManager();

	void handlePlayingEvents(); //Handle the events while the game is playing
	bool isPlayerAlive() const; //Verification of the player's status
	bool isPaused() const; //Returned if the game is paused
	void handlePausedEvents(); //Handle events while the game is paused
	void handleMainMenuEvents(); //Handle events of the main menu
	//void registerPlayer(Runner& player); //Register the player
	void exitGame(); //Manage what's happening on exiting the game
	void handleInstructions(); //Handle events while on instructions screen
	unit_list& getUnits(); //Return a reference to the units
	void handleGameOver();
	void handleWinning();

private:
	void handleBorderCollision(); //Collision from the side of the game
	void handleUnitCollision(); //Collision betweens units
	void registerDelete(int n); //Register the id of a Unit for future removal
	void playerZapper(); //Handle the player zapper use
	void handleUnitsDeath(); //Remove the units from the game
	void unpause(); //Unpause
	void newGame(); //Start a new game
	void newLevel(); //Start a new level
	void verifyMobSpawn(); //Make sur no mob spawn on us or in the safe zone
	void handleTombstoneCollision(ID tomb); //Collision between the player and tombstone
	bool verifyCorner(Unit* u);

	//Returns the rect of the margin to verify
	sf::FloatRect getVerifyMargin(Unit& u);

	Window& m_window;
	sf::RenderWindow& m_sfWindow;
	bool m_playerAlive;
	unit_list m_units;
	const int m_playerPos;
	std::shared_ptr<Ressources> m_ressources; 
	std::set<ID> m_toDelete; //Contains the list of id's units to remove
	bool m_paused;
	sf::Clock m_clock;
	Level& m_level;
	Runner* m_player;
	int m_nbreEnemies,
		m_nbreUnits;
	std::shared_ptr<Score> m_score;
	unsigned int m_joystickId;
	bool m_joystickTeleportPressed,
		 m_joystickZapperPressed;

	struct Deallocator {
		void operator()(const std::pair<int, Unit*>& p) const {
			delete p.second;
		}
	};
};

#endif