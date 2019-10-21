#include<stdio.h>
#define N 32

int bin[N];

void init()
{
	for(int i=0 ; i<N ; i++)
		bin[i] = 0;
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


int main(int argc, char const *argv[])
{
	char a ,b,c,d;
	scanf("%c %c %c %c",&a,&b,&c,&d);

	int number = (int)a;
	printf("%c:\n", a);
	printf("%d = ",number );
	output(number);

	printf("%c:\n", b);	
	number = (int)b;
	printf("%d = ",number );
	output(number);

	printf("%c:\n", c);
	number = (int)c;
	printf("%d = ",number );
	output(number);

	printf("%c:\n", d);	
	number = (int)d;
	printf("%d = ",number );
	output(number);
	
	printf("'%c' and '%c' and '%c' and '%c' packed in an unsigned int:
\n",a,b,c,d );

	

	return 0;
}