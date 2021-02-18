#include "eventSim.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <queue>

//#include <string.h>
//#include <assert.h>
using namespace std;

//Declaring global variables
//boolean for component variables
int currentT;
int count = 0;
bool CPUbusy = false;
bool disk1Busy= false;
bool disk2Busy= false;
bool networkBusy= false;


//Priority Queue
//used tutorials point as reference
//https://www.tutorialspoint.com/cplusplus-program-to-implement-priority-queue

//structure to hold the events
struct node{
    int time;
    int type;
    string jobID;
    struct node *tail;
};


//using included FIFO queue
//used cplusplus point as reference
//https://www.cplusplus.com/reference/queue/queue/queue/
std::priority_queue<node>jobQueue;
std::queue<node>CPUqueue;
std::queue<node>disk1Queue;
std::queue<node>disk2Queue;
std::queue<node>networkQueue;


/**priorityQueue
class priorityQueue{
    //Private access method for head pointer
    private:
    node *head;

    //Public access method
    public:
    priorityQueue(){
        //initialized null
        head = NULL;
    }//end of priorityQueue()

    //function to push into queue
    //similar to the push function used in a stack
    void push(string tID,int tType, int tTime){
        node *temp;
        node *temp2;

        temp = new node;
        temp -> jobID = tID;
        temp -> type = tType;
        temp -> time = tTime;

        if(head == NULL || tTime < head -> time){
            temp -> tail = head;
            head = temp;
        }//end of if
        else{
            temp2 = head;
            while(temp2 -> tail != NULL && temp2 ->tail->time <= tTime ) {
                temp2 = temp2->tail;
            }//end of while
            temp -> tail = temp2 -> tail;
            temp2 -> tail = temp;

        }//end of else
    }//end of push

        void empty(){
            node *temp;
            if(head == NULL){
              cout<< "Queue Underflow\n";
            }//end of if
            else{
                temp = head;
                cout <<"Deleted item is: "<< temp -> type<<endl;
                head = head -> tail;
                free(temp);
            }//end of else
        }//end of empty()

        void printQ(){
        node *pointer;
        pointer = head;

            if(head == NULL){
                cout<<"Queue is empty\n";

            }//end of if
            else{
                cout<<"Queue is :\n";
                cout<<"Priority Item\n";
                while(pointer != NULL){
                    cout<<pointer->time<<" "<<pointer->jobID<<endl;
                    pointer = pointer ->tail;
                }//end of while

            }//end of else

        }//end of printQ

};// end of priorityQueue CLASS**/


//random number generator
int randomNumber(int min, int max){
    int number;
    number = (rand() % (min + max + 1) + min) ;
    return number;
}
//void config()
/**

//function to read  in and parse the config.txt file
//used geeksforgeeks point as reference
//https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
//https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
void config(){

    int cfig[15];
    int i = 0;
    char buff[15];
    char fName[] ="config.txt";

    //open file
    ifstream file;
    file.open(fName);

    file >> buff;

    //while file
    while(file.good()){
        char* token = strtok(buff, ": ");

        cfig[i] = atof(token);

        file >> buff;
        i++;
    }//end of while

file.close();
}//end of config()
**/



//probability calculator 1-100 all else is false
bool probabilityCalc(int probability ){


    if(probability  < 0 || probability  > 100){
        cout<<"Out of range"<<endl;
        return 1;
    }//end if
    else{
       int temp;
       temp = randomNumber(0,100);
       if(temp <= probability ){
           return true;
       }//end of if
       else{
           return false;
       }
    }//end of else

}//end of probCalc()



//creating a new job
//if cpu is not busy will job to cpu
// if cup is busy will push to FIFO
void startJob(int ARRIVE_MIN, int ARRIVE_MAX){
    node tempN = jobQueue.top();
    string tempS = jobQueue.top().jobID;
    jobQueue.pop();

    //if CPU is not busy will push job there
    if(CPUbusy != true && CPUqueue.empty() ){
        int timeR = randomNumber(ARRIVE_MIN, ARRIVE_MAX);
        currentT = (currentT + timeR);
        jobQueue.push(tempN);
    }//end of if
    else if(CPUbusy == true && !CPUqueue.empty() ){

        CPUqueue.push(tempN);

    }//end of else

    jobQueue.push(tempN);
    return;
}//end of job start


//When CPU starts the event
int startCPU(int CPU_MIN, int CPU_MAX){
   node tempN = jobQueue.top();
   jobQueue.pop();

    CPUbusy = true;
    int timeR = randomNumber(CPU_MIN, CPU_MAX);
    currentT = (currentT + timeR);
    jobQueue.push(tempN);
    return currentT;

}//end of startCPU




int disk1Start(int DISK1_MIN, int DISK1_MAX) {
    node tempN = jobQueue.top();
    jobQueue.pop();

    disk1Busy = true;
    int timeR = randomNumber(DISK1_MIN, DISK1_MAX);
    int  currentT = (currentT + timeR);
    jobQueue.push(tempN);
    return currentT;

}//end of disk1Start

void disk1End(){
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk1Busy = false;

    if(disk1Busy == true || !CPUqueue.empty()){
        CPUqueue.push(tempN);
    }//end of if
    else if(disk1Busy == false && CPUqueue.empty()){
        CPUqueue.push(tempN);
    }//end of elseif

    if(disk1Queue.empty()== false){
        node tempJob  =networkQueue.front();
        disk1Queue.pop();
        disk1Queue.push(tempJob);
    }//end of if
    return;

}


void disk2Start(int DISK2_MIN, int DISK2_MAX){
    node tempN = jobQueue.top();
    jobQueue.pop();

    disk2Busy = true;
    int timeR = randomNumber(DISK2_MIN, DISK2_MAX);
    int  currentT = (currentT + timeR);
    jobQueue.push(tempN);
    return;



}//end of disk2Start

void disk2End(){
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk2Busy = false;

    if(disk2Busy == true || !CPUqueue.empty()){
        CPUqueue.push(tempN);
    }//end of if
    else if(disk2Busy == false && CPUqueue.empty()){
        CPUqueue.push(tempN);
    }//end of elseif

    if(disk2Queue.empty()== false){
        node tempJob  =networkQueue.front();
        disk2Queue.pop();
        disk2Queue.push(tempJob);
    }//end of if
    return;



}//end of disk2end



int networkStart(int NETWORK_MIN, int NETWORK_MAX){

    node tempN = jobQueue.top();
    jobQueue.pop();

    networkBusy = true;
    int timeR = randomNumber(NETWORK_MIN, NETWORK_MAX);
    int  currentT = (currentT + timeR);
    jobQueue.push(tempN);
    return currentT;


}

void networkEnd(){
    node tempN = jobQueue.top();
    jobQueue.pop();
    networkBusy = false;

    if(networkBusy == true || !CPUqueue.empty()){
        CPUqueue.push(tempN);
    }//end of if
    else if(networkBusy == false && CPUqueue.empty()){
        CPUqueue.push(tempN);
    }//end of elseif

    if(networkQueue.empty()== false){
        node tempJob  =networkQueue.front();
        networkQueue.pop();
        networkQueue.push(tempJob);
    }//end of if
    return;

}//end of networkEnd




void endCPU(int QUIT_PROB, int NETWORK_PROB){
    node tempN = jobQueue.top();
    jobQueue.pop();
    CPUbusy = false;



}


int main(){





}//end of main