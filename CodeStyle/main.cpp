#include<iostream>
#include"check.h"
using namespace std;

int main()
{
	check style;
	style.getFileContent("_test.cpp");
	style.changeStyle();
	style.writeBack("o_test.txt");
}