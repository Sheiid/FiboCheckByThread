/*
 * thread.c
 *
 *  Created on: Apr 3, 2018
 *      Author: sheida
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define n 5


void *other_func(void *argument)
{
	int i;
	int A[n];
	while (true)
		{


		printf("Enter the numbers: ");

			for(i=0;i<n;i++){
				scanf("%d",&A[i]);

				printf("A[%d]--> %d \n",i,A[i]);
			if (fiboCheck(A[i],1,1)==1){

			   printf("---the number belongs to Fibonacci sequence--- \n");
			  }else
				  printf("---the number doesn't belong to Fibonacci sequence---\n");
			}
		}
}

int fiboCheck(int,int,int);

int main(){


	int rc;
	pthread_t tid;

	sleep(2);
	rc = pthread_create(&tid, NULL, other_func, (void *));
	return 0;


}
int fiboCheck(int number,int a,int b){

	int next;

	if(number ==0 || number ==1)
		return 1;

	next=a+b;
	if(next>number)
		return 0;
	else if (next==number)
		 return 1;
	else
		return fiboCheck(number,b,next);

	//return 0;
}

