/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef RUNNER_H
#define RUNNER_H

#include <string>
#include <unordered_map>

#include "unit.h"
#include "timer.h"

//Forward Declaration
class Mine;

/**
 * Inheritance from unit. Represent the player.
 **/
class Runner : public Unit {
public:
	Runner(Position position, std::shared_ptr<Ressources> ressources, Window& window);

	void update(sf::Time delta);
	void draw();

	bool useZapper(); //Returns true if it can use the zapper, and lower the number of zapp left by one. Returns false otherwise
	Mine* useMine(); //Returns a new mine to put on the map
	//Bomb* useBomb(); //Not yet implemented

	void addZapper(int qte = 1);
	void addMine(int qte = 1);
	//void addBomb(int qte = 1);

	void useTeleport(); //Teleport the player to a random position in the window
	int getNbreZapper() const; //Return the number of zapper
	void setZapper(int n); //Set a specific number of zapper

	sf::FloatRect getSafeZone(); //Returns a safe zone around the player where no mob can spawn
	sf::FloatRect getZapperZone(); //Return a zone for the zapper effect

private:
	int m_qteZapper;
	int m_qteMine;
	/*int m_qteBomb;*/
	std::unordered_map<Direction, sf::Sprite> m_sprite;
	std::vector<sf::Sprite> m_zapperSprite;
	unsigned int m_currentZapSprite;
	Timer m_timer;
	bool m_drawZapper;
};

#endif