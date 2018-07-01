///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <fstream>

///////////////////////////
// LIGHTMAPMAKER
///////////////////////////
#include "Shader.h"
#include "../System/Logger.h"
using namespace OpenGL_API;

//-------------------------------------------------------------------------//

bool GetShaderCode( const string& RouteToShader, string& ShaderCode )
{
	ifstream ShaderFile( RouteToShader );
	string LineCode;

	if ( !ShaderFile.is_open() )
		return false;

	while ( getline( ShaderFile, LineCode, '\0' ) )
		ShaderCode += LineCode + '\n';

	ShaderFile.close();
	return true;
}

//-------------------------------------------------------------------------//

Shader::Shader() :
	VertexID( 0 ),
	GeometryID( 0 ),
	FragmentID( 0 ),
	ProgramID( 0 )
{}

//-------------------------------------------------------------------------//

Shader::Shader( map<string, int>& AttribLocation ) :
	VertexID( 0 ),
	GeometryID( 0 ),
	FragmentID( 0 ),
	ProgramID( 0 )
{
	this->AttribLocation = AttribLocation;
}

//-------------------------------------------------------------------------//

Shader::~Shader()
{
	if ( ProgramID != 0 )
	{
		glDeleteShader( VertexID );
		glDeleteShader( GeometryID );
		glDeleteShader( FragmentID );
		glDeleteProgram( ProgramID );
	}
}

//-------------------------------------------------------------------------//

void Shader::Bind( const Shader* Shader )
{
	if ( Shader != NULL && Shader->ProgramID )
		glUseProgram( Shader->ProgramID );
	else
		glUseProgram( 0 );
}

//-------------------------------------------------------------------------//

bool Shader::LoadFromFile( const string& VertexShader, const string& FragmentShader )
{
	string VertexShader_Code;
	string FragmentShader_Code;

	// Загружаем код вершиного шейдера
	if ( !GetShaderCode( VertexShader, VertexShader_Code ) )
	{
		PRINT_LOG( "Error: File [" << VertexShader << "] Not Found" );
		return false;
	}

	// Загружаем код фрагментного шейдера
	if ( !GetShaderCode( FragmentShader, FragmentShader_Code ) )
	{
		PRINT_LOG( "Error: File [" << FragmentShader << "] Not Found" );
		return false;
	}

	// Компилируем шейдер
	return Compile( VertexShader_Code, "", FragmentShader_Code );
}

//-------------------------------------------------------------------------//

bool Shader::LoadFromFile( const string& VertexShader, const string& GeometryShader, const string& FragmentShader )
{
	string VertexShader_Code;
	string GeometryShader_Code;
	string FragmentShader_Code;

	// Загружаем код вершиного шейдера
	if ( !GetShaderCode( VertexShader, VertexShader_Code ) )
	{
		PRINT_LOG( "Error: File [" << VertexShader << "] Not Found" );
		return false;
	}

	// Загружаем код геометрического шейдера
	if ( !GetShaderCode( GeometryShader, GeometryShader_Code ) )
	{
		PRINT_LOG( "Error: File [" << GeometryShader << "] Not Found" );
		return false;
	}

	// Загружаем код фрагментного шейдера
	if ( !GetShaderCode( FragmentShader, FragmentShader_Code ) )
	{
		PRINT_LOG( "Error: File [" << FragmentShader << "] Not Found" );
		return false;
	}

	// Компилируем шейдер
	return Compile( VertexShader_Code, GeometryShader_Code, FragmentShader_Code );
}

//-------------------------------------------------------------------------//

bool Shader::LoadFromMemory( const string& VertexShader, const string& FragmentShader )
{
	return Compile( VertexShader, "", FragmentShader );
}

//-------------------------------------------------------------------------//

bool Shader::LoadFromMemory( const string& VertexShader, const string& GeometryShader, const string& FragmentShader )
{
	return Compile( VertexShader, GeometryShader, FragmentShader );
}

//-------------------------------------------------------------------------//

void Shader::SetAttribLocation( map<string, int>& AttribLocation )
{
	this->AttribLocation = AttribLocation;
}

//-------------------------------------------------------------------------//

const GLuint& Shader::GetNativeHandle()
{
	return ProgramID;
}

//-------------------------------------------------------------------------//

bool Shader::Compile( const string& VertexShader, const string& GeometryShader, const string& FragmentShader )
{
	// Удаляем шейдер, если был уже создан
	if ( ProgramID != 0 )
	{
		glDeleteShader( VertexID );
		glDeleteShader( GeometryID );
		glDeleteShader( FragmentID );
		glDeleteProgram( ProgramID );
	}

	Uniforms.clear();
	ProgramID = glCreateProgram();

	// *************************
	// Создаем вершинный шейдер

	if ( !VertexShader.empty() )
	{
		int ErrorCompilation = 0;
		const char* CodeSource = VertexShader.c_str();

		VertexID = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( VertexID, 1, &CodeSource, NULL );
		glCompileShader( VertexID );

		// Проверяем результат компиляции	
		glGetShaderiv( VertexID, GL_COMPILE_STATUS, &ErrorCompilation );

		// Если произошла ошибка
		if ( ErrorCompilation != GL_TRUE )
		{
			int LengthLog = 0;
			char *Error;

			glGetShaderiv( VertexID, GL_INFO_LOG_LENGTH, &LengthLog );
			Error = new char[ LengthLog ];

			glGetShaderInfoLog( VertexID, LengthLog, &LengthLog, Error );

			if ( Error[ LengthLog - 1 ] == '\n' )
				Error[ LengthLog - 1 ] = '\0';

			if ( Error[ LengthLog - 2 ] == '\n' )
				Error[ LengthLog - 2 ] = '\0';

			PRINT_LOG( "**** Shader Error ****" );
			PRINT_LOG( "Failed To Compile Vertex Shader:" );
			PRINT_LOG( Error );
			PRINT_LOG( "**** Shader Error End ****" );

			delete[] Error;
			glDeleteShader( VertexID );
			glDeleteProgram( ProgramID );
			return false;
		}

		glAttachShader( ProgramID, VertexID );
	}

	// *************************
	// Создаем геометрический шейдер

	if ( !GeometryShader.empty() )
	{
		int ErrorCompilation = 0;
		const char* CodeSource = GeometryShader.c_str();

		GeometryID = glCreateShader( GL_GEOMETRY_SHADER );
		glShaderSource( GeometryID, 1, &CodeSource, NULL );
		glCompileShader( GeometryID );

		// Проверяем результат компиляции	
		glGetShaderiv( GeometryID, GL_COMPILE_STATUS, &ErrorCompilation );

		// Если произошла ошибка
		if ( ErrorCompilation != GL_TRUE )
		{
			int LengthLog = 0;
			char *Error;

			glGetShaderiv( GeometryID, GL_INFO_LOG_LENGTH, &LengthLog );
			Error = new char[ LengthLog ];

			glGetShaderInfoLog( GeometryID, LengthLog, &LengthLog, Error );
			
			if ( Error[ LengthLog - 1 ] == '\n' )
				Error[ LengthLog - 1 ] = '\0';

			if ( Error[ LengthLog - 2 ] == '\n' )
				Error[ LengthLog - 2 ] = '\0';

			PRINT_LOG( "**** Shader Error ****" );
			PRINT_LOG( "Failed To Compile Geometry Shader:" );
			PRINT_LOG( Error );
			PRINT_LOG( "**** Shader Error End ****" );

			delete[] Error;
			glDeleteShader( GeometryID );
			glDeleteProgram( ProgramID );
			return false;
		}

		glAttachShader( ProgramID, GeometryID );
	}

	// *************************
	// Создаем фрагментный шейдер

	if ( !FragmentShader.empty() )
	{
		int ErrorCompilation = 0;
		const char* CodeSource = FragmentShader.c_str();

		FragmentID = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( FragmentID, 1, &CodeSource, NULL );
		glCompileShader( FragmentID );

		// Проверяем результат компиляции	
		glGetShaderiv( FragmentID, GL_COMPILE_STATUS, &ErrorCompilation );

		// Если произошла ошибка
		if ( ErrorCompilation != GL_TRUE )
		{
			int LengthLog = 0;
			char *Error;

			glGetShaderiv( FragmentID, GL_INFO_LOG_LENGTH, &LengthLog );
			Error = new char[ LengthLog ];

			glGetShaderInfoLog( FragmentID, LengthLog, &LengthLog, Error );
			
			if ( Error[ LengthLog - 1 ] == '\n' )
				Error[ LengthLog - 1 ] = '\0';

			if ( Error[ LengthLog - 2 ] == '\n' )
				Error[ LengthLog - 2 ] = '\0';

			PRINT_LOG( "**** Shader Error ****" );
			PRINT_LOG( "Failed To Compile Fragment Shader:" );
			PRINT_LOG( Error );
			PRINT_LOG( "**** Shader Error End ****" );

			delete[] Error;
			glDeleteShader( FragmentID );
			glDeleteProgram( ProgramID );
			return false;
		}

		glAttachShader( ProgramID, FragmentID );
	}

	// *********************************
	// Задаем позицию для атрибутов вершин и линкуем программу 

	for ( auto it = AttribLocation.begin(); it != AttribLocation.end(); it++ )
		glBindAttribLocation( ProgramID, it->second, it->first.c_str() );

	glLinkProgram( ProgramID );

	// *********************************
	// Провераем линковку

	int ErrorLink = 0;
	glGetProgramiv( ProgramID, GL_LINK_STATUS, &ErrorLink );

	if ( ErrorLink != GL_TRUE )
	{
		int LengthLog = 0;
		char *Error;

		glGetProgramiv( ProgramID, GL_INFO_LOG_LENGTH, &LengthLog );
		Error = new char[ LengthLog ];

		glGetShaderInfoLog( ProgramID, LengthLog, &LengthLog, Error );
		
		if ( Error[ LengthLog - 1 ] == '\n' )
			Error[ LengthLog - 1 ] = '\0';

		if ( Error[ LengthLog - 2 ] == '\n' )
			Error[ LengthLog - 2 ] = '\0';

		PRINT_LOG( "**** Shader Error ****" );
		PRINT_LOG( "Failed To Link Shader:" );
		PRINT_LOG( Error );
		PRINT_LOG( "**** Shader Error End ****" );

		delete[] Error;
		glDeleteShader( VertexID );
		glDeleteShader( GeometryID );
		glDeleteShader( FragmentID );
		glDeleteProgram( ProgramID );
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------//

void Shader::SetUniform( const string& Name, bool X )
{
	if ( ProgramID != 0 )
	{
		GLuint SavedProgram = glGetHandleARB( GL_PROGRAM_OBJECT_ARB );

		if ( ProgramID != SavedProgram )
			glUseProgram( ProgramID );

		int Location = GetUniformLocation( Name );

		if ( Location != -1 )
			glUniform1i( Location, static_cast< int >( X ) );

		if ( ProgramID != SavedProgram )
			glUseProgram( SavedProgram );
	}
}

//-------------------------------------------------------------------------//

void Shader::SetUniform( const string& Name, int X )
{
	if ( ProgramID != 0 )
	{
		GLuint SavedProgram = glGetHandleARB( GL_PROGRAM_OBJECT_ARB );

		if ( ProgramID != SavedProgram )
			glUseProgram( ProgramID );

		int Location = GetUniformLocation( Name );

		if ( Location != -1 )
			glUniform1i( Location, X );

		if ( ProgramID != SavedProgram )
			glUseProgram( SavedProgram );
	}
}

//-------------------------------------------------------------------------//

void Shader::SetUniform( const string& Name, float X )
{
	if ( ProgramID != 0 )
	{
		GLuint SavedProgram = glGetHandleARB( GL_PROGRAM_OBJECT_ARB );

		if ( ProgramID != SavedProgram )
			glUseProgram( ProgramID );

		int Location = GetUniformLocation( Name );

		if ( Location != -1 )
			glUniform1f( Location, X );

		if ( ProgramID != SavedProgram )
			glUseProgram( SavedProgram );
	}
}

//-------------------------------------------------------------------------//

void Shader::SetUniform( const string& Name, GLuint& X )
{
	if ( ProgramID != 0 )
	{
		GLuint SavedProgram = glGetHandleARB( GL_PROGRAM_OBJECT_ARB );

		if ( ProgramID != SavedProgram )
			glUseProgram( ProgramID );

		int Location = GetUniformLocation( Name );

		if ( Location != -1 )
			glUniform1i( Location, X );

		if ( ProgramID != SavedProgram )
			glUseProgram( SavedProgram );
	}
}

//-------------------------------------------------------------------------//

void Shader::SetUniform( const string& Name, glm::mat4& Matrix )
{
	if ( ProgramID != 0 )
	{
		GLuint SavedProgram = glGetHandleARB( GL_PROGRAM_OBJECT_ARB );

		if ( ProgramID != SavedProgram )
			glUseProgram( ProgramID );

		int Location = GetUniformLocation( Name );

		if ( Location != -1 )
			glUniformMatrix4fv( Location, 1, GL_FALSE, glm::value_ptr( Matrix ) );

		if ( ProgramID != SavedProgram )
			glUseProgram( SavedProgram );
	}
}

//-------------------------------------------------------------------------//

void Shader::SetUniform( const string& Name, glm::vec2& Vector2 )
{
	if ( ProgramID != 0 )
	{
		GLuint SavedProgram = glGetHandleARB( GL_PROGRAM_OBJECT_ARB );

		if ( ProgramID != SavedProgram )
			glUseProgram( ProgramID );

		int Location = GetUniformLocation( Name );

		if ( Location != -1 )
			glUniform2f( Location, Vector2.x, Vector2.y );

		if ( ProgramID != SavedProgram )
			glUseProgram( SavedProgram );
	}
}

//-------------------------------------------------------------------------//

void Shader::SetUniform( const string& Name, glm::vec3& Vector3 )
{
	if ( ProgramID != 0 )
	{
		GLuint SavedProgram = glGetHandleARB( GL_PROGRAM_OBJECT_ARB );

		if ( ProgramID != SavedProgram )
			glUseProgram( ProgramID );

		int Location = GetUniformLocation( Name );

		if ( Location != -1 )
			glUniform3f( Location, Vector3.x, Vector3.y, Vector3.z );

		if ( ProgramID != SavedProgram )
			glUseProgram( SavedProgram );
	}
}

//-------------------------------------------------------------------------//

void Shader::SetUniform( const string& Name, glm::vec4& Vector4 )
{
	if ( ProgramID != 0 )
	{
		GLuint SavedProgram = glGetHandleARB( GL_PROGRAM_OBJECT_ARB );

		if ( ProgramID != SavedProgram )
			glUseProgram( ProgramID );

		int Location = GetUniformLocation( Name );

		if ( Location != -1 )
			glUniform4f( Location, Vector4.x, Vector4.y, Vector4.z, Vector4.w );

		if ( ProgramID != SavedProgram )
			glUseProgram( SavedProgram );
	}
}

//-------------------------------------------------------------------------//

int Shader::GetUniformLocation( const string& NameUniform )
{
	// Провиряем кеш юниформов
	auto it = Uniforms.find( NameUniform );

	// Нашли в кеше - возвращаем позицию с него
	if ( it != Uniforms.end() )
		return it->second;
	else
	{
		// В кеше не нашли, то тогда запрашиваем позицию в OpenGL'е
		int Location = glGetUniformLocation( ProgramID, NameUniform.c_str() );
		Uniforms.insert( std::make_pair( NameUniform, Location ) );

		if ( Location == -1 )
			PRINT_LOG( "Uniform [" << NameUniform << "] Not Found In Shader" );

		return Location;
	}
}

//-------------------------------------------------------------------------//