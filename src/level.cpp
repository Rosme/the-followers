/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "level.h"
#include "brown.h"
#include "runner.h"
#include "ressource.h"
#include "window.h"
#include "blue.h"

#include <pugixml/pugixml.hpp>
#include <string>
#include <sstream>

int toInt(std::string s) {
	std::istringstream iss(s);
	int n;
	iss >> n;
	return n;
}

Level::Level()
	: m_currentLevel(0), m_levelFile("level.xml") {
	readLevels();
}

unit_list Level::getLevelUnits(std::shared_ptr<Ressources> ressources, Window& window, Runner& player) {
	LevelUnits levelUnits = m_levels.at(m_currentLevel-1);
	unit_list units;
	//Brown generation
	for(int i  = 0; i < levelUnits.nbreBrown; ++i) {
		Brown *brown = new Brown(ressources, window, player);
		units[units.size()+1] = brown;
	}

	//Blue generation
	for(int i = 0; i < levelUnits.nbreBlue; ++i) {
		Blue *blue = new Blue(ressources, window, player);
		units[units.size()+1] = blue;
	}

	units[0] = &player;
	return units;
}

int Level::getCurrentLevel() const {
	return m_currentLevel;
}

bool Level::levelUp() {
	++m_currentLevel;
	if(m_currentLevel > m_maxLevel)
		return false;
	return true;
}

void Level::readLevels() {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("level.xml");

	if(result.status == pugi::status_ok) {
		for(pugi::xml_node node = doc.first_child(); node; node = node.next_sibling()) {
			LevelUnits lvl;
			lvl.nbreBrown = toInt(node.attribute("brown").value());
			lvl.nbreBlue = toInt(node.attribute("blue").value());
			m_levels.push_back(lvl);
		}
	} else {
		sf::err() << result.description() << std::endl;
	}

	m_maxLevel = m_levels.size();
}

void Level::setLevel(int l) {
	m_currentLevel = l;
}