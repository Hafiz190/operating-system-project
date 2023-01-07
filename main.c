#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 5
#define LINE_MAX 1024


struct linkedList {
	
    	int Name; //Name
    	int bTime; //Brust Time
    	int aTime; //Arrival Time
    	int wTime; //Waiting Time
    	int p; //Priority    	
    	int sr; //Show Result
		
}

linkedList;

void FCFS(struct linkedList process[]){

	FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	
	
    	struct linkedList *temp;
    	temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    	int i;
   	 	int totalWaiting=0;
    	double averageWaiting;

    for(i=0;i<SIZE;i++)
        temp[i]=process[i];

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) 
		
		{
            if (temp[b].aTime > temp[b + 1].aTime) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            
            }
        }
    }

    totalWaiting = temp[0].wTime = 0;

    for(i = 1; i < SIZE; i++){
        temp[i].wTime = (temp[i-1].bTime + temp[i-1].aTime + temp[i-1].wTime) - temp[i].aTime;
        
        totalWaiting += temp[i].wTime;
    }
    
    	averageWaiting = (double)totalWaiting/SIZE;
    		fprintf(fptr, "%s" ,"\nScheduling Method : First Come First Served\nProcess Waiting Times:\n");

    for(i = 0; i < SIZE; i++) 
	
	{
		
        fprintf(fptr,"\nP%d: %d ms", i+1, temp[i].wTime);
    
	}

    fprintf(fptr, "\nAverage waiting time: %f ms\n",averageWaiting);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}

void SJFS_nonpreemptive(struct linkedList process[])

{
	
	FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	
	
    	struct linkedList *temp, list, list2;
   	 	temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    	int i,a,b;
    	int totalWaitingTime=0;
    	double averageWaitingTime;

    for(i=0;i<SIZE;i++) {
        temp[i] = process[i];
        
    }

    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) 
		
		{
           		if (temp[b].aTime > temp[b + 1].aTime) {
            list2 = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list2;
            
            }
        }
    }

    for(a=2;a<SIZE;a++) {
        for (b = 1; b < SIZE - a+1; b++) 
		{
            	if (temp[b].bTime > temp[b + 1].bTime) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            }
        }
    }

    totalWaitingTime = temp[0].wTime = 0;
	 for(i = 1; i < SIZE; i++)
	{
        temp[i].wTime = (temp[i-1].bTime + temp[i-1].aTime + temp[i-1].wTime) - temp[i].aTime;
        totalWaitingTime += temp[i].wTime;
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    for(a=1;a<SIZE;a++) 
	
	{
        for (b = 0; b < SIZE - a; b++) 
		
		{
            	if (temp[b].Name > temp[b + 1].Name) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            }
        }
    }

    fprintf(fptr, "%s" , "\nScheduling Method : Shortest Job First Scheduling (Non-Preemptive)\nProcess Waiting Times:");
   
    for(i = 0; i < SIZE; i++) 
	
	{
        fprintf(fptr,"\nP%d: %d ms", i+1, temp[i].wTime);
    }
    
    
    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
    
}

void SJFS_preemptive(struct linkedList process[])

{
	
	FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	
	
    	struct linkedList *temp;
    	temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    	int i,x,timer,shortestJob,totalBurstTime;
    	int totalWaitingTime=0;
    	double averageWaitingTime;

    for(i=0;i<SIZE;i++) 
	
	{
        temp[i] = process[i];
        totalBurstTime += process[i].bTime;
    }

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) 
	
	{
        for (b = 0; b < SIZE - a; b++) 
		
		{
           		 if (temp[b].aTime > temp[b + 1].aTime) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            }
        }
    }

    totalWaitingTime = temp[0].wTime = 0;

    i=0;
    for (timer = 0; timer < totalBurstTime; timer++) 
	
	{
        if(temp[i].bTime > 0 && temp[i].aTime <= timer)
            temp[i].bTime--;

        if(temp[i].bTime<=0 && temp[i].sr != 1)
        
        {
            temp[i].sr = 1;
            temp[i].wTime = (timer+1) - process[i].bTime - temp[i].aTime;
            totalWaitingTime+=temp[i].wTime;
        }
        
        shortestJob = 65435;
        for(x = 0; x < SIZE; x++)
		{

            if(temp[x].aTime <= (timer+1) && temp[x].sr != 1){

                if(shortestJob != temp[x].bTime && shortestJob > temp[x].bTime){
                    shortestJob = temp[x].bTime;
                    i=x;
                }
            }
        }
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    fprintf(fptr , "%s" , "\nScheduling Method : Shortest Job Scheduling (Preemptive)\nProcess Waiting Times:");
   
    for(i = 0; i < SIZE; i++)
	
	{
        fprintf(fptr , "\nP%d: %d ms", i+1, temp[i].wTime);
    }

    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}

void PS_preemptive(struct linkedList process[], FILE *fp

){
    struct linkedList *temp;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    int i,x,timer,minimumPriority,totalBurstTime;
    int totalWaitingTime=0;
    double averageWaitingTime;
    
	FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
    for(i=0;i<SIZE;i++) 
	
	{
        temp[i] = process[i];
        totalBurstTime += process[i].bTime;
    }

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) 
	
	{
        for (b = 0; b < SIZE - a; b++) {
            if (temp[b].aTime > temp[b + 1].aTime) {
                list = temp[b];
                temp[b] = temp[b + 1];
                temp[b + 1] = list;
            }
        }
    }

    totalWaitingTime = temp[0].wTime = 0;

    i=0;
    for (timer = 0; timer < totalBurstTime; timer++) 
	
	{
        if(temp[i].bTime > 0 && temp[i].aTime <= timer)
            temp[i].bTime--;

        if(temp[i].bTime<=0 && temp[i].sr != 1)
        
        {
            temp[i].sr = 1;
            temp[i].wTime = (timer+1) - process[i].bTime - temp[i].aTime;
            totalWaitingTime+=temp[i].wTime;
        }
        minimumPriority = 65435;
        for(x = 0; x < SIZE; x++)
		
		{

            if(temp[x].aTime <= (timer+1) && temp[x].sr != 1){

                if(minimumPriority != temp[x].p && minimumPriority > temp[x].p){
                    minimumPriority = temp[x].p;
                    i=x;
                }
            }
        }
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    fprintf(fptr  ,  "%s" , "\nScheduling Method : Priority Scheduling (Preemptive)\nProcess Waiting Times:");
 
    for(i = 0; i < SIZE; i++) {
        fprintf(fptr , "\nP%d: %d ms", i+1, temp[i].wTime);
    }
    
    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}

void PS_nonpreemptive(struct linkedList process[]){
    struct linkedList *temp;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    struct  linkedList list1,list2;
    int i,j,x,y;
    int totalWaitingTime=0;
    double averageWaitingTime;
    
    FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	
	
    for(i=0;i<SIZE;i++) 
	
	{
        temp[i] = process[i];
    }

    for(i=2;i<SIZE;i++)
        for(j=1;j<SIZE-i+1;j++){
            if(temp[j].p > temp[j+1].p)
			
			{
                list1 = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = list1;
            }
        }

    totalWaitingTime = temp[0].wTime = 0;

    for(i=1;i<SIZE;i++)
	
	{
        temp[i].wTime = (temp[i-1].bTime + temp[i-1].aTime + temp[i-1].wTime) - temp[i].aTime;
        totalWaitingTime+=temp[i].wTime;
    }
    averageWaitingTime = (double)totalWaitingTime/SIZE;

    for(x=1;x<SIZE;x++) 
	
	{
        for (y = 0; y < SIZE - x; y++) {
            if (temp[y].Name > temp[y + 1].Name) {
                list2 = temp[y];
                temp[y] = temp[y + 1];
                temp[y + 1] = list2;
            }
        }
    }
