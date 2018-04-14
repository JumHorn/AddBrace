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
	void changeelseStyle();
	void writeBack(const char* outputfile);

protected:
	template<typename T>
	void IgnoreComments(T& t);

	template<typename T>
	void IgnoreOneLineComments(T& t);

	template<typename T>
	void IgnoreApostrophe(T& t);

	template<typename T>
	void IgnoreQuotation(T& t);

	template<typename T>
	void IgnoreParenthesis(T& t);

	template<typename T>
	void IgnoreBrace(T& t);
};

#endif