/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#ifndef _CHECK_H_
#define _CHECK_H_

#include<string>
#include<list>
#include<vector>
using namespace std;

class check
{
private:
	string filestr;
	list<char> filelist;
	vector<char> filevec;

	bool beforCheck(const char *c);
	bool afterCheck(const char *c);
	void changeendifstyle(list<char>::iterator& flag);
public:
	check();
	~check();

	void start();
	void getFileContent(const char* inputfile);
	void changeStyle(list<char>::iterator& start, list<char>::iterator& end);
	void changeifStyle(list<char>::iterator& start, list<char>::iterator& end);
	void changeforStyle(list<char>::iterator& start, list<char>::iterator& end);
	void changeelseStyle(list<char>::iterator& start, list<char>::iterator& end);
	void addelse(list<char>::iterator& start, list<char>::iterator& end);
	void writeBack(const char* outputfile);

private:
	template<typename T>
	void IgnoreComments(T& t, T& end);

	template<typename T>
	void IgnoreOneLineComments(T& t, T& end);

	template<typename T>
	void IgnoreApostrophe(T& t, T& end);

	template<typename T>
	void IgnoreQuotation(T& t, T& end);

	template<typename T>
	void IgnoreParenthesis(T& t, T& end);

	template<typename T>
	void IgnoreBrace(T& t, T& end);
};

#endif
