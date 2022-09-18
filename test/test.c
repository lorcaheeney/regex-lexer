#include<stdio.h>
#include<lexer.h>

int main(){
	results_t res = lexer("numchars \"hello, world!\" == 7 + 5",4,"IDENTIFIER","[a-zA-Z]+","STRING","\"[a-zA-Z,! ]*\"","OPERATOR","\\+|==","NUM","[0-9]+");
	printf("%d TOKENS RETURNED\n", res.ntoks);
	for(int i = 0 ; i < res.ntoks ; i++ ){
		printf("TYPE : %s | TEXT : %s\n",res.toks[i].type, res.toks[i].str);
	}
	return 0;
}
