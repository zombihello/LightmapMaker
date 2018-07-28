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
	// Ğàçáèâàåì áğàøè íà ïëîñêîñòè

	for ( size_t Id_Brush = 0; Id_Brush < Brushes.size(); Id_Brush++ )
	{
		BrushPlanes = &Brushes[ Id_Brush ]->GetPlanes();

		for ( size_t Id_Plane = 0; Id_Plane < BrushPlanes->size(); Id_Plane++ )
			Planes.push_back( BrushPlanes->at( Id_Plane ) );
	}
}

//-------------------------------------------------------------------------//
#include "../System/Logger.h"
float x = 0;
float y = 0;
float id = 0;
float id2 = 0;

void Lightmap::Generate( sf::RenderWindow& Window )
{
	// ÒÅÑÒÎÂÛÉ ÊÎÄ ÄËß ÏĞÎÂÅĞÊÈ ĞÅÍÄÅĞÀ ÁĞÀØÅÉ È ÒÎ×Å×ÍÎÃÎ ÈÑÒÎ×ÍÈÊÀ ÑÂÅÒÀ

	
	glm::vec2 UVFactor;
	glm::vec3 Newedge1, Newedge2, PositionFragment;

	sf::Event Event;
	glm::mat4 Pojection = glm::perspective( glm::radians( 75.f ), 1.f, 0.1f, 1500.f );
	Camera Camera( PositionFragment, glm::vec3( -64, 0, -64 ), glm::vec3( 0, 1, 0 ) );
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

	while ( Window.isOpen() )
	{
		while ( Window.pollEvent( Event ) )
			if ( Event.type == sf::Event::Closed )
				Window.close();

		Sleep( 200 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		Triangle* Triangle = &Planes[ id ]->GetTriangles()[ id2 ];
		UVFactor = glm::vec2( ( x + 0.5f ) / Triangle->SizeLightmap.x, ( y + 0.5f ) / Triangle->SizeLightmap.y );

		Newedge1.x = Triangle->Edge1.x * UVFactor.x;
		Newedge1.y = Triangle->Edge1.y * UVFactor.x;
		Newedge1.z = Triangle->Edge1.z * UVFactor.x;
		Newedge2.x = Triangle->Edge2.x * UVFactor.y;
		Newedge2.y = Triangle->Edge2.y * UVFactor.y;
		Newedge2.z = Triangle->Edge2.z * UVFactor.y;

		PositionFragment = Triangle->UVVector + Newedge2 + Newedge1;

		Camera.SetPosition( PositionFragment );

		if ( x >= Triangle->SizeLightmap.x )
			x = -1;
		else if ( x < Triangle->SizeLightmap.x )
			x++;

		if ( y >= Triangle->SizeLightmap.y )
			y = -1;
		else if ( y < Triangle->SizeLightmap.y )
			y++;

		if ( x == -1 && y == -1 )
		{
			id2++;
			x = y = 0;
		}

		if ( id2 > Planes[ id ]->GetTriangles().size() )
		{
			id2 = -1;
		}

		if ( id2 == -1 )
		{
			id++;
			id2 = 0;
			x = y = 0;
		}

		if ( id > Planes.size() )
		{
			id = 0;
			id2 = 0;
			x = y = 0;
		}

		PRINT_LOG( "id " << id << " id2 " << id2 );

		//if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
		//	Position.x -= 0.05;

		//if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
		//	Position.x += 0.05;

		//if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
		//	Position.z += 0.05;

		//if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
		//	Position.z -= 0.05;

		glm::mat4 PV = Pojection * Camera.GetViewMatrix();
		Shader.SetUniform( "PV", PV );
		ShaderLight.SetUniform( "PV", PV );

		OpenGL_API::Shader::Bind( &Shader );
		for ( size_t i = 0; i < Planes.size(); i++ )
			Planes[ i ]->Render();

		OpenGL_API::Shader::Bind( &ShaderLight );

		/*for ( size_t i = 0; i < PointLights->size(); i++ )
		{
			glm::vec4 Color = PointLights->at( i ).Color;
			glm::mat4 Mat = PointLights->at( i ).LightSphere.GetTransformation();

			ShaderLight.SetUniform( "Color", Color );
			ShaderLight.SetUniform( "TR", Mat );
			PointLights->at( i ).LightSphere.Render();
		}*/

		OpenGL_API::Shader::Bind( NULL );

		Window.display();
	}
}

//-------------------------------------------------------------------------//