#include<stdio.h>

char HEX[16] = "0123456789ABCDEF";

int main(int argc, char const *argv[])
{
	long long  num ;
	int time = 1;
	while(scanf("%lld",&num)!= EOF)
	{
		printf("Case %d: %lld\n",time,num );
		time ++;
	
		char ans[8] ;
		for(int i=0 ; i<8 ; i++)
			ans[i] = '0';

		int temp = 7;
		while(num>0)
		{
			ans[temp--] = HEX[num & 0xf] ; 
			num = num >>4;
		}

		for(int i=0 ; i<8 ; i++)
		{
			printf("%c ", ans[i]);
		}
		
		printf("\n");
	}
	
	return 0;
}