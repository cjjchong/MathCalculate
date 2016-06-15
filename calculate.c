/*
 (C)cjj 2016-6-15 
 Filename    : calculate.c
 Compiler    : C-Free 5.0
 Description : read FILE1 ,calulate then save result into FILE2
 
 FILE1 
 f1  X10 X11 X12 X13 .....
 f2  X20 X21 X22 X23 .....
 f3 ....
 ......
 
 FILE2
 f1 result1
 f2 result2
 f3 result3
 ......
 
 Formula
 
 result = sqrt( sum( square ( Xij*2*PI*fi) )   / countOf(Xij) )
 
 Release     : 06/15/2016 1.0
 */
 
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <math.h>
 
double SQUARE(double x)
{
	return x*x;
}

double FACTOR(double x,double y,double j)
{
	return x*y*j*2.0;
}

int calculate(FILE *fout,const char *lineCharacters,const double pi,const char* rule,int ifDebug)
{
	char lines[65535]={0};
	double frequence;
	double Xij;
	double result;
	
	char tempNumber[32]={0};
	unsigned int count = 0;
	char *point ;
	int findFrequence = 0;
	double sum = 0.0;
	char cmdLine[128]={0};
	
	
	strncpy(lines,lineCharacters,strlen(lineCharacters)-1);
	if(ifDebug)
		printf("%s\n",lines);
	if(strlen(lines))
	{
		point = strtok(lines, rule);
	
		while( point!= NULL) {
			
			strcpy(tempNumber,point);
			if(!findFrequence)
			{
				sscanf(tempNumber,"%lf",&frequence);
				findFrequence = 1;				
			}
			else
			{
				sscanf(tempNumber,"%lf",&Xij);	
				sum += SQUARE(FACTOR(Xij,pi,frequence));
				count++;
			}			
			point = strtok(NULL, rule);
		}
		result = sqrt(sum/count); 
		
		if(ifDebug)
			printf("frequence[%lf] countOfXij[%d]  sum[%lf] result[%lf]\n",frequence,count,sum,result);
			
		sprintf(cmdLine,"%lf  %lf\n",frequence,result);
		fputs(cmdLine,fout);
	}
}
 
int main(void)
{
	
 	char finName[128]={0};
  	char foutName[128]={0};
 	double pi=0; 
 	int debugMode = 1; 	
 	char splitSymbol[8]=" ";
 	int splitSymbolMode=0;
	FILE *fin; 
	FILE *fout;
	char * strerror(int errnum);
	char cmd[128]={0};
	char lineString[65535] = {0};  
	int readfileFailed = 0;
	
	printf("��������Ҫ���������ļ�����");
	scanf("%s",&finName) ;
#if 1	
	printf("��ѡ��%s�����ּ�ķָ���:\n1. �ո� \n2Ӣ�Ķ��� \n3: | \n======>:",finName);
	scanf("%d",&splitSymbolMode) ;
	while( splitSymbolMode != 1 && splitSymbolMode != 2 && splitSymbolMode != 3)
	{
		printf("\n���뷶Χ������ѡ��1��2��3");
		scanf("%d",&splitSymbolMode) ;		
	}
	switch(splitSymbolMode) 
	{
		case 1:
			strcpy(splitSymbol," ");
			break;
		case 2:
			strcpy(splitSymbol,",");
			break;
		case 3:
			strcpy(splitSymbol,"|");
			break;
		default:
			strcpy(splitSymbol," ");
			break;
	}
#endif	
	printf("\n�����뽫Ҫ������ļ�����");
	scanf("%s",&foutName) ;
	printf("\n������ ����ֵ��") ;
	scanf("%lf",&pi) ;
	printf("\n�Ƿ���ʾ�������(����ʾ������0,��ʾ������1):") ;
	scanf("%d",&debugMode) ;
	while( debugMode != 0 && debugMode != 1 ) 
	{
		printf("\n���뷶Χ������ѡ��0��1:");
		scanf("%d",&debugMode) ;
	}
	
	fin = fopen(finName, "r");
	if( fin == NULL )
	{
		sprintf(cmd,"��%s�ļ�ʧ��",finName);
		perror(cmd);
		readfileFailed |= 1;
		
	}
	fout = fopen(foutName, "w+");
	if( fout == NULL )
	{
		sprintf(cmd,"��%s�ļ�ʧ��",foutName);
		perror(cmd);
		readfileFailed |= 1;
		
	}
	
	if(readfileFailed == 0)
	{
		printf("\n\n������... ...\n");
		while(!feof(fin))  
	    {  
	        memset(lineString, 0, sizeof(lineString));  
	        fgets(lineString, sizeof(lineString) - 1, fin); // ������\n  
	        if(strlen(lineString)==1)
	        	break;
	        calculate(fout,lineString,pi,splitSymbol,debugMode);
	    }  
		printf("\n�������\n\n");	
		if(fclose(fin)!=0)
		{
			sprintf(cmd,"�ر�%s�ļ�ʧ��",finName);
			perror(cmd);
		}	
		
	 	if(fclose(fout)!=0)
	 	{
		 	sprintf(cmd,"�ر�%s�ļ�ʧ��",foutName);
			perror(cmd);
	 	}
	 	printf("\n�밴Ctrl+C�˳�\n");
		scanf("%s",&cmd);
	}
	else
	{
		printf("\n�밴Ctrl+C�˳�\n");
		scanf("%s",&cmd);		
	}
	return 0;	
}
