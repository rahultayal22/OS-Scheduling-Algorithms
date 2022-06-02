#include<stdio.h>
#include<conio.h>
#include<iostream>

using namespace std;

struct Process{
	int P_ID;       //Process ID
	int bt;	        //Burst Time
	int wt;		    //Waiting Time
	int tat;		//Turn Around Time
};

void FCFS();						//First Come First Serve Scheduling
void SJF();                         //Shortest Job First Scheduling
void Priority();                    //Priority Scheduling
void RoundRobin();                  //Round Robin Scheduling
void Gantt(Process p[],int);        //Gantt Chart for scheduling algorithms


 //MAIN METHOD
int main() {
    int choice;
    system("cls");
	cout<<"Specify the scheduling algorithm to allocate processes:\n1. First Come First Serve\n2. Shortest Job First\n3. Priority Scheduling\n4. Round Robin Scheduling\n Enter your choice: ";
    cin>>choice;

    switch(choice){
        case 1:
            FCFS();
            break;
        case 2:
            SJF();
            break;
        case 3:
            Priority();
            break;
        case 4:
            RoundRobin();
            break;
        default:
            cout<<"Incorrect Input!!";
            break;
    }
    
    return 0;
}



//FIRST COME FIRST SERVE SCHEDULING ALGORITHM
void FCFS(){
	int n, avwt= 0, avtat=0, i, j;
    cout<<"\nEnter total number of processes: ";
	cin>>n;

	Process P[100];
	
	for(i=0; i<n; i++)
        P[i].P_ID = i+1;

	cout<<"\nEnter Process Burst Time:\n";
	
    for (i=0;i<n;i++) {
		cout<<"P["<<i+1<<"]:";
		cin>>P[i].bt;
    }
	P[0].wt =0;        	//waiting time for first process is 0
	
    //Calculating waiting time
	for (i=1;i<n;i++) {
		P[i].wt = 0;
		for (j=0;j<i;j++)
		            P[i].wt += P[j].bt;
        
	}
	
    cout<<"\nProcess \tBurstTime\tWaitingTime\tTurnAroundTime";
    
	//Calculating turnaround time
	for (i=0;i<n;i++) {
		P[i].tat = P[i].bt + P[i].wt;
		avwt += P[i].wt;
		avtat += P[i].tat;
		cout<<"\nP["<<P[i].P_ID<<"]"<<"\t\t"<<P[i].bt<<"\t\t"<<P[i].wt<<" \t\t"<<P[i].tat;
	}
	avwt/=i;
	avtat/=i;
	cout<<"\n\nAverage Waiting Time:  "<<avwt;
	cout<<"\nAverage Turnaround Time:  "<<avtat;
	cout<<"\n\n";
	Gantt(P,n);
}



//SHORTEST JOB FIRST SCHEDULING ALGORITHM
void SJF(){
    int n,bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j;
    cout<<"\nEnter total number of processes: ";
	cin>>n;
	
	
}



//PRIORITY SCHEDULING ALGORITHM
void Priority(){
    int pr[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
    Process P[100];
	cout<<"\nEnter Total Number of Process:";
	cin>>n;
	for(i=0; i<n; i++)
        P[i].P_ID = i+1;
    
	cout<<"\nEnter Burst Time and Priority(lower the number higher the priority)\n";
	for (i=0;i<n;i++) {
		cout<<"\nP["<<i+1<<"]\n";
		cout<<"Burst Time: ";
		cin>>P[i].bt;
		cout<<"Priority:";
		cin>>pr[i];
		P[i].P_ID=i+1;         
	}

	//Sorting burst time, priority and process number in ascending order using selection sort
	for (i=0;i<n;i++) {
		pos=i;
		for (j=i+1;j<n;j++) {
			if(pr[j]<pr[pos] && P[j].bt > P[pos].bt)
			                pos=j;
		    }

		temp=pr[i];                    //Sorting the process using its priority
		pr[i]=pr[pos];
		pr[pos]=temp;

		temp = P[i].bt;                //PLacing the burst time of the process
		P[i].bt = P[pos].bt;
		P[pos].bt = temp;

		temp=P[i].P_ID;                //PLacing the process at the required position
		P[i].P_ID = P[pos].P_ID;
		P[pos].P_ID = temp;
	}

	P[0].wt=0;   	//Waiting time for first process is zero
	

	for (i=1;i<n;i++) {
		P[i].wt = 0;
		for (j=0;j<i;j++)
		            P[i].wt += P[j].bt;
		total+= P[i].wt;
	}
	avg_wt=total/n;
	
	total=0;
	cout<<"\nProcess \tPriority       \tBurst Time     \tWaiting Time    \tTurnAround Time";
	for (i=0;i<n;i++) {
		P[i].tat = P[i].bt + P[i].wt;
		total+= P[i].tat;
		cout<<"\nP["<<P[i].P_ID<<"]\t\t  "<<pr[i]<<"\t\t"<<P[i].bt<<"\t\t    "<<P[i].wt<<"\t\t\t"<<P[i].tat;
	}
	avg_tat=total/n;
	
	cout<<"\n\nAverage Waiting Time="<<avg_wt;
	cout<<"\nAverage Turnaround Time="<<avg_tat<<"\n\n";
	Gantt(P,n);
}



//ROUND ROBIN SCHEDULING ALGORITHM
void RoundRobin(){

}


//Gantt Chart for all scheduling algorithms
void Gantt(Process P[], int n){
    int i, j;
    cout<<"\n\n-----------GANTT CHART--------------\n\n";
	cout<<" ";
	// print top bar
    for(i=0; i<n; i++) {
        for(j=0; j<=P[i].bt; j++) 
			cout<<"__";
        cout<<" ";
    	}
    cout<<"\n\n|";
 
    // Printing process id in the middle
    for(i=0; i<n; i++) {
        for(j=0; j<(P[i].bt - 1); j++) 	
			cout<<" ";
        cout<<"P["<<P[i].P_ID<<"]";
        for(j=0; j<(P[i].bt - 1); j++) 
			cout<<" ";
        cout<<"|";
    }
    cout<<"\n ";
    // Printing bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<=P[i].bt; j++) 
			cout<<"__";
        cout<<" ";
    }
    cout<<"\n"<<endl;
 
    // Printing the timeline of the process
    cout<<"0";
    for(i=0; i<n; i++) {
        for(j=0; j<=P[i].bt; j++) 
			cout<<"  ";
        if(P[i].tat > 9) 
			cout<<"\b\b";           // backspace : remove 1 space
        cout<<P[i].tat<<" ";
 	}
    cout<<"\n";
 
}
