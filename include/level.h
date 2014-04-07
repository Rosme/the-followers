/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

class Unit;
class Runner;
class Ressources;
class Window;

typedef std::map<int, Unit*> unit_list;

class Level {
public:
	Level();

	unit_list getLevelUnits(std::shared_ptr<Ressources> ressources, Window& window, Runner& player); //Returns a map of the units of the current level
	int getCurrentLevel() const; ///Return the current level of the game
	bool levelUp(); //Add 1 to the current level
	void setLevel(int l); //Set manually the current level

private:
	//Contains the information of all the units in a level
	struct LevelUnits {
		int nbreBrown;
		int nbreBlue;
	};
	void readLevels(); //Read the levels from an xml file

	int m_currentLevel;
	int m_maxLevel;
	std::vector<LevelUnits> m_levels;
	std::string m_levelFile;
};

#endif