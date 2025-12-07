## 🍽️ Philosophers (Philo): The Dining Problem

**Philosophers (Philo)** is a **42 School** project that implements the famous **Dining Philosophers Problem**. It serves as a practical exercise in understanding and mastering **threading**, **concurrency**, and **synchronization** primitives, specifically **mutexes**, to prevent conditions like **deadlocks** and **race conditions**.

---

## 💡 The Problem

The Dining Philosophers Problem is a classic multi-process synchronization problem. Five philosophers sit around a circular table. Between each pair of philosophers is a single fork. A philosopher must have **two forks** (one on their left, one on their right) to eat.

### States of a Philosopher

1.  **Thinking:** Waiting to become hungry.
2.  **Hungry:** Waiting for forks.
3.  **Eating:** Holding both forks.
4.  **Sleeping:** Finished eating, waiting to become hungry again.

### The Challenge

The primary goal is to ensure that no philosopher **starves** (liveness issue) and that the system does not enter a **deadlock** state where all philosophers simultaneously grab their left fork and wait indefinitely for their right fork. 

---

## 🚀 Features and Constraints

Our implementation of the Dining Philosophers problem adheres to the following rules and constraints:

* **Synchronization:** Uses **`pthread_mutex_t`** to protect shared resources (forks) and critical sections (status updates, data access).
* **Threading:** Each philosopher is represented by a separate **thread** (`pthread`).
* **No Deadlocks:** The implementation guarantees a solution that prevents all threads from blocking indefinitely.
* **No Race Conditions:** Ensures that shared data (like the last time a philosopher ate, or the total meals eaten) is accessed safely.
* **Time Monitoring:** The simulation tracks time in milliseconds.

### Input Parameters

The program takes four (or five) required arguments:

| Argument | Description |
| :--- | :--- |
| `number_of_philosophers` | The number of philosophers (and forks). |
| `time_to_die` | Max time (in ms) a philosopher can go without eating before dying. |
| `time_to_eat` | Time (in ms) it takes a philosopher to eat. |
| `time_to_sleep` | Time (in ms) it takes a philosopher to sleep. |
| `[number_of_times_each_philosopher_must_eat]` | **(Optional)** If set, the simulation stops once every philosopher has eaten this many times. |

### Output

The simulation logs actions in the following format:
[timestamp_in_ms] [philosopher_id] [action]
**Actions Logged:**

* `is thinking`
* `is eating`
* `is sleeping`
* `has taken a fork`
* `died` (Terminates the simulation)

---

## ⚙️ Implementation Details

### Data Structures

* **`t_philo` (Philosopher structure):** Holds individual state (ID, meals eaten, last meal time) and pointers to its left and right forks.
* **`t_fork` (Mutex):** A `pthread_mutex_t` used to represent a single fork resource.
* **`t_data` (Shared Data):** Holds simulation-wide information (input parameters, the array of forks, the main monitor mutex, and the global stop flag).

### Synchronization Strategy

We employ a strategy to break the circular dependency that causes deadlocks. A common solution implemented here involves:

* **Asymmetric Ordering:** Enforcing a rule where all **odd-numbered** philosophers pick up their **left fork** first, and all **even-numbered** philosophers pick up their **right fork** first. This ensures at least one philosopher can eventually grab both forks.

### The Monitoring Thread

A separate **monitor thread** is crucial for checking the vital signs of all philosophers.

* The monitor periodically checks the `last_meal_time` of every philosopher.
* If a philosopher's hunger duration exceeds `time_to_die`, the monitor sets the global **stop flag** and logs the death message.
* If the optional meal count is set, the monitor checks if all philosophers have reached the required number of meals and stops the simulation if they have.

---

## 💻 Installation and Usage

### Prerequisites

* **C Compiler:** GCC or Clang.
* **`make`:** For building the project.
* **`pthread` library:** Standard POSIX threads library.

### Build

1.  **Clone the repository:**
    ```bash
    git clone <your_repo_url>
    cd philo
    ```

2.  **Compile the project** using the provided `Makefile`:
    ```bash
    make
    ```

### Run

Execute the program with 4 or 5 arguments:

```bash
# Example 1: 5 philosophers, high risk of death
./philo 5 800 200 200

# Example 2: 4 philosophers, fixed meal count (5 meals each)
./philo 4 410 200 200 5

🤝 Authors
  Youssef Bahij
