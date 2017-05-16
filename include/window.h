/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to
Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "ressource.h"
#include "menu.h"

//Typedef
typedef std::map<int, Unit*> unit_list;
typedef sf::FloatRect GameArea;

//Forward declaration
class Unit;
class Runner;
class EventManager;
class Score;

//Class that manage what is shown on the screen
class Window {
public:
	//Enum for the different possibility of where the main view is
	enum Status {
		Main,
		Pause,
		Playing,
		Exiting,
		Instructions,
		Won,
		GameOver,
		Credits,
		HighScore
	};
	//Public constant of window
	const int windowWidth,
		windowHeight,
		gameFooterHeight;
	Window();

	sf::RenderWindow& getSFWindow(); //Returns the SFWindow
	Status getGameStatus() const;
	void setGameStatus(Status s);
	int getGameFooterMargin();
	GameArea getPlayableArea() const;
	void draw();
	void registerRessources(std::shared_ptr<Ressources> ressources);
	PauseMenu& getPauseMenu();
	void endGame();
	void registerPlayer(Runner& player);
	MainMenu& getMainMenu();
	void drawFps();
	FooterMenu& getFooterMenu();
	void registerEvents(std::shared_ptr<EventManager> eventManager);
	GameOverMenu& getGameOverMenu();
	void registerScore(std::shared_ptr<Score> score);
	ScoreMenu& getScoreMenu();
	WinningMenu& getWinningMenu();

private:
	void loadMenus();
	void drawUnits();
	void drawPauseMenu();
	void drawMainMenu();
	void drawInstructions();
	void drawGameOver();
	void drawCredits();
	void drawScore();
	void drawWinning();

	sf::RenderWindow m_sfWindow;
	Status m_gameStatus;
	//Ressources* m_ressources;
	std::shared_ptr<Ressources> m_ressources;
	std::unique_ptr<PauseMenu> m_pauseMenu;
	std::unique_ptr<FooterMenu> m_footerMenu;
	std::unique_ptr<MainMenu> m_mainMenu;
	std::unique_ptr<InstructionMenu> m_instructionMenu;
	std::unique_ptr<GameOverMenu> m_gameOverMenu;
	std::unique_ptr<CreditsMenu> m_creditsMenu;
	std::unique_ptr<ScoreMenu> m_scoreMenu;
	std::unique_ptr<WinningMenu> m_winMenu;
	sf::Clock m_fpsClock;
	sf::Font m_fpsFont;
	std::unique_ptr<sf::Text> m_fpsText;
	Runner* m_player;
	bool m_drawFps;
	std::shared_ptr<EventManager> m_eventManager;
	std::shared_ptr<Score> m_score;
};

#endif