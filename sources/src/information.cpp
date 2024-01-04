#include "to_include.hpp"



Information::Information() :
	sus(1 / Game::get_nbAmogusAlive()),
	alive(true),
	deathPos(-1, -1)
{}