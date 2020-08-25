#include<stdio.h>
#include"FileUtil.h"

int main(){
	char temp_char[256];
	getCurrentDirectory(temp_char,sizeof(temp_char));
	printf("%s\n",temp_char);
	return 0;
}