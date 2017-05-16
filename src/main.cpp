/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "runner.h"
#include "ressource.h"
#include "error.h"
#include "brown.h"
#include "eventmanager.h"
#include "level.h"
#include "window.h"
#include "score.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main() {
	Window window;

	std::ofstream file("game-log.txt", std::ios::app);
	sf::err().rdbuf(file.rdbuf());

	bool hadError = false;

	sf::Font fontError;
	fontError.loadFromFile("assets/TrajanPro-Regular.otf");
	sf::Text errorText("", fontError);
	errorText.setCharacterSize(20);

	std::shared_ptr<Ressources> ressources;

	try {
		ressources = std::shared_ptr<Ressources>(new Ressources());
	} catch(Error const& e) {
		hadError = true;
		sf::err() << e.what() << std::endl;
		errorText.setString(e.what());
		errorText.setPosition(window.getSFWindow().getSize().x/2 - errorText.getLocalBounds().width / 2, window.getSFWindow().getSize().y / 2 - errorText.getLocalBounds().height / 2);
	}

	//If there was an error with the ressources, we show the error message
	if(hadError) {
		while(window.getSFWindow().isOpen()) {
			sf::Event event;
			while(window.getSFWindow().pollEvent(event)) {
				if(event.type == sf::Event::Closed)
					window.endGame();
				if(event.type == sf::Event::KeyPressed)
					window.endGame();
			}
			window.getSFWindow().clear();

			window.getSFWindow().draw(errorText);

			window.getSFWindow().display();
		}
	}

	std::shared_ptr<Score> score = std::shared_ptr<Score>(new Score());
	window.registerScore(score);
	window.registerRessources(ressources);
	Level lvl;
	std::shared_ptr<EventManager> eventManager = std::shared_ptr<EventManager>(new EventManager(window, ressources, lvl, score));
	window.registerEvents(eventManager);
	while(window.getSFWindow().isOpen()) {
			
		switch(window.getGameStatus()) {
		case Window::Playing:
			if(eventManager->isPlayerAlive()) {
				eventManager->handlePlayingEvents();
			} else {
				eventManager->exitGame();
				window.getFooterMenu().reset();
				window.setGameStatus(Window::GameOver);
				window.getGameOverMenu().reset();
				window.getGameOverMenu().setScore(score->getCurrentScore());
			}
			break;
		case Window::Pause:
			eventManager->handlePausedEvents();
			break;
		case Window::Exiting:
			window.endGame();
			break;
		case Window::Main:
			eventManager->handleMainMenuEvents();
			break;
		case Window::Instructions:
		case Window::Credits:
		case Window::HighScore:
			eventManager->handleInstructions();
			break;
		case Window::GameOver:
			eventManager->handleGameOver();
			break;
		case Window::Won:
			eventManager->handleWinning();
			break;
		}
		window.getSFWindow().clear();
		window.draw();


		window.getSFWindow().display();
	}

	return (hadError) ? EXIT_FAILURE : EXIT_SUCCESS;
}