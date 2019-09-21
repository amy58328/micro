#include<stdio.h>

char HEX[16] = "0123456789ABCDEF";
char BIN[2] = "01";
char OCT[8] = "01234567";

int main(int argc, char const *argv[])
{
	int time = 1;
	long long num ;
	char bin[32];
	char oct[12];
	char hex[8];

	while(scanf("%lld", &num) != EOF)
	{
		printf("Case %d: %lld\n",time, num );
		time ++;

		long long sum = num;
		int temp = 0;
		// binary 
		for(int i=0 ;i < 32 ; i++)
			bin[i] = '0';
		while(sum > 0 )
		{
			bin[temp] = BIN[sum & 1];
			temp ++;
			sum = sum >>1;
		}
		for(int i=31 ; i>=0 ; i--)
			printf("%c",bin[i] );
		printf("\n");

		//octary
		sum = num ;
		temp = 0;
		for(int i=0 ; i<12 ; i++)
			oct[i] = '0';
		while(sum >0)
		{
			oct[temp] = OCT[sum & 7];
			temp ++ ;
			sum = sum >> 3;
		}
		for(int i=11 ; i>=0 ; i--)
			printf("%c", oct[i]);
		printf("\n");

		//hex
		sum = num ;
		temp = 0;
		for(int i=0 ; i<8 ; i++)
			hex[i] = '0';
		while(sum >0)
		{
			hex[temp] = HEX[sum & 0xf] ; 
			sum = sum >>4;
			temp ++;
		}
		printf("0x");
		for(int i=7 ; i>=0 ; i--)
			printf("%c", hex[i]);
		printf("\n");

	}
	
	return 0;
}
