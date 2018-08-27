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
	iter = content.begin();
	eraseExtraNewline(iter,content.end());
	iter = content.begin();
	erasePrelineWhitespace(iter,content.end());
}
/*
delete white character before each line
*/
void Style::erasePrelineWhitespace(list<char>::iterator& start,const list<char>::iterator end)
{
	list<char>::iterator tmp = start;
	list<char>::iterator backward;
	//delete header line white space
	while(tmp!=end&&isWhitespace(*tmp))
	{
		list<char>::iterator it = tmp;
		tmp++;
		content.erase(it);
	}

	while(tmp!=end)
	{
		if(*tmp!='\n')
		{
			tmp++;
			continue;
		}
		backward=tmp;
		backward++;
		while(isWhitespace(*backward))
		{
			list<char>::iterator it = backward;
			backward++;
			content.erase(it);
		}
		tmp=backward;
	}
}


/*
delete white character after each line
*/
void Style::erasePostlineWhitespace(list<char>::iterator& start,const list<char>::iterator end)
{
	list<char>::iterator tmp = start;
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
			tmp++;
			continue;
		}
		while(isWhitespace(*forward))
		{
			list<char>::iterator it = forward;
			forward--;
			content.erase(it);
		}
		tmp++;
	}
}

/*
delete extra new line
*/
void Style::eraseExtraNewline(list<char>::iterator& start,const list<char>::iterator end)
{
	list<char>::iterator tmp = start;
	list<char>::iterator backward;
	while(tmp!=end)
	{
		if(*tmp!='\n')
		{
			tmp++;
			continue;
		}
		backward=tmp;
		backward++;
		if(*backward=='\r')
		{
			backward++;
		}
		if(*backward!='\n')
		{
			tmp=backward;
			continue;
		}
		backward++;
		while((backward!=end)&&(*backward=='\r'||*backward=='\n'))
		{
			list<char>::iterator it = backward;
			backward++;
			content.erase(it);
		}
		tmp=backward;
	}
	//delete tailer '\n'
	tmp--;
	while((tmp!=start)&&(*tmp=='\r'||*tmp=='\n'))
	{
		list<char>::iterator it = tmp;
		tmp--;
		content.erase(it);
	}
	//delete header '\n'
	tmp=start;
	while((tmp!=end)&&(*tmp=='\r'||*tmp=='\n'))
	{
		list<char>::iterator it = tmp;
		tmp++;
		content.erase(it);
	}
}

void addNewline(list<char>::iterator& start,const list<char>::iterator end)
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

bool Style::isNewline(char c) const
{
	unsigned int temp = ARRAY_SIZE(new_line);
	return new_line + temp != find(new_line, new_line + temp, c);
}

bool Style::isWhitespace(char c) const
{
	unsigned int temp = ARRAY_SIZE(white_space);
	return white_space + temp != find(white_space, white_space + temp, c);
}
