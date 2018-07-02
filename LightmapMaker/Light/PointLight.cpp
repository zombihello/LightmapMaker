///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <string>
#include <sstream>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "PointLight.h"

//-------------------------------------------------------------------------//

PointLight::PointLight() :
	Intensivity( 1.f ),
	Radius( 25.f ),
	Color( 0.6f, 0.6f, 0.6f, 1.f )
{}

//-------------------------------------------------------------------------//

PointLight::PointLight( const PointLight& Copy ) :
	Intensivity( Copy.Intensivity ),
	Radius( Copy.Radius ),
	Position( Copy.Position ),
	Color( Copy.Color ),
	LightSphere( Copy.LightSphere )
{}

//-------------------------------------------------------------------------//

PointLight::PointLight( TiXmlElement& Element ) :
	Intensivity( 1.f ),
	Radius( 25.f ),
	Color( 0.6f, 0.6f, 0.6f, 1.f )
{
	// ***************************************** //
	// Загружаем позицию источника в мире

	TiXmlElement* xml_Position;
	xml_Position = Element.FirstChildElement( "Position" );

	if ( xml_Position )
	{
		Position.x = static_cast< float >( atof( xml_Position->Attribute( "X" ) ) );
		Position.y = static_cast< float >( atof( xml_Position->Attribute( "Y" ) ) );
		Position.z = static_cast< float >( atof( xml_Position->Attribute( "Z" ) ) );
	}

	// ***************************************** //
	// Загружаем свойства света

	TiXmlElement* xlm_Value;
	string NameValue;
	xlm_Value = Element.FirstChildElement( "Value" );

	while ( xlm_Value )
	{
		NameValue = xlm_Value->Attribute( "Name" );

		if ( NameValue == "Color" )
		{
			int IdComp = 0;
			stringstream StringStream( xlm_Value->Attribute( "Value" ) );
			string TempString;

			while ( !StringStream.eof() )
			{
				StringStream >> TempString;

				switch ( IdComp )
				{
				case 0: Color.x = static_cast< float >( atof( TempString.c_str() ) ) / 255.f; break;
				case 1: Color.y = static_cast< float >( atof( TempString.c_str() ) ) / 255.f; break;
				case 2: Color.z = static_cast< float >( atof( TempString.c_str() ) ) / 255.f; break;
				case 3: Color.w = static_cast< float >( atof( TempString.c_str() ) ) / 255.f; break;
				}

				TempString.clear();
				IdComp++;
			}
		}
		else if ( NameValue == "Radius" )
			Radius = static_cast< float >( atof( xlm_Value->Attribute( "Value" ) ) );
		else if ( NameValue == "Intensivity" )
			Intensivity = static_cast< float >( atof( xlm_Value->Attribute( "Value" ) ) );

		xlm_Value = xlm_Value->NextSiblingElement();
	}

	LightSphere.InitSphere( Radius );
	LightSphere.SetPosition( Position );
}

//-------------------------------------------------------------------------//

PointLight& PointLight::operator=( const PointLight& Copy )
{
	Intensivity = Copy.Intensivity;
	Radius = Copy.Radius;
	Position = Copy.Position;
	Color = Copy.Color;
	LightSphere = Copy.LightSphere;

	return *this;
}

//-------------------------------------------------------------------------//
