# philosophers
This is a small C project that implements a solution to the classic concurrency problem "The Dining Philosophers" using POSIX threads (pthreads) and mutexes.

## Overview

The program simulates a set of philosophers that alternate between thinking, eating and sleeping. To eat, a philosopher needs to pick up two forks (represented by mutexes). The goal is to coordinate the philosophers so that the system avoids deadlock and correctly detects when a philosopher dies (fails to eat within a time limit). The simulation also supports an optional stop condition: stop after each philosopher has eaten a specified number of times.

This repository contains a student-style implementation used for learning concurrent programming concepts and synchronization primitives.

## The Dining Philosophers Problem (brief)

The Dining Philosophers is a classical concurrency problem that illustrates synchronization and deadlock issues:

- N philosophers sit around a table.
- There is one fork between each pair of philosophers (so N forks total).
- To eat, a philosopher needs both the fork on their left and the fork on their right.
- Philosophers alternate between thinking, trying to acquire forks to eat, eating, and sleeping.

Problems to solve include deadlock (every philosopher holds one fork and waits forever for the other) and starvation (some philosophers never get to eat). The usual solutions rely on ordering, asymmetry, backoff, or separate monitor threads.

## Implementation

- Language: C
- Threading: POSIX threads (`pthread_t`) are used to represent each philosopher.
- Synchronization: `pthread_mutex_t` is used for forks and other shared data.
- Monitoring: a separate monitor thread checks philosopher states (time since last meal) and stops the simulation if a philosopher dies.
- Shared state protection: dedicated mutexes protect printing, meal counters and other shared values.

Key types and fields (from `includes/philosophers.h`):

- `t_philo` — per-philosopher structure containing a thread, pointers to left/right fork mutexes, a per-philosopher mutex, counters for meals and last meal time, and a pointer to the global state.
- `t_philosophers` — global simulation state: array of philosopher pointers, monitor thread, `meal_mutex`, `print_mutex`, timing values (`t_die`, `t_eat`, `t_sleep`), optional `n_meals`, and flags to indicate finish status.

Files of interest:

- `SRCS/` — C source files for the implementation (simulation logic, utils, monitoring, printing, etc.).
- `includes/philosophers.h` — project header with types and function prototypes.
- `Makefile` — build file (compiles with `-pthread` and includes `-Iincludes`).

Implementation notes

- The program uses mutexes to represent forks. Each philosopher holds pointers to their left and right fork mutexes and locks them to eat.
- A `print_mutex` protects output to avoid interleaving messages from concurrent threads.
- A `monitor` thread observes philosopher last-meal timestamps and signals termination if a philosopher exceeds `time_to_die` without eating.
- Helper mutexes (for example `meal_mutex`) and small accessors are used to safely get/set shared variables.

This implementation favors clarity and correctness for learning; it uses common patterns: per-resource mutexes for forks, a monitor thread for liveness checks and protected prints.

## Build

From the project root (where this `README.md` and the `Makefile` live), run:

```bash
make
```

This Makefile compiles sources in `SRCS/`. The project is built with `-pthread`.

Note: the `Makefile` in this repository defines `SHOW_MEALS` at compile time so that meal summary reporting is enabled by default.

Clean:

```bash
make fclean
```

## Usage

After building, run the simulator `./philo` with the following arguments:

```text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Arguments (all are integers, times are in milliseconds):

- `number_of_philosophers`: number of philosopher threads (N)
- `time_to_die`: time (ms) a philosopher can live without eating before dying
- `time_to_eat`: time (ms) a philosopher spends eating
- `time_to_sleep`: time (ms) a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional): if provided, the simulation stops when every philosopher has eaten at least this many times

Example:

```bash
./philo 5 800 200 200
# 5 philosophers, die after 800ms without eating, eat for 200ms, sleep for 200ms

./philo 5 800 200 200 7
# same, but stop after each philosopher has eaten at least 7 times
```

Output

The program prints timestamped events such as: taking forks, eating, sleeping, thinking, and death. Colors are used in the terminal for readability. Output is protected by a mutex so messages appear atomically.

## Concurrency considerations

Important issues with concurrent implementations like this:

- Deadlock: naive implementations may get into a deadlock if every philosopher grabs their left fork at the same time. Typical fixes include making at least one philosopher pick forks in the opposite order, using an arbitrator, or limiting the number of philosophers that can try to pick forks concurrently.
- Starvation: ensure fairness so that no philosopher is perpetually denied access to resources.
- Accurate timing and sleeping: using `usleep` naively while holding locks can block progress; the project uses a helper `precise_usleep` to manage sleeping while checking simulation state.
- Data races: all shared variables (flags, counters, timestamps) must be accessed under appropriate mutexes.

The code intentionally separates responsibilities: philosopher threads perform local actions, while a monitor thread checks global termination conditions. Mutexes guard both forks and shared counters/flags.

## Testing and expected behavior

- Try small numbers and short times to exercise the death detector (e.g., `./philo 2 60 50 50`).
- Try specifying the optional meals argument to see the simulation stop when every philosopher has eaten the specified times.

## Project structure

- `Makefile` — build rules
- `includes/` — header files (`philosophers.h`)
- `SRCS/` — implementation (.c files)

## Notes / Extending the project

- You can modify the `Makefile` if you want `SHOW_MEALS` to be optional at build time (for example, use `make SHOW_MEALS=1` or configure the Makefile to default to false).

## Author

- Hector Gamiz (hgamiz-g)
