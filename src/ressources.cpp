/*
Copyright (C) - Jean-Sébastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "ressource.h"
#include "error.h"

Ressources::Ressources()
	: widthSprite(47), heightSprite(47), m_mask(204, 102, 255), m_rng(static_cast<unsigned int>(std::time(nullptr))) {
	//Trying to load ressources, otherwise throw an exception
	if(!m_texture.loadFromFile("assets/players.bmp")) {
		throw Error("Sprite ressource file not found.\nYou should consider reinstalling the game.");
	} else {
		//Mask the color for sprites
		m_image = m_texture.copyToImage();
		m_image.createMaskFromColor(sf::Color(m_mask));
		m_texture.update(m_image);
	}

	if(!m_itemTexture.loadFromFile("assets/item.bmp")) {
		throw Error("Item ressource file not found.\nYou should consider reinstalling the game.");
	} else {
		//Mask the color
		m_itemImage = m_itemTexture.copyToImage();
		m_itemImage.createMaskFromColor(sf::Color(m_mask));
		m_itemTexture.update(m_itemImage);
	}

	if(!m_sfmlLogo.loadFromFile("assets/sfml-logo.png")) {
		throw Error("SFML Logo file not found.\nYou should consider reinstalling the game.");
	}

	if(!m_font.loadFromFile("assets/TrajanPro-Regular.otf")) {
		throw Error("Font ressource file not found.\nYou should consider reinstalling the game.");
	}
}

sf::Sprite Ressources::aquireBomb() const {
	sf::Sprite bomb;
	bomb.setTexture(m_texture);
	bomb.setTextureRect(sf::IntRect(0, 0, 32, 32));

	return bomb;
}

sf::Sprite Ressources::aquireMine() const {
	sf::Sprite mine;
	mine.setTexture(m_texture);
	mine.setTextureRect(sf::IntRect(32, 0, 32, 32));

	return mine;
}

std::unordered_map<Direction, sf::Sprite> Ressources::aquirePlayer() const {
	std::unordered_map<Direction, sf::Sprite> player;
	player[Up].setTexture(m_texture);
	player[Down].setTexture(m_texture);
	player[Left].setTexture(m_texture);
	player[Right].setTexture(m_texture);

	player[Up].setTextureRect(sf::IntRect(9*widthSprite, 0, widthSprite, heightSprite));
	player[Down].setTextureRect(sf::IntRect(8*widthSprite, 0, widthSprite, heightSprite));
	player[Left].setTextureRect(sf::IntRect(10*widthSprite, 0, widthSprite, heightSprite));
	player[Right].setTextureRect(sf::IntRect(11*widthSprite, 0, widthSprite, heightSprite));

	return player;
}

std::unordered_map<Direction, sf::Sprite> Ressources::aquireBrownFollower() const {
	std::unordered_map<Direction, sf::Sprite> brown;
	brown[Up].setTexture(m_texture);
	brown[Down].setTexture(m_texture);
	brown[Left].setTexture(m_texture);
	brown[Right].setTexture(m_texture);
	
	brown[Down].setTextureRect(sf::IntRect(0*widthSprite, 0, widthSprite, heightSprite));
	brown[Up].setTextureRect(sf::IntRect(1*widthSprite, 0, widthSprite, heightSprite));
	brown[Left].setTextureRect(sf::IntRect(2*widthSprite, 0, widthSprite, heightSprite));
	brown[Right].setTextureRect(sf::IntRect(3*widthSprite, 0, widthSprite, heightSprite));

	return brown;
}

std::unordered_map<Direction, sf::Sprite> Ressources::aquireBlueFollower() const {
	std::unordered_map<Direction, sf::Sprite> blue;
	blue[Up].setTexture(m_texture);
	blue[Down].setTexture(m_texture);
	blue[Left].setTexture(m_texture);
	blue[Right].setTexture(m_texture);
	
	blue[Down].setTextureRect(sf::IntRect(4*widthSprite, 0, widthSprite, heightSprite));
	blue[Up].setTextureRect(sf::IntRect(5*widthSprite, 0, widthSprite, heightSprite));
	blue[Left].setTextureRect(sf::IntRect(6*widthSprite, 0, widthSprite, heightSprite));
	blue[Right].setTextureRect(sf::IntRect(7*widthSprite, 0, widthSprite, heightSprite));

	return blue;
}

sf::Font& Ressources::aquireFont() {
	return m_font;
}

sf::Sprite Ressources::aquirePlayerIcon() const {
	sf::Sprite icon(m_texture);
	icon.setTextureRect(sf::IntRect(8*widthSprite, 0, widthSprite, heightSprite));
	return icon;
}

sf::Sprite Ressources::aquireTombstone() const {
	sf::Sprite tombstone(m_texture);
	tombstone.setTextureRect(sf::IntRect(0*widthSprite, 1*heightSprite, widthSprite, heightSprite));
	return tombstone;
}

sf::Sprite Ressources::aquireDeadTombstone() const {
	sf::Sprite tombstone(m_texture);
	tombstone.setTextureRect(sf::IntRect(1*widthSprite, 1*heightSprite, widthSprite, heightSprite));
	return tombstone;
}

std::mt19937& Ressources::getRNG() {
	return m_rng;
}

std::vector<sf::Sprite> Ressources::aquireZapperInUse() const {
	std::vector<sf::Sprite> zapper(8);
	for(unsigned int i = 0; i < zapper.size(); ++i) {
		zapper.at(i).setTexture(m_itemTexture);
	}
	zapper.at(0).setTextureRect(sf::IntRect(0, 0, widthSprite, heightSprite)); //Corner Top Right
	zapper.at(1).setTextureRect(sf::IntRect(widthSprite*1, 0, widthSprite, heightSprite)); //Above player
	zapper.at(2).setTextureRect(sf::IntRect(0, 0, widthSprite, heightSprite)); //Corner Top Left
	zapper.at(7).setTextureRect(sf::IntRect(widthSprite*1, 0, widthSprite, heightSprite)); //Left Side
	zapper.at(4).setTextureRect(sf::IntRect(0, 0, widthSprite, heightSprite)); //Corner Bottom Right
	zapper.at(3).setTextureRect(sf::IntRect(widthSprite*1, 0, widthSprite, heightSprite)); //Right Side
	zapper.at(6).setTextureRect(sf::IntRect(0, 0, widthSprite, heightSprite)); //Corner Bottom Left
	zapper.at(5).setTextureRect(sf::IntRect(widthSprite*1, 0, widthSprite, heightSprite)); //Under player

	zapper.at(2).rotate(90); //Corner Top right
	zapper.at(7).rotate(270); //Left Side
	zapper.at(4).rotate(180); //Corner Bottom Right
	zapper.at(3).rotate(90); //Right Side
	zapper.at(6).rotate(270); //Corner Bottom left
	zapper.at(5).rotate(180); //Under player
	return zapper;
}

sf::Sprite Ressources::aquireSFMLLogo() const {
	return sf::Sprite(m_sfmlLogo);
}