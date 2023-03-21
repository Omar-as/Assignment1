# Comp304 - Operating Systems Assignment 1

## Dependencies:
- gcc 12.2.0

## Problem 1 :  Forks
In Unix/Linux, new processes can be created using the **fork()** system call. Calling **fork()** creates a copy of calling process and the new process starts executing immediately. After the **fork()** call, both parent and child processes start executing the same code.

### Part (a)
Write a C program that calls **fork()** n times consecutively where n is an integer parameter
provided as a command-line argument. Then each of the forked processes prints its ID, its
parent’s ID and its level in the process tree (The level of the main process is 0). **Run the
program for** n **equal to** 2, 3, and 5.

To run the code
```
gcc p1a.c -o main
./main n
```
- n = the nuber of children you would like to fork.

### Part (b)
Write a C program that forks a child process that immediately becomes a zombie process.
This zombie process must remain in the system for at least 5 seconds.
- Use the **sleep()** call for the time requirement
- Run the program in the background (using the & feature of your shell) and then run
the command ps − l to see if the child has become a zombie.
- Kill the parent with the kill command if you create too many zombie processes.

To run the code
```
gcc p1a.c -o main
./main | ps -l
```
The zombie process would show up as Z

## Problem 2 :  Pipes
Rather than duplicating the parent process, we can create a new process for the children to
execute using the **exec()** family of calls, which the parent can monitor. In this part you will
write a simple benchmarking program that measures how long programs take to execute.
- Write a C program that forks **n** child processes simultaneously, each executing a given
**command name** concurrently. Both **n** and **command name** are taken from commandline arguments, as shown below. Note that you may need to fork again inside the
children.
- The child processes should record the starting and finishing times of the given command
and send an estimate of the time it took to execute back to the parent process using
pipes. The parent then prints the execution times it receives from the children as they
are sent. You can use the **gettimeofday()** library call for this purpose.
- The child processes should not print anything to stdout or stderr. You can forward
those streams to `/dev/null` to suppress the output.
- After all children finish executing, the parent should print the maximum and minimum
times of all runs, as well the average time of all children.

To run the code
```
gcc p1a.c -o main
./main n command
```
- n = number of children forked
- command = command you want the children to run

Example:
```
./main 5 ls -la
```

## Problem 3 :  Shared Memory

In this part you will be implementing a program to search for a given number in a sequence
using multiple processes.
- The parent process reads a newline-delimited sequence of at most 1000 numbers from
stdin and parses them into an array.
- The parent creates **n** child processes that go through disjoint portions of the array to
search a given number **x**. Both **n** and **x** are provided as command-line arguments. For
example, the program should search for the number 98 with 3 children if invoked as
follows: `./search 98 3`
- Each forked child must sequentially search for **x** in their portion of the array, and print
the index of the element and exit with the return code **0** if found. If a child does not
find the given number in its portion, it should instead exit with the return code **1**.
- When any child exits with a success the parent should kill other running children and
terminate.
- The last child might have to go through more numbers if the sequence length isn’t
perfectly divisible by the number of children. Make sure to handle edge cases!
You can use the **shuf** command from coreutils to feed random numeric sequences to your
program as follows:
```
 shuf -i 1-1000 | ./search 98 3
```
To run the code
```
gcc p1a.c -o main
shuf -i j-k | ./main x n
```
- j = starting number
- k = end number. No more than 1000
- x = the number we want to find the index for
- n = the number of children forked you want

Uncommenting lines 42-45 will print out the array with all the numbers and their indeces.
