#include "to_include.hpp"



Information::Information() :
	sus(1 / (Game::get_nbAmogusAlive()-1)),
	alive(true)
{}