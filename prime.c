#include<stdio.h>
#define N 100

int num[N+5];

int main(int argc, char const *argv[])
{
	for(int i=0 ; i<=N ; i++)
		num[i] = 0;

	for(int i=2 ; i<= N ; i++)
	{
		int temp = 0 ;
		for(int j=2 ; j < i ; j++)
		{
			if(i % j == 0)
			{
				temp = 1;
				break;			
			}
		}

		if(temp == 0 )
		{
			num[i] = 1;
		}
	}

	int  temp = 0;
	for(int i=0 ; i<= N ; i++)
	{
		if(num[i] == 1)
		{
			printf("%d ",i);
			temp ++;
		}
		
		if(temp == 10)
		{
			printf("\n");
			temp = 0;
		}

	}
	return 0;
}