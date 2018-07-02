///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "BrushVertex.h"

//-------------------------------------------------------------------------//

bool BrushVertex::operator==( BrushVertex & BrushVertex )
{
	return Position == BrushVertex.Position &&
		TextureCoord_LightMap == BrushVertex.TextureCoord_LightMap;
}

//-------------------------------------------------------------------------//