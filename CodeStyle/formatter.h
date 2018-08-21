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

class Formatter
{
private:
	string filestr;
	list<char> filelist;
	vector<char> filevec;

public:
	Formatter();
	~Formatter();

	void start();

	void changeIfStyle(list<char>::iterator& start, const list<char>::iterator& end);
	void changeForStyle(list<char>::iterator& start, const list<char>::iterator& end);
	void changeElseStyle(list<char>::iterator& start, const list<char>::iterator& end);
	void addElse(list<char>::iterator& start, const list<char>::iterator& end);

	bool getContent(const string& inputfile);
	void writeBack(const string& outputfile) const;

private:
	bool beforCheck(char c) const;
	bool afterCheck(char c) const;
	void changeStyle(list<char>::iterator& start, const list<char>::iterator& end, const string& token);
	bool compare(list<char>::iterator& start, const list<char>::iterator& end, const string& token) const;

private:
	template<typename T>
	void IgnoreComments(T& t, const T& end);

	template<typename T>
	void IgnoreOneLineComments(T& t, const T& end);

	template<typename T>
	void IgnoreApostrophe(T& t, const T& end);

	template<typename T>
	void IgnoreQuotation(T& t, const T& end);

	template<typename T>
	void IgnoreParenthesis(T& t, const T& end);

	template<typename T>
	void IgnoreBrace(T& t, const T& end);
};

#endif
