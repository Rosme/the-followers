/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to
Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef SCORE_H
#define SCORE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>

typedef std::vector<std::pair<std::string, int> > HighScore;

class Score {
public:
	Score();

	int getCurrentScore() const;
	void addPoints(int n = 10);
	void reset();
	void addHighScore(std::string name, int score);
	HighScore& getHighScore();

private:
	void loadHighScore();
	void saveScore();
	void sort();

	int m_currentScore;
	HighScore m_highscore;

	struct Sorter {
		bool operator()(std::pair<std::string, int> i, std::pair<std::string, int> j) {
			return i.second > j.second;
		}
	};

	
	template<class T>
	std::string toString(T t) {
		std::ostringstream oss;
		oss << t;
		return oss.str();
	}

	int toInt(std::string s) {
		std::istringstream iss(s);
		int n;
		iss >> n;
		return n;
	}
};

#endif