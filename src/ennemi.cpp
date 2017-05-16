/*
Copyright (C) - Jean-Sébastien Fauteux 2017
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include "ennemi.h"
#include "runner.h"
#include "window.h"

Ennemi::Ennemi(std::shared_ptr<Ressources> ressources, Window& window, Runner& player, float velocity)
	: Unit(ressources, window, velocity, Alive), m_player(player) {
}



