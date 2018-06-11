#include "Level.h"

//-------------------------------------------------------------------------//

bool Level::LoadLevel( const string& Route )
{
	PRINT_LOG( "- Loading Level" );
	TiXmlDocument Level;

	if ( !Level.LoadFile( Route.c_str() ) )
	{
		PRINT_LOG( "Error: Level Not Found Or Not Currect Format" );
		return false;
	}

	TiXmlElement* Map;
	Map = Level.FirstChildElement( "Map" );

	if ( Map == NULL )
	{
		PRINT_LOG( "Error: Not Correct Format In Level. Not Found Tag \"Map\"" );
		return false;
	}

	// ****************************
	// Загружаем твердые браши
	// ****************************

	TiXmlElement* Brushes;
	Brushes = Map->FirstChildElement( "Brushes" );

	if ( Brushes == NULL )
	{
		PRINT_LOG( "Error: Not Correct Format In Level. Not Found Tag \"Brushes\"" );
		return false;
	}

	TiXmlElement* Solid;
	Solid = Brushes->FirstChildElement( "Solid" );

	if ( Solid != NULL )
	{
		vector<unsigned int> IdVertex =
		{
			7, 3, 4,
			3, 0, 4,

			2, 6, 1,
			6, 5, 1,

			7, 6, 3,
			6, 2, 3,

			0, 1, 4,
			1, 5, 4,

			6, 4, 5,
			6, 7, 4,

			0, 2, 1,
			0, 3, 2
		};

		TiXmlElement* Brush;
		Brush = Solid->FirstChildElement( "Brush" );

		glm::vec3 TempVector3;
		Plane* TempPlane = NULL;
		vector<glm::vec3> Vertexs;

		while ( Brush )
		{
			// ****************************
			// Загружаем позиции вершин
			// ****************************

			TiXmlElement *PositionVertex, *Vertex;
			PositionVertex = Brush->FirstChildElement( "PositionVertex" );
			Vertex = PositionVertex->FirstChildElement( "Vertex" );

			while ( Vertex )
			{
				TempVector3.x = ( float ) atof( Vertex->Attribute( "X" ) );
				TempVector3.y = ( float ) atof( Vertex->Attribute( "Y" ) );
				TempVector3.z = ( float ) atof( Vertex->Attribute( "Z" ) );

				Vertexs.push_back( TempVector3 );
				Vertex = Vertex->NextSiblingElement();
			}

			for ( size_t i = 0, Id = 0, IdTriangleOnPlane = 0; i < IdVertex.size() / 3; i++, IdTriangleOnPlane++, Id += 3 )
			{
				if ( IdTriangleOnPlane == 2 ) IdTriangleOnPlane = 0;

				if ( IdTriangleOnPlane == 0 )
				{
					Planes.push_back( Plane() );
					TempPlane = &Planes[ Planes.size() - 1 ];
				}

				TempPlane->Triangles[ IdTriangleOnPlane ] = Triangle( Vertexs[ IdVertex[ Id ] ], Vertexs[ IdVertex[ Id + 1 ] ], Vertexs[ IdVertex[ Id + 2 ] ] );	
			}

			Vertexs.clear();
			Brush = Brush->NextSiblingElement();
		}
	}

	//====== ЗАГРУЖАЕМ СТАТИЧНЫЕ ИСТОЧНИКИ СВЕТА ======//

	TiXmlElement *Entitys;
	Entitys = Map->FirstChildElement( "Entitys" );

	if ( Entitys == NULL )
	{
		PRINT_LOG( "Error: Not Correct Format In Level. Not Found Tag \"Entitys\"" );
		return false;
	}

	TiXmlElement *Entity;
	string NameEntity;
	Entity = Entitys->FirstChildElement( "Entity" );

	while ( Entity )
	{
		NameEntity = Entity->Attribute( "Name" );

		if ( NameEntity == "light" )
		{
			PointLight PointLight( *Entity );
			PointLights.push_back( PointLight );

			PRINT_LOG( " - Add Point Light" );
			PRINT_LOG( "   Intensivity: " << PointLight.Intensivity );
			PRINT_LOG( "   Radius: " << PointLight.Radius );
			PRINT_LOG( "   Color: " << PointLight.Color.x << ", " << PointLight.Color.y << ", " << PointLight.Color.z << ", " << PointLight.Color.w );
			PRINT_LOG( "   Position: " << PointLight.Position.x << ", " << PointLight.Position.y << ", " << PointLight.Position.z );
			PRINT_LOG( "	****\n" );
		}

		Entity = Entity->NextSiblingElement();
	}

	PRINT_LOG( " - Total Planes: " << Planes.size() );
	PRINT_LOG( " - Total Point Lights: " << PointLights.size() );
	PRINT_LOG( "- Level Loaded" );
	return true;
}

//-------------------------------------------------------------------------//

vector<Plane>& Level::GetPlanes()
{
	return Planes;
}

//-------------------------------------------------------------------------//

vector<PointLight>& Level::GetPointLights()
{
	return PointLights;
}

//-------------------------------------------------------------------------//
