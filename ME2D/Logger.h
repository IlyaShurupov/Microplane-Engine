/*
* Logger
* Copyright (c) 2018 Ivan Kmeťo
*
* Licensed under the MIT License.
* http://opensource.org/licenses/mit-license
*/

#pragma once

#include <iostream>

void Logger(std::string func, std::string file, int line);

#define Error(x)\
	if (x) {\
	Logger(#x, __FILE__, __LINE__);\
}

bool Log_Open(std::string);
void Log_Write(std::string);
bool Log_Close();
void Log_Init(std::string);
void Log_End(std::string);
void Log_WriteIn(std::string text, std::string);