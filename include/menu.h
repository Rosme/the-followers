/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <sstream>
#include <vector>

typedef std::unique_ptr<sf::Text> TextPtr;

class PauseMenu {
public:
	enum TextMenuPosition {
		ReturnGame,
		ReturnMain,
		End
	};
	enum MenuDirection {
		Up,
		Down
	};
	PauseMenu(sf::Font& font);

	sf::RenderTexture& getTexture();
	void changeMenuPosition(MenuDirection dir);
	TextMenuPosition getCurrentMenuPosition() const;
	void reset();

private:
	void setIconPosition();

	sf::RenderTexture m_texture;
	sf::Font& m_font;
	TextPtr m_returnGame;
	TextPtr m_returnMain;
	TextPtr m_end;
	sf::ConvexShape m_icon;
	sf::Vector2f m_returnGamePosition[3],
		m_returnMainPosition[3],
		m_endPosition[3];
	TextMenuPosition m_currentMenuPosition;
};


class FooterMenu {
public:
	FooterMenu(sf::Font& font, int width, int height);

	sf::RenderTexture& getTexture();
	void setZapper(int n);
	void setLevel(int n);
	void setEnemies(int n);
	void setScore(int n);
	void reset();

private:
	sf::Font& m_font;
	sf::RenderTexture m_texture;
	TextPtr m_teleportText;
	TextPtr m_zapperText;
	TextPtr m_levelText;
	TextPtr m_enemiesText;
	TextPtr m_scoreText;
	//TextPtr m_mineText;
	sf::RectangleShape m_delimiter;
};

class MainMenu {
public:
	enum MenuPosition {
		PlayGame,
		Instructions,
		HighScore,
		Credits,
		QuitGame
	};
	enum MenuDirection {
		Up,
		Down
	};
	MainMenu(sf::Font& font, int width, int height, sf::Sprite sprite);

	sf::RenderTexture& getTexture();
	void changeMenuPosition(MenuDirection dir);
	MenuPosition getCurrentMenuPosition() const;


private:
	void setIconPosition();
	
	sf::Font& m_font;
	sf::RenderTexture m_texture;
	TextPtr m_playGame;
	TextPtr m_quitGame;
	TextPtr m_instructions;
	TextPtr m_score;
	TextPtr m_credits;
	TextPtr m_title;
	sf::ConvexShape m_icon;
	sf::Vector2f m_playGamePosition[3],
		m_quitGamePosition[3],
		m_instructionsPosition[3],
		m_scorePosition[3],
		m_creditsPosition[3];
	sf::Sprite m_sprite;
	MenuPosition m_currentMenuPosition;
};

class InstructionMenu {
public:
	InstructionMenu(sf::Font& font, int width, int height);

	sf::RenderTexture& getTexture();

private:
	sf::Font& m_font;
	sf::RenderTexture m_texture;
	TextPtr m_text;
};

class GameOverMenu {
public:
	GameOverMenu(sf::Font& font, int widthGO, int heightGO, int widthBack, int heightBack, sf::Sprite tomb);

	void setScore(int n);
	void addLetter(sf::Uint32 letter);
	void reset();
	std::string getName();

	sf::RenderTexture& getGameOverTexture();
	sf::RenderTexture& getBackgroundTexture();

private:
	sf::Font& m_font;
	int m_score;
	int m_widthGO, m_heightGO;
	sf::RenderTexture m_gameOverTexture;
	sf::RenderTexture m_backgroundTexture;
	TextPtr m_text;
	TextPtr m_scoreText;
	TextPtr m_nameText;
	sf::Sprite m_tomb;
};

class CreditsMenu {
public:
	CreditsMenu(sf::Font& font, int width, int height, sf::Sprite sfmlLogo);

	sf::RenderTexture& getTexture();

private:
	sf::Font& m_font;
	sf::RenderTexture m_texture;
	TextPtr m_programmerText;
	TextPtr m_libraryText;
	TextPtr m_thanksText;
	sf::Sprite m_logo;
};

typedef std::vector<std::pair<std::string, int> > HighScore;
class Score;
class ScoreMenu {
public:
	ScoreMenu(sf::Font& font, std::shared_ptr<Score> scores, int width, int height);

	sf::RenderTexture& getTexture();
	void update();

private:
	sf::Font& m_font;
	std::shared_ptr<Score> m_highscore;
	std::vector<TextPtr> m_nameText;
	std::vector<TextPtr> m_scoreText;
	TextPtr m_descriptionText;
	TextPtr m_highestText;
	sf::RenderTexture m_texture;
	int m_width, m_height;
};

class WinningMenu {
public:
	WinningMenu(sf::Font& font, int widthWin, int heightWin, int widthBack, int heightBack);

	sf::RenderTexture& getTexture();
	sf::RenderTexture& getBackground();

	void setScore(int n);
	void addLetter(sf::Uint32 letter);
	void reset();
	std::string getName();

private:
	sf::RenderTexture m_texture;
	sf::RenderTexture m_backgroundTexture;
	sf::Font& m_font;
	TextPtr m_niceText;
	TextPtr m_gratsText;
	TextPtr m_scoreText;
	TextPtr m_nameText;
	int m_widthWin, m_heightWin, m_widthBack, m_heightBack;
};

template<class T>
std::string toString(T n) {
	std::ostringstream oss;
	oss << n;
	return oss.str();
}

#endif