/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#ifndef _CHAR_H_
#define _CHAR_H_

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

char befor_check[] = { '\t','\n',' ',';','{','}','/' };
char after_check[] = { '\t','\n',' ','(','{','/' };

char add_indentation[] = {'{'};
char remove_indentation[] = {'}'};
char new_line[] = {';'};

#endif
