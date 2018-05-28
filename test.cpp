#include<iostream>
#include<math.h>
using namespace std;

/*�Զ�������ʽ��ӡ������̨����*/
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
    //ע��ú����ڶ�����ڲ����Ǵ�ַ
	//��˸�CRC���ɺ������Զ������ֽڵ����ݽ���CRC���ɼ���
	//���и߿�����
    //Ĭ��ʹ�õ����ɶ���ʽ x^(7)+x^(3)+x^(0) --> 0x89
    //ע�����ɶ���ʽ�����λ�����λ����Ϊ1
void crc8(char ch,unsigned char &crc)   
//chΪ��ҪУ����ַ�,crcΪУ���
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
	//��������Ҫ����CRCУ���������Ϊ0x5f6d��
	//�������ֽڣ��Ӹ��ֽڵ����ֽ����ε���crc8����
	//crc������ʼ��Ϊ0
    unsigned char crc = 0x00;
	crc8(ch1,crc);
	crc8(ch2,crc);
	//�����ɵ�CRCУ�����Զ�������ʽ��ӡ������̨
	func((void*)&crc,sizeof(crc)); 
    return 0;
}
