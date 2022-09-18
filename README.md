# regex-lexer (Sep 2018) ![](https://img.shields.io/badge/C-GCC-brightgreen.svg)

![](https://benjam.info/blog/posts/2019-09-18-python-deep-dive-tokenizer/tokenizer-abstract.png)
*Image credit: https://benjam.info/blog*

# Overview
A regular-expressions based lexer written in C. Easily include in any project via a single header file with no external dependicies. Aiming to make interpreters and compilers easier to write by handling the boring stuff for you.


# How to use
An small example of using the lexer is included in [test/test.c](test/test.c). For more detailed instructions...
## 1) Linking
Clone the repository and move the single `lexer.h` file into your project's documentary. Ensure to tell the compiler where to look for local header files (e.g using the `-I` flag in GCC). No other dependencies are needed except the standard library's `stdlib`, `stdbool`, `stdarg`, `string` and `regex` header files.

## 2) Calling the lexer

The main functionality of the library can be accessed using the `lexer` function whose signature is shown below:
```c
results_t lexer(char * source, unsigned int npatterns, ...);
```
The first argument is the text to be tokenized and the second the number of patterns that are to be passed in. Each pattern is passed in using two arguments, its name and POSIX regex pattern, both as strings, in that order.

An example use of the lexer function to tokenize a simple piece of text with only a few patterns is shown below.
```c
lexer("numchars \"hello, world!\" == 7 + 5",4,"IDENTIFIER","[a-zA-Z]+","STRING","\"[a-zA-Z,!]*\"","OPERATOR","\\+|==","NUM","[0-9]+");
```

## 3) Reading the results
The `lexer` function returns an instance of the `results_t` struct, which contains a list of `token_t` types. Both structure types are detailed below:
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
Output: 
```
6 TOKENS RETURNED
TYPE : IDENTIFIER | TEXT : numchars 
TYPE : STRING | TEXT : "hello,world!" 
TYPE : OPERATOR | TEXT : == 
TYPE : NUM | TEXT : 7 
TYPE : OPERATOR | TEXT : + 
TYPE : NUM | TEXT : 5
```
