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

#define OUTOFBOUNDS(a,b) if(a==b)break;

Style::Style() :indent(0)
{
	tab[0] = "";
	for (int i = 1; i < 10; i++)
	{
		tab[i] = tab[i - 1] + "\t";
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
	addNewline(iter, content.end());//eliminate hidden spaces

	iter = content.begin();
	erasePostlineWhitespace(iter, content.end());

	iter = content.begin();
	eraseExtraNewline(iter, content.end());

	iter = content.begin();
	erasePrelineWhitespace(iter, content.end());

	iter = content.begin();
	makeBraceIndentation(iter, content.end());

	iter = content.begin();
	removeIndentation(iter, content.end());

	iter = content.begin();
	removeNestingComment(iter, content.end());
}

/*
delete white character before each line
*/
void Style::erasePrelineWhitespace(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator tmp = start;
	list<char>::iterator backward;
	//delete header line white space
	while (tmp != end&&isWhitespace(*tmp))
	{
		list<char>::iterator it = tmp;
		tmp++;
		content.erase(it);
	}

	while (tmp != end)
	{
		if (*tmp != '\n')
		{
			tmp++;
			continue;
		}
		backward = tmp;
		backward++;
		while (isWhitespace(*backward))
		{
			list<char>::iterator it = backward;
			backward++;
			content.erase(it);
		}
		tmp = backward;
	}
}

/*
delete white character after each line
*/
void Style::erasePostlineWhitespace(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator tmp = start;
	list<char>::iterator forward;
	while (tmp != end)
	{
		if (*tmp != '\n' || tmp == start)
		{
			tmp++;
			continue;
		}
		forward = tmp;
		forward--;
		if (*forward == '\r')
		{
			forward--;
		}
		if (*forward == '\n')
		{
			tmp++;
			continue;
		}
		while (isWhitespace(*forward))
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
void Style::eraseExtraNewline(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator tmp = start;
	list<char>::iterator backward;
	while (tmp != end)
	{
		if (*tmp != '\n')
		{
			tmp++;
			continue;
		}
		backward = tmp;
		backward++;
		if (*backward == '\r')
		{
			backward++;
		}
		if (*backward != '\n')
		{
			tmp = backward;
			continue;
		}
		backward++;
		while ((backward != end) && (*backward == '\r' || *backward == '\n'))
		{
			list<char>::iterator it = backward;
			backward++;
			content.erase(it);
		}
		tmp = backward;
	}
	//delete tailer '\n'
	tmp--;
	while ((tmp != start) && (*tmp == '\r' || *tmp == '\n'))
	{
		list<char>::iterator it = tmp;
		tmp--;
		content.erase(it);
	}
	//delete header '\n'
	tmp = start;
	while ((tmp != end) && (*tmp == '\r' || *tmp == '\n'))
	{
		list<char>::iterator it = tmp;
		tmp++;
		content.erase(it);
	}
}

void Style::addNewline(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator& tmp = start;
	while (tmp != end)
	{
		IgnoreComments(tmp, end);
		IgnoreApostrophe(tmp, end);
		IgnoreQuotation(tmp, end);
		OUTOFBOUNDS(tmp, end);
		if (*tmp == '{'|| *tmp == '}')
		{
			list<char>::iterator t = tmp;
			t--;
			while (*t == ' ' || *t == '\t')
			{
				t--;
				if (t == start)
				{
					break;
				}
			}
			if (*t != '\n')
			{
				content.insert(tmp, '\n');
			}
			tmp++;
			IgnoreWhitespace(tmp, end);
			OUTOFBOUNDS(tmp, end);
			if (*tmp != '\n')
			{
				content.insert(tmp, '\n');
			}

		}
		else
		{
			tmp++;
		}
	}
}

void Style::addSpace(list<char>::iterator& start, const list<char>::iterator& end)
{}

void Style::makeBraceIndentation(list<char>::iterator& start, const list<char>::iterator& end)
{
	indent = 0;
	list<char>::iterator& tmp = start;
	while (tmp != end)
	{
		makeCommentsIndentation(tmp, end);
		IgnoreApostrophe(tmp, end);
		IgnoreQuotation(tmp, end);
		OUTOFBOUNDS(tmp, end);

		if (*tmp == '{')
		{
			indent++;
			tmp++;
		}
		else if (*tmp == '}' && indent > 0)
		{
			indent--;
			tmp++;
		}
		else if (*tmp == '\n')
		{
			tmp++;
			if (tmp != end)
			{
				if (*tmp == '}')
				{
					string t = getIndent(indent-1);
					content.insert(tmp, t.begin(), t.end());
				}
				else if (*tmp == '#')
				{
					//
				}
				else
				{
					string t = getIndent(indent);
					content.insert(tmp, t.begin(), t.end());
				}
			}
		}
		else
		{
			tmp++;
		}
	}
}

string Style::getIndent(int indentnum)
{
	if (indentnum < 10)
	{
		return tab[indentnum];
	}
	string indent = tab[9];
	for (int i = 0; i < indentnum - 9; i++)
	{
		indent += "\t";
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

void Style::makeCommentsIndentation(list<char>::iterator& t, const list<char>::iterator& end)
{
	if (t == end)
	{
		return;
	}

	if (*t == '/')
	{
		t++;
		if (*t == '/')
		{
			while (t != end && *t != '\n')t++;
			if (t != end)
			{
				t++;
				string tmp = getIndent(indent);
				content.insert(t, tmp.begin(), tmp.end());
				return makeCommentsIndentation(t, end);
			}
		}
		else if (*t == '*')
		{
			while (t != end)
			{
				t++;
				if (*t == '\n')
				{
					t++;
					string tmp = getIndent(indent);
					content.insert(t, tmp.begin(), tmp.end());
					t--;
				}
				else if (*t == '*')
				{
					t++;
					if (*t == '*')
					{
						t--;
					}
					else if (*t == '/')
					{
						t++;
						return makeCommentsIndentation(t, end);
					}
				}
			}
		}
	}
	return;
}

void Style::removeIndentation(list<char>::iterator& start, const list<char>::iterator& end)
{}

void Style::removeNestingComment(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator& tmp = start;
	while (tmp != end)
	{
		rmNestingComment(tmp, end);
		IgnoreApostrophe(tmp, end);
		IgnoreQuotation(tmp, end);
		OUTOFBOUNDS(tmp, end);
		tmp++;
	}
}

void Style::rmNestingComment(list<char>::iterator& t, const list<char>::iterator& end)
{
	if (t == end)
	{
		return;
	}

	while (*t == ' ' || *t == '\t' || *t == '\n' || *t == '\r')
	{
		t++;
		if (t == end)
		{
			return;
		}

	}

	if (*t == '/')
	{
		t++;
		if (*t == '/')
		{
			while (t != end && *t != '\n')t++;
			if (t != end)
			{
				t++;
				return rmNestingComment(t, end);
			}
		}
		else if (*t == '*')
		{
			while (t != end)
			{
				t++;
				if (*t == '*')
				{
					t++;
					if (*t == '*')
					{
						t--;
					}
					else if (*t == '/')
					{
						t++;
						return rmNestingComment(t, end);
					}
				}
			}
		}
	}
	return;
}