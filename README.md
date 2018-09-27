# Add Brace

### usage
this is a little tool to adjust code format that a single statement after "if" or "for" without brace.
Now it can add else{} after else if statement without else.
Add brace after that to pass code test (for example testbed)

put the executive file in a directory and run it
it will change the .cpp file code format recursively


### mind
#### first
this tool can't solve # else(there is a space between # and else) style.
do not include header files
Even do not use it in cpp files with # else   
code like this will remain unchanged
```C++
bool check()
{
    if(check())
#if 0
#endif
    return true;
}
```
you probably solve this problem by delete white character between # and if

#### second
code like this have been solved after the version of V2.5
```C++
if(true)
    if(false)
        cout<<1<<endl;
    else if(false)
        cout<<2<<endl;
    else
        cout<<3<<endl;
```

#### third
this big problem still exists until V3.0   
if statement without semicolon and the braces not match correctly   
```C++
void fun()
{
#if 0
    if(true)
        statement
    else if(true)
    {
#endif
    statement;
}

int main()
{}
```
### bug list
* bad format
```C++
const int[] = {0};
```
will change to this (a bit ugly)
```C++
const int[] =
{
    0
};
```
* uncompiled
code that can not compiled may cause a lot of unexpected questions

### conclusion
my code will make you cry which I don't want to review any more

### version history
* V3.1
1. simplify code logic
2. add make indentation feature
3. add statistics framework

* V3.0
1. new line macro to support various systems
2. a new feature style formatter to be added 
3. do not define any symbol with external link in header file

* V2.9
1. fix adding else without skipping # statement 
```C++
#if 0
    if(true)
        statement;
    else if(false)
    {
#endif
    int a;
```
2. add brace causing #endif after } not working 
```C++
#if 0
    if(true)
        {statement;//comment
}#endif
```
3. add support for mac new line \r
4. add a safety pig to bless you

* V2.8
1. remove time consuming stl function distance
2. add a lot of OUTOFBOUNDS macro to avoid undeferecable iterator 

* V2.7
1. fix the bug that ignore comment code failure cause handle the if in the comment
```C++
if(true)// if no
    statement;
```
2. fix code that can not compiled causing app stop running   
especially parethesie or brace not match

* V2.6   
more abstract using template. A great Refactoring code now.

* V2.5   
fix a big problem described above **second**

* V2.4   
Refactor my code

* V2.3   
fix some bugs as follows:
1. do not gererate useless files when given file name is incorrect
2. change variable name for better understanding
3. some other optimazations

* V2.1   
fix add more else bugs
```C++
int main()
{
    if(check())
        {statement;}
#if 1
    else if(check())//comment
        {statement;}else{}
#endif
    else//comment
        {statement;}
}
```
