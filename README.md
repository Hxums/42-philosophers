*This project has been created as part of the 42 curriculum by hcissoko.*

# Philosophers

## Description
The **Philosophers** project is a concurrency and synchronization exercise based on the classic Dining Philosophers problem.

The goal is to simulate philosophers that alternate between:
- taking forks,
- eating,
- sleeping,
- thinking.

Each philosopher is a thread, and each fork is protected by a mutex. The program must avoid race conditions and correctly stop the simulation when:
- a philosopher dies (did not eat before `time_to_die`), or
- every philosopher has eaten enough times (when the optional argument is provided).

This implementation uses:
- POSIX threads (`pthread`),
- mutexes for forks and shared state,
- a monitor loop to detect death and completion,
- custom timing/sleep helpers.

## Resources
- [The Dining Philosophers Problem](https://www.youtube.com/watch?v=VSkvwzqo-Pk)
- [Thread & Mutex](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)

