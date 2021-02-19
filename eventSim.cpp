#include "eventSim.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <string.h>


using namespace std;

//Declaring global variables

//https://www.geeksforgeeks.org/enumerated-types-or-enums-in-c/
enum job{ sJob,
          eJob,
          sCPU,
          eCPU,
          sDisk1,
          eDisk1,
          sDisk2,
          eDisk2,
          sNetwork,
          eNetwork};


//boolean for component variables
bool CPUbusy = false;
bool disk1Busy= false;
bool disk2Busy= false;
bool networkBusy= false;



//structure to hold the events
struct node{
    int time;
    int type;
    int jobID;
};

//using included priority queue queue
//using included FIFO queue
//used cplusplus point as reference
//https://www.cplusplus.com/reference/queue/queue/queue/
//https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
//http://www.cplusplus.com/reference/queue/priority_queue/
std::priority_queue<node>jobQueue;
std::queue<node>CPUqueue;
std::queue<node>disk1Queue;
std::queue<node>disk2Queue;
std::queue<node>networkQueue;



//random number generator
int randomNumber(int min, int max){
    int number;
    number = rand()% min+max;
    return number;
}//end of randomNum()

//probability calculator 1-100 all else is false
bool probabilityCalc(int probability ){
       int temp;
       temp = randomNumber(0,100);
       if(temp <= probability ){
           return true;
       }//end of if
       else{
           return false;
       }
  //  }//end of else

}//end of probCalc()


//creating a new job
//if cpu is not busy will job to cpu
// if cup is busy will push to FIFO
void startJob(int ARRIVE_MIN, int ARRIVE_MAX){
    int timeR = randomNumber(ARRIVE_MIN, ARRIVE_MAX);


    node tempN = jobQueue.top();
    int tempI = jobQueue.top().jobID;
    jobQueue.pop();

 //if CPU is not busy will push job there
    if(CPUbusy == false && CPUqueue.empty() ){

        node JobN={(timeR+tempN.time),sCPU, tempI};
        jobQueue.push(JobN);
    }//end of if
    else if(CPUbusy == true && !CPUqueue.empty() ){

        CPUqueue.push(tempN);
    }//end of else

    node jobA = {(timeR + tempN.time), sJob, ++tempI};
    jobQueue.push(jobA);
}//end of job tart


//When CPU starts the event
int startCPU(int CPU_MIN, int CPU_MAX){
    int timeR = randomNumber(CPU_MIN, CPU_MAX);
    node tempN = jobQueue.top();
    jobQueue.pop();
    CPUbusy = true;

    node jobA = {(timeR + tempN.time), eCPU, tempN.jobID};
    jobQueue.push(jobA);
    return (timeR + tempN.time);

}//end of startCPU

int disk1Start(int DISK1_MIN, int DISK1_MAX) {
    int timeR = randomNumber(DISK1_MIN, DISK1_MAX);
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk1Busy = true;

    node jobA = {(timeR + tempN.time), eDisk1, tempN.jobID};
    jobQueue.push(jobA);
    return (timeR + tempN.time);
}//end of disk1Start

void disk1End(){
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk1Busy = false;

    if(CPUbusy && CPUqueue.size() ==0){
        node jobA = {tempN.time, sCPU, tempN.jobID};
        jobQueue.push(jobA);
    }//end of if
    else if(CPUbusy == true ||CPUqueue.size() !=0){
        CPUqueue.push(tempN);
    }//end of else if

    if (disk1Queue.size() != 0){
        node job = disk2Queue.front();
        disk1Queue.pop();
        node jobD1 = {job.time, sDisk1, job.jobID};
        jobQueue.push(jobD1);

    }//end of if
}//end of disk1end


int disk2Start(int DISK2_MIN, int DISK2_MAX){
    int timeR = randomNumber(DISK2_MIN, DISK2_MAX);
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk2Busy = true;

    node jobA = {(timeR + tempN.time), eDisk2, tempN.jobID};
    jobQueue.push(jobA);
    return (timeR + tempN.time);

}//end of disk2Start

void disk2End(){
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk2Busy = false;

    if(CPUbusy && CPUqueue.size() ==0){
        node jobA = {tempN.time, sCPU, tempN.jobID};
        jobQueue.push(jobA);
    }//end of if
    else if(CPUbusy == true ||CPUqueue.size() !=0){
        CPUqueue.push(tempN);
    }//end of else if

    if (disk1Queue.size() != 0) {
        node job = disk2Queue.front();
        disk2Queue.pop();
        node jobD2 = {job.time, sDisk2, job.jobID};
        jobQueue.push(jobD2);
    }
}//end of disk2end


int networkStart(int NETWORK_MIN, int NETWORK_MAX){
    int timeR = randomNumber(NETWORK_MIN, NETWORK_MAX);
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk2Busy = true;

    node jobA = {(timeR + tempN.time), eNetwork, tempN.jobID};
    jobQueue.push(jobA);
    return (timeR + tempN.time);


}//end of networkstart()

void networkEnd(){
    node tempN = jobQueue.top();
    jobQueue.pop();
    networkBusy = false;

    if(CPUbusy && CPUqueue.size() ==0){
        node jobA = {tempN.time, sCPU, tempN.jobID};
        jobQueue.push(jobA);
    }//end of if
    else if(CPUbusy == true ||CPUqueue.size() !=0){
        CPUqueue.push(tempN);
    }//end of else if

    if (networkQueue.size() != 0) {
        node job = networkQueue.front();
        networkQueue.pop();
        node jobN = {job.time, sDisk2, job.jobID};
        jobQueue.push(jobN);
    }//end of if
}//end of networkEnd



void endCPU(int QUIT_PROB, int NETWORK_PROB){
    node tempN = jobQueue.top();
    jobQueue.pop();
    CPUbusy = false;


    if(disk1Busy && disk1Queue.size() ==0){
        node job ={tempN.jobID, sDisk1, tempN.time};
        jobQueue.push(job);
    }//end of ifd1

    else if(disk2Busy && disk2Queue.size() ==0){
        node job ={ tempN.jobID, sDisk2, tempN.time};
        jobQueue.push(job);
    }//end of if d2
    else if(disk1Queue.size() < disk2Queue.size()){
        disk2Queue.push(tempN);
    }// end of if()

    else if(disk1Queue.size() > disk2Queue.size()){
        disk2Queue.push(tempN);
    }// end of if()d1q

    else if(probabilityCalc(NETWORK_PROB)) {
        if (networkBusy && networkQueue.size() == 0) {
            node job = {tempN.jobID, sNetwork, tempN.time};
            jobQueue.push(job);
        }//end of if net
    }//end of netprob

    else if(probabilityCalc(QUIT_PROB)){
        node job ={tempN.jobID, eJob, tempN.time};
        jobQueue.push(job);
    }//end of qiut prob

    if (CPUqueue.size() != 0) {
        node job = CPUqueue.front();
        CPUqueue.pop();
        node jobC = {job.time, sDisk2, job.jobID};
        jobQueue.push(jobC);
    }//end of if cpuque
}//end of CPU


int main(){

}//end of main