# 🤔 Philosophers
A multithreading and multiprocessing project simulating the dining philosophers problem. Part of the School 1337 cursus.

## 📋 Project Structure
```
📦 Philosophers
├── 📂 philo/         # Mandatory part (threads version)
│   ├── 📂 utils
│   ├── 📄 Makefile
│   ├── 📄 philo.c
│   └── 📄 philo.h
└── 📂 philo_bonus/   # Bonus part (processes version)
    ├── 📂 utils
    ├── 📄 Makefile
    ├── 📄 philo_bonus.c
    └── 📄 philo_bonus.h
```

## 🎯 Description
The Dining Philosophers problem is a classic computer science problem illustrating synchronization issues and techniques for resolving them. The challenge involves philosophers sitting at a round table who do nothing but think and eat, with a bowl of spaghetti and one fork between each pair of philosophers.

- ⚡ Features
- ✨ Thread Management
- 🔄 Process Synchronization
- ⏱️ Precise Timing System
- 🍝 Resource Sharing
- ⚠️ Death Detection
- 📊 Performance Monitoring

## 🛠️ Installation
```bash
# Clone the repository
git clone https://github.com/Serghini04/Philosophers.git

# Navigate to the project directory
cd Philosophers

# Compile the programs
make            # For mandatory part (threads)
cd philo_bonus
make            # For bonus part (processes)
```

## 💻 Usage
### Mandatory (Threads):
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Bonus (Processes):
```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example:
```bash
./philo 5 800 200 200 7
```

## 🔧 Program Arguments
- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time (in ms) a philosopher can spend without eating
- `time_to_eat`: Time (in ms) it takes to eat
- `time_to_sleep`: Time (in ms) spent sleeping
- `[number_of_times_each_philosopher_must_eat]`: Optional argument

## ⚙️ Technical Requirements
- C Language
- Norm Compliant (42 School Code Standards)
- No Memory Leaks
- No Data Races
- Limited Functions:
  - Mandatory Part:
    - memset, printf, malloc, free, write
    - usleep, gettimeofday
    - pthread_create, pthread_detach, pthread_join
    - pthread_mutex_init, pthread_mutex_destroy
    - pthread_mutex_lock, pthread_mutex_unlock
  - Bonus Part:
    - Additional: fork, kill, exit
    - wait, waitpid, sem_open, sem_close
    - sem_post, sem_wait, sem_unlink

## 🔍 Implementation Details
### 1. 🧵 Threads Version (Mandatory)
   - One thread per philosopher
   - Mutex for each fork
   - Death monitoring system
   - Resource management

### 2. 🔄 Processes Version (Bonus)
   - One process per philosopher
   - Semaphores for forks
   - Shared memory management
   - Inter-process communication

## 🐛 Error Handling
The program handles various cases:
- Invalid arguments
- Memory allocation failures
- Thread/Process creation errors
- Mutex/Semaphore initialization failures
- System call failures

## 🚀 Simulation Rules
- Philosophers alternate between eating, thinking, and sleeping
- While eating, they need two forks
- If a philosopher doesn't start eating within time_to_die, they die
- All philosophers need to eat number_of_times_each_philosopher_must_eat times
- Simulation stops if a philosopher dies or all have eaten enough

## 📝 Testing Examples
```bash
# Basic test
./philo 4 410 200 200

# With number of meals
./philo 5 800 200 200 7

# Edge cases
./philo 1 800 200 200
./philo 4 310 200 100
```

## 📚 Resources
- POSIX Threads Programming
- Process Synchronization
- Race Conditions
- Deadlock Prevention
- Inter-Process Communication
- Semaphores vs Mutexes

## 🌟 Development Tips
- Use -g -fsanitize=thread for testing
- Monitor thread creation carefully
- Implement precise timing system
- Avoid race conditions
- Prevent deadlocks
- Check for memory leaks
- Test edge cases thoroughly

This project is part of the School 1337 curriculum.
