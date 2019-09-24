#include <stdio.h>
#define N 32

int bin[N];

void init()
{
	for(int i=0 ; i<N ; i++)
	{
		bin[i] = 0 ;
	}
}

void output(int n)
{	
	init();
	int temp = 0;
	while(n > 0 )
	{
		bin[temp] = n & 1;
		temp ++;
		n = n >> 1;
	}

	temp =0 ; 
	for(int i=N-1 ; i>= 0 ;i--)
	{
		printf("%d",bin[i] );
		temp ++ ;
		if(temp == 8)
		{
			temp = 0;
			printf(" ");
		}
	}
	printf("\n");
}

int zeroshift(int n)
{
	if(n != 0)
	{
		int temp = n & 1;
		while(temp == 0)
		{
			n = n >> 1;
			temp = n & 1;
		}
	}
	
	return n;
}

int main(int argc, char const *argv[])
{
	int num;

	while(~scanf("%d",&num))
	{
		init();

		printf("The packed character representation is:\n");
		printf("%d = ",num );	

		int num1 = num & 0xFF000000;
		num1 = num1 >> 24;
		int num2 = num & 0xFF0000;
		num2 = num2 >> 16;
		int num3 = num & 0xFF00;
		num3 = num3 >> 8;
		int num4 = num & 0xFF;
		
		output(num);
		printf("\n");

		char str[10];
		sprintf(str,"%d",num1);
		printf("%s = ",str);
		output(num1);

		sprintf(str,"%d",num2);
		printf("%s = ",str);
		output(num2);

		sprintf(str,"%d",num3);
		printf("%s = ",str);
		output(num3);

		sprintf(str,"%d",num4);
		printf("%s = ",str);
		output(num4);

	}
	return 0;
}