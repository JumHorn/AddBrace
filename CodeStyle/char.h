/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

/*
const variable with internal link
these code may not be compiled by the compiler that does not support it
and it is still easy to set these variable to be static to pass the compiler
*/

#ifndef _CHAR_H_
#define _CHAR_H_

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/*
newline and return
r stand for return to the head of line
n stand for new line

Windows \r\n
Unix \n
Mac \r
*/
#ifdef __LINUX__
const char newline = '\n';
#endif

#ifdef _WIN32
const char newline = '\n';
#endif

#ifdef __APPLE__
const char newline = '\r';
#endif

/*
only these characters can be placed in front of a token or after a token
*/
const char befor_check[] = { '\t','\n','\r',' ',';','{','}','/' };
const char after_check[] = { '\t','\n','\r',' ','(','{','/' };

/*
indentation
*/
const char add_indentation[] = { '{' };
const char remove_indentation[] = { '}' };
const char new_line[] = { ';' };
const char white_space[] = { ' ','\t' };

/*
operators
the = operator must be after the == and != to be last matched one
remove =,+=,-= due to this statement *to++=ch
*/
//const char* const oper[] = { "&&","||",">>=","<<=",">=","<=","==","!=","+=","-=","*=","/=","%=","|=","^=","&=","=" };
const char* const oper[] = { "&&","||",">>=","<<=",">=","<=","==","!=","*=","/=","%=","|=","^=","&=" };

#endif
