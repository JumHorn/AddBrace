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
	unsigned int temp = sizeof(befor_check) / sizeof(befor_check[0]);
	return befor_check + temp != find(befor_check, befor_check + temp, *c);
}

bool check::afterCheck(const char *c)
{
	unsigned int temp = sizeof(after_check) / sizeof(after_check[0]);
	return after_check + temp != find(after_check, after_check + temp, *c);
}

void check::changeifStyle()
{
	list<char>::iterator iter0;
	list<char>::iterator iter1;
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

		iter1 = iter0 = temp;
		int i;
		for (i = 1; i < sizeof(check_if) / sizeof(check_if[0]); i++)
		{
			iter1++;
			if (*iter1 != check_if[i])
			{
				break;
			}
		}
		if (i != sizeof(check_if) / sizeof(check_if[0]))
		{
			temp++;
			continue;
		}

		iter1++;
		iter0--;
		temp = iter1;
		if (iter0 != filelist.end() && beforCheck(&*iter0) && iter1 != filelist.end() && afterCheck(&*iter1)) //处理if token
		{
			IgnoreComments(iter1);
			IgnoreApostrophe(iter1);
			IgnoreQuotation(iter1);
			IgnoreParenthesis(iter1);
			temp = iter1;
			//此时处理到if结束的)括号处
			iter0 = iter1;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				IgnoreApostrophe(iter1);
				IgnoreQuotation(iter1);
				//IgnoreParenthesis(iter1);
				IgnoreComments(iter1);

				if (*iter1 == '{')
				{
					break;
				}
				else if (*iter1 == ';')
				{
					iter1++;
					filelist.insert(iter1, '}');
					filelist.insert(iter0, '{');
					break;
				}
				else if (!beforCheck(&*iter1))
				{
					filelist.insert(iter1, '{');
					for (iter0 = iter1; iter0 != filelist.end(); iter0++)
					{
						IgnoreComments(iter0);
						IgnoreApostrophe(iter0);
						IgnoreQuotation(iter0);
						IgnoreParenthesis(iter0);

						if (*iter0 == ';')
						{
							iter0++;
							IgnoreOneLineComments(iter0);
							filelist.insert(iter0, '}');
							break;
						}
						else if (*iter0 == '{')
						{
							IgnoreBrace(iter0);
							filelist.insert(iter0, '}');
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
	list<char>::iterator iter0;
	list<char>::iterator iter1;
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

		iter1 = iter0 = temp;
		int i;
		for (i = 1; i < sizeof(check_for) / sizeof(check_for[0]); i++)
		{
			if (iter1 == filelist.end())
			{
				break;
			}
			iter1++;
			if (iter1 != filelist.end() && *iter1 != check_for[i])
			{
				break;
			}
		}
		if (i != sizeof(check_for) / sizeof(check_for[0]))
		{
			if (temp != filelist.end())
			{
				temp++;
			}
			continue;
		}

		iter1++;
		iter0--;
		temp = iter1;
		if (iter0 != filelist.end() && beforCheck(&*iter0) && iter1 != filelist.end() && afterCheck(&*iter1)) //处理for token
		{
			IgnoreComments(iter1);
			IgnoreApostrophe(iter1);
			IgnoreQuotation(iter1);
			IgnoreParenthesis(iter1);
			temp = iter1;
			//此时处理到for结束的)括号处
			iter0 = iter1;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				IgnoreApostrophe(iter1);
				IgnoreQuotation(iter1);
				//IgnoreParenthesis(iter1);
				IgnoreComments(iter1);

				if (*iter1 == '{')
				{
					break;
				}
				else if (*iter1 == ';')
				{
					iter1++;
					filelist.insert(iter1, '}');
					filelist.insert(iter0, '{');
					break;
				}
				else if (!beforCheck(&*iter1))
				{
					IgnoreComments(iter1);
					filelist.insert(iter1, '{');

					for (iter0 = iter1; iter0 != filelist.end(); iter0++)
					{
						IgnoreComments(iter0);
						IgnoreApostrophe(iter0);
						IgnoreQuotation(iter0);
						IgnoreParenthesis(iter0);

						if (*iter0 == ';')
						{
							iter0++;
							IgnoreOneLineComments(iter0);
							filelist.insert(iter0, '}');
							break;
						}
						else if (*iter0 == '{')
						{
							IgnoreBrace(iter0);
							filelist.insert(iter0, '}');
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
	list<char>::iterator iter0;
	list<char>::iterator iter1;
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

		iter1 = iter0 = temp;
		int i;
		for (i = 1; i < sizeof(check_else) / sizeof(check_else[0]); i++)
		{
			iter1++;
			if (*iter1 != check_else[i])
			{
				break;
			}
		}
		if (i != sizeof(check_else) / sizeof(check_else[0]))
		{
			temp++;
			continue;
		}

		iter1++;
		iter0--;
		temp = iter1;
		if (iter0 != filelist.end() && beforCheck(&*iter0) && iter1 != filelist.end() && afterCheck(&*iter1)) //处理else token
		{
			IgnoreComments(iter1);
			IgnoreApostrophe(iter1);
			IgnoreQuotation(iter1);
			IgnoreParenthesis(iter1);

			if (*iter1 == '{')
			{
				iter1++;
				continue;
			}

			if (*iter1 == 'i')
			{
				iter1++;
				if (*iter1 == 'f')
				{
					iter1++;
					if (afterCheck(&*iter1))
					{
						temp = iter1;
						continue;
					}
					iter1--;
				}
				iter1--;
			}

			iter0 = iter1;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				IgnoreApostrophe(iter1);
				IgnoreQuotation(iter1);
				//IgnoreParenthesis(iter1);
				IgnoreComments(iter1);

				if (*iter1 == '{')
				{
					break;
				}
				else if (*iter1 == ';')
				{
					iter1++;
					filelist.insert(iter1, '}');
					filelist.insert(iter0, '{');
					break;
				}
				else if (!beforCheck(&*iter1))
				{
					IgnoreComments(iter1);
					filelist.insert(iter0, '{');

					for (iter0 = iter1; iter0 != filelist.end(); iter0++)
					{
						IgnoreComments(iter0);
						IgnoreApostrophe(iter0);
						IgnoreQuotation(iter0);
						IgnoreParenthesis(iter0);

						if (*iter0 == ';')
						{
							iter0++;
							IgnoreOneLineComments(iter0);
							filelist.insert(iter0, '}');
							break;
						}
						else if (*iter0 == '{')
						{
							IgnoreBrace(iter0);
							filelist.insert(iter0, '}');
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
	list<char>::iterator iter0;
	list<char>::iterator iter1;
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

		iter1 = iter0 = temp;
		int i;
		for (i = 1; i < sizeof(check_else) / sizeof(check_else[0]); i++)
		{
			iter1++;
			if (*iter1 != check_else[i])
			{
				break;
			}
		}
		if (i != sizeof(check_else) / sizeof(check_else[0]))
		{
			temp++;
			continue;
		}

		iter1++;
		iter0--;
		temp = iter1;
		if (iter0 != filelist.end() && beforCheck(&*iter0) && iter1 != filelist.end() && afterCheck(&*iter1)) //处理else token
		{
			IgnoreComments(iter1);
			IgnoreApostrophe(iter1);
			IgnoreQuotation(iter1);
			IgnoreParenthesis(iter1);

			if (*iter1 == '{')
			{
				iter1++;
				continue;
			}

			if (*iter1 == 'i')
			{
				iter1++;
				if (*iter1 == 'f')
				{
					iter1++;
					if (afterCheck(&*iter1))
					{
						IgnoreComments(iter1);
						IgnoreApostrophe(iter1);
						IgnoreQuotation(iter1);
						IgnoreParenthesis(iter1);
						IgnoreComments(iter1);
						IgnoreBrace(iter1);
						temp = iter1;

						IgnoreComments(iter1);
						iter0 = iter1;
						int j=0;
						for (j = 0; j < sizeof(check_else) / sizeof(check_else[0]); j++)
						{
							if (*iter1 != check_else[j])
							{
								string streles = "else{}";
								filelist.insert(temp,streles.begin(),streles.end());
								temp = iter0; 
								break;
							}
							iter1++;
						}
						if(j==sizeof(check_else) / sizeof(check_else[0]))
						{
							if(!afterCheck(&*iter1))
							{
								string streles = "else{}";
								filelist.insert(temp,streles.begin(),streles.end());
								temp = iter1;
							}
							else
							{
								iter1 = iter0;
								temp = iter0;
							}
						}
						continue;
					}
					iter1--;
				}
				iter1--;
			}

			iter0 = iter1;
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
