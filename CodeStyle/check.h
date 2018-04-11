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
public:
	check();
	~check();

	void getFileContent(const char* inputfile);
	void changeStyle();
	void changeifStyle();
	void changeforStyle();
	void writeBack(const char* outputfile);
};

#endif