#include<stdio.h>
#include"ByteUtil.h"

int main(){
	float dest = 136.42;
	int targetLen = sizeof(float);
	int isBin = 1;
	int isReverse = 1;
	int lineNum = 6;
	int resultLen = byte2StrGetLen(targetLen,isBin,lineNum);
	char src[resultLen];
	byte2Str(src,&dest,targetLen,isBin,isReverse,lineNum);
	printf("%s",&src);
	return 0;
}