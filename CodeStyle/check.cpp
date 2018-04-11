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
	list<char>::iterator iter2;
	list<char>::iterator temp;
	temp = find(filelist.begin(), filelist.end(),'i');
	while (temp != filelist.end())
	{
		iter0 = iter1 = temp;
		iter1++;
		iter0--;
		iter2 = iter1;
		iter2++;
		char c0 = *iter0;
		char c1 = *iter2;
		if (*iter1 == 'f' && beforCheck(&c0) && afterCheck(&c1)) //处理if，token
		{ }

		temp++;
		temp = find(temp, filelist.end(), 'i');
	}
}

void check::changeforStyle()
{
	for (list<char>::iterator iter = filelist.begin(); iter != filelist.end(); iter++)
	{

	}
}

void check::changeStyle()
{
	changeifStyle();
	changeforStyle();
}

void check::writeBack(const char* outputfile)
{
	ofstream fout(outputfile);
	for (list<char>::iterator iter = filelist.begin(); iter != filelist.end(); iter++)
	{
		cout << *iter;
		fout << *iter;
	}

	//for(vector<char>::iterator iter = filevec.begin();iter!=filevec.end();iter++)
	//{
	//	cout<<*iter;
	//}
}