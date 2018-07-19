/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#include<iostream>
#include<string.h>
#include"check.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "Usage: \nAddBrace [filename]" << endl;
		cout << "Mind the file must be in the same directory with this tool" << endl;
		return 0;
	}
	if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "-V"))
	{
		cout << "V2.1" << endl;
		cout << "created by JumHorn" << endl;
		cout << "all rights reserved" << endl;
		return 0;
	}

	check style;
	for (int i = 1; i < argc; i++)
	{
		cout << "processing " << argv[i];
		style.getFileContent(argv[i]);
		style.start();
		style.writeBack(argv[i]);
		cout << "\t" << "finished" << endl;
	}

	return 0;
}
