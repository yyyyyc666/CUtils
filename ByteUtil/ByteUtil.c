#include<string.h>
#include<stdio.h>
#include"ByteUtil.h"

//byte2Str 的时候 每个字节之间的分隔符
static char* separation = " ";
//byte2Str 的时候 每个字节之间的分隔符长度,与separation对应 
//注意,计算这个长度的时候不应该加上 '\0' 因为是要复制到目标中去的
//但是 '\0' 并不需要复制过去
static int separationLen = 1;



//字节码转换字符串核心(2进制)
//dest 存储结果
//source 要转换的字符
void byte2StrCoreBin(char* dest,char source);
//字节码转换字符串核心(16进制)
//dest 存储结果
//source 要转换的字符
void byte2StrCoreHex(char* dest,char source);


void byte2Str(char* dest,void* source,int len,int isBin,int isReverse,int lineNum){
	//开始的位置
	char* start;
	//递增的方向
	int direction;
	//首先判断是否需要反转
	if(isReverse){
		//需要反转
		start = (char*)source+len-1;
		direction = -1;
	}else{
		start = (char*)source;
		direction = 1;
	}
	//计算每个字节转化后所占用的长度
	int temp_len;
	if(isBin){
		temp_len = 8;
	}else{
		temp_len = 2;
	}
	//辅助保存每个字节转化后的字符串
	char temp_arr[temp_len];
	//开始循环取每个字节
	char temp_char;
	int i;
	for(i=0;i<len;i++){
		memcpy(&temp_char,start,1);
		start+=direction;
		//开始转换
		if(isBin){
			byte2StrCoreBin(temp_arr,temp_char);
		}else{
			byte2StrCoreHex(temp_arr,temp_char);
		}
		//转换完毕之后开始复制到目标数组
		memcpy(dest,temp_arr,temp_len);
		dest+=temp_len;
		//添加分割符号或者换行符
		//如果当前字符是最后一个,则既不添加换行也不添加分隔符
		if(i+1==len){
			continue;
		}
		//走到这里,当前字节,肯定不是最后一个
		if((i+1)%lineNum==0){
			*dest = '\n';
			dest++;
		}else{
			memcpy(dest,separation,separationLen);
			dest+=separationLen;
		}
	}
	//将字符数组最后一个值置为0,以表示字符串结尾
	*dest = 0;
}

int byte2StrGetLen(int len,int isBin,int lineNum){
	//首先计算所有字节转化完毕之后要多少个长度
	int totla = isBin?len*8:len*2;
	//然后计算 分隔符 换行符 之类占多少个字节
	int enterNum;//需要多少个换行符
	int separationNum;//需要多少个分隔符
	
	int line = len/lineNum;//计算出有多少个完整的行
	int remain = len%lineNum;//计算出完整的行之后还有多少余数
	if(remain==0){
		enterNum = line-1;
		separationNum = line*(lineNum-1);
	}else{
		enterNum = line;
		separationNum = line*(lineNum-1)+remain-1;
	}
	//printf("total: %d enterNum: %d separationNum: %d\n",totla,enterNum,separationNum);
	return totla+enterNum+separationNum*separationLen+1;
}
void byte2StrCoreBin(char* dest,char source){
	//右移X位
	int right = 0;
	char temp;
	int i = 0;
	for(i=0;i<8;i++){
		right = 8-i-1;
		temp = source>>right;
		//只保留最后一位,其他位置置0
		temp = temp&1;
		if(temp==1){
			dest[i] = '1';
		}else{
			dest[i] = '0';
		}
	}
}

void byte2StrCoreHex(char* dest,char source){
	//取出前4位
	char temp;
	temp = source>>4;
	temp = temp&0x0f;
	if(temp>=0&&temp<=9){
		dest[0] = temp+48;
	}
	if(temp>=10&&temp<=15){
		dest[0] = temp+55;
	}
	//取出后4位
	temp = source&0x0f;
	if(temp>=0&&temp<=9){
		dest[1] = temp+48;
	}
	if(temp>=10&&temp<=15){
		dest[1] = temp+55;
	}
}