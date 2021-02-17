#include "eventSim.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <queue>

//#include <string.h>
//#include <assert.h>


//Declaring global variables
int currentT;

using namespace std;

//Priority Queue
//used tutorials point as reference
//https://www.tutorialspoint.com/cplusplus-program-to-implement-priority-queue

//structure to hold the events
struct node{
    int time;//
    int type;
    string jobID;
    struct node *tail;
};


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

};// end of priorityQueue CLASS


//random number generator
int randomNumber(int min, int max){
    int number;
    number = (rand() % (min + max + 1) + min) ;
    return number;
}

/**

//function to read  in and parse the config.txt file
//used geeksforgeeks point as reference
//https://www.0.org/tokenizing-a-string-cpp/
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

 *//

//probability calculator 1-100 all else is false
bool probCalc(int probability ){
    if(probability  < 0 || probability  >100){
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

//boolean for component variables
bool CPUbusy;

//using included FIFO queue
//used cplusplus point as reference
//https://www.cplusplus.com/reference/queue/queue/queue/
std::priority_queue<node>jobQueue;
std::queue<node>CPUqueue;


void startJob(int min, int max){
    node tempN = jobQueue.top();
    string tempS = jobQueue.top().jobID;
    jobQueue.pop();

    //if CPU is not busy will push job there
    if(CPUbusy == false && CPUqueue.empty() ){
        int rand = randomNumber(min, max);
        currentT = (currentT + rand);
        jobQueue.push(tempN);
    }//end of if
    else if(CPUbusy == true && !CPUqueue.empty() ){
        CPUqueue.push();
    }//end of else


}//end of job start


void CPUstart(int min, int max){


}

void CPUend(){

}

void disk1Start(){

}

void disk1End(){

}


void disk2Start(){

}

void disk2End(){

}



void networkStart(){

}

void networkEnd(){

}

int main(){





/**
    priorityQueue pq;

    pq.push("job1",1,0);
    pq.push("jobN",5,500);
    pq.printQ();

    return 0;
**/

}//end of main