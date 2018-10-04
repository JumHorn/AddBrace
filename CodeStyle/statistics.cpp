/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#include <fstream>
#include "statistics.h"

#define OUTOFRANGE(a,b) if(a==b)break;

Statistics::Statistics()
{
}

Statistics::~Statistics()
{
}

bool Statistics::setContent(const string& input)
{
	fstream fin(input);
	if (!fin)
	{
		return false;
	}
	content.assign(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());
	return true;
}

void Statistics::flushContent(const string& output) const
{
	ofstream fout(output);
	for (list<char>::const_iterator iter = content.begin(); iter != content.end(); iter++)
	{
		fout << *iter;
	}
}

int Statistics::getTotalComments()
{
	list<char>::iterator tmp = content.begin();
	const list<char>::iterator& end = content.end();
	int line = 0;
	while (tmp != end)
	{
		line += countComments(tmp, end);
		OUTOFRANGE(tmp, end);
		tmp++;
	}
	return line;
}
/*
ignore the line only consist with white space
*/
int Statistics::getTotalCode()
{
	list<char>::iterator tmp = content.begin();
	const list<char>::iterator& end = content.end();
	int line = 0;
	while (tmp != end)
	{
		IgnoreWhitespace(tmp, end);
		if (*tmp == '\n')
		{
			tmp++;
		}
		else
		{
			line++;
			while (tmp != end&&*tmp != '\n')tmp++;
			if (tmp != end)
			{
				tmp++;
			}
		}
	}
	return line;
}

int Statistics::countComments(list<char>::iterator& t, const list<char>::iterator& end)
{
	if (t == end)
	{
		return 0;
	}

	int line = 0;
	if (*t == '/')
	{
		t++;
		if (*t == '/')
		{
			while (t != end&&*t != '\n')t++;
			line = 1;
		}
		else if (*t == '*')
		{
			t++;
			while (t != end)
			{
				if (*t == '*')
				{
					t++;
					if (*t == '/')
					{
						t++;
						return ++line;
					}
				}
				else if (*t == '\n')
				{
					t++;
					line++;
				}
				else
				{
					t++;
				}
			}
		}
	}
	return line;
}
