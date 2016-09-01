/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "menu.h"
#include "score.h"

//PauseMenu
PauseMenu::PauseMenu(sf::Font& font)
	: m_font(font), m_icon(3), m_currentMenuPosition(ReturnGame) {
		m_returnGame = TextPtr(new sf::Text("Return to game", m_font));

        m_returnGame->setColor(sf::Color::White);
		m_returnGame->setPosition(18, 10);
		m_returnGame->setCharacterSize(14);

		m_returnMain = TextPtr(new sf::Text("Return to main menu", m_font));
		m_returnMain->setColor(sf::Color::White);
		m_returnMain->setPosition(18, 35);
		m_returnMain->setCharacterSize(14);

		m_end = TextPtr(new sf::Text("End game", m_font));
		m_end->setColor(sf::Color::White);
		m_end->setPosition(18, 60);
		m_end->setCharacterSize(14);

		if(!m_texture.create(205, 90)) {
			sf::err() << "Couldn't create texture for pause menu" << std::endl;
		}

		m_returnGamePosition[0] = sf::Vector2f(8.f, 14.f);
		m_returnGamePosition[1] = sf::Vector2f(8.f, 24.f);
		m_returnGamePosition[2] = sf::Vector2f(14.f, 19.f);

		m_returnMainPosition[0] = sf::Vector2f(8.f, 39.f);
		m_returnMainPosition[1] = sf::Vector2f(8.f, 49.f);
		m_returnMainPosition[2] = sf::Vector2f(14.f, 44.f);

		m_endPosition[0] = sf::Vector2f(8.f, 64.f);
		m_endPosition[1] = sf::Vector2f(8.f, 74.f);
		m_endPosition[2] = sf::Vector2f(14.f, 69.f);

		setIconPosition();
}

sf::RenderTexture& PauseMenu::getTexture() {
	m_texture.clear(sf::Color(50, 50, 50));
	m_texture.draw(*m_returnGame);
	m_texture.draw(*m_returnMain);
	m_texture.draw(*m_end);
	m_texture.draw(m_icon);
	m_texture.display();
	return m_texture;
}

void PauseMenu::changeMenuPosition(MenuDirection dir) {
	if(dir == Up) {
		if(m_currentMenuPosition == ReturnGame)
			m_currentMenuPosition = End;
		else {
			int pos = m_currentMenuPosition;
			--pos;
			m_currentMenuPosition = static_cast<TextMenuPosition>(pos);
		}
	} else {
		if(m_currentMenuPosition == End)
			m_currentMenuPosition = ReturnGame;
		else {
			int pos = m_currentMenuPosition;
			++pos;
			m_currentMenuPosition = static_cast<TextMenuPosition>(pos);
		}
	}
	setIconPosition();
}

void PauseMenu::setIconPosition() {
	switch(m_currentMenuPosition) {
	case ReturnGame:
		m_icon.setPoint(0, m_returnGamePosition[0]);
		m_icon.setPoint(1, m_returnGamePosition[1]);
		m_icon.setPoint(2, m_returnGamePosition[2]);
		break;
	case ReturnMain:
		m_icon.setPoint(0, m_returnMainPosition[0]);
		m_icon.setPoint(1, m_returnMainPosition[1]);
		m_icon.setPoint(2, m_returnMainPosition[2]);
		break;
	case End:
		m_icon.setPoint(0, m_endPosition[0]);
		m_icon.setPoint(1, m_endPosition[1]);
		m_icon.setPoint(2, m_endPosition[2]);
		break;
	}
	m_icon.setFillColor(sf::Color::White);
	m_icon.setOutlineColor(sf::Color::White);
}

PauseMenu::TextMenuPosition PauseMenu::getCurrentMenuPosition() const {
	return m_currentMenuPosition;
}

void PauseMenu::reset() {
	m_currentMenuPosition = ReturnGame;
	setIconPosition();
}

//FooterMenu
FooterMenu::FooterMenu(sf::Font& font, int width, int height)
	: m_font(font), m_delimiter(sf::Vector2f(800, 5)) {
		m_teleportText = TextPtr(new sf::Text("Teleporter(T)", m_font));
		m_teleportText->setCharacterSize(17);
		m_teleportText->setPosition(50, 45);		
		m_teleportText->setColor(sf::Color::White);

		m_zapperText = TextPtr(new sf::Text("Zapper(Z): ", m_font));
		m_zapperText->setCharacterSize(17);
		m_zapperText->setPosition(275, 45);
		m_zapperText->setColor(sf::Color::White);

		m_levelText = TextPtr(new sf::Text("Level: ", m_font));
		m_levelText->setCharacterSize(17);
		m_levelText->setPosition(600, 25);
		m_levelText->setColor(sf::Color::White);

		m_enemiesText = TextPtr(new sf::Text("Enemies left: ", m_font));
		m_enemiesText->setCharacterSize(17);
		m_enemiesText->setPosition(600, 55);
		m_enemiesText->setColor(sf::Color::White);

		m_scoreText = TextPtr(new sf::Text("Score: ", m_font));
		m_scoreText->setCharacterSize(17);
		m_scoreText->setPosition(450, 45);
		m_scoreText->setColor(sf::Color::White);

		if(!m_texture.create(width, height)) {
			sf::err() << "Couldn't create texture for footer menu" << std::endl;
		}

		m_delimiter.setPosition(0, 0);
		m_delimiter.setFillColor(sf::Color(50, 50, 50));
}

void FooterMenu::setZapper(int n) {
	if(n == 0)
		m_zapperText->setColor(sf::Color::Red);
	else
		m_zapperText->setColor(sf::Color::White);

	m_zapperText->setString("Zapper(Z): " + toString(n));
}

sf::RenderTexture& FooterMenu::getTexture() {
	m_texture.clear();
	m_texture.draw(*m_teleportText);
	m_texture.draw(*m_zapperText);
	m_texture.draw(*m_levelText);
	m_texture.draw(*m_enemiesText);
	m_texture.draw(*m_scoreText);
	m_texture.draw(m_delimiter);
	m_texture.display();
	return m_texture;
}

void FooterMenu::setLevel(int n) {
	m_levelText->setString("Level: " + toString(n));
}

void FooterMenu::setEnemies(int n) {
	m_enemiesText->setString("Enemies left: " + toString(n));
}

void FooterMenu::setScore(int n) {
	m_scoreText->setString("Score: " + toString(n));
}

void FooterMenu::reset() {
	m_enemiesText->setString("Enemies left: 0");
	m_zapperText->setString("Zapper(Z): 0");
}

//MainMenu
MainMenu::MainMenu(sf::Font& font, int width, int height, sf::Sprite sprite)
	: m_font(font), m_icon(3), m_currentMenuPosition(PlayGame), m_sprite(sprite) {
		float partHeight = height/6;

		m_playGame = TextPtr(new sf::Text("Play Game", font));
		m_playGame->setPosition(300.f, partHeight);
		m_playGame->setCharacterSize(17);
		m_playGame->setColor(sf::Color::White);
		m_playGame->setStyle(sf::Text::Underlined);

		m_instructions = TextPtr(new sf::Text("Instructions", font));
		m_instructions->setPosition(300.f, partHeight*2);
		m_instructions->setCharacterSize(17);
		m_instructions->setColor(sf::Color::White);
		m_instructions->setStyle(sf::Text::Underlined);

		m_score = TextPtr(new sf::Text("High Score", font));
		m_score->setPosition(300.f, partHeight*3);
		m_score->setCharacterSize(17);
		m_score->setColor(sf::Color::White);
		m_score->setStyle(sf::Text::Underlined);

		m_credits = TextPtr(new sf::Text("Credits", font));
		m_credits->setPosition(300.f, partHeight*4);
		m_credits->setCharacterSize(17);
		m_credits->setColor(sf::Color::White);
		m_credits->setStyle(sf::Text::Underlined);

		m_quitGame = TextPtr(new sf::Text("Quit Game", font));
		m_quitGame->setPosition(300.f, partHeight*5);
		m_quitGame->setCharacterSize(17);
		m_quitGame->setColor(sf::Color::White);
		m_quitGame->setStyle(sf::Text::Underlined);

		m_title = TextPtr(new sf::Text("The Followers", font));
		m_title->setPosition(10.f, 780.f);
		m_title->rotate(-90.f);
		m_title->setCharacterSize(54);
		m_title->setColor(sf::Color::White);

		m_sprite.setPosition(23.f, 275.f);

		if(!m_texture.create(width, height)) {
			sf::err() << "Couldn't create texture for main menu" << std::endl;
		}

		m_playGamePosition[0] = sf::Vector2f(290.f, partHeight+5.f);
		m_playGamePosition[1] = sf::Vector2f(290.f, partHeight+18.f);
		m_playGamePosition[2] = sf::Vector2f(296.f, partHeight+11.5f);

		m_instructionsPosition[0] = sf::Vector2f(290.f, (partHeight*2)+5.f);
		m_instructionsPosition[1] = sf::Vector2f(290.f, (partHeight*2)+18.f);
		m_instructionsPosition[2] = sf::Vector2f(296.f, (partHeight*2)+11.5f);

		m_scorePosition[0] = sf::Vector2f(290.f, (partHeight*3)+5.f);
		m_scorePosition[1] = sf::Vector2f(290.f, (partHeight*3)+18.f);
		m_scorePosition[2] = sf::Vector2f(296.f, (partHeight*3)+11.5f);

		m_creditsPosition[0] = sf::Vector2f(290.f, (partHeight*4)+5.f);
		m_creditsPosition[1] = sf::Vector2f(290.f, (partHeight*4)+18.f);
		m_creditsPosition[2] = sf::Vector2f(296.f, (partHeight*4)+11.5f);

		m_quitGamePosition[0] = sf::Vector2f(290.f, (partHeight*5)+5.f);
		m_quitGamePosition[1] = sf::Vector2f(290.f, (partHeight*5)+18.f);
		m_quitGamePosition[2] = sf::Vector2f(296.f, (partHeight*5)+11.5f);

		setIconPosition();
}

sf::RenderTexture& MainMenu::getTexture() {
	m_texture.clear();
	m_texture.draw(*m_playGame);
	m_texture.draw(*m_instructions);
	m_texture.draw(*m_score);
	m_texture.draw(*m_credits);
	m_texture.draw(*m_quitGame);
	m_texture.draw(*m_title);
	m_texture.draw(m_sprite);
	m_texture.draw(m_icon);
	m_texture.display();
	return m_texture;
}

void MainMenu::setIconPosition() {
	switch(m_currentMenuPosition) {
	case PlayGame:
		m_icon.setPoint(0, m_playGamePosition[0]);
		m_icon.setPoint(1, m_playGamePosition[1]);
		m_icon.setPoint(2, m_playGamePosition[2]);
		break;
	case Instructions:
		m_icon.setPoint(0, m_instructionsPosition[0]);
		m_icon.setPoint(1, m_instructionsPosition[1]);
		m_icon.setPoint(2, m_instructionsPosition[2]);
		break;
	case HighScore:
		m_icon.setPoint(0, m_scorePosition[0]);
		m_icon.setPoint(1, m_scorePosition[1]);
		m_icon.setPoint(2, m_scorePosition[2]);
		break;
	case Credits:
		m_icon.setPoint(0, m_creditsPosition[0]);
		m_icon.setPoint(1, m_creditsPosition[1]);
		m_icon.setPoint(2, m_creditsPosition[2]);
		break;
	case QuitGame:
		m_icon.setPoint(0, m_quitGamePosition[0]);
		m_icon.setPoint(1, m_quitGamePosition[1]);
		m_icon.setPoint(2, m_quitGamePosition[2]);
		break;
	}
	m_icon.setFillColor(sf::Color::White);
}

MainMenu::MenuPosition MainMenu::getCurrentMenuPosition() const {
	return m_currentMenuPosition;
}

void MainMenu::changeMenuPosition(MenuDirection dir) {
	if(dir == Up) {
		if(m_currentMenuPosition == PlayGame)
			m_currentMenuPosition = QuitGame;
		else {
			int pos = m_currentMenuPosition;
			--pos;
			m_currentMenuPosition = static_cast<MenuPosition>(pos);
		}
	} else {
		if(m_currentMenuPosition == QuitGame)
			m_currentMenuPosition = PlayGame;
		else {
			int pos = m_currentMenuPosition;
			++pos;
			m_currentMenuPosition = static_cast<MenuPosition>(pos);
		}
	}
	setIconPosition();
}

//Instruction Menu
InstructionMenu::InstructionMenu(sf::Font& font, int width, int height)
	: m_font(font) {
		m_text = TextPtr(new sf::Text("", m_font));
		m_text->setPosition(0, 0);
		m_text->setCharacterSize(17);
		m_text->setColor(sf::Color::White);
		m_text->setString("Goal: Run away from all enemies and survive.\nYou can kill enemies by making them collide together.\n\nTools:\nTeleporter: Press T to teleport yourself randomly.\nWarning:You may be teleported on a enemy.\n\nZapper: The Zapper destroys everything around you.\nPress Z to use it.\nYou get 1 zapper per level.\n\nHave fun!");

		if(!m_texture.create(width, height)) {
			sf::err() << "Couldn't create texture for Instructions" << std::endl;
		}
}

sf::RenderTexture& InstructionMenu::getTexture() {
	m_texture.clear(sf::Color(50, 50, 50));
	m_texture.draw(*m_text);
	m_texture.display();
	return m_texture;
}

//GameOver Menu
GameOverMenu::GameOverMenu(sf::Font& font, int widthGO, int heightGO, int widthBack, int heightBack, sf::Sprite tomb)
	: m_font(font), m_tomb(tomb), m_score(0), m_widthGO(widthGO), m_heightGO(heightGO) {
		m_text = TextPtr(new sf::Text("", m_font));
		m_text->setCharacterSize(15);
		m_text->setColor(sf::Color::Red);
		m_text->setString("\t\t\t\t\t\tOh noes! You just died.\nThe followers are now feeding upon your body!");
		m_text->setPosition(0, 0);

		m_tomb.setPosition(widthGO/2-m_tomb.getLocalBounds().width/2, 50);

		m_scoreText = TextPtr(new sf::Text("", m_font));
		m_scoreText->setCharacterSize(15);
		m_scoreText->setPosition(widthGO/2-m_scoreText->getLocalBounds().width/2, 100);
		m_scoreText->setColor(sf::Color::White);

		m_nameText = TextPtr(new sf::Text("Type your name", m_font));
		m_nameText->setCharacterSize(20);
		m_nameText->setColor(sf::Color::White);
		m_nameText->setPosition(widthGO/2-m_nameText->getLocalBounds().width/2, 125);

		if(!m_gameOverTexture.create(widthGO, heightGO)) {
			sf::err() << "Couldn't create texture for GameOver" << std::endl;
		}

		if(!m_backgroundTexture.create(widthBack, heightBack)) {
			sf::err() << "Couldn't create texture for red screen" << std::endl;
		}
}

sf::RenderTexture& GameOverMenu::getGameOverTexture() {
	m_gameOverTexture.clear();
	m_gameOverTexture.draw(*m_text);
	m_gameOverTexture.draw(m_tomb);
	m_gameOverTexture.draw(*m_scoreText);
	m_gameOverTexture.draw(*m_nameText);
	m_gameOverTexture.display();
	return m_gameOverTexture;
}

sf::RenderTexture& GameOverMenu::getBackgroundTexture() {
	m_backgroundTexture.clear(sf::Color(255, 0, 0, 128));
	m_backgroundTexture.display();
	return m_backgroundTexture;
}

void GameOverMenu::setScore(int n) {
	m_score = n;
	m_scoreText->setString("Your final score is " + toString(n));
	m_scoreText->setPosition(m_widthGO/2-m_scoreText->getLocalBounds().width/2, 100);
}

void GameOverMenu::addLetter(sf::Uint32 letter) {
	if(m_nameText->getString() == "Type your name")
		m_nameText->setString("");
	if(letter == 8) {
		sf::String current = m_nameText->getString();
		if(current.getSize() > 0) {
			current.erase(current.getSize()-1);
			m_nameText->setString(current);
		}
	} else {
		if(letter != 13 || letter != 27)
			m_nameText->setString(m_nameText->getString() + letter);
	}
	if(m_nameText->getString() == "")
		m_nameText->setString("Type your name");
	m_nameText->setPosition(m_widthGO/2-m_nameText->getLocalBounds().width/2, 125);
}

void GameOverMenu::reset() {
	m_nameText->setString("Type your name");
	m_nameText->setPosition(m_widthGO/2-m_nameText->getLocalBounds().width/2, 125);
}

std::string GameOverMenu::getName() {
	std::string name = m_nameText->getString().toAnsiString();
	if(name == "Type your name")
		return "Emelio Estevez";
	else
		return name;
}

//Credits Menu
CreditsMenu::CreditsMenu(sf::Font& font, int width, int height, sf::Sprite sfmlLogo)
	: m_font(font), m_logo(sfmlLogo) {
		m_programmerText = TextPtr(new sf::Text("Programming/Graphics:\nRosme", m_font));
		m_programmerText->setCharacterSize(17);
		m_programmerText->setColor(sf::Color::White);
		m_programmerText->setPosition(10, 10);

		m_thanksText = TextPtr(new sf::Text("Special thanks to:\nReplix and Redyz\nFor their help and ideas!", m_font));
		m_thanksText->setCharacterSize(17);
		m_thanksText->setColor(sf::Color::White);
		m_thanksText->setPosition(10, 90);

		m_libraryText = TextPtr(new sf::Text("Using SFML 2.0 RC", m_font));
		m_libraryText->setCharacterSize(17);
		m_libraryText->setColor(sf::Color::White);
		m_libraryText->setPosition(10, 190);

		m_logo.setPosition(10, 215);

		if(!m_texture.create(width, height)) {
			sf::err() << "Couldn't create texture for credits" << std::endl;
		}
}

sf::RenderTexture& CreditsMenu::getTexture() {
	m_texture.clear(sf::Color(50, 50, 50));
	m_texture.draw(*m_programmerText);
	m_texture.draw(*m_thanksText);
	m_texture.draw(*m_libraryText);
	m_texture.draw(m_logo);
	m_texture.display();
	return m_texture;
}

//Score Menu
ScoreMenu::ScoreMenu(sf::Font& font, std::shared_ptr<Score> scores, int width, int height)
	: m_font(font), m_highscore(scores), m_width(width), m_height(height) {
		m_descriptionText = TextPtr(new sf::Text("HighScore", m_font));
		m_descriptionText->setCharacterSize(20);
		m_descriptionText->setColor(sf::Color::White);
		m_descriptionText->setPosition(width/2-m_descriptionText->getLocalBounds().width/2, 0);

		m_highestText = TextPtr(new sf::Text("(Only the 10 highest are kept)", m_font));
		m_highestText->setCharacterSize(12);
		m_highestText->setColor(sf::Color::White);
		m_highestText->setPosition(width/2-m_highestText->getLocalBounds().width/2, m_descriptionText->getLocalBounds().top+m_descriptionText->getLocalBounds().height);

		if(!m_texture.create(width, height)) {
			sf::err() << "Couldn't create texture for HighScore Menu" << std::endl;
		}
		update();
}

sf::RenderTexture& ScoreMenu::getTexture() {
	m_texture.clear(sf::Color(50, 50, 50));
	m_texture.draw(*m_descriptionText);
	m_texture.draw(*m_highestText);
	for(unsigned int i = 0; i < m_scoreText.size(); ++i) {
		m_texture.draw(*m_scoreText.at(i));
	}
	for(unsigned int i = 0; i < m_nameText.size(); ++i) {
		m_texture.draw(*m_nameText.at(i));
	}
	m_texture.display();
	return m_texture;
}

void ScoreMenu::update() {
	//UGLY HACK
	m_nameText.erase(m_nameText.begin(), m_nameText.end());
	m_scoreText.erase(m_scoreText.begin(), m_scoreText.end());
	int height = m_height - 50;
	int seperation = height/11;
	HighScore& highscore = m_highscore->getHighScore();
	for(unsigned int i = 0; i < highscore.size(); ++i) {
		TextPtr name = TextPtr(new sf::Text(highscore.at(i).first, m_font, 17));
		name->setPosition(m_width/4, (seperation*(i+1)));
		m_nameText.push_back(std::move(name));
		TextPtr score = TextPtr(new sf::Text(toString(highscore.at(i).second), m_font, 17));
		score->setPosition((m_width/4)*3, (seperation*(i+1)));
		m_scoreText.push_back(std::move(score));
	}
}

//Winning Menu
WinningMenu::WinningMenu(sf::Font& font, int widthWin, int heightWin, int widthBack, int heightBack)
	: m_font(font), m_widthWin(widthWin), m_heightWin(heightWin), m_widthBack(widthBack), m_heightBack(heightBack) {
		m_niceText = TextPtr(new sf::Text("Nice Job!", m_font, 17));
		m_niceText->setColor(sf::Color::White);
		m_niceText->setPosition(widthWin/2-m_niceText->getLocalBounds().width/2, 0);

		m_gratsText = TextPtr(new sf::Text("You've survived to all the followers!", m_font, 17));
		m_gratsText->setColor(sf::Color::White);
		m_gratsText->setPosition(widthWin/2-m_gratsText->getLocalBounds().width/2, m_niceText->getLocalBounds().height);

		m_scoreText = TextPtr(new sf::Text("Your final score is: ", m_font, 17));
		m_scoreText->setColor(sf::Color::White);
		m_scoreText->setPosition(widthWin/2-m_scoreText->getLocalBounds().width/2, 75);

		m_nameText = TextPtr(new sf::Text("Type your name", m_font, 20));
		m_nameText->setColor(sf::Color::White);
		m_nameText->setPosition(widthWin/2-m_nameText->getLocalBounds().width/2, 95);

		if(!m_texture.create(widthWin, heightWin)) {
			sf::err() << "Couldn't create texture for winning menu" << std::endl;
		}

		if(!m_backgroundTexture.create(widthBack, heightBack)) {
			sf::err() << "Couldn't create texture for background winning" << std::endl;
		}
}

sf::RenderTexture& WinningMenu::getTexture() {
	m_texture.clear();
	m_texture.draw(*m_niceText);
	m_texture.draw(*m_gratsText);
	m_texture.draw(*m_scoreText);
	m_texture.draw(*m_nameText);
	m_texture.display();
	return m_texture;
}

sf::RenderTexture& WinningMenu::getBackground() {
	m_backgroundTexture.clear(sf::Color(183, 183, 183, 128));
	m_backgroundTexture.display();
	return m_backgroundTexture;
}

void WinningMenu::setScore(int n) {
	m_scoreText->setString("Your final score is: " + toString(n));
	m_scoreText->setPosition(m_widthWin/2-m_scoreText->getLocalBounds().width/2, 75);
}

void WinningMenu::addLetter(sf::Uint32 letter) {
	if(m_nameText->getString() == "Type your name")
		m_nameText->setString("");
	if(letter == 8) {
		sf::String current = m_nameText->getString();
		if(current.getSize() > 0) {
			current.erase(current.getSize()-1);
			m_nameText->setString(current);
		}
	} else {
		if(letter != 13 || letter != 27)
			m_nameText->setString(m_nameText->getString() + letter);
	}
	if(m_nameText->getString() == "")
		m_nameText->setString("Type your name");
	m_nameText->setPosition(m_widthWin/2-m_nameText->getLocalBounds().width/2, 95);
}

void WinningMenu::reset() {
	m_nameText->setString("Type your name");
	m_nameText->setPosition(m_widthWin/2-m_nameText->getLocalBounds().width/2, 95);
}

std::string WinningMenu::getName() {
	std::string name = m_nameText->getString().toAnsiString();
	if(name == "Type your name")
		return "Emelio Estevez";
	else
		return name;
}
