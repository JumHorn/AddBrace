/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#include <fstream>
#include "style.h"
using namespace std;

Style::Style()
{
	tab[0]="";
	for(int i=1;i<10;i++)
	{
		tab[i]=tab[i-1]+"\t";
	}
}

Style::~Style()
{
}

bool Style::setContent(const string& input)
{
	ifstream fin(input);
	if (!fin)
	{
		return false;
	}
	content.assign(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());
	return true;
}

void Style::flushContent(const string& output) const
{
	ofstream fout(output);
	for (list<char>::const_iterator iter = content.begin(); iter != content.end(); iter++)
	{
		fout << *iter;
	}

}

void Style::Format()
{
}

string Style::getIndent(int indentnum) 
{
	if(indentnum<10)
	{
		return tab[indentnum];
	}
	string indent=tab[9];
	for(int i=0;i<indentnum-9;i++)
	{
		indent+="\t";
	}
	return indent;
}
