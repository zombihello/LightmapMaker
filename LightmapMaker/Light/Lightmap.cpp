#include "Lightmap.h"
#include <glm\gtx\transform.hpp>

//-------------------------------------------------------------------------//

void Lightmap::InitLightmap( Level& Level )
{
	vector<Brush*>	Brushes = Level.GetBrushes();
	vector<Plane*>*	BrushPlanes;

	Projection = glm::perspective( glm::radians( 90.f ), 1.f, 0.1f, 1500.f );
	RenderTexture.Create( ArgumentsStart::SizeRenderTexture, ArgumentsStart::SizeRenderTexture );

	// ***********************************
	// Разбиваем браши на плоскости

	for ( size_t Id_Brush = 0; Id_Brush < Brushes.size(); Id_Brush++ )
	{
		BrushPlanes = &Brushes[ Id_Brush ]->GetPlanes();

		for ( size_t Id_Plane = 0; Id_Plane < BrushPlanes->size(); Id_Plane++ )
			Planes.push_back( BrushPlanes->at( Id_Plane ) );
	}

	PointLights = &Level.GetPointLights();

	// ***********************************
	// Загружаем шейдера

	map<string, int> AttribLocation;
	AttribLocation[ "Position" ] = 0;
	AttribLocation[ "TexCoord" ] = 1;

	Shader_RenderPlane.SetAttribLocation( AttribLocation );
	Shader_RenderLight.SetAttribLocation( AttribLocation );

	if ( !Shader_RenderPlane.LoadFromFile( Directories::ShaderDirectory + "\\vs.vs", Directories::ShaderDirectory + "\\fs.fs" ) )
		Error( "Error Shader Load", "Error In Load Shader. Look Log File For Details", -1 );

	if ( !Shader_RenderLight.LoadFromFile( Directories::ShaderDirectory + "\\vsl.vs", Directories::ShaderDirectory + "\\fsl.fs" ) )
		Error( "Error Shader Load", "Error In Load Shader. Look Log File For Details", -1 );
}

//-------------------------------------------------------------------------//

void Lightmap::Generate( sf::RenderWindow& Window )
{
	sf::Event Event;
	glm::vec3 PositionFragment;
	glm::vec2 SizeLightmap;
	Plane* Plane;

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );
	Camera.SetAxisVertical( glm::vec3( 0, 1, 0 ) );	

	// ****************************
	// Генерируем карты освещения

	for ( size_t RadiosityStep = 0; RadiosityStep < 3; RadiosityStep++ )
	{
		for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++ )
		{
			Plane = Planes[ IdPlane ];
			SizeLightmap = Plane->GetSizeLightmap();

			for ( float x = 0; x < SizeLightmap.x; x++ )
				for ( float y = 0; y < SizeLightmap.y; y++ )
				{
					Plane->GetPositionFragment( ( x + 0.5f ) / SizeLightmap.x, ( y + 0.5f ) / SizeLightmap.y, PositionFragment );

					Camera.SetPosition( PositionFragment );
					Camera.SetTargetPoint( PositionFragment + Plane->GetNormal() );

					Plane->GetDataLightMap().setPixel( x, y, PathRender() );
				}			
		}

		for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++ )
			Planes[ IdPlane ]->GenerateGLTexture();
	}

	for ( size_t IdPlane = 0; IdPlane < Planes.size(); IdPlane++ )
	{
		Plane = Planes[ IdPlane ];
		Plane->GetDataLightMap().saveToFile( Directories::SaveLightmapDirectory + "\\lm_" + to_string( IdPlane ) + ".png" );
	}

	Camera.SetPosition( glm::vec3( 0, 0, 0 ) );
	Camera.SetTargetPoint( glm::vec3( -64, 0, -64 ) );
	glm::vec3 Position;

	while ( Window.isOpen() )
	{
		while ( Window.pollEvent( Event ) )
			if ( Event.type == sf::Event::Closed )
				Window.close();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
			Position.x -= 0.05;

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
			Position.x += 0.05;

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
			Position.z += 0.05;

		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
			Position.z -= 0.05;

		Camera.SetPosition( Position );

		PV = Projection * Camera.GetViewMatrix();
		Shader_RenderPlane.SetUniform( "PV", PV );

		OpenGL_API::Shader::Bind( &Shader_RenderPlane );

		for ( size_t i = 0; i < Planes.size(); i++ )
			Planes[ i ]->Render();

		OpenGL_API::Shader::Bind( NULL );
		Window.display();
	}
}

//-------------------------------------------------------------------------//

sf::Color Lightmap::PathRender()
{
	RenderTexture.Bind();
	RenderScene();
	RenderTexture.Unbind();

	glm::vec3 ColorPixel = RenderTexture.GetMediumColorTexture();
	PRINT_LOG( ColorPixel.x << " " << ColorPixel.y << " " << ColorPixel.z );
	return sf::Color( ColorPixel.x * 255.f, ColorPixel.y * 255.f, ColorPixel.z * 255.f, 255.f );
}

//-------------------------------------------------------------------------//

void Lightmap::RenderScene()
{
	PV = Projection * Camera.GetViewMatrix();
	Shader_RenderPlane.SetUniform( "PV", PV );

	// ****************************
	// Рендерим плоскости брашей

	OpenGL_API::Shader::Bind( &Shader_RenderPlane );

	for ( size_t i = 0; i < Planes.size(); i++ )
		Planes[ i ]->Render();

	// ****************************
	// Рендерим источники света

	OpenGL_API::Shader::Bind( &Shader_RenderLight );

	for ( size_t i = 0; i < PointLights->size(); i++ )
	{
		PVT = PV * PointLights->at( i ).LightSphere.GetTransformation();
		Shader_RenderLight.SetUniform( "PV", PVT );
		Shader_RenderLight.SetUniform( "Color", PointLights->at( i ).Color );

		PointLights->at( i ).LightSphere.Render();
	}

	OpenGL_API::Shader::Bind( NULL );
}

//-------------------------------------------------------------------------//