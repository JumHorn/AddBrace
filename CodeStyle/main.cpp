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
		cout << "V1.0" << endl;
		cout << "created by JumHorn" << endl;
		cout << "all rights reserved" << endl;
		return 0;
	}

	check style;
	for (int i = 1; i < argc; i++)
	{
		cout << "processing " << argv[i];
		style.getFileContent(argv[i]);
		style.changeStyle();
		style.writeBack(argv[i]);
		cout << "\t" << "finished" << endl;
	}

	return 0;
}