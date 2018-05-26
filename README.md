# Add Brace

### what it can do
this is a little tool to adjust code format that a single statement after "if" or "for" without brace.
Add brace after it to pass code test (for example testbed)

put the executive file in a directory and run it
it will change the .cpp file code format recursively


### mind
#### first
this tool can't solve # else(there is a space between # and else) questions.
do not include header files
Even do not use it on cpp files with # else   
it still can not skip #if false statement which will make a lot of mistakes

****bug fixed on version 1.1****   
~~
#### second
code like this can not handle now
```C++
if(statement)
    (pointer + n) -> function();
```
the tool will make a mistake like this

```C++
if(statement)
    (pointer + n) {-> function();}
```

because I haven't checked the characters after the right ) of it yet
and ignore all characters between the brace
~~

my code may make you cry which I don't want to review any more
