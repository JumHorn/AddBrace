#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include"parenthesis.h"
using namespace std;

//input 输入流
//output 输出文件名
void addBrace(const char* inputfile, const char* outputfile)
{
	ofstream fout(outputfile);
	ifstream fin(inputfile);
	//构建string还是list等待优化
	string filestr((istreambuf_iterator<char>(fin)),istreambuf_iterator<char>());
	//list<char> filechar(filestr.begin(),filestr.end());
	//for(list<char>::iterator iter = filechar.begin();iter!=filechar.end();iter++)
	//{
	//	cout<<*iter;
	//}
	vector<char> filechar(filestr.begin(),filestr.end());
	for(vector<char>::iterator iter = filechar.begin();iter!=filechar.end();iter++)
	{
		cout<<*iter;
	}

}
