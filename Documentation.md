# ringOS Documentation
This documentation is intended to guide you in developing, compiling, debugging and running ringOS

[SYSTEM REQUIREMENTS](https://github.com/ringwormGO-organization/ringOS#system-requiratmens)

## Compile and run in Qemu (betas)
[You can use this script (Linux, run in Qemu)](https://github.com/Andrej123456789/ringOS/blob/main/ringOS-Builder-full.sh)

[Stable release (Linux, run in Qemu)](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-stable-Builder.sh)
or continue manually.

### Software you need
1. [Qemu recommended](#install-qemu) or [Virtual Box, VmWare](#running-in-virtual-box-or-vmware)
2. WSL/WSL2 (If developing on Windows) or Linux (recommended)

### Type of release for running in Qemu
Download a Zip file of Qemu release (example: https://github.com/Andrej123456789/ringOS/releases/tag/Beta11_Qemu).

Unzip the downloaded Zip folder and navigate to the contents in your Terminal (Linux) or using WSL/WSL2 on Windows ('cd')

--------------------------------------------------------------------------------------------------------------------------------
For compiling Beta version.

`git clone https://github.com/VanGutan/gnu-efi` 

Create one ringOS folder, clone `gnu-efi`, `ringOS-beta17` rename as `kernel` and clone `git clone https://github.com/VanGutan/ringOS-Beta14-OVMFTemplate` and rename as `OVMFbin`.
Copy `ringOS-Beta17-bootloader` folder into `gnu-efi` folder and rename it to `bootloader`.

For cloning bootloader, you can [Makefile](https://github.com/ringwormGO-organization/ringOS/blob/main/Makefile)

### Compiling
The following commands work on Debian-based (ex. Ubuntu) Linux distros and within WSL/WSL2 on Windows. Users of non-Debian distros will need to locate the correct packages for their chosen operating system.

If this is your first time attemtping to to compile ringOS, you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`sudo apt update`

`sudo apt-get install build-essential mtools`

`sudo apt install nasm`

`sudo apt-get install lld`
___________________________________________________________________

To compile the bootloader (gnu-efi) you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`cd gnu-efi`

`make bootloader`

________________________________________________________________

To compile the ringOS kernel you will need to run the following commands in your Terminal (Linux) or using WSL/WSL2 on Windows:

`cd kernel` or (if you are in gnu-efi folder) `cd ../kernel`

`make kernel`

______________________________________________________________

To run ringOS within Qemu on Linux or Windows:

**Windows** double-click the  `run2.bat` file to initialize a Qemu VM and run ringOS.

**Linux** `make buildimg` [run from with the 'kernel' folder]

**Linux** `make run`

# Compile and run the latest stable release from shell script

[Shell scipt](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-stable-Builder.sh)

[Manually download binary](https://github.com/ringwormGO-organization/ringOS/releases/tag/ringOSv1)

______

## Install Qemu

**Windows** Download executable file, run it (https://www.qemu.org/download/#windows) and add Qemu to PATH

**Linux** `sudo apt install qemu-system-x86`
___
## Running in Virtual Box or VMWare

**Minimum RAM: 4096MB**

You need install two more apps:

`sudo apt-get install xorriso`

`sudo apt-get install mkisofs`

Enter kernel/bin directory.

Type these commands in order:

`mkdir -p iso`

`rm -rf iso/*.iso`

`rm -rf iso/*.img`

`cp ringOS.img iso`

`xorriso -as mkisofs -R -f -e ringOS.img -no-emul-boot -o ./iso/ringOS.iso iso`

Open Virtual Box, create new virtual machine and put ISO as CD-ROM device and enable ICH9 CPU chipset.

Open VMWare, create new virtual machine, put ISO, enter Boot Manager by pressing **ESC** during boot and select **EFI Internal Shell**.

![image](https://user-images.githubusercontent.com/83548580/143719557-aee05602-e163-4693-a124-2307aa09eac0.png)

![image](https://user-images.githubusercontent.com/83548580/143719800-0600b9fe-8ca7-48bd-bd24-edc6c3048d56.png)

- - - - - - 

![image](https://user-images.githubusercontent.com/83548580/149768519-9a16bc9d-dd7e-4e29-8941-86f9733e19f0.png)

![image](https://user-images.githubusercontent.com/83548580/143719473-982e21ff-def5-4383-aa4f-3b249eab4e90.png)

(You can execute this commands in WSL and run Virtual Box on Windows)

Operating system must be marked as EFI (Virtual box) or UEFI Firmware type (VMWare).
_____
## Running on real hardware
*Files in [version] - image*

Format USB as MBR/GPT partition style (tool for example: Rufus).

Create EFI folder.

Inside EFI folder create BOOT folder.

Copy `bootx64.efi` file into BOOT folder.

In root directory of USB copy `kernel.elf`, `zap-light16.psf` and `Picture.bmp` files.

Restart computer, enter UEFI Menu and boot from USB.
___
## Debug
We have a [debug branch](https://github.com/ringwormGO-organization/ringOS/tree/Debug) but the code is not updated and is only for Windows platform developers.

If you want to debug new code follow these steps:

Download code to be debugged, install gdb (```sudo apt-get install gdb```), open Visual Studio Code and create two JSON files.

[Code](https://www.youtube.com/watch?v=XLw_K4rEl1I)

Click F5 to run.
______
## Modules
[Modules](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-Beta17/Modules.txt) are for customizing ringOS.

You can currently personalize the operating system output by using the provided [official modules](https://github.com/ringwormGO-organization/ringOS/blob/main-and-beta-things/ringOS-Beta17/Modules.txt)  and printing text in kernel.cpp.

Feel free to customize some other parts like panic.cpp as appropriate for your use case.

### License for modules
The modules provided for customization are intended for private, non-commerical use only.

IF YOU PLANNING USE THESE MODULES TO MODIFY ringOS AND PUBLISH ringOS AS YOUR OWN DISTRIBUTION, PERMISSION MUST FIRST BE OBTAINED FROM ringwormGO.
___

## Other

If you have problems or ideas plese create an **issue**.

To contribute to ringOS, please create a **Pull Request** and refer to [our coding sytle](#coding-sytle-for-pull-requests) down below.

This documentation will continue improving based on new features in ringOS.

[ringOSY documentation](https://github.com/ringwormGO-organization/ringOS/tree/ringOSY) 

## Coding sytle for Pull Requests
### Indentation and line width
1. Line width much be at most **100** characters.
2. Use tabs, tabs ident size **MUST BE** 4!
3. Indent both a case label and the case statement of a switch statement.

Right:

```
switch (Condition)
{
    case 1:
        DoSomething();
        break;
}
```
Wrong:

```
switch (Condition)
{
case 1:
     DoSomething();
     break;
}
```
When a function call does not fit onto a line, align arguments like this:

```
FunctionCall(arg1,
             arg2,
             arg3);
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

```
for (int i = 0; i < 5; i++)
    DoSomething();

func1(a, b);
```

Wrong:

```
for (int i = 0 ; i < 5 ; i++)
    DoSomething();
    
func1(a , b) ;
```

4. Place spaces between control statements and their parentheses.

Right:

```
if (Condition)
    DoSomething();
```

Wrong:

```
if(Condition)
    DoSomething();
```

5. Do not place spaces between a function and its parentheses, or between a parenthesis and its content.

Right:

`func(a, b);`

Wrong:

```
func (a, b);
func( a, b );
```

### Line breaking
1. Each statement should get its own line.

Right:

```
x++;
y++;

if (Condition)
{
    DoSomething();
}
```
Also right but don't use it often

```
if (Condition) DoSomething(); 

if (Condition)
    DoSomething();
```
Wrong:

```
x++; y++;
```

### Braces
1. Always put braces ({ and }) on their own lines.
2. One-line control clauses may use braces, but this is not a requirement. An exception are one-line control clauses including additional comments.

Right:

```
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

```
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

```
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

```
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
```
struct Test
{
  int number;
}

Test test;
```

**Wrong:**
```
struct test
{
  int Number;
}

test Test;
```

### Commenting
1. Avoid line-wasting comments, which could fit into a single line.

Right:

```
// This is a one-line comment

/* This is a C-style comment */


//
// This is a comment over multiple lines.
// We don’t define any strict rules for it.
//
```

Wrong:

```
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
________________________________________________________________________________________________________________________________________________

Thank you for choosing ringOS and ringOSY

©ringwormGO 2022
