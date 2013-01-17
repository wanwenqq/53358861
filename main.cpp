#include <stdio.h>
#include <stdarg.h>
#include "./public/XYTypedef.h"

#include "./public/MMTrace.h"
#include "./public/XYLogFile.h"
#include "./public/XYString.h"
#include "./public/XYDateTime.h"
#include "./public/XYFile.h"




void test( const char * fmt,...);

int main( int arg,char * args[])
{

	printf("welcome to test unit\n");
	
	int nreturn = 0;

//	string name = "mmtrace test";
//	MMTrace mt(name);
//	string msg = "main func MMTrace msg ";
//	mt.Debug( msg );



//	char sMsg[] = {"XYLogFile Model Test\n"};
//	XYLogFile lf;
//	XYLogFile::GetInstance()->XYNull( false,"%s","错误信息描述" );
//	XYLogFile::GetInstance()->XYLog(2,false,"%s","测试打印日志模块");

//	char sBuffer[1024] = {0};
//	XY_snprintf( sBuffer,1024,"%s",sMsg);

//	printf(sBuffer);

//	test( "%s,%s,%d","Main22222222",__FILE__,__LINE__ );

/*
	char s1[] = {"first string catch!"};
	char s2[] = {"string"};

	int n = s1 - s2;
	printf("n=====%d\n",n);
	register char * pTemp;
	pTemp = strstr( s1,s2);
	int nn = pTemp - s1;
	printf(" nn =====%d\n",nn);
	printf("ss===%s\n",pTemp);

*/


/*
	XYString str = "123";
	XYString str1 = "Windows and Linux";
	printf("str = %ld\n",str.ToLong());
	XYString str2 = str1.FindFrontStr( "and" );
	printf("Find str=%s\n",str2.c_str());
	XYString str3 = str1.FindTailStr( "and" );
	printf("Find str tail=%s\n",str3.c_str());
	XYString str4 = str1.GetUpper();
	XYString str5 = str1.GetLower();
	printf("upper=%s,low=%s\n",str4.c_str(),str5.c_str());

	int n  = str1.SetAt(4,'D');
	printf( "SetAt =%s\n",str1.c_str());

	assert( 0 );

*/

/*
	int nerr = 0x7127;
	int nerr1 = 0x80000001;
	long nMaster = nerr & 0x7FFFFFFF;

	printf("nMaster = %ld\n",nMaster);
*/


/*
	XYDateTime dt = XYDateTime::Now();
	printf("year=%d,mon=%d,day=%d,hour=%d,min=%d,sec=%d\n",dt.GetYear(),dt.GetMon(),dt.GetDay(),
				dt.GetHour(),dt.GetMin(),dt.Getsec());
	printf("String=%s\n",dt.ToString().c_str());
	printf("date=%s\n",dt.DateToString().c_str());	
	printf("time=%s\n",dt.TimeToString().c_str());	
	printf("date long=%ld\n",dt.DateToLong());	
	printf("time long=%ld\n",dt.TimeToLong());


	XYMsecCounter cc;
	cc.SetCurTickCounter();
	printf("XYClockCounter seet=%s\n",cc.ToString().c_str());	

	sleep(2);
	printf("XYClockCounter cur=%ld\n",cc.GetCurTickCounter());

	XYClockCounter cc1;
	cc1.SetCurTickCounter();
	printf("XYClockCounter seet1=%s\n",cc1.ToString().c_str());	

	for(int i=0;i<1000000;i++)
	{
		dt.DateTimeToString();
		
	}

//	sleep(2);//不能使用
	printf("XYClockCounter cur1=%ld\n",cc1.GetCurTickCounter());	


	XYRDTSCCounter cc2;
	cc2.SetCurTickCounter();
	printf("XYClockCounter seet2=%s\n",cc2.ToString().c_str());	

	sleep(1);
	printf("XYClockCounter cur2=%ld\n",cc2.GetCurTickCounter());		
*/	
	
	XYFile dir1;
//	printf("get current path=%s\n",dir1.GetCurrentPath().c_str());
//	dir1.CreatDir("test/test1");
//	printf(" CreatDir return =%d\n",nreturn);
//	bool bDir = dir1.IsDir("test2");
//	printf("IsDir=%d\n",bDir);
//	dir1.DeleteDir("test1");
	nreturn = XYFile::RenameFile("aaa","bbb");
	printf("RenameFile=%d\n",nreturn);

	return 0;
}


