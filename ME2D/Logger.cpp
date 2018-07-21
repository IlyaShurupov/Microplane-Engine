/*
* Logger
* Copyright (c) 2018 Ivan Kmeťo
*
* Licensed under the MIT License.
* http://opensource.org/licenses/mit-license
*/

#include "stdafx.h"
#include <string>
#include <fstream>

#include "Logger.h"
#include "uConfig.h"

std::fstream filehandle{};

void Logger(std::string func, std::string file, int line) {
	std::string code = "logging: Func: " + func + " in file: " + file;
	code += " on line " + std::to_string(line) + "\n";;

	std::cout << code;

	Log_Write(code);
}

bool Log_Open(std::string filename) {
	if (!filehandle.is_open()) {
		filehandle.open(filename.c_str(), std::ios_base::app | std::ios::out);

		_wsetlocale(LC_ALL, L"");
		std::ios_base::sync_with_stdio(false);
		filehandle.imbue(std::locale(""));

		return true;
	}

	return false;
}

void Log_Write(std::string text) {
	if (filehandle.is_open()) {
		filehandle << text;
	}
}

bool Log_Close() {
	if (filehandle.is_open()) {
		filehandle.close();

		return true;
	}

	return false;
}

void Log_Init(std::string filename) {
	if (!filehandle.is_open()) {
		filehandle.open(filename.c_str(), std::ios::out | std::ios::trunc);

		filehandle << "Debug Log\n--------------\n";
		filehandle << MEDEF_USR_APPNAME << " | " << MEDEF_USR_APPDEVN;
		filehandle << " | " << MEDEF_USR_APPVERD;
		filehandle << " | " << MEDEF_USR_APPVERS;
		filehandle << "\n";
		filehandle << MEDEF_ENG_ENGNAME << " (" << MEDEF_ENG_ENGABBV << ")";
		filehandle << " | " << MEDEF_ENG_ENGVERD;
		filehandle << " | " << MEDEF_ENG_ENGVERS;
		filehandle << "\n--------------\n";

		Log_Close();
	}
}

void Log_End(std::string filename) {
	if (!filehandle.is_open()) {
		filehandle.open(filename.c_str(), std::ios_base::app | std::ios::out);
		filehandle << "\nEND\n";
		Log_Close();
	}
}

void Log_WriteIn(std::string text, std::string filename) {
	if (!filehandle.is_open()) {
		filehandle.open(filename.c_str(), std::ios_base::app | std::ios::out);
		filehandle << text << "\n";
		filehandle.close();
	}
	filehandle << text << "\n";
	filehandle.close();
}