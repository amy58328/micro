#include<stdio.h>

char HEX[16] = "0123456789ABCDEF";
char BIN[2] = "01";
char OCT[8] = "01234567";
char bin[32];
char oct[12];
char hex[8];

void printBinary(long long   a)
{
	int temp = 0;
	for(int i=0 ;i < 32 ; i++)
			bin[i] = '0';
		while(a > 0 )
		{
			bin[temp] = BIN[a & 1];
			temp ++;
			a = a >>1;
		}
		for(int i=31 ; i>=0 ; i--)
			printf("%c",bin[i] );
		printf("\n");
}

void printOctal(long long a)
{
	int temp = 0;
	for(int i=0 ; i<12 ; i++)
		oct[i] = '0';
	while(a >0)
	{
		oct[temp] = OCT[a & 7];
		temp ++ ;
		a = a >> 3;
	}
	for(int i=11 ; i>=0 ; i--)
		printf("%c", oct[i]);
	printf("\n");
}

void printHexidecimal(long long a)
{
	int temp = 0;
	for(int i=0 ; i<8 ; i++)
		hex[i] = '0';
	while(a >0)
	{
		hex[temp] = HEX[a & 0xf] ; 
		a = a >>4;
		temp ++;
	}
	printf("0x");
	for(int i=7 ; i>=0 ; i--)
		printf("%c", hex[i]);
	printf("\n");

}
int main(int argc, char const *argv[])
{
	int time = 1;
	long long num ;


	while(scanf("%lld", &num) != EOF)
	{
		printf("Case %d: %lld\n",time, num );
		time ++;

		long long sum = num;
		int temp = 0;
		// binary 
		printBinary(num);

		//octary
		printOctal(num);

		//hex
		printHexidecimal(num);
	}
	
	return 0;
}
