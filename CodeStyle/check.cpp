#include<iostream>
#include<fstream>
#include<algorithm>
#include "check.h"
#include "char.h"
using namespace std;

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
		char c0 = *iter0;
		char c1 = *iter1;
		if (beforCheck(&c0) && afterCheck(&c1)) //处理if token
		{
			int parenthesis = 0;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				if (*iter1 == '(')
				{
					parenthesis++;
					break;
				}
			}
			iter1++;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				if (*iter1 == '(')
				{
					parenthesis++;
				}
				else if (*iter1 == ')')
				{
					parenthesis--;
					if (parenthesis == 0)
					{
						break;
					}
				}
			}
			temp = iter1;
			//此时处理到if结束的)括号处
			iter1++;
			iter0 = iter1;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				if (*iter1 == '(')
				{
					parenthesis++;
				}
				else if (*iter1 == ')')
				{
					parenthesis--;
				}

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
						if (*iter0 == '(')
						{
							parenthesis++;
						}
						else if (*iter0 == ')')
						{
							parenthesis--;
						}

						if (parenthesis == 0)
						{
							if (*iter0 == ';')
							{
								iter0++;
								while (*iter0 == ' ' || *iter0 == '\t')iter0++;
								IgnoreComments(iter0);
								filelist.insert(iter0, '}');
								break;
							}
						}
					}
					break;
				}
			}
		}

		temp++;
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

		if (*temp != 'f')
		{
			temp++;
			continue;
		}

		iter1 = iter0 = temp;
		int i;
		for (i = 1; i < sizeof(check_for) / sizeof(check_for[0]); i++)
		{
			iter1++;
			if (*iter1 != check_for[i])
			{
				break;
			}
		}
		if (i != sizeof(check_for) / sizeof(check_for[0]))
		{
			temp++;
			continue;
		}

		iter1++;
		iter0--;
		temp = iter1;
		char c0 = *iter0;
		char c1 = *iter1;
		if (beforCheck(&c0) && afterCheck(&c1)) //处理for token
		{
			int parenthesis = 0;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				if (*iter1 == '(')
				{
					parenthesis++;
					break;
				}
			}
			iter1++;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				if (*iter1 == '(')
				{
					parenthesis++;
				}
				else if (*iter1 == ')')
				{
					parenthesis--;
					if (parenthesis == 0)
					{
						break;
					}
				}
			}
			temp = iter1;
			//此时处理到for结束的)括号处
			iter1++;
			iter0 = iter1;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				if (*iter1 == '(')
				{
					parenthesis++;
				}
				else if (*iter1 == ')')
				{
					parenthesis--;
				}

				if (parenthesis == 0)
				{
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
							if (*iter0 == '(')
							{
								parenthesis++;
							}
							else if (*iter0 == ')')
							{
								parenthesis--;
							}

							if (parenthesis == 0)
							{
								if (*iter0 == ';')
								{
									iter0++;
									while (*iter0 == ' ' || *iter0 == '\t')iter0++;
									IgnoreComments(iter0);
									filelist.insert(iter0, '}');
									break;
								}
							}
						}
						break;

					}
				}
			}
		}

		temp++;
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
		char c0 = *iter0;
		char c1 = *iter1;
		if (beforCheck(&c0) && afterCheck(&c1)) //处理else token
		{
			while (*iter1 == ' ' || *iter1 == '\n' || *iter1 == '\t')iter1++;
			IgnoreComments(iter1);
			while (*iter1 == ' ' || *iter1 == '\n' || *iter1 == '\t')iter1++;

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
				}
			}
			temp = iter1;
			iter0 = iter1;
			int parenthesis = 0;
			for (; iter1 != filelist.end(); iter1++)
			{
				IgnoreComments(iter1);
				if (*iter1 == '(')
				{
					parenthesis++;
				}
				else if (*iter1 == ')')
				{
					parenthesis--;
				}

				if (parenthesis == 0)
				{
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
							if (*iter0 == '(')
							{
								parenthesis++;
							}
							else if (*iter0 == ')')
							{
								parenthesis--;
							}

							if (parenthesis == 0)
							{
								if (*iter0 == ';')
								{
									iter0++;
									while (*iter0 == ' ' || *iter0 == '\t')iter0++;
									IgnoreComments(iter0);
									filelist.insert(iter0, '}');
									break;
								}
							}
						}
						break;

					}
				}
			}
		}

		temp++;
	}
}

void check::changeStyle()
{
	changeifStyle();
	changeforStyle();
	changeelseStyle();
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
	if (*t == '/')
	{
		t++;
		if (*t == '/')
		{
			while (*t++ != '\n');
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
					if (*t != '/')
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