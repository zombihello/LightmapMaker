///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Brush.h"

//-------------------------------------------------------------------------//

vector<unsigned int> Brush::IdVertex =
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

//-------------------------------------------------------------------------//

Brush::~Brush()
{
	for ( size_t Id = 0; Id < Planes.size(); Id++ )
		delete Planes[ Id ];

	OpenGL_API::VAO::DeleteBuffer( VertexBuffer );
}

//-------------------------------------------------------------------------//

void Brush::Create( TiXmlElement& Element )
{
	glm::vec3							TempVector3;
	glm::vec2							TempVector2;
	vector<glm::vec3>					Vertexs;
	vector<glm::vec2>					TexCoords;
	vector<BrushVertex>					BrushVertexs;
	map<int, vector<unsigned int> >		PlaneIdVertex;
	map<int, vector<BrushVertex> >		PlaneVertex;

	// ****************************
	// Загружаем позиции вершин

	TiXmlElement *xml_Vertexs;
	xml_Vertexs = Element.FirstChildElement( "PositionVertex" );

	if ( xml_Vertexs )
	{
		TiXmlElement *xml_Vertex;
		xml_Vertex = xml_Vertexs->FirstChildElement( "Vertex" );

		while ( xml_Vertex )
		{
			TempVector3.x = static_cast< float >( atof( xml_Vertex->Attribute( "X" ) ) );
			TempVector3.y = static_cast< float >( atof( xml_Vertex->Attribute( "Y" ) ) );
			TempVector3.z = static_cast< float >( atof( xml_Vertex->Attribute( "Z" ) ) );

			Vertexs.push_back( TempVector3 );
			xml_Vertex = xml_Vertex->NextSiblingElement();
		}
	}

	// ****************************************************
	// Загружаем текстурные координаты для карты освещения

	TiXmlElement *xml_TexCoord;
	xml_TexCoord = Element.FirstChildElement( "TextureCoords_LightMap" );

	if ( xml_TexCoord )
	{
		TiXmlElement *xml_Point = xml_TexCoord->FirstChildElement( "Point" );

		while ( xml_Point )
		{
			TempVector2.x = static_cast< float >( atof( xml_Point->Attribute( "X" ) ) );
			TempVector2.y = static_cast< float >( atof( xml_Point->Attribute( "Y" ) ) );

			TexCoords.push_back( TempVector2 );
			xml_Point = xml_Point->NextSiblingElement();
		}
	}

	// ****************************************************
	// Объеденяем позици и текстурные координаты в одну вершину для OpenGL'a

	BrushVertex TempVertex;
	for ( size_t Id = 0, Face = 0, VertexInFace = 0; Id < IdVertex.size(); Id++, VertexInFace++ )
	{
		TempVertex.Position = Vertexs[ IdVertex[ Id ] ];
		TempVertex.TextureCoord_LightMap = TexCoords[ Id ];

		bool IsFindInArray = false;
		for ( size_t i = 0; i < BrushVertexs.size(); i++ )
			if ( TempVertex == BrushVertexs[ i ] )
			{
				PlaneIdVertex[ Face ].push_back( i );
				IsFindInArray = true;
				break;
			}

		if ( !IsFindInArray )
		{
			PlaneIdVertex[ Face ].push_back( BrushVertexs.size() );
			BrushVertexs.push_back( TempVertex );
		}

		if ( VertexInFace == 5 ) // В каждой плоскости по 6-ть вершин ( два треугольника по три вершины )
		{
			Face++;
			VertexInFace = -1;
		}
	}

	// ****************************************************
	// Распределяем вершины на стороны

	for ( int Face = 0; Face < 6; Face++ )
		for ( size_t Id = 0; Id < PlaneIdVertex[ Face ].size(); Id++ )
			PlaneVertex[ Face ].push_back( BrushVertexs[ PlaneIdVertex[ Face ][ Id ] ] );

	// ****************************************************
	// Инициализируем плоскости браша

	Plane* TempPlane;
	VertexBuffer = OpenGL_API::VAO::CreateBuffer( OpenGL_API::VAO::Vertex_Buffer, BrushVertexs, OpenGL_API::VAO::Static_Draw );

	for ( size_t Face = 0; Face < 6; Face++ )
	{
		TempPlane = new Plane();
		TempPlane->InitPlane( VertexBuffer, PlaneIdVertex[ Face ], PlaneVertex[ Face ] );
		Planes.push_back( TempPlane );
	}
}

//-------------------------------------------------------------------------//

void Brush::Render()
{
	for ( size_t i = 0; i < Planes.size(); i++ )
		Planes[ i ]->Render();
}

//-------------------------------------------------------------------------//

vector<Plane*>& Brush::GetPlanes()
{
	return Planes;
}

//-------------------------------------------------------------------------//
