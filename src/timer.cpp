/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "timer.h"

//Watch
Watch::Watch(bool initRunning)
	: m_running(initRunning) { }

sf::Time Watch::getElapsedTime() const {
	if(m_running)
		return m_clock.getElapsedTime();
	return m_buffer;
}

bool Watch::isRunning() const {
	return m_running;
}

void Watch::start() {
	if(!m_running) {
		m_running = true;
		m_clock.restart();
	}
}

void Watch::stop() {
	if(!m_running) {
		m_buffer += m_clock.getElapsedTime();
		m_running = false;
	}
}

void Watch::restart(bool keepRunning) {
	m_buffer = sf::Time::Zero;
	m_running = keepRunning;
	m_clock.restart();
}

//Timer
Timer::Timer() { }

Timer::Timer(sf::Time timeLimit, bool initRunning)
	: m_clock(initRunning), m_timeLimit(timeLimit) {
}

Timer::~Timer() { }

sf::Time Timer::getRemainingTime() const {
	return std::max((m_timeLimit - m_clock.getElapsedTime()), sf::Time::Zero);
}

bool Timer::isRunning() const {
	return (m_clock.isRunning() && !isExpired());
}

bool Timer::isExpired() const {
	return (m_clock.getElapsedTime() > m_timeLimit);
}

void Timer::start() {
	m_clock.start();
}

void Timer::stop() {
	m_clock.stop();
}

void Timer::restart(sf::Time timeLimit, bool keepRunning) {
	m_timeLimit = timeLimit;
	m_clock.restart(keepRunning);
}

void Timer::restart(bool keepRunning) {
	m_clock.restart(keepRunning);
}