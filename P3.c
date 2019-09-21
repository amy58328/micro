#include<stdio.h>
#include <stdlib.h>

int special[32] ;
int special_re[32];

char BIN[2] = "01";

void swap(int i,int site)
{
	int temp = special[i];
	special[i] = special[site];
	special[site] = temp;
}
void sort(int l)
{
	for (int i = 0 ; i <l ; i++)
	{
		int min_site = i;
		for(int j=i+1 ; j<l ; j++)
			if(special[j] < special[min_site])
				min_site = j;

		swap(i , min_site);

	}
}

int del_re(int l )
{
	int ll = l ;
	int index = 0 ; 
	int i = 1 ;
	for(;i<l;i++)
	{
		if(special[i] != special[index])
		{
			index++;
			special[index] = special[i] ;
		}

		else 
		{
			ll--;
		}
	}	
	return ll ;
}

int main(int argc, char const *argv[])
{
	int temp ;
	int special_number =0 ;
	while(scanf("%d",&temp)!=EOF)
	{
		if(temp == -1)
		{
			sort(special_number);
			special_number = del_re(special_number);
			for(int i=0;i<special_number ; i++)
				printf("%d ",special[i]);
			printf("\n");
			break;
			
		}
		special[special_number++] = temp;
	}

	
	long long num ;
	int time =1;
	char bin[32];
	
	while(scanf("%lld",&num)!=EOF)
	{
		temp = 0;
		printf("Case %d: %lld\n",time,num );
		time ++;
		for(int i=0 ; i<32 ; i++)
			bin[i] = '0';

		while(num > 0 )
		{
			bin[temp] = BIN[num & 1];
			temp ++;
			num = num >>1;
		}

		int ans = 0;
		for(int i=0 ; i<special_number ; i++)
		{
			if(bin[special[i]] == '1')
			{
				ans ++;
			}
		}

		if(ans == special_number)
		{
			printf("true(all bits 1)\n");
			printf("true(exist bits 1)\n");
		}
		else if(ans!=0)
		{
			printf("false(all bits 1)\n");
			printf("true(exist bits 1)\n");
		}
		else
		{
			printf("false(all bits 1)\n");
			printf("false(exist bits 1)\n");
		}


	}
	return 0;
}
