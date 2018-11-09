/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#include <fstream>
#include <vector>
#include <string>
#include "style.h"
#include "char.h"
using namespace std;

#define OUTOFRANGE(a,b) if((a)==(b))break;

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

	iter = content.begin();
	addSpace(iter, content.end());
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
		IgnoreMacro(tmp, end);
		OUTOFRANGE(tmp, end);
		list<char>::iterator it = tmp;
		tmp++;
		content.erase(it);
	}

	while (tmp != end)
	{
		IgnoreMacro(tmp, end);
		OUTOFRANGE(tmp, end);
		if (*tmp != '\n')
		{
			tmp++;
			continue;
		}
		backward = tmp;
		backward++;
		while (backward != end&&isWhitespace(*backward))
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
		IgnoreMacro(tmp, end);
		OUTOFRANGE(tmp, end);
		if (*tmp != '\n')
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
		while (isWhitespace(*forward) && forward != start)
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
	if (tmp == end)
	{
		return;
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
		if (backward == end)
		{
			tmp = backward;
			break;
		}
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
	//for some compiler need a new line at the end of the file
	content.insert(++tmp, '\n');
	//delete header '\n'
	tmp = start;
	while ((tmp != end) && (*tmp == '\r' || *tmp == '\n'))
	{
		list<char>::iterator it = tmp;
		tmp++;
		content.erase(it);
	}
}

/*
add new line before and after brace
add new line after ;
*/
void Style::addNewline(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator& tmp = start;
	while (tmp != end)
	{
		IgnoreComments(tmp, end);
		IgnoreApostrophe(tmp, end);
		IgnoreQuotation(tmp, end);
		IgnoreParenthesis(tmp, end);
		IgnoreMacro(tmp, end);
		IgnoreComments(tmp, end);
		OUTOFRANGE(tmp, end);
		if (*tmp == '{' || *tmp == '}')
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
			if (*t == '=')
			{
				IgnoreBrace(tmp, end);
				continue;
			}
			else if (*t != '\n')
			{
				content.insert(tmp, '\n');
			}

			if (*tmp == '{')
			{
				tmp++;
				IgnoreWhitespace(tmp, end);
				OUTOFRANGE(tmp, end);
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
		else if (*tmp == ';')
		{
			tmp++;
			IgnoreWhitespace(tmp, end);
			OUTOFRANGE(tmp, end);
			if (*tmp != '\n'&&*tmp != '/')
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

/*
add space before and after operator
*/
void Style::addSpace(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator& tmp = start;
	list<char>::iterator runner = start;
	vector<string> op(oper, oper + ARRAY_SIZE(oper));
	while (tmp != end)
	{
		IgnoreComments(tmp, end);
		IgnoreApostrophe(tmp, end);
		IgnoreQuotation(tmp, end);
		OUTOFRANGE(tmp, end);
		runner = tmp;
		if (compare(runner, end, op))
		{
			if (*runner != ' '&&*runner != '\t')
			{
				content.insert(runner, ' ');
			}
			tmp--;
			if (*tmp != ' '&&*tmp != '\t')
			{
				tmp++;
				content.insert(tmp, ' ');
			}
		}
		tmp = runner;
	}
}

bool Style::compare(list<char>::iterator& start, const list<char>::iterator& end, const vector<string>& opers) const
{
	list<char>::iterator runner = start;
	for (vector<string>::size_type i = 0; i < opers.size(); i++)
	{
		string::size_type j = 0;
		runner = start;
		for (j = 0; j < opers[i].length(); j++)
		{
			if (runner == end)
			{
				start = runner;
				return false;
			}
			else if (*runner++ != opers[i][j])
			{
				break;
			}
		}
		if (j == opers[i].length())
		{
			start = runner;
			return true;
		}
	}
	start = runner;
	return false;
}

void Style::makeBraceIndentation(list<char>::iterator& start, const list<char>::iterator& end)
{
	indent = 0;
	list<char>::iterator& tmp = start;
	while (tmp != end)
	{
		makeCommentsIndentation(tmp, end);
		IgnoreApostrophe(tmp, end);
		IgnoreQuotation(tmp, end);
		OUTOFRANGE(tmp, end);

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
					string str = getIndent(indent - 1);
					content.insert(tmp, str.begin(), str.end());
				}
				else if (*tmp == '#')
				{
					//
				}
				else
				{
					string str = getIndent(indent);
					content.insert(tmp, str.begin(), str.end());
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
		}
		else if (*t == '*')
		{
			t++;
			while (t != end)
			{
				if (*t == '\n')
				{
					t++;
					string tmp = getIndent(indent);
					content.insert(t, tmp.begin(), tmp.end());
				}
				else if (*t == '*')
				{
					t++;
					if (*t == '/')
					{
						t++;
						return makeCommentsIndentation(t, end);
					}
				}
				else
				{
					t++;
				}
			}
		}
	}
	return;
}

void Style::removeIndentation(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator& tmp = start;
	while (tmp != end)
	{
		IgnoreComments(tmp, end);
		IgnoreApostrophe(tmp, end);
		IgnoreQuotation(tmp, end);
		OUTOFRANGE(tmp, end);
		if (*tmp == ':')
		{
			list<char>::iterator it = tmp;
			IgnoreWhitespace(++it, end);
			OUTOFRANGE(it, end);
			if (*it == '\n' || *it == '/')
			{
				it = tmp;
				while (*it != '\n')it--;
				it++;
				if (*it == '\t')
				{
					content.erase(it);
				}
			}
		}
		tmp++;
	}
}

void Style::removeNestingComment(list<char>::iterator& start, const list<char>::iterator& end)
{
	list<char>::iterator& tmp = start;
	while (tmp != end)
	{
		rmNestingComment(tmp, end);
		IgnoreApostrophe(tmp, end);
		IgnoreQuotation(tmp, end);
		OUTOFRANGE(tmp, end);
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
			t++;
			while (t != end)
			{
				if (*t == '\n')
				{
					t++;
					return rmNestingComment(t, end);
				}
				else if (*t == '/')
				{
					t++;
					if (*t == '\n')
					{
						t++;
						return rmNestingComment(t, end);
					}
					else if (*t == '*')
					{
						list<char>::iterator it = t;
						it--;
						t++;
						content.erase(it, t);
					}
				}
				else if (*t == '*')
				{
					t++;
					if (*t == '\n')
					{
						t++;
						return rmNestingComment(t, end);
					}
					else if (*t == '/')
					{
						list<char>::iterator it = t;
						it--;
						t++;
						content.erase(it, t);
					}
				}
				else
				{
					t++;
				}
			}
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
						return rmNestingComment(t, end);
					}
				}
				else if (*t == '/')
				{
					t++;
					if (*t == '/')
					{
						list<char>::iterator it = t;
						it--;
						t++;
						content.erase(it, t);
					}
					else if (*t == '*')
					{
						t++;
						if (*t == '/')
						{
							return rmNestingComment(t, end);
						}
						else
						{
							list<char>::iterator it = t;
							advance(it, -2);
							content.erase(it, t);
						}
					}
				}
				else
				{
					t++;
				}
			}
		}
	}
	return;
}
