//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// Ñâÿçü ñî ìíîé:		https://vk.com/zombihello
// Ğåïîçèòîğèé äâèæêà:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LIGHTMAP_H
#define LIGHTMAP_H

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../Level/Level.h"

class Lightmap
{
public:
	/* ÈÍÈÖÈÀËÈÇÈĞÎÂÀÒÜ ÈÍÔÎĞÌÀÖÈŞ ÄËß ÏĞÎÑ×ÅÒÎÂ */
	void InitLightmap( Level& Level );

	/* ÑÃÅÍÅĞÈĞÎÂÀÒÜ ÊÀĞÒÓ ÎÑÂÅÙÅÍÈß */
	void Generate( sf::RenderWindow& Window );

private:

	vector<Plane*>		Planes;
};

#endif // !LIGHTMAP_H
