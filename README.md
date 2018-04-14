# Add parenthesis

### what it can do
this is a little tool to adjust code format that a single statement after "if" or "for" without add brace.
Add brace after it to pass code test

leave the executive file under a directory and run it
it will change the .cpp file code format recursively

### what to do in the future
there is still a lot to do with comment in the source file

### mind
#### first
this tool can't solve # else(there is a space between # and else) questions.
do not include header files
Even do not write # else in cpp files

#### second
code like this can not handle now
```C++
if(statement)
    (pointer + n) -> function();
```
the tool will make mistake like this

```C++
if(statement)
    (pointer + n) {-> function();}
```

because I haven't check the characters after the right ) of if yet
and ignore all characters between the brace

my code is a piece of trash which I don't want to review any more