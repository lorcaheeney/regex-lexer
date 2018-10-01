# regex-lexer
## Overview
A regular-expressions based lexer written in C, easily included with any project via a single header file with no external dependicies. Aiming to make interpreters and compilers easier to write by handling the boring stuff for you.
## Linking
Download the single header file using the following commmand, in the directory of your source files:
```
wget -O lexer.h https://github.com/lorcajheeney/regex-lexer/blob/master/lexer.h?raw=true
```
Add `#include<lexer.h>` to the top of your source files, **NOTE: No dependencies are needed for the library, only the standard library's `stdlib`, `stdbool`, `stdarg`, `string` and `regex` header files are included by the lexer.**

When compiling your project, ensure the compiler knows to search the current directory for header files, shown below for GCC:
```
gcc -I. (the rest of your parameters and flags)
```
## Use
**NOTE: Calling `lexer` using an POSIX uncompatible regex pattern may result in a segmentation fault.**
### Calling the function
The main functionality of the library can be accessed using the `lexer` function whose signature is shown below:
```c
results_t lexer(char * source, unsigned int npatterns, ...);
```
The first argument is the text to be tokenized and the second the number of patterns passed in as variadic arguments. Each pattern is passed in using two arguments, its name and regex pattern, both as `char*`, in that order.
An example use of the lexer function to tokenize a simple piece of text with only a few patterns is shown below.
```c
#include<regex.h>
...
lexer("numchars \"hello, world!\" == 7 + 5",4,"IDENTIFIER","[a-zA-Z]+","STRING","\"[a-zA-Z,!]*\"","OPERATOR","\\+|==","NUM","[0-9]+");
...
```
### Reading your results
The `lexer` function returns an instance of the `results_t` struct.The fields of said struct and `token_t` struct which is used within the results can be seen below:
```c
typedef struct {
	token_t * toks;
	unsigned int ntoks;
} results_t;

typedef struct {
	char * type;
	char * str;
} token_t;
```
For use, `results_t` contains the number of tokens returned - `ntoks`, along with a dynamically allocated list of `token_t` instances, each containing their own type - `type` and matched text - `str`.
Below shows an example of using this data to print a formatted list of tokens:
```c
#include<regex.h>
...
results_t res = lexer("numchars \"hello, world!\" == 7 + 5",4,"IDENTIFIER","[a-zA-Z]+","STRING","\"[a-zA-Z,!]*\"","OPERATOR","\\+|==","NUM","[0-9]+");
...
printf("%d TOKENS RETURNED\n", res.ntoks);
for(int i = 0 ; i < res.ntoks ; i++ ){
	printf("TYPE : %s | TEXT : %s\n",res.toks[i].type, res.toks[i].str);
}
...
```
The above code's output will then be like this:
```
6 TOKENS RETURNED
TYPE : IDENTIFIER | TEXT : numchars 
TYPE : STRING | TEXT : "hello,world!" 
TYPE : OPERATOR | TEXT : == 
TYPE : NUM | TEXT : 7 
TYPE : OPERATOR | TEXT : + 
TYPE : NUM | TEXT : 5
```
## TODO:
Use Perl-Compatible-Regular-Expressions(PCRE) to allow a wider variety of regex constructs to be used to further enhance the capabilites of the lexer.
