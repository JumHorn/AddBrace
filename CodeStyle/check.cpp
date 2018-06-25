/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#include<iostream>
#include<fstream>
#include<algorithm>
#include "check.h"
#include "char.h"
using namespace std;

#define OutofBounds(a,b) if(a==b)break;

check::check()
{
}

check::~check()
{
}

void check::getFileContent(const char* inputfile)
{
	ifstream fin(inputfile);
	//构建string,list,vector等待优化
	//string filestr((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
	filelist.assign(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());
	//filelist.assign(filestr.begin(), filestr.end());
	//filevec.assign(filestr.begin(),filestr.end());
}

bool check::beforCheck(const char *c)
{
	unsigned int temp = ARRAY_SIZE(befor_check);
	return befor_check + temp != find(befor_check, befor_check + temp, *c);
}

bool check::afterCheck(const char *c)
{
	unsigned int temp = ARRAY_SIZE(after_check);
	return after_check + temp != find(after_check, after_check + temp, *c);
}

void check::changeifStyle()
{
	list<char>::iterator worker;
	list<char>::iterator runner;
	list<char>::iterator temp;
	temp = filelist.begin();
	while (temp != filelist.end())
	{
		IgnoreComments(temp);//ignore comments
		IgnoreApostrophe(temp);
		IgnoreQuotation(temp);
		OutofBounds(temp, filelist.end());

		if (*temp != 'i')
		{
			temp++;
			continue;
		}

		runner = worker = temp;
		int i;
		for (i = 1; i < ARRAY_SIZE(check_if); i++)
		{
			runner++;
			if (*runner != check_if[i])
			{
				break;
			}
		}
		if (i != ARRAY_SIZE(check_if))
		{
			temp++;
			continue;
		}

		runner++;
		worker--;
		temp = runner;
		if (worker != filelist.end() && beforCheck(&*worker) && runner != filelist.end() && afterCheck(&*runner)) //处理if token
		{
			IgnoreComments(runner);
			IgnoreApostrophe(runner);
			IgnoreQuotation(runner);
			IgnoreParenthesis(runner);
			temp = runner;
			//此时处理到if结束的)括号处
			worker = runner;
			for (; runner != filelist.end(); runner++)
			{
				IgnoreComments(runner);
				IgnoreApostrophe(runner);
				IgnoreQuotation(runner);
				//IgnoreParenthesis(runner);
				IgnoreComments(runner);

				if (*runner == '{')
				{
					break;
				}
				else if (*runner == ';')
				{
					runner++;
					filelist.insert(runner, '}');
					filelist.insert(worker, '{');
					break;
				}
				else if (!beforCheck(&*runner))
				{
					filelist.insert(runner, '{');
					for (worker = runner; worker != filelist.end(); worker++)
					{
						IgnoreComments(worker);
						IgnoreApostrophe(worker);
						IgnoreQuotation(worker);
						IgnoreParenthesis(worker);

						if (*worker == ';')
						{
							worker++;
							IgnoreOneLineComments(worker);
							filelist.insert(worker, '}');
							break;
						}
						else if (*worker == '{')
						{
							IgnoreBrace(worker);
							filelist.insert(worker, '}');
							break;
						}
					}
					break;
				}
			}
		}
		else
		{
			continue;
		}

		if (temp != filelist.end())
		{
			temp++;
		}
	}
}

void check::changeforStyle()
{
	list<char>::iterator worker;
	list<char>::iterator runner;
	list<char>::iterator temp;
	temp = filelist.begin();
	while (temp != filelist.end())
	{
		IgnoreComments(temp);
		IgnoreApostrophe(temp);
		IgnoreQuotation(temp);
		OutofBounds(temp, filelist.end());

		if (*temp != 'f')
		{
			temp++;
			continue;
		}

		runner = worker = temp;
		int i;
		for (i = 1; i < ARRAY_SIZE(check_for); i++)
		{
			if (runner == filelist.end())
			{
				break;
			}
			runner++;
			if (runner != filelist.end() && *runner != check_for[i])
			{
				break;
			}
		}
		if (i != ARRAY_SIZE(check_for))
		{
			if (temp != filelist.end())
			{
				temp++;
			}
			continue;
		}

		runner++;
		worker--;
		temp = runner;
		if (worker != filelist.end() && beforCheck(&*worker) && runner != filelist.end() && afterCheck(&*runner)) //处理for token
		{
			IgnoreComments(runner);
			IgnoreApostrophe(runner);
			IgnoreQuotation(runner);
			IgnoreParenthesis(runner);
			temp = runner;
			//此时处理到for结束的)括号处
			worker = runner;
			for (; runner != filelist.end(); runner++)
			{
				IgnoreComments(runner);
				IgnoreApostrophe(runner);
				IgnoreQuotation(runner);
				//IgnoreParenthesis(runner);
				IgnoreComments(runner);

				if (*runner == '{')
				{
					break;
				}
				else if (*runner == ';')
				{
					runner++;
					filelist.insert(runner, '}');
					filelist.insert(worker, '{');
					break;
				}
				else if (!beforCheck(&*runner))
				{
					IgnoreComments(runner);
					filelist.insert(runner, '{');

					for (worker = runner; worker != filelist.end(); worker++)
					{
						IgnoreComments(worker);
						IgnoreApostrophe(worker);
						IgnoreQuotation(worker);
						IgnoreParenthesis(worker);

						if (*worker == ';')
						{
							worker++;
							IgnoreOneLineComments(worker);
							filelist.insert(worker, '}');
							break;
						}
						else if (*worker == '{')
						{
							IgnoreBrace(worker);
							filelist.insert(worker, '}');
							break;
						}
					}
					break;

				}
			}
		}
		else
		{
			continue;
		}

		if (temp != filelist.end())
		{
			temp++;
		}
	}
}

void check::changeelseStyle()
{
	list<char>::iterator worker;
	list<char>::iterator runner;
	list<char>::iterator temp;
	temp = filelist.begin();
	while (temp != filelist.end())
	{
		IgnoreComments(temp);
		IgnoreApostrophe(temp);
		IgnoreQuotation(temp);
		OutofBounds(temp, filelist.end());

		if (*temp != 'e')
		{
			temp++;
			continue;
		}

		runner = worker = temp;
		int i;
		for (i = 1; i < ARRAY_SIZE(check_else); i++)
		{
			runner++;
			if (*runner != check_else[i])
			{
				break;
			}
		}
		if (i != ARRAY_SIZE(check_else))
		{
			temp++;
			continue;
		}

		runner++;
		worker--;
		temp = runner;
		if (worker != filelist.end() && beforCheck(&*worker) && runner != filelist.end() && afterCheck(&*runner)) //处理else token
		{
			IgnoreComments(runner);
			IgnoreApostrophe(runner);
			IgnoreQuotation(runner);
			IgnoreParenthesis(runner);

			if (*runner == '{')
			{
				runner++;
				continue;
			}

			if (*runner == 'i')
			{
				runner++;
				if (*runner == 'f')
				{
					runner++;
					if (afterCheck(&*runner))
					{
						temp = runner;
						continue;
					}
					runner--;
				}
				runner--;
			}

			worker = runner;
			for (; runner != filelist.end(); runner++)
			{
				IgnoreComments(runner);
				IgnoreApostrophe(runner);
				IgnoreQuotation(runner);
				//IgnoreParenthesis(runner);
				IgnoreComments(runner);

				if (*runner == '{')
				{
					break;
				}
				else if (*runner == ';')
				{
					runner++;
					filelist.insert(runner, '}');
					filelist.insert(worker, '{');
					break;
				}
				else if (!beforCheck(&*runner))
				{
					IgnoreComments(runner);
					filelist.insert(worker, '{');

					for (worker = runner; worker != filelist.end(); worker++)
					{
						IgnoreComments(worker);
						IgnoreApostrophe(worker);
						IgnoreQuotation(worker);
						IgnoreParenthesis(worker);

						if (*worker == ';')
						{
							worker++;
							IgnoreOneLineComments(worker);
							filelist.insert(worker, '}');
							break;
						}
						else if (*worker == '{')
						{
							IgnoreBrace(worker);
							filelist.insert(worker, '}');
							break;
						}
					}
					break;

				}
			}
		}
		else
		{
			continue;
		}

		if (temp != filelist.end())
		{
			temp++;
		}
	}
}

void check::addelse()
{
	list<char>::iterator worker;
	list<char>::iterator runner;
	list<char>::iterator temp;
	temp = filelist.begin();
	while (temp != filelist.end())
	{
		IgnoreComments(temp);
		IgnoreApostrophe(temp);
		IgnoreQuotation(temp);
		OutofBounds(temp, filelist.end());

		if (*temp != 'e')
		{
			temp++;
			continue;
		}

		runner = worker = temp;
		int i;
		for (i = 1; i < ARRAY_SIZE(check_else); i++)
		{
			runner++;
			if (*runner != check_else[i])
			{
				break;
			}
		}
		if (i != ARRAY_SIZE(check_else))
		{
			temp++;
			continue;
		}

		runner++;
		worker--;
		temp = runner;
		if (worker != filelist.end() && beforCheck(&*worker) && runner != filelist.end() && afterCheck(&*runner)) //处理else token
		{
			IgnoreComments(runner);
			IgnoreApostrophe(runner);
			IgnoreQuotation(runner);
			IgnoreParenthesis(runner);

			if (*runner == '{')
			{
				runner++;
				continue;
			}

			if (*runner == 'i')
			{
				runner++;
				if (*runner == 'f')
				{
					runner++;
					if (afterCheck(&*runner))
					{
						IgnoreComments(runner);
						IgnoreApostrophe(runner);
						IgnoreQuotation(runner);
						IgnoreParenthesis(runner);
						IgnoreComments(runner);
						IgnoreBrace(runner);
						temp = runner;

						IgnoreComments(runner);
						worker = runner;
						int j=0;
						for (j = 0; j < ARRAY_SIZE(check_else); j++)
						{
							if (*runner != check_else[j])
							{
								string streles = "else{}";
								filelist.insert(temp,streles.begin(),streles.end());
								temp = worker; 
								break;
							}
							runner++;
						}
						if(j==ARRAY_SIZE(check_else))
						{
							if(!afterCheck(&*runner))
							{
								string streles = "else{}";
								filelist.insert(temp,streles.begin(),streles.end());
								temp = runner;
							}
							else
							{
								runner = worker;
								temp = worker;
							}
						}
						continue;
					}
					runner--;
				}
				runner--;
			}

			worker = runner;
		}
		else
		{
			continue;
		}

		if (temp != filelist.end())
		{
			temp++;
		}
	}
}

void check::changeStyle()
{
	changeifStyle();
	changeforStyle();
	changeelseStyle();
	addelse();
}

void check::writeBack(const char* outputfile)
{
	ofstream fout(outputfile);
	for (list<char>::iterator iter = filelist.begin(); iter != filelist.end(); iter++)
	{
		//cout << *iter;
		fout << *iter;
	}

	//for(vector<char>::iterator iter = filevec.begin();iter!=filevec.end();iter++)
	//{
	//	cout<<*iter;
	//}
}

template<typename T>
void check::IgnoreComments(T& t)
{
	if (t == filelist.end())
	{
		return;
	}

	while (*t == ' ' || *t == '\t' || *t == '\n' || *t == '\r')
	{
		t++;
		if (t == filelist.end())
		{
			return;
		}

	}

	if (*t == '/')
	{
		t++;
		if (*t == '/')
		{
			while (t != filelist.end() && *t != '\n')t++;
			if (t != filelist.end())
			{
				t++;
				return IgnoreComments(t);
			}
			return;
		}
		else if (*t == '*')
		{
			while (t != filelist.end())
			{
				t++;
				if (*t != '*')
				{
					continue;
				}
				else
				{
					t++;
					if (*t == '*')
					{
						t--;
						continue;
					}
					else if (*t != '/')
					{
						continue;
					}
					else
					{
						t++;
						return IgnoreComments(t);
					}
				}
			}
			return;
		}
	}
	return;
}

template<typename T>
void check::IgnoreOneLineComments(T& t)
{
	if (t == filelist.end())
	{
		return;
	}

	while (*t == ' ' || *t == '\t')
	{
		t++;
		if (t == filelist.end())
		{
			return;
		}

	}

	if (*t == '/')
	{
		t++;
		if (*t == '/')
		{
			while (t != filelist.end() && *t != '\n')t++;
			if (t != filelist.end())
			{
				t++;
				return;
			}
			return;
		}
		else if (*t == '*')
		{
			while (t != filelist.end())
			{
				t++;
				if (*t != '*')
				{
					continue;
				}
				else
				{
					t++;
					if (*t == '*')
					{
						t--;
						continue;
					}
					else if (*t != '/')
					{
						continue;
					}
					else
					{
						t++;
						return;
					}
				}
			}
			return;
		}
	}
	return;
}

template<typename T>
void check::IgnoreApostrophe(T& t)
{
	if (t == filelist.end())
	{
		return;
	}

	if (*t == '\'')
	{
		while (true)
		{
			t++;
			if (*t == '\\')
			{
				t++;
			}
			else if (*t == '\'')
			{
				t++;
				return;
			}
			else
			{
			}
		}
	}
	return;
}

template<typename T>
void check::IgnoreQuotation(T& t)
{
	if (t == filelist.end())
	{
		return;
	}

	if (*t == '\"')
	{
		while (true)
		{
			t++;
			if (*t == '\\')
			{
				t++;
			}
			else if (*t == '\"')
			{
				t++;
				return IgnoreQuotation(t);
			}
			else
			{
			}
		}
	}
	return;
}

template<typename T>
void check::IgnoreParenthesis(T& t)
{
	if (t == filelist.end())
	{
		return;
	}

	int parenthesis = 1;
	if (*t == '(')
	{
		while (true)
		{
			t++;
			IgnoreComments(t);
			IgnoreApostrophe(t);
			IgnoreQuotation(t);

			if (*t == '(')
			{
				parenthesis++;
			}
			else if (*t == ')')
			{
				parenthesis--;
			}
			else
			{
			}

			if (parenthesis == 0)
			{
				t++;
				return;
			}
		}
	}
	return;
}

template<typename T>
void check::IgnoreBrace(T& t)
{
	if (t == filelist.end())
	{
		return;
	}

	int parenthesis = 1;
	if (*t == '{')
	{
		while (true)
		{
			t++;
			IgnoreComments(t);
			IgnoreApostrophe(t);
			IgnoreQuotation(t);

			if (*t == '{')
			{
				parenthesis++;
			}
			else if (*t == '}')
			{
				parenthesis--;
			}
			else
			{
			}

			if (parenthesis == 0)
			{
				t++;
				return;
			}
		}
	}
	return;
}
