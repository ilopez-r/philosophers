![image](https://github.com/ilopez-r/resources/blob/main/covers/cover-philosophers-bonus.png?raw=true)

## Subject
This is the [subject](https://github.com/ilopez-r/resources/blob/main/subjects/03_philosophers_en.pdf) for this project.

## Introduction
This project is a version of the [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

The goal of this project was to learn the basic principles of spinning a process. You will learn how to create threads and discover mutexes.

## Rules
The program takes the following arguments:

`./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`

- `number_of_philosophers`: The number of philosophers and also the number
of forks.
- `time_to_die` (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## Output
The output of the program is in the format `<timestamp> <philosopher (1 to number_of_philosophers)> <action>`

Each philosopher logs the following actions:
- Taking a fork
- Eating
- Sleeping
- Thinking
- Dying

The logged messages are always in sequential order.

## Installation and Usage
To install and run the Philosopher project, follow these steps:

Clone the project repository: 

				git clone https://github.com/ilopez-r/philosophers.git
Navigate to the project directory: 
				
					cd philosopher
Compile the project using the provided Makefile: 

				   		 make
Run the program with the desired number of philosophers: 

	./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
