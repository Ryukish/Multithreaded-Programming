# Simulated Multithreaded Database 
This program simulates a database that has 10 positions for threads to run on concurrently. There are 2 groups of users(1, 2), in the input we specific which has priority. For the group that is not the priority, they are schuduled after the priority group is finished. Each user comes with a position, a wait time and a sleep time. Wait time is the time the user waits before requesting a position. The sleep time is the requested amount of time for a position.

```
1 // Group with Priority

1 3 0 5 // Group - Position Requested - Wait Time - Sleep Time

2 3 2 5

1 3 1 5

2 1 3 1
```
Once we have read in and queued all of the threads, we start creating them. We use Mutex Seamphores to control the critical section. After said position is done, we release the position in the array and unlock the critical section using Mutex Seaphores.

OutPut
```
User 1 from Group 1 arrives to the DBMS
User 1 is accessing the position 3 of the database for 5 second(s)
User 2 from Group 2 arrives to the DBMS
User 2 is waiting due to its group
User 3 from Group 1 arrives to the DBMS
User 3 is waiting: position 3 of the databse is being used by user 1
User 1 finished its execution
User 3 is accessing the position 3 of the database for 5 second(s)
User 4 from Group 2 arrives to the DBMS
User 4 is waiting due to its group
User 3 finished its execution

All users from Group 1 finished their execution
The userrs from Group 2 start their execution

User 2 is accessing the position 3 of the database for 5 second(s)
User 4 is accessing the position 1 of the database for 1 second(s)
User 4 finished its execution
User 2 finished its execution

Total Requests:
         Group 1: 2
         Group 2: 2

Requests that waited:
         Due to its  group: 2
         Due to a locked position: 1
```
