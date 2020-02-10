//把目标内存处的内存,转换为字符串形式存储到指定位置
//dest存储位置(存放结果,请给出足够大的空间)
//source目标内存
//len 转化长度
//isBin 是否以2进制形式转化 如果是真 则 2进制 如果是假 则 16进制
//isReverse 是否反转 此参数主要是为了应对目标是数值类型的时候,因为如果是数值类型通常都是反向存储的
//lineNum 每行展示多少个字节
//separation 两组字节之间的分割符
//例如 10000 = ‭01011111 01011110 00010000 0000‬ 
//isBIn = 1 isReverse = 1 lineNum = 2 separation = " "
//则转换后就是 01011111 01011110 \n XX00010000 0000
void byte2Str(char* dest,void* source,int len,int isBin,int isReverse,int lineNum);
//辅助计算 byte2Str 中 dest 需要的长度
//len 待转换的长度
//isisBin 是否是2进制
int byte2StrGetLen(int len,int isBin,int lineNum);