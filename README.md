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


### conclusion
my code will make you cry which I don't want to review any more

### version history
* V2.3   
fix some bugs as follows:
1. do not gererate useless files when given file name is incorrect
2. change variable name for better understanding
3. some other optimazation

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
