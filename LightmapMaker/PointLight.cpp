///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <sstream>
using namespace std;

#include "PointLight.h"

//-------------------------------------------------------------------------//

PointLight::PointLight() :
	Intensivity( 1.f ),
	Radius( 25.f ),
	Color( 153.f, 153.f, 153.f, 255.f )
{}

//-------------------------------------------------------------------------//

PointLight::PointLight( TiXmlElement& ElementEntity ) :
	Intensivity( 1.f ),
	Radius( 25.f ),
	Color( 153.f, 153.f, 153.f, 255.f )
{
	// ***************************************** //
	// Загружаем позицию источника в мире

	TiXmlElement* position;
	position = ElementEntity.FirstChildElement( "Position" );

	if ( position != NULL )
	{
		Position.x = ( float ) atof( position->Attribute( "X" ) );
		Position.y = ( float ) atof( position->Attribute( "Y" ) );
		Position.z = ( float ) atof( position->Attribute( "Z" ) );
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
				case 0: Color.x = ( float ) atof( TempString.c_str() ); break;
				case 1: Color.y = ( float ) atof( TempString.c_str() ); break;
				case 2: Color.z = ( float ) atof( TempString.c_str() ); break;
				case 3: Color.w = ( float ) atof( TempString.c_str() ); break;
				}

				TempString.clear();
				IdComp++;
			}
		}
		else if ( NameValue == "Radius" )
			Radius = ( float ) atof( Value->Attribute( "Value" ) );
		else if ( NameValue == "Intensivity" )
			Intensivity = ( float ) atof( Value->Attribute( "Value" ) );

		Value = Value->NextSiblingElement();
	}
}

//-------------------------------------------------------------------------//

float PointLight::CalculateAttenuation( float Distance )
{
	float LinearCoeff = ( 2.0f * Distance ) / Radius;
	float QuadCoeff = Distance * Distance / ( Radius * Radius );

	return 1.0f / ( 1.0f + LinearCoeff + QuadCoeff );
}

//-------------------------------------------------------------------------//