#include<iostream>
#include<math.h>
using namespace std;

/*以二进制形式打印到控制台函数*/
void func( void *pBuffer, int nSize) 
{ 
   unsigned char *pTemp =
	   (unsigned char*)pBuffer; 
   int   i,   j,   nResult; 
   for(i=nSize-1;i>=0;i--) 
   { 
        for ( j=7;j>=0;j--)
		{ 
          nResult = pTemp[i]  &
			  (int)pow(2, j); 
          nResult = (0!= nResult ); 
          cout<<nResult; 
		} 
   } 
   cout<<endl;
} 

/*  generate checksum of CRC 
*   author :  Zeyang Lin       
*   date :     6 May, 2018                             
*/
    //注意该函数第二个入口参数是传址
	//因此该CRC生成函数可以对任意字节的数据进行CRC生成计算
	//具有高可用性
    //默认使用的生成多项式 x^(7)+x^(3)+x^(0) --> 0x89
    //注意生成多项式的最高位和最低位必须为1
void crc8(char ch,unsigned char &crc)   
//ch为需要校验的字符,crc为校验和
{
	unsigned char i;
	crc ^= ch;
    //func((void*)&crc,sizeof(crc)); 
	for(i = 0;i < 8;i++)
	{
		crc = crc << 1;
		if(crc & 0x80)
		{
			crc = crc ^ 0x89;
		}
       //func((void*)&crc,sizeof(crc)); 
	}
}


int mmain()
{
    short ch1 = 0x5f;
	short ch2 = 0x6d;
	//假设我需要生成CRC校验码的数据为0x5f6d，
	//共两个字节，从高字节到低字节依次调用crc8函数
	//crc变量初始化为0
    unsigned char crc = 0x00;
	crc8(ch1,crc);
	crc8(ch2,crc);
	//将生成的CRC校验码以二进制形式打印到控制台
	func((void*)&crc,sizeof(crc)); 
    return 0;
}
