#include "Lightmap.h"

#include <glm\gtx\transform.hpp>
#include "..\System\Directories.h"
#include "..\System\Camera.h"
#include <Windows.h>
//-------------------------------------------------------------------------//

void Lightmap::InitLightmap( Level& Level )
{
	vector<Brush*>	Brushes = Level.GetBrushes();
	vector<Plane*>*	BrushPlanes;

	// ***********************************
	// –‡Á·Ë‚‡ÂÏ ·‡¯Ë Ì‡ ÔÎÓÒÍÓÒÚË

	for ( size_t Id_Brush = 0; Id_Brush < Brushes.size(); Id_Brush++ )
	{
		BrushPlanes = &Brushes[ Id_Brush ]->GetPlanes();

		for ( size_t Id_Plane = 0; Id_Plane < BrushPlanes->size(); Id_Plane++ )
			Planes.push_back( BrushPlanes->at( Id_Plane ) );
	}
}

//-------------------------------------------------------------------------//

#include "../System/Logger.h"


void Lightmap::Generate( sf::RenderWindow& Window )
{
	// “≈—“Œ¬€…  Œƒ ƒÀﬂ œ–Œ¬≈– » –≈Õƒ≈–¿ ¡–¿ÿ≈… » “Œ◊≈◊ÕŒ√Œ »—“Œ◊Õ» ¿ —¬≈“¿

	sf::Event Event;
	sf::Vector2i MousePosition, CenterWindow( 800 / 2, 600 / 2 );
	glm::vec3 Position = glm::vec3( 0, 0, 0 ), Direction;
	glm::vec2 Angle;
	glm::mat4 Pojection = glm::perspective( glm::radians( 90.f ), 1.f, 0.1f, 1500.f );
	Camera Camera( Position, glm::vec3( -64, 0, -64 ), glm::vec3( 0, 1, 0 ) );
	map<string, int> Attrib;

	Attrib[ "Position" ] = 0;
	Attrib[ "TexCoord" ] = 1;

	OpenGL_API::Shader Shader( Attrib );
	Shader.LoadFromFile( Directories::ShaderDirectory + "\\vs.vs", Directories::ShaderDirectory + "\\fs.fs" );

	Attrib.clear();
	Attrib[ "Position" ] = 0;

	OpenGL_API::Shader ShaderLight( Attrib );
	ShaderLight.LoadFromFile( Directories::ShaderDirectory + "\\vsl.vs", Directories::ShaderDirectory + "\\fsl.fs" );

	glEnable( GL_DEPTH_TEST );
	//glEnable( GL_CULL_FACE );

	//--------------------------------------------

	glm::vec3 PositionFragment, Newedge1, Newedge2;
	glm::vec2 UVFactor;
	int Id = 0;
	bool f = false;

	float x = 0, y = 0;

	Triangle* Triangle = &Planes[ 0 ]->GetTriangles()[ 0 ];
	UVFactor = glm::vec2( 0.5f / Triangle->SizeLightmap.x, 0.5f / Triangle->SizeLightmap.y );

	Newedge1.x = Triangle->Edge1.x * UVFactor.x;
	Newedge1.y = Triangle->Edge1.y * UVFactor.x;
	Newedge1.z = Triangle->Edge1.z * UVFactor.x;
	Newedge2.x = Triangle->Edge2.x * UVFactor.y;
	Newedge2.y = Triangle->Edge2.y * UVFactor.y;
	Newedge2.z = Triangle->Edge2.z * UVFactor.y;

	PositionFragment = Triangle->UVVector + Newedge2 + Newedge1;

	//--------------------------------------------

	while ( Window.isOpen() )
	{
		while ( Window.pollEvent( Event ) )
			if ( Event.type == sf::Event::Closed )
				Window.close();		

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::E ) && !f )
		{
			Id++;
			f = true;

			if ( Id < Planes.size() )
			{
				Triangle = &Planes[ Id ]->GetTriangles()[ 0 ];
				UVFactor = glm::vec2( 0.5f / Triangle->SizeLightmap.x, 0.5f / Triangle->SizeLightmap.y );

				Newedge1.x = Triangle->Edge1.x * UVFactor.x;
				Newedge1.y = Triangle->Edge1.y * UVFactor.x;
				Newedge1.z = Triangle->Edge1.z * UVFactor.x;
				Newedge2.x = Triangle->Edge2.x * UVFactor.y;
				Newedge2.y = Triangle->Edge2.y * UVFactor.y;
				Newedge2.z = Triangle->Edge2.z * UVFactor.y;

				PositionFragment = Triangle->UVVector + Newedge2 + Newedge1;
			}
		}
		else if ( !sf::Keyboard::isKeyPressed( sf::Keyboard::E ) && f )
			f = false;

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
			PositionFragment.x -= 0.05;

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
			PositionFragment.x += 0.05;

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
			PositionFragment.z += 0.05;

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
			PositionFragment.z -= 0.05;

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
			Window.close();

		Camera.SetPosition( PositionFragment );

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) )
		{
			MousePosition = sf::Mouse::getPosition( Window );

			float OffsetX = ( MousePosition.x - CenterWindow.x ) * 0.15;
			float OffsetY = ( CenterWindow.y - MousePosition.y ) * 0.15;

			Angle.x += glm::radians( OffsetX );
			Angle.y += glm::radians( OffsetY );

			if ( Angle.y < -1.55f )
				Angle.y = -1.55f;
			else if ( Angle.y > 1.55f )
				Angle.y = 1.55f;

			Direction.x = glm::cos( Angle.x ) * glm::cos( Angle.y );
			Direction.y = glm::sin( Angle.y );
			Direction.z = glm::sin( Angle.x ) * glm::cos( Angle.y );
			Direction = glm::normalize( Direction );

			Camera.SetTargetPoint( PositionFragment + Direction );
			sf::Mouse::setPosition( CenterWindow, Window );
		}
		else
			Camera.SetTargetPoint( PositionFragment + Triangle->Normal );

		glm::mat4 PV = Pojection * Camera.GetViewMatrix();
		Shader.SetUniform( "PV", PV );

		OpenGL_API::Shader::Bind( &Shader );
		for ( size_t i = 0; i < Planes.size(); i++ )
			Planes[ i ]->Render();
		OpenGL_API::Shader::Bind( NULL );

		Window.display();
	}
}

//-------------------------------------------------------------------------//