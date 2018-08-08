///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <sstream>
using namespace std;

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "SpotLight.h"

//-------------------------------------------------------------------------//

SpotLight::SpotLight() :
	Intensivity( 1 ),
	SpotCutoff( -1 ), // cos 180 градусов = -1
	Radius( 25.f ),
	Height( 45.f ),
	Color( 150.f, 150.f, 150.f ),
	SpotDirection( 0.f, -1.f, 0.f )
{}

//-------------------------------------------------------------------------//

SpotLight::SpotLight( TiXmlElement& ElementEntity ) :
	Intensivity( 1 ),
	SpotCutoff( -1 ), // cos 180 градусов = -1
	Radius( 25.f ),
	Height( 45.f ),
	Color( 150.f, 150.f, 150.f ),
	SpotDirection( 0.f, -1.f, 0.f )
{
	// ***************************************** //
	// Загружаем позицию источника в мире

	TiXmlElement* position;
	position = ElementEntity.FirstChildElement( "Position" );

	if ( position != NULL )
	{
		Position.x = static_cast< float >( atof( position->Attribute( "X" ) ) );
		Position.y = static_cast< float > ( atof( position->Attribute( "Y" ) ) );
		Position.z = static_cast< float > ( atof( position->Attribute( "Z" ) ) );
	}

	// ***************************************** //
	// Загружаем свойства света

	TiXmlElement* Value;
	string NameValue;
	Value = ElementEntity.FirstChildElement( "Value" );

	while ( Value )
	{
		NameValue = Value->Attribute( "Name" );

		if ( NameValue == "Color" || NameValue == "Rotation" )
		{
			int IdComp = 0;
			stringstream StringStream( Value->Attribute( "Value" ) );
			glm::vec4 TempVector4;
			string TempString;

			while ( !StringStream.eof() )
			{
				StringStream >> TempString;

				switch ( IdComp )
				{
				case 0: TempVector4.x = static_cast< float >( atof( TempString.c_str() ) ); break;
				case 1: TempVector4.y = static_cast< float >( atof( TempString.c_str() ) ); break;
				case 2: TempVector4.z = static_cast< float >( atof( TempString.c_str() ) ); break;
				case 3: TempVector4.w = static_cast< float >( atof( TempString.c_str() ) ); break;
				}

				TempString.clear();
				IdComp++;
			}

			if ( NameValue == "Color" )
				Color = TempVector4;
			else if ( NameValue == "Rotation" )
				Rotation = TempVector4;
		}
		else if ( NameValue == "Radius" )
			Radius = static_cast< float >( atof( Value->Attribute( "Value" ) ) );
		else if ( NameValue == "Height" )
			Height = static_cast< float > ( atof( Value->Attribute( "Value" ) ) );
		else if ( NameValue == "Intensivity" )
			Intensivity = static_cast< float >( atof( Value->Attribute( "Value" ) ) );

		Value = Value->NextSiblingElement();
	}

	// ********************************************
	// Вычисляем напровление прожекторного света

	float C = sqrt( pow( Height, 2 ) + pow( Radius, 2 ) );
	SpotCutoff = Height / C;

	glm::vec3 Axis( sin( Rotation.x / 2 ), sin( Rotation.y / 2 ), sin( Rotation.z / 2 ) );
	glm::vec3 Rotations( cos( Rotation.x / 2 ), cos( Rotation.y / 2 ), cos( Rotation.z / 2 ) );

	glm::quat RotateX( Rotations.x, Axis.x, 0, 0 );
	glm::quat RotateY( Rotations.y, 0, Axis.y, 0 );
	glm::quat RotateZ( Rotations.z, 0, 0, Axis.z );

	glm::quat QuatRotation = RotateX * RotateY * RotateZ;

	SpotDirection = QuatRotation * SpotDirection;
	SpotDirection = glm::normalize( SpotDirection );
}

//-------------------------------------------------------------------------//

float SpotLight::CalculateAttenuation( float Distance )
{
	float LinearCoeff = ( 2.0f * Distance ) / Height;
	float QuadCoeff = Distance * Distance / ( Height * Height );

	return 1.0f / ( 1.0f + LinearCoeff + QuadCoeff );
}

//-------------------------------------------------------------------------//