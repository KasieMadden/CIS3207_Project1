#define _CRT_SECURE_NO_WARNINGS
#include "eventSim.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <string>
using namespace std;

//Declaring global variables

//https://www.geeksforgeeks.org/enumerated-types-or-enums-in-c/
enum job{
    sJob,
    eJob,
    sCPU,
    eCPU,
    sDisk1,
    eDisk1,
    sDisk2,
    eDisk2,
    sNetwork,
    eNetwork,
    eSim
};


//boolean for component variables
bool    CPUbusy = false,
        disk1Busy = false,
        disk2Busy = false,
        networkBusy = false;

// Added compare operator for sorting priority queue
//https://stackoverflow.com/questions/15601973/stl-priority-queue-of-c-with-struct
//structure to hold the events
struct node {
    int jobID,
        time,
        type;

// Added compare operator for sorting priority queue
    bool operator<(const node& o) const
    {
        return time > o.time;
    }
};

//using included priority queue queue
//using included FIFO queue
//used cplusplus point as reference
//https://www.cplusplus.com/reference/queue/queue/queue/
//https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
//http://www.cplusplus.com/reference/queue/priority_queue/


std::priority_queue<node> jobQueue;
std::queue<node> CPUqueue;
std::queue<node> disk1Queue;
std::queue<node> disk2Queue;
std::queue<node> networkQueue;

//prototypes for programs functions
int randomNumber(int min, int max);
bool probabilityCalc(int probability);
void startJob(int ARRIVE_MIN, int ARRIVE_MAX);
int startCPU(int CPU_MIN, int CPU_MAX);
int disk1Start(int DISK1_MIN, int DISK1_MAX);
int disk2Start(int DISK2_MIN, int DISK2_MAX);
int networkStart(int NETWORK_MIN, int NETWORK_MAX);
void disk1End();
void disk2End();
void networkEnd();
void endCPU(int QUIT_PROB, int NETWORK_PROB);
void endJob();
void endSim();

string logmessage[12] = { "JOB INITIATED",
                          "JOB TERMINATED" ,
                          "CPU ARRIVAL" ,
                          "CPU FINISHED" ,
                          "DISK1 ARRIVAL" ,
                          "DISK1 FINISHED",
                          "DISK2 ARRIVAL" ,
                          "DISK2 FINISHED",
                          "NETWORK ARRIVAL" ,
                          "NETWORK FINISHED",
                          "SIMULATION ENDED",
                          "SIMULATION STARTED" };


int main() {


    // read in config file
    ifstream rFile;
    rFile.open("config.txt");

    //write to log file
    ofstream wFile;
    wFile.open("log.txt");


// Get values from file - Labels are in arrayF and Values are in arrayG
    string line;
    string arrayF[15];
    string arrayG[15];
    int arrayV[15];


 // Read values from file and split into two arrays
    for (int j = 0; j < 15; j++) {
        getline(rFile, line);

        stringstream ss;
        ss << line;

        ss >> arrayF[j] >> arrayG[j];
        arrayV[j] = std::stoi(arrayG[j]);
/**
        // Print output for debugging and send to Log File
        cout << arrayF[j] << " " << arrayG[j] << " " << arrayV[j] << endl;
        wFile << arrayF[j] << " " << arrayG[j] << " " << endl;
**/
    }//end of for
    rFile.close(); // close config.txt
    srand(arrayV[0]);
    int currentT = arrayV[1];//INIT_TIME


    //structure to hold the events
    //struct node {jobID, time, type};
    int jobID = 0;
    int lastjobID=1000;
    int fin_time = arrayV[2];


    //Start Simulation
    // Log Start of Sim
    wFile << "AT TIME " << currentT << " " << "JOB " << jobID << " " << logmessage[11] << " " << endl;
    cout << "AT TIME " << currentT << " " << "JOB " << jobID << " " << logmessage[11] << " " << endl;

    //creating a first and last job
    node first = { jobID, 0, sJob}; // First Job
    node last = { lastjobID, fin_time, eSim}; // Sim Ends when MAX_TIME is pop'ed

    //push the pushing first and last job
    jobQueue.push(first);
    jobQueue.push(last);



    //start of the while loop that will run though cases for the job
    while (!jobQueue.empty() && currentT < fin_time) {

        node currentJ = jobQueue.top();
        jobQueue.pop();

        std::string s = std::to_string(currentJ.time);


        switch (currentJ.type) {
        case sJob:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sJob] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sJob] << endl;
            startJob(arrayV[3], arrayV[4]);
            break;

        case sCPU:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sCPU] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sCPU] << endl;
            startCPU(arrayV[7],arrayV[8]);

            break;

        case eCPU:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eCPU] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eCPU] << endl;
            endCPU(arrayV[5], arrayV[6]);

            break;

        case sDisk1:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sDisk1] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sDisk1] << endl;
            disk1Start(arrayV[9], arrayV[10]);

            break;

        case eDisk1:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eDisk1] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eDisk1] << endl;
            disk1End();


            break;

        case sDisk2:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sDisk2] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sDisk2] << endl;
            disk2Start(arrayV[11], arrayV[12]);

            break;

        case eDisk2:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eDisk2] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eDisk2] << endl;
            disk2End();


            break;

        case sNetwork:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sNetwork] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[sNetwork] << endl;
            networkStart(arrayV[13],arrayV[14]);

            break;

        case eNetwork:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eNetwork] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eNetwork] << endl;
            networkEnd();

            break;

        case eJob:
            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eJob] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eJob] << endl;
            endJob();
            break;

        case eSim:

            wFile << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eSim] << endl;
            cout << "AT TIME " << s << " " << "JOB " << currentJ.jobID << " " << logmessage[eSim] << endl;

            endSim();
            break;


        }//end of switch

    } // end of while

    wFile.close(); // Close log file

}//end of main


//random number generator
int randomNumber(int min, int max) {
    int number;
    number = rand() % min + max;
    return number;
}//end of randomNum()

//probability calculator 1-100 all else is false
bool probabilityCalc(int probability) {
    int temp;
    temp = randomNumber(0, 100);
    if (temp <= probability) {
        return true;
    }//end of if
    else {
        return false;
    }
    //  }//end of else

}//end of probCalc()


//creating a new job
//if cpu is not busy will job to cpu
// if cup is busy will push to FIFO
void startJob(int ARRIVE_MIN, int ARRIVE_MAX) {
    node tempN =jobQueue.top();
    int tempI = jobQueue.top().jobID;
    int timeR = randomNumber(ARRIVE_MIN, ARRIVE_MAX);
    jobQueue.pop();

    //if CPU is not busy will push job there
    if (CPUbusy == false && CPUqueue.empty()) {

        node JobN = {(timeR + tempN.time), sCPU, ++tempI};
        jobQueue.push(JobN);
    }//end of if
    else if (CPUbusy == true && !CPUqueue.empty()) {

        CPUqueue.push(tempN);
    }//end of else

    node jobA = { (timeR + tempN.time), sJob, tempI};
    jobQueue.push(jobA);
}//end of job tart

//if the queues is empty will enter the CPU
//if it is full is
//When CPU starts the event
int startCPU(int CPU_MIN, int CPU_MAX) {
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

    node jobA = { (timeR + tempN.time), eDisk1, tempN.jobID };
    jobQueue.push(jobA);
    return (timeR + tempN.time);
}//end of disk1Start

void disk1End() {
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk1Busy = false;

    if (CPUbusy && CPUqueue.size() == 0) {
        node jobA = { tempN.time, sCPU, tempN.jobID };
        jobQueue.push(jobA);
    }//end of if
    else if (CPUbusy == true || CPUqueue.size() != 0) {
        CPUqueue.push(tempN);
    }//end of else if

    if (disk1Queue.size() != 0) {
        node job = disk2Queue.front();
        disk1Queue.pop();
        node jobD1 = { job.time, sDisk1, job.jobID };
        jobQueue.push(jobD1);

    }//end of if
}//end of disk1end

int disk2Start(int DISK2_MIN, int DISK2_MAX) {
    int timeR = randomNumber(DISK2_MIN, DISK2_MAX);
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk2Busy = true;

    node jobA = { (timeR + tempN.time), eDisk2, tempN.jobID };
    jobQueue.push(jobA);
    return (timeR + tempN.time);

}//end of disk2Start

void disk2End() {
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk2Busy = false;

    if (CPUbusy && CPUqueue.size() == 0) {
        node jobA = { tempN.time, sCPU, tempN.jobID };
        jobQueue.push(jobA);
    }//end of if
    else if (CPUbusy == true || CPUqueue.size() != 0) {
        CPUqueue.push(tempN);
    }//end of else if

    if (disk1Queue.size() != 0) {
        node job = disk2Queue.front();
        disk2Queue.pop();
        node jobD2 = { job.time, sDisk2, job.jobID };
        jobQueue.push(jobD2);
    }
}//end of disk2end

int networkStart(int NETWORK_MIN, int NETWORK_MAX) {
    int timeR = randomNumber(NETWORK_MIN, NETWORK_MAX);
    node tempN = jobQueue.top();
    jobQueue.pop();
    disk2Busy = true;

    node jobA = { (timeR + tempN.time), eNetwork, tempN.jobID };
    jobQueue.push(jobA);
    return (timeR + tempN.time);


}//end of networkstart()

void networkEnd() {
    node tempN = jobQueue.top();
    jobQueue.pop();
    networkBusy = false;

    if (CPUbusy && CPUqueue.size() == 0) {
        node jobA = { tempN.time, sCPU, tempN.jobID };
        jobQueue.push(jobA);
    }//end of if
    else if (CPUbusy == true || CPUqueue.size() != 0) {
        CPUqueue.push(tempN);
    }//end of else if

    if (networkQueue.size() != 0) {
        node job = networkQueue.front();
        networkQueue.pop();
        node jobN = { job.time, sDisk2, job.jobID };
        jobQueue.push(jobN);
    }//end of if
}//end of networkEnd

void endCPU(int QUIT_PROB, int NETWORK_PROB) {
    node tempN = jobQueue.top();
    jobQueue.pop();
    CPUbusy = false;

    if (probabilityCalc(NETWORK_PROB)) {
        if (networkBusy && networkQueue.size() == 0) {
            node job = { tempN.jobID, sNetwork, tempN.time };
            jobQueue.push(job);
        }//end of if net
    }//end of netprob

    else if (probabilityCalc(QUIT_PROB)) {
        node job = { tempN.jobID, eJob, tempN.time };
        jobQueue.push(job);
    }//end of qiut prob

    else if (disk1Busy && disk1Queue.size() == 0) {
        node job = { tempN.jobID, sDisk1, tempN.time };
        jobQueue.push(job);
    }//end of ifd1

    else if (disk2Busy && disk2Queue.size() == 0) {
        node job = { tempN.jobID, sDisk2, tempN.time };
        jobQueue.push(job);
    }//end of if d2
    else if (disk1Queue.size() < disk2Queue.size()) {
        disk2Queue.push(tempN);
    }// end of if()

    else if (disk1Queue.size() > disk2Queue.size()) {
        disk2Queue.push(tempN);
    }// end of if()d1q


    if (CPUqueue.size() != 0) {
        node job = CPUqueue.front();
        CPUqueue.pop();
        node jobC = { job.time, sCPU, job.jobID };
        jobQueue.push(jobC);
    }//end of if cpuque
}//end of CPU

void endJob() {
    jobQueue.pop();
}//end of endjob

void endSim() {
    exit(0);
}//end of endsim

