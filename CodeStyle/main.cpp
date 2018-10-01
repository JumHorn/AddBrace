/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#include<iostream>
#include<string>
#include<string.h> //for strcmp
#include"formatter.h"
#include"style.h"
#include"statistics.h"
using namespace std;

int main(int argc, char* argv[])
{
	string pig =
		"                              _   \n"
		"      _._ _..._ .-',     _.._(`))  \n"
		"     '-. `     '  /-._.-'    ',/   \n"
		"       )         \\            '.   \n"
		"      / _    _    |             \\  \n"
		"     |  a    a    /              | \n"
		"      \\   .-.                     ;\n"
		"       '-('' ).-'       ,'       ; \n"
		"          '-;           |      .'  \n"
		"            \\           \\    /     \n"
		"            | 7  .__  _.-\\   \\     \n"
		"            | |  |  ``/  /`  /     \n"
		"           /,_|  |   /,_/   /      \n"
		"              /,_/      '`-'       \n";
	if (argc == 1)
	{
		cout << endl;
		cout << "WARNING: This tool may destroy your code:" << endl;
		cout << "A Safety Pig has been provided below for your benefit" << endl;
		cout << pig << endl;

		cout << "Usage: \nAddBrace [filename] ..." << endl;
		cout << "The file must be in the same directory with this tool or input the absolute path of your files" << endl;
		return 0;
	}
	if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "-V"))
	{
		cout << endl;
		cout << "WARNING: This tool may destroy your code:" << endl;
		cout << "A Safety Pig has been provided below for your benefit" << endl;
		cout << pig << endl;

		cout << "Version 3.1" << endl;
		cout << "created by JumHorn" << endl;
		cout << "all rights reserved" << endl;
		return 0;
	}

	Formatter formatter;
	Style checker;
	Statistics st;
	for (int i = 1; i < argc; i++)
	{
		if (!formatter.setContent(argv[i]))
		{
			continue;
		}
		cout << "processing " << argv[i];
		formatter.start();
		formatter.flushContent(argv[i]);

		checker.setContent(argv[i]);
		checker.start();
		checker.flushContent(argv[i]);
		cout << "\t" << "finished" << endl;

		st.setContent(argv[i]);
		cout << "code line: " << st.getTotalCode() << endl;
		cout << "comment line: " << st.getTotalComments() << endl;
	}

	cout << endl;
	cout << "WARNING: These changes cannot be cancelled:" << endl;
	cout << "A Safety Pig has been provided below for your benefit" << endl;
	cout << pig << endl;
	return 0;
}
