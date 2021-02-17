#include "eventSim.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

//Priority Queue
//used tutorials point as reference
//https://www.tutorialspoint.com/cplusplus-program-to-implement-priority-queue

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
            }
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






int main(){

    priorityQueue pq;

    pq.push("job1",1,0);
    pq.push("jobN",5,500);
    pq.printQ();



            return 0;


}//end of main