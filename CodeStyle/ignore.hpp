/*
Copyright(C) 2018  JumHorn <JumHorn@gmail.com>

This program is free software.you can redistribute it and / or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.
*/

#ifndef _IGNORE_HPP_
#define _IGNORE_HPP_

//definition
template<typename T>
class Ignore
{
protected:
	void IgnoreComments(T& t, const T& end);

	void IgnoreOneLineComments(T& t, const T& end);

	void IgnoreApostrophe(T& t, const T& end);

	void IgnoreQuotation(T& t, const T& end);

	void IgnoreParenthesis(T& t, const T& end);

	void IgnoreBrace(T& t, const T& end);
};


//implementation
template<typename T>
void Ignore<T>::IgnoreComments(T& t, const T& end)
{
	if (t == end)
	{
		return;
	}

	while (*t == ' ' || *t == '\t' || *t == '\n' || *t == '\r')
	{
		t++;
		if (t == end)
		{
			return;
		}

	}

	if (*t == '/')
	{
		t++;
		if (*t == '/')
		{
			while (t != end && *t != '\n')t++;
			if (t != end)
			{
				t++;
				return IgnoreComments(t, end);
			}
			return;
		}
		else if (*t == '*')
		{
			while (t != end)
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
						return IgnoreComments(t, end);
					}
				}
			}
			return;
		}
	}
	return;
}

template<typename T>
void Ignore<T>::IgnoreOneLineComments(T& t, const T& end)
{
	if (t == end)
	{
		return;
	}

	while (*t == ' ' || *t == '\t')
	{
		t++;
		if (t == end)
		{
			return;
		}

	}

	if (*t == '/')
	{
		t++;
		if (*t == '/')
		{
			while (t != end && *t != '\n')t++;
			if (t != end)
			{
				t++;
				return;
			}
			return;
		}
		else if (*t == '*')
		{
			while (t != end)
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
void Ignore<T>::IgnoreApostrophe(T& t, const T& end)
{
	if (t == end)
	{
		return;
	}

	if (*t == '\'')
	{
		t++;
		while (t!=end)
		{
			if(*t=='\\')
			{
				t++;
			}	
			else if (*t == '\'')
			{
				t++;
				return;
			}
			t++;
		}
	}
	return;
}

template<typename T>
void Ignore<T>::IgnoreQuotation(T& t, const T& end)
{
	if (t == end)
	{
		return;
	}

	if (*t == '\"')
	{
		t++;
		while (t!=end)
		{
			if (*t == '\\')
			{
				t++;
			}
			else if (*t == '\"')
			{
				t++;
				return IgnoreQuotation(t, end);
			}
			t++;
		}
	}
	return;
}

template<typename T>
void Ignore<T>::IgnoreParenthesis(T& t, const T& end)
{
	if (t == end)
	{
		return;
	}

	int parenthesis = 1;
	if (*t == '(')
	{
		t++;
		while (t!=end)
		{
			IgnoreComments(t, end);
			IgnoreApostrophe(t, end);
			IgnoreQuotation(t, end);

			if (*t == '(')
			{
				parenthesis++;
			}
			else if (*t == ')')
			{
				parenthesis--;
			}

			if (parenthesis == 0)
			{
				t++;
				return;
			}
			t++;
		}
	}
	return;
}

template<typename T>
void Ignore<T>::IgnoreBrace(T& t, const T& end)
{
	if (t == end)
	{
		return;
	}

	int parenthesis = 1;
	if (*t == '{')
	{
		t++;
		while (t!=end)
		{
			IgnoreComments(t, end);
			IgnoreApostrophe(t, end);
			IgnoreQuotation(t, end);

			if (*t == '{')
			{
				parenthesis++;
			}
			else if (*t == '}')
			{
				parenthesis--;
			}

			if (parenthesis == 0)
			{
				t++;
				return;
			}
			t++;
		}
	}
	return;
}

#endif
