#ifndef DEF_INFORAMTION
#define DEF_INFORAMTION

#include "to_include.hpp"

/// @brief mémoire d'un crewmate vers un autre amogus
struct Information{
	/// @brief taux de suspition envers l'amogus concerné [0, 1]
	float sus;
	bool alive;
	Information();
};

#endif