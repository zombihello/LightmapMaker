﻿///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "../System/Logger.h"
#include "Level.h"

//-------------------------------------------------------------------------//

Level::~Level()
{
	Clear();
}

//-------------------------------------------------------------------------//

bool Level::LoadLevel( const string& Route )
{
	PRINT_LOG( "*** Loading Level ***\n" );
	TiXmlDocument Level;

	if ( !Level.LoadFile( Route.c_str() ) )
	{
		PRINT_LOG( "Error: Level Not Found Or Not Currect Format\n" );
		return false;
	}

	TiXmlElement* xml_Map;
	xml_Map = Level.FirstChildElement( "Map" );

	if ( !xml_Map )
	{
		PRINT_LOG( "Error: Not Correct Format In Level. Not Found Tag \"Map\"\n" );
		return false;
	}

	// ****************************
	// Загружаем цвет окружающей среды

	TiXmlElement* xml_Settings;
	xml_Settings = xml_Map->FirstChildElement( "Settings" );

	if ( xml_Settings )
	{
		TiXmlElement *AmbienceColor;
		AmbienceColor = xml_Settings->FirstChildElement( "AmbienceColor" );

		if ( AmbienceColor )
			if ( AmbienceColor->Attribute( "Value" ) )
			{
				int IdComp = 0;
				stringstream StringStream( AmbienceColor->Attribute( "Value" ) );
				string TempString;

				while ( !StringStream.eof() )
				{
					StringStream >> TempString;

					switch ( IdComp )
					{
					case 0: this->AmbienceColor.x = static_cast< float >( atof( TempString.c_str() ) ) / 255.f; break;
					case 1: this->AmbienceColor.y = static_cast< float >( atof( TempString.c_str() ) ) / 255.f; break;
					case 2: this->AmbienceColor.z = static_cast< float >( atof( TempString.c_str() ) ) / 255.f; break;
					case 3: this->AmbienceColor.w = static_cast< float >( atof( TempString.c_str() ) ) / 255.f; break;
					}

					TempString.clear();
					IdComp++;
				}
			}
	}

	// ****************************
	// Загружаем текстуры брашей

	TiXmlElement *xml_Textures;
	xml_Textures = xml_Map->FirstChildElement( "Textures" );
	
	PRINT_LOG( " - Load Textures\n" );

	if ( xml_Textures )
	{
		TiXmlElement *xml_Texture;
		string Name;
		xml_Texture = xml_Textures->FirstChildElement( "Texture" );

		while ( xml_Texture )
		{
			Name = xml_Texture->Attribute( "Name" );

			ResourcesManager::LoadGlTexture( Name, Directories::TexturesDirectory + "\\" + Name );
			xml_Texture = xml_Texture->NextSiblingElement();
		}

		PRINT_LOG( "\n" );
	}
	else
		PRINT_LOG( "Warning: In Level [" << Route << "]. Not Found Tag \"Textures\"\n" );

	// ****************************
	// Загружаем твердые браши

	TiXmlElement* xml_Brushes;
	xml_Brushes = xml_Map->FirstChildElement( "Brushes" );

	if ( !xml_Brushes )
	{
		PRINT_LOG( "Error: Not Correct Format In Level. Not Found Tag \"Brushes\"\n" );
		return false;
	}

	TiXmlElement* xml_Solid;
	xml_Solid = xml_Brushes->FirstChildElement( "Solid" );

	if ( xml_Solid )
	{
		Brush* TempBrush;
		TiXmlElement* xml_Brush;
		xml_Brush = xml_Solid->FirstChildElement( "Brush" );

		while ( xml_Brush )
		{
			TempBrush = new Brush();
			TempBrush->Create( *xml_Brush );
			Brushes.push_back( TempBrush );

			xml_Brush = xml_Brush->NextSiblingElement();
		}
	}

	// ****************************
	// Загружаем источники освещения

	TiXmlElement *xml_Entitys;
	xml_Entitys = xml_Map->FirstChildElement( "Entitys" );

	if ( !xml_Entitys )
	{
		PRINT_LOG( "Error: Not Correct Format In Level. Not Found Tag \"Entitys\"\n" );
		return false;
	}

	TiXmlElement *xml_Entity;
	string NameEntity;
	xml_Entity = xml_Entitys->FirstChildElement( "Entity" );

	while ( xml_Entity )
	{
		NameEntity = xml_Entity->Attribute( "Name" );

		if ( NameEntity == "Static_Light" )
		{
			PointLight PointLight( *xml_Entity );
			PointLights.push_back( PointLight );

			PRINT_LOG( " - Add Point Light\n" );
			PRINT_LOG( "   Intensivity: " << PointLight.Intensivity << endl );
			PRINT_LOG( "   Radius: " << PointLight.Radius << endl );
			PRINT_LOG( "   Color: " << PointLight.Color.x * 255.f << ", " << PointLight.Color.y * 255.f << ", " << PointLight.Color.z * 255.f << ", " << PointLight.Color.w * 255.f << endl );
			PRINT_LOG( "   Position: " << PointLight.Position.x << ", " << PointLight.Position.y << ", " << PointLight.Position.z << endl );
			PRINT_LOG( "	****\n" );
			PRINT_LOG( "\n" );
		}

		xml_Entity = xml_Entity->NextSiblingElement();
	}

	PRINT_LOG( " - Total Brushes: " << Brushes.size() << endl );
	PRINT_LOG( " - Total Planes: " << Brushes.size() * 6 << endl );
	PRINT_LOG( " - Total Point Lights: " << PointLights.size() << endl );
	PRINT_LOG( "*** Level Loaded ***\n" );
	return true;
}

//-------------------------------------------------------------------------//

void Level::Clear()
{
	for ( size_t Id = 0; Id < Brushes.size(); Id++ )
		delete Brushes[ Id ];

	Brushes.clear();
	ResourcesManager::DeleteAllGlTexture();
}

//-------------------------------------------------------------------------//

const glm::vec4& Level::GetAmbienceColor()
{
	return AmbienceColor;
}

//-------------------------------------------------------------------------//

vector<Brush*>& Level::GetBrushes()
{
	return Brushes;
}

//-------------------------------------------------------------------------//

vector<PointLight>& Level::GetPointLights()
{
	return PointLights;
}

//-------------------------------------------------------------------------//
