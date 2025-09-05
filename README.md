# 🍽️ Philosophers-42

> **philosophers-42** is a custom implementation of the classic "Dining Philosophers" problem, developed as part of the 42 School curriculum. This project delves into process synchronization, multithreading, and resource sharing, providing a practical understanding of concurrency in C programming.

---

## 📌 Project Overview

**philosophers-42** aims to:

- Simulate a scenario where philosophers alternate between thinking and eating.
- Ensure that each philosopher has access to two forks (resources) to eat.
- Prevent deadlock and starvation by implementing proper synchronization mechanisms.
- Enhance understanding of multithreading and process synchronization in C.

By completing this project, you will gain hands-on experience with:

- Managing multiple threads using POSIX threads (pthreads).
- Implementing mutexes and semaphores for resource synchronization.
- Handling shared resources safely in a multithreaded environment.
- Designing algorithms to prevent deadlock and ensure fair resource allocation.

---

## ✨ Features

- **Multithreading:** Each philosopher is represented by a separate thread, allowing simultaneous thinking and eating.
- **Mutexes:** Utilizes mutexes to ensure that only one philosopher can access a fork at a time, preventing race conditions.
- **Deadlock Prevention:** Implements strategies to avoid situations where philosophers are indefinitely waiting for each other to release forks.
- **Starvation Avoidance:** Ensures that all philosophers get a chance to eat, preventing any philosopher from being left out.
- **Customizable Parameters:** Allows setting the number of philosophers, time to die, time to eat, and time to sleep via command-line arguments.
- **Bonus Features (Optional):**
  - **Philosopher Must Eat:** Optionally specify the number of times each philosopher must eat before the simulation ends.

---

## 🛠 Technologies Used

- **Programming Language:** C
- **Multithreading:** POSIX threads (pthreads)
- **Synchronization:** Mutexes and semaphores
- **Memory Management:** Manual memory allocation and deallocation
- **Build System:** Makefile
- **Version Control:** Git & GitHub
- **Operating Systems:** Linux (Ubuntu 22.04), macOS

---

## 🧠 Algorithm & Logic

The algorithm follows these main steps to solve the dining philosophers problem efficiently:

1. **Initialization:**
   - Parse command-line arguments (number of philosophers, time to die, eat, sleep, optional number of meals).
   - Initialize mutexes for each fork.
   - Create philosopher threads, each representing a philosopher with unique ID.

2. **Philosopher Life Cycle (Thread Function):**
   - **Think:** Philosopher thinks for an indefinite time.
   - **Take Forks:**
     - Attempt to pick up the left fork (mutex lock).
     - Attempt to pick up the right fork (mutex lock).
     - Use ordering strategy (e.g., odd philosophers pick left first, even pick right first) to avoid deadlock.
   - **Eat:** Philosopher eats for the specified time.
     - Update last meal timestamp.
     - Increment meals eaten counter if the "must eat" bonus is active.
   - **Release Forks:** Unlock both left and right forks (mutex unlock).
   - **Sleep:** Philosopher sleeps for the specified time before thinking again.
   - Loop until termination condition is met (all philosophers have eaten required times or a philosopher dies).

3. **Monitoring:**
   - A separate thread monitors philosophers’ states.
   - Checks if any philosopher exceeds `time_to_die`.
   - Terminates simulation if a philosopher dies or all have eaten required meals.

4. **Termination:**
   - Join all threads to ensure clean exit.
   - Free all allocated memory.
   - Destroy all mutexes.

5. **Deadlock & Starvation Prevention:**
   - Odd-even fork picking strategy prevents cyclic wait.
   - Monitoring ensures that no philosopher starves.

---

## 📌 Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
