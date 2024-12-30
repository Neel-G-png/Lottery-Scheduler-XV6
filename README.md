# XV6 Lottery Scheduler

This project enhances the XV6 operating system by implementing a lottery scheduler and introducing several custom system calls. This README provides an overview of the changes, commands, and files associated with the project.

## Features

### Lottery Scheduler

This scheduler allocates CPU time to processes based on a lottery system, allowing for a more dynamic and fair distribution of resources.

### Custom System Calls

We have implemented the following custom system calls to support the lottery scheduler:

1. `SYS_nice`: Adjusts the priority (and hence, the ticket count) of a process.
2. `SYS_ps`: Retrieves information about running processes.
3. `SYS_resetticks`: Resets the ticks for the process specified.
4. `SYS_killifticks`: Kills a process after the process reaches a specific number of ticks.
5. `SYS_random`: Provides a system call to generate random numbers between two values.

## Commands

You can build and test the project using the following commands:
##### Specifying the Scheduler
- `make SCHEDPOLICY=LOTTERY`: Build XV6 with the lottery scheduler.
- `make clean`: Before building with different scheduler policy
- `make SCHEDPOLICY=DEFAULT`: Build XV6 with the default scheduler (Round Robin).
- `make`: Build XV6 with the default scheduler.
##### Starting xv6
- `make qemu-nox`: Enters xv6 terminal.
##### Inside the terminal
- `nice_test`: Observe changes in process priorities and explore edge cases.
- `lottery_test`: Run multiple tests to assess the lottery scheduler's performance.
- `randTest`: Test the random number generation system call.

## Files

### Modified Files
- `syscall.h`
- `syscall.c`
- `sysproc.c`
- `usys.S`
- `defs.h`
- `user.h`
- `proc.h`
- `proc.c`
- `Makefile`

### New Files
- `lottery_test.c`
- `nice.c`
- `nice_test.c`
- `scheduler_utils.c`
- `randTest.c`

## Usage

1. Build XV6 with your preferred scheduler using one of the provided `make` commands.
2. Execute tests such as `nice_test`, `lottery_test`, and `randTest` to explore the lottery scheduler's functionality and the custom system calls.
3. Analyze the source code in the modified and new files to understand the implementation details.