#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include"parenthesis.h"
using namespace std;

//input ������
//output ����ļ���
void addBrace(const char* inputfile, const char* outputfile)
{
	ofstream fout(outputfile);
	ifstream fin(inputfile);
	//����string����list�ȴ��Ż�
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
