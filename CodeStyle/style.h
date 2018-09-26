/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#ifndef _STYLE_H_
#define _STYLE_H_

#include<list>
#include<map>
#include<string>
#include "ignore.hpp"
using namespace std;

class Style : public Ignore<list<char>::iterator>
{
public:
	Style();
	~Style();

	bool setContent(const string& input);
	void flushContent(const string& output) const;
	void erasePrelineWhitespace(list<char>::iterator& start, const list<char>::iterator& end);
	void erasePostlineWhitespace(list<char>::iterator& start, const list<char>::iterator& end);
	void eraseExtraNewline(list<char>::iterator& start, const list<char>::iterator& end);
	void addNewline(list<char>::iterator& start, const list<char>::iterator& end);
	void addSpace(list<char>::iterator& start, const list<char>::iterator& end);
	void makeBraceIndentation(list<char>::iterator& start, const list<char>::iterator& end);
	void removeIndentation(list<char>::iterator& start, const list<char>::iterator& end);
	void removeNestingComment(list<char>::iterator& start, const list<char>::iterator& end);
	void start();

private:
	bool isWhitespace(char c) const;
	bool isNewline(char c) const;
	string getIndent(int indentnum);
	void makeCommentsIndentation(list<char>::iterator& t, const list<char>::iterator& end);
	void rmNestingComment(list<char>::iterator& start, const list<char>::iterator& end);

private:
	list<char> content;
	map<int, string> tab;
	int indent;
};

#endif
