/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "window.h"
#include "unit.h"
#include "runner.h"
#include "eventmanager.h"
#include "score.h"
#include <algorithm>

Window::Window()
	: windowWidth(800), windowHeight(800), gameFooterHeight(100), m_gameStatus(Main), m_drawFps(false) { 
		m_sfWindow.create(sf::VideoMode(
			std::min(sf::VideoMode::getDesktopMode().width, (unsigned)windowWidth),
			std::min(sf::VideoMode::getDesktopMode().height, (unsigned)windowHeight),
			32), "The Followers", sf::Style::Resize);
		m_sfWindow.setFramerateLimit(60);
		m_fpsFont.loadFromFile("assets/version.otf");
		m_fpsText = std::unique_ptr<sf::Text>(new sf::Text("FPS: ", m_fpsFont));
		m_fpsText->setCharacterSize(20);
		m_fpsText->setPosition(385, 0);
}

sf::RenderWindow& Window::getSFWindow() {
	return m_sfWindow;
}

Window::Status Window::getGameStatus() const {
	return m_gameStatus;
}

int Window::getGameFooterMargin() {
	return windowHeight - gameFooterHeight;
}

void Window::setGameStatus(Status s) {
	m_gameStatus = s;
}

void Window::registerRessources(std::shared_ptr<Ressources> ressources) {
	m_ressources = ressources;
	loadMenus(); //Load menus now that we have the ressources
}

void Window::draw() {
	switch(m_gameStatus) {
	case Main:
		drawMainMenu();
		break;
	case Playing:
		drawUnits();
		break;
	case Pause:
		drawUnits();
		drawPauseMenu();
		break;
	case Instructions:
		drawMainMenu();
		drawInstructions();
		break;
	case GameOver:
		drawUnits();
		drawGameOver();
		break;
	case Credits:
		drawMainMenu();
		drawCredits();
		break;
	case HighScore:
		drawMainMenu();
		drawScore();
		break;
	case Won:
		drawUnits();
		drawWinning();
		break;
	}

	if(m_drawFps) {
		m_fpsText->setString("FPS: " + toString(static_cast<int>(1.f/m_fpsClock.restart().asSeconds())));
		m_sfWindow.draw(*m_fpsText);
	}
}

void Window::drawUnits() {
	for(unit_list::iterator it = m_eventManager->getUnits().begin(); it != m_eventManager->getUnits().end(); ++it) {
		it->second->draw();
	}

	sf::Sprite footer(m_footerMenu->getTexture().getTexture());
	footer.setPosition(0, getGameFooterMargin());
	m_sfWindow.draw(footer);
}

void Window::drawPauseMenu() {
	sf::Sprite menu(m_pauseMenu->getTexture().getTexture()); //Use the texture of the sf::RenderTexture from pauseMenu
	menu.setPosition(windowWidth/2 - menu.getTexture()->getSize().x/2, windowHeight/2 - menu.getTexture()->getSize().y/2); //Central position
	
	m_sfWindow.draw(menu);
}

PauseMenu& Window::getPauseMenu() {
	return *m_pauseMenu;
}

void Window::endGame() {
	m_sfWindow.close();
}

void Window::registerPlayer(Runner& player) {
	m_player = &player;
}

void Window::drawMainMenu() {
	sf::Sprite menu(m_mainMenu->getTexture().getTexture());
	menu.setPosition(0, 0);

	m_sfWindow.draw(menu);
}

MainMenu& Window::getMainMenu() {
	return *m_mainMenu;
}

void Window::drawFps() {
	m_drawFps = !m_drawFps;
}

void Window::drawInstructions() {
	sf::Sprite instruc(m_instructionMenu->getTexture().getTexture());
	instruc.setPosition(windowWidth/2-instruc.getTextureRect().width/2, windowHeight/2-instruc.getTextureRect().height/2);

	m_sfWindow.draw(instruc);
}

GameArea Window::getPlayableArea() const {
	return GameArea(0, 0, windowWidth, windowHeight-gameFooterHeight);
}

FooterMenu& Window::getFooterMenu() {
	return *m_footerMenu;
}

void Window::drawGameOver() {
	sf::Sprite gameOver(m_gameOverMenu->getGameOverTexture().getTexture());
	gameOver.setPosition(windowWidth/2-gameOver.getTexture()->getSize().x/2, windowHeight/2-gameOver.getTexture()->getSize().y/2);

	sf::Sprite background(m_gameOverMenu->getBackgroundTexture().getTexture());
	background.setPosition(0, 0);

	m_sfWindow.draw(background);
	m_sfWindow.draw(gameOver);
}

void Window::loadMenus() {
	m_pauseMenu = std::unique_ptr<PauseMenu>(new PauseMenu(m_ressources->aquireFont()));
	m_footerMenu = std::unique_ptr<FooterMenu>(new FooterMenu(m_ressources->aquireFont(), windowWidth, gameFooterHeight));
	m_mainMenu = std::unique_ptr<MainMenu>(new MainMenu(m_ressources->aquireFont(), windowWidth, windowHeight, m_ressources->aquirePlayerIcon()));
	m_instructionMenu = std::unique_ptr<InstructionMenu>(new InstructionMenu(m_ressources->aquireFont(), 550, 280));
	m_gameOverMenu = std::unique_ptr<GameOverMenu>(new GameOverMenu(m_ressources->aquireFont(), 425, 150, windowWidth, windowHeight, m_ressources->aquireDeadTombstone()));
	m_creditsMenu = std::unique_ptr<CreditsMenu>(new CreditsMenu(m_ressources->aquireFont(), 315, 315, m_ressources->aquireSFMLLogo()));
	m_scoreMenu = std::unique_ptr<ScoreMenu>(new ScoreMenu(m_ressources->aquireFont(), m_score, 400, 600));
	m_winMenu = std::unique_ptr<WinningMenu>(new WinningMenu(m_ressources->aquireFont(), 425, 150, windowWidth, windowHeight));
}

void Window::registerEvents(std::shared_ptr<EventManager> eventManager) {
	m_eventManager = eventManager;
}

void Window::drawCredits() {
	sf::Sprite credits(m_creditsMenu->getTexture().getTexture());
	credits.setPosition(windowWidth/2-credits.getTextureRect().width/2, windowHeight/2-credits.getTextureRect().height/2);

	m_sfWindow.draw(credits);
}

GameOverMenu& Window::getGameOverMenu() {
	return *m_gameOverMenu;
}

void Window::registerScore(std::shared_ptr<Score> score) {
	m_score = score;
}

void Window::drawScore() {
	sf::Sprite score(m_scoreMenu->getTexture().getTexture());
	score.setPosition(windowWidth/2-score.getTextureRect().width/2, windowHeight/2-score.getTextureRect().height/2);

	m_sfWindow.draw(score);
}

ScoreMenu& Window::getScoreMenu() {
	return *m_scoreMenu;
}

void Window::drawWinning() {
	sf::Sprite winning(m_winMenu->getTexture().getTexture());
	winning.setPosition(windowWidth/2-winning.getTextureRect().width/2, windowHeight/2-winning.getTextureRect().height/2);

	sf::Sprite background(m_winMenu->getBackground().getTexture());
	background.setPosition(0, 0);

	m_sfWindow.draw(background);
	m_sfWindow.draw(winning);
}

WinningMenu& Window::getWinningMenu() {
	return *m_winMenu;
}