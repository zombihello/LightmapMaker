///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <sstream>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "DirectionalLight.h"

//-------------------------------------------------------------------------//

DirectionalLight::DirectionalLight() :
	Intensivity( 1.f ),
	Color( 150.f, 150.f, 150.f )
{}

//-------------------------------------------------------------------------//

DirectionalLight::DirectionalLight( TiXmlElement & ElementEntity ) :
	Intensivity( 1.f ),
	Color( 150.f, 150.f, 150.f )
{
	// ***************************************** //
	// Загружаем позицию источника в мире

	TiXmlElement* position;
	position = ElementEntity.FirstChildElement( "Position" );

	if ( position != NULL )
	{
		Position.x = static_cast< float >( atof( position->Attribute( "X" ) ) );
		Position.y = static_cast< float >( atof( position->Attribute( "Y" ) ) );
		Position.z = static_cast< float >( atof( position->Attribute( "Z" ) ) );
	}

	// ***************************************** //
	// Загружаем свойства света

	TiXmlElement* Value;
	string NameValue;
	Value = ElementEntity.FirstChildElement( "Value" );

	while ( Value )
	{
		NameValue = Value->Attribute( "Name" );

		if ( NameValue == "Color" )
		{
			int IdComp = 0;
			stringstream StringStream( Value->Attribute( "Value" ) );
			string TempString;

			while ( !StringStream.eof() )
			{
				StringStream >> TempString;

				switch ( IdComp )
				{
				case 0: Color.x = static_cast< float >( atof( TempString.c_str() ) ); break;
				case 1: Color.y = static_cast< float >( atof( TempString.c_str() ) ); break;
				case 2: Color.z = static_cast< float >( atof( TempString.c_str() ) ); break;
				}

				TempString.clear();
				IdComp++;
			}
		}
		else if ( NameValue == "Intensivity" )
			Intensivity = static_cast< float >( atof( Value->Attribute( "Value" ) ) );

		Value = Value->NextSiblingElement();
	}
}

//-------------------------------------------------------------------------//