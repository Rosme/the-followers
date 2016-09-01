/*
Copyright (C) - Jean-S�bastien Fauteux 2014
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <random>

#include "unit.h"

/**
 * Ressource manager that has the different ressources, images, etc.
 **/
class Ressources {
public:
	Ressources();

	std::unordered_map<int, sf::Sprite> aquirePlayer() const; //Get the player Sprites
	std::unordered_map<int, sf::Sprite> aquireBrownFollower() const; //Get the brown sprites
	std::unordered_map<int, sf::Sprite> aquireBlueFollower() const; //Get the blue sprites
	sf::Sprite aquireMine() const; //Get the Mine Sprites
	sf::Sprite aquireBomb() const; //Get the Bomb Sprites
	sf::Sprite aquirePlayerIcon() const; //Get the game icon
	sf::Sprite aquireTombstone() const; //Get the tombstone sprite
	sf::Sprite aquireDeadTombstone() const;
	std::vector<sf::Sprite> aquireZapperInUse() const;
	sf::Sprite aquireSFMLLogo() const;

	sf::Font& aquireFont(); //Font for the game

	std::mt19937& getRNG();

	const int widthSprite, heightSprite; //Width and height sprite
private:
	sf::Image m_image;
	sf::Texture m_texture;
	sf::Image m_itemImage;
	sf::Texture m_itemTexture;
	sf::Texture m_sfmlLogo;
	sf::Font m_font;
	sf::Color m_mask;
	std::mt19937 m_rng;
};

#endif