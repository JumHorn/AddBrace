/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#include <fstream>
#include "style.h"
#include "char.h"
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
	fstream fin(input);
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

void Style::start()
{
	list<char>::iterator iter = content.begin();
	erasePostlineWhitespace(iter,content.end());
}
/*
delete white character before each line
*/
void Style::erasePrelineWhitespace(list<char>::iterator& start,const list<char>::iterator end)
{
}


/*
delete white character after each line
*/
void Style::erasePostlineWhitespace(list<char>::iterator& start,const list<char>::iterator end)
{
	list<char>::iterator tmp;
	list<char>::iterator forward;
	while(tmp!=end)
	{
		if(*tmp!='\n')
		{
			tmp++;
			continue;
		}
		forward=tmp;
		forward--;
		if(*forward=='\r')
		{
			forward--;
		}
		if(*forward=='\n')
		{
			continue;
		}
		while(isWhitespace(*forward))
		{
			list<char>::iterator it = forward;
			forward--;
			content.erase(it);
		}
	}
}

/*
delete extra new line
*/
void Style::eraseExtraNewline(list<char>::iterator& start,const list<char>::iterator end)
{}

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

bool Style::isWhitespace(char c) const
{
	unsigned int temp = ARRAY_SIZE(white_space);
	return white_space + temp != find(white_space, white_space + temp, c);
}
