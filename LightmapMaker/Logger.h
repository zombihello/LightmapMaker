//////////////////////////////////////////////////////////////////////////
// 
//				*** LightmapMaker ***
//				  Copyright (C) 2018
//
// ����� �� ����:		https://vk.com/zombihello
// ����������� ������:  https://github.com/zombihello/LightmapMaker
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LOGGER_H
#define LOGGER_H

#define PRINT_LOG( X ) Logger::Log << X << endl; cout << X << endl;

///////////////////////////
// ��������� ����������
///////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Logger
{
public:
	/* ��������� ���� � ���� */
	static void SaveInFile( const string& Route );

	/* �������� ���� */
	static void Clear();

	static stringstream		Log;
};

#endif // LOGGER_H

