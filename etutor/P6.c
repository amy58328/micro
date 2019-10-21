#include<stdio.h>
#define N 32

int bin[N];

void init()
{
	for(int i=0 ; i<N ;i++)
	{
		bin[i] = 0;
	}
}
int main(int argc, char const *argv[])
{
	int num;
	while(~scanf("%d",&num))
	{
		printf("Before bits are reversed:\n");
		printf("%d = ",num );

		init();

		int temp =0 ; 

		while(num>0)
		{
			bin[temp] = num & 1;
			temp ++;
			num = num >> 1;
		}

		for(int i=N-1 ; i>=0 ; i--)
		{	
			printf("%d",bin[i] );
			int space = i & 7;
			if(space == 0)
				printf(" ");
		}

		printf("\n\nAfter bits are reversed:\n");
		
		long long trans = 0;
		for(int i=0 ; i<N ; i++)
		{	
			trans = trans << 1 ;
			trans += bin[i];
		}

		printf("%lld = ", trans );
		temp = 0;
		for(int i=0 ; i<N ; i++)
		{
			printf("%d",bin[i] );
			temp ++;
			if(temp == 8)
			{
				printf(" ");
				temp = 0 ;
			}
		}
		printf("\n");
	}
	return 0;
}