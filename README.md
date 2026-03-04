*This project has been created as part of the 42 curriculum by hcissoko.*

# Philosophers

## Description

The **Philosophers** project is a concurrency and synchronization exercise based on the classic **Dining Philosophers Problem**.

The goal is to simulate a scenario where multiple philosophers sit at a round table with a bowl of spaghetti. Each philosopher alternates between three states:
1. **Eating** - requires two forks (one on each side)
2. **Sleeping** - resting after a meal
3. **Thinking** - waiting for the next opportunity to eat

Each philosopher is represented by a **thread**, and each fork is protected by a **mutex** to prevent data races. The program must avoid **deadlocks**, **race conditions**, and ensure that:
- The simulation stops when a philosopher dies (fails to eat within `time_to_die` milliseconds)
- OR all philosophers have eaten the required number of times (optional parameter)

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate the `philo` executable in the root directory.

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Parameters:
- **number_of_philosophers**: Number of philosophers at the table (must be greater than 0)
- **time_to_die** (ms): Maximum time a philosopher can go without eating before dying
- **time_to_eat** (ms): Duration of the eating action
- **time_to_sleep** (ms): Duration of the sleeping action
- **[number_of_times_each_philosopher_must_eat]** (optional): If provided, the simulation stops after each philosopher has eaten this many times

#### Examples:

```bash
# Basic stable simulation (should run indefinitely until a philosopher dies)
./philo 5 800 200 200

# Optional must_eat argument (simulation stops after 7 meals each)
./philo 5 800 200 200 7

# Edge case - single philosopher (should die)
./philo 1 800 200 200

# Starvation test (should die)
./philo 3 610 200 100

# Quick death test
./philo 4 310 200 100
```

## Resources

### Classic References
- [The Dining Philosophers Problem - Computerphile (YouTube)](https://www.youtube.com/watch?v=VSkvwzqo-Pk) - Visual explanation of the problem
- [Threads & Mutex in C - CodeQuoi (FR)](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/) - POSIX threads tutorial

### AI Usage

Optimized think_time logic via AI to pass some tests without causing starvation.
I tried to calculate the optimal `think_time` for philosophers to avoid starvation while still allowing them to eat in time. The formula I used is:

```c
think_time = (time_to_die - (get_current_time() - last_eating_time) - time_to_eat) / 2;
```

In the implementation, `think_time` is restricted:
- if `think_time < 0`, it is set to `0`
- if `think_time > 1000`, it is set to `100`
