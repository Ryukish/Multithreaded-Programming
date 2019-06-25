# Multithreaded-Programming
This program simulates a database that has 10 positions for threads to run on concurrently. There are 2 groups of users(1, 2), in the input we specific which has priority. For the group that is not the priority, they are schuduled after the priority group is finished. Each user comes with a position, a wait time and a sleep time. Wait time is the time the user waits before requesting a position. The sleep time is the requested amount of time for a position.

```
1 // Group with Priority

1 3 0 5 // Group - Position Requested - Wait Time - Sleep Time

2 3 2 5

1 3 1 5

2 1 3 1
```
Once we have read in and queued all of the threads, we start creating them. We use Mutex Seamphores to control the critical section. After said position is done, we release the position in the array and unlock the critical section using Mutex Seaphores.
