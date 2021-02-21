Kasie E. Madden
Professor Fiore
TA: Blake Patterson
Operating Systems - CIS3207
Giorgio Discrete Event Simulator: written in C++.


This program's objective is to simulate the process of a computing system. This computing system
simulation is a simplified representation of an actual computing system but carries the same general
principles. Here, generic "jobs" are generated at intervals and added into the process. The jobs then flow
through the process until eventually terminated.

The job first enters the CPU where a process occurs. After the job leaves the CPU, a decision is then
made to either terminate the job or decide that it will need to be directed to a system component. These
system components will either be the network or to one of the disks. The system components will each
initialize a process for the job. Once the component process is finished, the job will be directed back to
the CPU for the entire sequence to be repeated. This is happening simultaneously as new jobs enter the
system.

Each process will be arbitrarily assigned a clock duration based on a predetermined duration range for
each new incoming job. The CPU and all the other system components each have separate queues
where the jobs will wait to be executed in the order that they are received. Specifically for the Disk
components, the job will be assigned to the disk with the shortest queue when possible.

A log is compiled with every event that the jobs will encounter. The events are listed in order of the
process clock at the time of the event and contains information that includes the job number and the
event type.

Some statistics will be generated at the end for reference. These items will include: the average and the
maximum size for each system component queue, the percentage utilization of each component over the
total system running time, and the job completion rate (throughput).

The specific information for the durations for each system component and flow through the system are
contained within the CONFIG.txt file. This file contains the specified interval for generating a new job and
the clock duration ranges for all the component processes and total system run time.

The total system run time is bounded by INIT_TIME for the start of the clock and FIN_TIME for the run
end. The new job arrival interval is determined by a randomly generated number within the range of
ARRIVE_MIN and ARRIVE_MAX. When the job enters the CPU, the CPU process clock duration is
determined by a randomly generated number within the range of CPU_MIN and CPU_MAX. Once the
CPU process is complete, a decision is made to terminate the job or continue to the system components
which is set by the value of QUIT_PROB. Once the decision to continue the job, a decision is made to
send to the network or to one of the disks which is set by the value of NET_PROB. If the job is sent to the
Network, the Network process clock duration is determined by a randomly generated number within the
range of NETWORK_MIN and NETWORK_MAX. If the decision to made to send to one of the disks
instead of the Network, the disk process clock duration is determined by a randomly generated number
within the range of DISK1_MIN and DISK1_MAX for Disk 1, or DISK2_MIN and DISK2_MAX for Disk 2.
The randomly generated clock durations will use a seed value set by the value of SEED.

The decision was made to program this simulation in C++ because of the included Queue libraries. I
thought this would simplify the program and result in cleaner code. Despite the amount of time I put into
this project, I continuously struggled with the implementation of managing such a complex process flow. It
seemed that every design cycle I would go through produced another function that I was missing and
needed to implement while every revision seemed to produce another set of errors that I had not yet seen.
I could only wish that I had more time to troubleshoot the project and to find a deeper understanding of
my shortcomings with coding in C++. I have unfortunately already exhausted my 3 free late days for this
project without producing a working version, but I am dedicated to continuing the process of revising and
troubleshooting this project until I can be successful.
