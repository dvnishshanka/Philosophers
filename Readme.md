# Philosophers


The Philosophers problem is a classic synchronization and concurrency problem.

The problem involves a scenario where a group of philosophers sits around a dining table with a bowl of spaghetti in front of each. The philosophers alternate between thinking and eating. To eat, a philosopher must pick up the two adjacent forks. The challenge is to design a solution that prevents deadlock (where no philosopher can proceed) and ensures that each philosopher gets a fair chance to eat without creating contention for resources. 

**Languages**

[![My Skills](https://skillicons.dev/icons?i=c)](https://skillicons.dev)

**Assignment**

Program take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

  - **number_of_philosophers:** The number of philosophers and also the number of forks.
  - **time_to_die (in milliseconds):** If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
  - **time_to_eat (in milliseconds):** The time it takes for a philosopher to eat.

During that time, they will need to hold two forks.
  - **time_to_sleep (in milliseconds):** The time a philosopher will spend sleeping.
  - **number_of_times_each_philosopher_must_eat (optional argument):** If all

philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
    
**Resources**

- https://www.youtube.com/watch?v=GXXE42bkqQk
- https://www.youtube.com/watch?v=zOpzGHwJ3MU
- https://nafuka11.github.io/philosophers-visualizer/
  
**Result: :one::zero::zero: / :one::zero::zero: :heavy_check_mark:**

