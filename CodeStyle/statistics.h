/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

/*
add up comment line and real code line
*/

#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include <string>
#include <list>
#include "ignore.hpp"
using namespace std;

class Statistics : public Ignore<list<char>::iterator>
{
public:
	Statistics();
	~Statistics();

	bool setContent(const string& input);
	void flushContent(const string& output) const;

	int getTotalComments();
	int getTotalCode();

private:
	list<char> content;

private:
	int countComments(list<char>::iterator& start, const list<char>::iterator& end);
};

#endif