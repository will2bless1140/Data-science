#include <iostream>
#include <cstdlib>
#define LINE_MAX 1024
#include <fstream>
using namespace std;
struct node{
int arrival;
int burst;
int processno;
int completiontime;
int priority;
int turnAround;
int waiting;
node* next;
};
struct node* createNode(int processes, int arrivaltime, int bursttime, int prioritytime){
struct node* temp;
temp = (struct node*) malloc(sizeof(node));
temp->processno = processes;
temp->arrival = arrivaltime;
temp->burst = bursttime;
temp->priority = prioritytime;
temp->next = NULL;
return temp;
}
struct node* insertBack(struct node* header,int processes, int arrivaltime, int bursttime, int prioritytime){
struct node* temp = createNode(processes, arrivaltime,  bursttime, prioritytime);
struct node* headertemp;
if(header == NULL){
header = temp;
return header;
}
headertemp = header;
while(headertemp->next!=NULL)
headertemp = headertemp->next;
headertemp->next = temp;
return header;


}

int is_empty(struct node *header){
	if(header==NULL){
		return 1;
	
	}
	else 
	return 0;
}
struct node* sortArrival(struct node* header ){
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = temp->next;
	for(i=temp; i != NULL; i = i->next){
		for(j=i->next; j != NULL; j = j->next){
			if(((i->arrival)) > ((j->arrival))){
			
			struct node* temp2 = createNode(i->processno, i->arrival, i->burst, i->priority);
			i->processno = j->processno;
			i->arrival = j->arrival;
			i->burst = j->burst;
			i->priority = j->priority;
			i->waiting = j->waiting;
			i->turnAround = j->turnAround;
			i->completiontime = j->completiontime;
			
			j->processno = temp2->processno;
			j->arrival = temp2->arrival;
			j->burst = temp2->burst;
			j->priority = temp2->priority;
				j->waiting = temp2->waiting;
			j->turnAround = temp2->turnAround;
			j->completiontime = temp2->completiontime;
		}
		}
	}
	return temp;
}
struct node* sortProcess(struct node* header){
	struct node* temp = header;
	struct node* i = temp;
	struct node* j = temp->next;
	for(i=temp; i != NULL; i = i->next){
		for(j=i->next; j!=NULL; j=j->next){
			if(((i->processno)) > ((j->processno))){
					struct node* temp2 = createNode(i->processno, i->arrival, i->burst, i->priority);
			i->processno = j->processno;
			i->arrival = j->arrival;
			i->burst = j->burst;
			i->priority = j->priority;
				i->waiting = j->waiting;
			i->turnAround = j->turnAround;
			i->completiontime = j->completiontime;
			
			j->processno = temp2->processno;
			j->arrival = temp2->arrival;
			j->burst = temp2->burst;
			j->priority = temp2->priority;
				j->waiting = temp2->waiting;
			j->turnAround = temp2->turnAround;
			j->completiontime = temp2->completiontime;
			}
			
		}
	}
}

void display(struct node *header)

{
    if (header == NULL)
        cout << "List is empty" << endl;
        
    struct node* temp = header;

    while (temp != NULL)
    {
        
        cout<<temp->arrival<<"-->";
        
        
        temp=temp->next;
        
    }
    cout << endl;
}
struct node* FCFS(struct node* header){
	int processes = 0;
	float average; 
	int wat = 0;
	int currentTime = 0;
	header = sortArrival(header);
	
	struct node* temp = header;
	struct node* temp2 = header;
	while(!is_empty(temp)){
	 processes+=1;
	 
	 if(temp->arrival>currentTime){
	 	currentTime +=1;
	 	 continue;
	 }
	
	
	currentTime += temp->burst;
	temp->completiontime = currentTime;
	temp->turnAround = temp->completiontime - temp->arrival;
	temp->waiting = temp->turnAround - temp->burst;
	wat+= temp->waiting;
	if(temp->next!= NULL)
		temp=temp->next;
		
		else
		break;
}
average = (float)wat/processes;

sortProcess(header);
ofstream myFile("output1.txt");
myFile<<"\nScheduling method: \n";
while(!is_empty(temp2)){
	myFile <<"p"	<<temp2->processno<<":"<<temp2->waiting<<"ms\n";
	temp2 = temp2->next;
	//display(anothertemp);
}
myFile<<"average waiting time"<<average<<"ms\n";
myFile.close();
}
int main(){
	struct node* header = NULL;
	
		
		FILE *fp;
	char line[LINE_MAX];
	unsigned int num[3];
	int process = 1;

	if ((fp = fopen("input.txt", "r")) == NULL){
			cout <<"can't open file input.txt"<<endl;
			exit(1);
	}
			
	while (fgets(line, LINE_MAX, fp) != NULL) {
		process+=1;
		
		sscanf(line,"%d:%d:%d\n",&num[0],&num[1],&num[2]);
		header = insertBack(header, process, num[1], num[0], num[2]);
		
		
				
	}
	fclose(fp);
	int choice;
    while(1){
    	
    
    	cout<<"CPU SCHEDULER SIMULATOR"<<endl;
    	cout<<"1) Scheduling Method"<<endl;
    	cout<<"2) Preemptive Mode"<<endl;
    	cout<<"3) Non-Preemptive Mode"<<endl;
    	cout<<"4) Show Result"<<endl;
    	cout<<"5) End Program"<<endl;
    	cout<<"Option"<<endl;
    	
    	cin>>choice;
    	switch(choice){
    		case 1:
    			cout<<"1) First come, First Served Scheduling;"<<endl;
    			cout<<"2) Shortest-Job-First Scheduling:"<<endl;
    			cout<<"3) Priority Scheduling:"<<endl;
    			cout<<"4) Round-Robin Scheduling:"<<endl;
    			cout<<"option"<<endl;
    			 int option;
    			 cin>>option;
    			if(option == 1){
    				FCFS(header);
				}
    

        

}
}
	
return 0;
}
