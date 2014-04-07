/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef WATCH_H
#define WATCH_H

#include <SFML/System.hpp>

//Watch class that can be stop and restart
class Watch {
public:
	Watch(bool initRunning = false);

	sf::Time getElapsedTime() const;
	bool isRunning() const;
	void start();
	void stop();
	void restart(bool keepRunning = false);

private:
	sf::Clock m_clock;
	sf::Time m_buffer;
	bool m_running;
};

//Timer class using a watch
class Timer {
public:
	Timer();
	Timer(sf::Time timeLimit, bool initRunning = false);

	~Timer(); //Could be inherit for other timer

	sf::Time getRemainingTime() const;

	bool isRunning() const;
	bool isExpired() const;
	void start();
	void stop();
	void restart(sf::Time timeLimit, bool keepRunning = false);
	void restart(bool keepRunning = false);

private:
	Watch m_clock;
	sf::Time m_timeLimit;
};
#endif