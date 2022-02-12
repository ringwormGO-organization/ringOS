# How to start contributing
Just drop a Pull Request :)

# Pull Request style
1. Use CRLF. Set up your Git settings with this: `git config --global core.autocrlf true` and check if it is OK by `git config --global core.autocrlf`. It need to return `true`
2. Use following style **WITH LOGIC**:

```
[LABEL NAME] Name of Pull Request
```

# Coding sytle for Pull Requests
### Indentation and line width
1. Line width much be at most **100** characters.
2. Use tabs, tabs ident size **MUST BE** 4!
3. Indent both a case label and the case statement of a switch statement.

Right:

```c
switch (Condition)
{
    case 1:
        DoSomething();
        break;
}
```
Wrong:

```c
switch (Condition)
{
case 1:
     DoSomething();
     break;
}
```
When a function call does not fit onto a line, align arguments like this:

```c
FunctionCall(arg1,
             arg2,
             arg3);
```

When making new functions, use an return type.
Right:
```c
int func() {}
```
Wrong:
```c
func() {}
```

### Spacing
1. Do not use spaces around unary operators.

**Right:** `i++`

**Wrong:** `i ++`

-------------------------------------------------------------

2. Place spaces around binary and ternary operators.

**Right:** `a = b + c;`

**Wrong:** `a=b+c;`

3. Do not place spaces before comma and semicolon.

Right:

```c
for (int i = 0; i < 5; i++)
    DoSomething();

func1(a, b);
```

Wrong:

```c
for (int i = 0 ; i < 5 ; i++)
    DoSomething();
    
func1(a , b) ;
```

4. Place spaces between control statements and their parentheses.

Right:

```c
if (Condition)
    DoSomething();
```

Wrong:

```c
if(Condition)
    DoSomething();
```

5. Do not place spaces between a function and its parentheses, or between a parenthesis and its content.

Right:

`func(a, b);`

Wrong:

```c
func (a, b);
func( a, b );
```

### Line breaking
1. Each statement should get its own line.

Right:

```c
x++;
y++;

if (Condition)
{
    DoSomething();
}
```
Also right but don't use it often

```c
if (Condition) DoSomething(); 

if (Condition)
    DoSomething();
```
Wrong:

```c
x++; y++;
```

### Braces
1. Always put braces ({ and }) on their own lines.
2. One-line control clauses may use braces, but this is not a requirement. An exception are one-line control clauses including additional comments.

Right:

```c
if (Condition)
    DoSomething();

if (Condition)
{
    DoSomething();
}

if (Condition)
{
    // This is a comment
    DoSomething();
}


if (Condition)
    DoSomething();
else
    DoSomethingElse();

if (Condition)
{
    DoSomething();
}
else
{
    DoSomethingElse();
    YetAnother();
}
```

Wrong:

```c
if (Condition) {
    DoSomething();
}

if (Condition)
    // This is a comment
    DoSomething();

if (Condition)
    DoSomething();
else
{
    DoSomethingElse();
    YetAnother();
}
```

### Control structures
1. Don’t use inverse logic in control clauses.

**Right:** `if (i == 1)`
**Wrong:** `if (1 == i)`

2. Avoid too many levels of cascaded control structures. Prefer a “linear style” over a “tree style”. Use goto when it helps to make the code cleaner (e.g. for cleanup paths).

Right:

```c
if (!func1())
    return;

i = func2();
if (i == 0)
    return;

j = func3();
if (j == 1)
    return;
```
…

Wrong:

```c
if (func1())
{
    i = func2();
    if (func2())
    {
        j = func3();
        if (func3())
        {
            …
        }
    }
}
```

### Naming
*Part called "Naming" is wrote by ringwormGO itself*

#### Naming functions
1. Name a function by capital letter.

**Right:** `void Test();`

**Wrong:** `void test();`

#### Naming structs, classes, unions and variables
2. Name a struct, class, union etc. with cappital letter and variable which lowercase letter

**Right:**
```c
struct Test
{
  int number;
}

Test test;
```

**Wrong:**
```c
struct test
{
  int Number;
}

test Test;
```

### Commenting
1. Avoid line-wasting comments, which could fit into a single line.

Right:

```c
// This is a one-line comment

/* This is a C-style comment */


//
// This is a comment over multiple lines.
// We don’t define any strict rules for it.
//
```

Wrong:

```c
//
// This comment wastes two lines
//
```

### Null, false and 0
1. The null pointer should be written as NULL.
2. In the rare case that your environment recommends a different null pointer (e.g. C++11 nullptr), you may use this one of course. Just don’t use the value 0.

### Notes on reformatting existing code
1. Never totally reformat a file and put a code change into it. Do this in separate commits.
2. If a commit only consists of formatting changes, say this clearly in the commit message by preceding it with [FORMATTING].

### Other points
1. Do not use `LARGE_INTEGER`/`ULARGE_INTEGER` unless needed for using APIs. Use `int64`/`uint64` instead
2. Use `#pragma once` instead of guard defines in headers
3. Don't specify a calling convention for a function unless required (usually for APIs or exported symbols)

### Resources used for this coding style:
* https://reactos.org/wiki/Coding_Style (some parts are modificeted)
