/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "score.h"

#include <pugixml/pugixml.hpp>

Score::Score()
	: m_currentScore(0) { 
		loadHighScore();
}

int Score::getCurrentScore() const {
	return m_currentScore;
}

void Score::addPoints(int n) {
	m_currentScore += n;
}

void Score::reset() {
	m_currentScore = 0;
}

void Score::loadHighScore() {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("score.xml");
	if(result.status == pugi::status_ok) {
		for(pugi::xml_node node = doc.first_child(); node; node = node.next_sibling()) {
			std::string name = node.attribute("player").value();
			std::string score = node.attribute("score").value();
			m_highscore.push_back(std::pair<std::string, int>(name, toInt(score)));
		}
	} else {
		sf::err() << "Error on loading score: " << result.description() << std::endl;
	}
}

void Score::addHighScore(std::string name, int score) {
	m_highscore.push_back(std::pair<std::string, int>(name, score));
	sort();
	saveScore();
}

void Score::saveScore() {
	pugi::xml_document doc;
	for(unsigned int i = 0; i < m_highscore.size(); ++i) {
		std::string fieldName = "h"+toString(i);
		doc.append_child(fieldName.c_str());
		doc.child(fieldName.c_str()).append_attribute("player").set_value(m_highscore.at(i).first.c_str());
		doc.child(fieldName.c_str()).append_attribute("score").set_value(m_highscore.at(i).second);
	}
	doc.save_file("score.xml");
}

HighScore& Score::getHighScore() {
	return m_highscore;
}

void Score::sort() {
	std::sort(m_highscore.begin(), m_highscore.end(), Sorter());
	if(m_highscore.size() > 10)
		m_highscore.erase(m_highscore.begin()+10, m_highscore.end());
}