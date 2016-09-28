#include<iostream>
#include<cstdlib>
#include<windows.h>
#include<time.h>                          
#include<conio.h>
#include<math.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
int gsa(int*, int, int, int, int);
int cmp(const void*a, const void*b)
{
	return(*(int*)a - *(int*)b);
}
int main()
{
	ofstream infile("graph.txt");
	int arr[6000];
	double sum=0,timec;
	int low, high,mid,n=100;
	clock_t start, end;
	while(n!=1000)
	{
		srand(time(NULL));
		for (int k=1;k<=1000;k++)
		{
			for(int i=1;i<=n;i++)
				arr[i]=rand()%1000;
			qsort(arr,n,sizeof(int),cmp);
			low=1;
			high=n;
			int key=rand() % 1000;
			cout<<key<<"\n";
			start=clock();
			for(int p=1;p<=100;p++)
				int loc=gsa(arr,low,high,9,key);
			end=clock();
			timec=(double(end - start)) / CLOCKS_PER_SEC;
			timec=timec / 1000.0;
			sum=sum+timec;
		}
		sum=sum*10000.0;
		infile<<n<<","<<sum<<"\n";
		n=n+50;
		sum=0;
	}
	infile.close();
	return 0;
}
int gsa(int* arr, int low, int high, int d, int key)           //THE FUNCTION APLLIES DIVIDE AND CONQUER SEARCH CRITERIA WHERE ARRAY IS 
{                                                             //IS DIVIDED INTO D PARTS.
	if(low<high)                                          //i.e. FOR TERNARY SEARCH D=3
	{                                                     //AND THEN COMPARES THE TIME TAKEN BY VARIOUS SEARCHES TO ESTABLISH 
		int mid[15],c;                                 //WHICH SEARCHING TECHNIQUE WILL BE BEST.
		mid[1]=low+(high-low)/d;
		for(int i=2;i<d;i++)
		{
			if(i==2)
				mid[i]=mid[1]+(high-low)/d;
			else
				mid[i]=mid[i-1]+(high-low)/d;
		}
		if(arr[mid[1]]==key)
			return mid[1];
		for(int i=2;i<d;i++)
		{
			if(arr[mid[i]]==key)
				return mid[i];
		}
		for(int i=1;i<d;i++)
		{
		lab:
			if(i==d)
				return gsa(arr,mid[i-1]+1,high,d,key);
			if((arr[mid[i]]<key))
			{
				i++;
				goto lab;
			}
			else
			{
				if(i==1)
					return gsa(arr,low,mid[1]-1,d,key);
				else
					return gsa(arr,mid[i-1]+1,mid[i]-1,d,key);
			}
		}
	}
	else
	{
		if (arr[low] == key)
			return low;
		else
			return -1;
	}
}
