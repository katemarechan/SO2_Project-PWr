# SO2_Project-PWr
Projekt na przedmiot Systemy Operacyjne 2, semestr 6, IGM, komentarze/readme po angielsku


This project has code for the Dining Philosophers Problem. 
The idea of the problem is that there are some philosophers around the table (for the sake of the example, we will say there are 5 of them)
5 philosophers are hungry and they are sitting at the table
On each side of the Philosophers, aka between each 2 Philosophers, there are chopsticks/fork. In the middle of the table theres a bowl of food. The philisophers are hungry and to eat, they require both chopsticks, both from left and right. But they cant eat when one of the chopsticks is being used. The idle state of philisopher is usually called "thinking". After eating, they put their chopsticks down and return to thinking, letting others use the chopsticks/forks. 

The main problem is that if all philosophers pick up their left chopstick simultaneously, no one can pick up their right chopstick, and everyone is stuck waiting forever (deadlock).

Below is the Philosophers life-cycle:
1. Philosopher thinks for some time
2. Philosopher gets hungry
3. Philosopher attempts to acquire the left chopstick
4. Philosopher attempts to acquire the right chopstick
5. If both acquired, philosopher eats for some time
6. Philosopher puts down both chopsticks
7. Philosopher returns to thinking
8. Cycle repeats

As in each project, there might be some potential problems, in this instance it's a phenomenon called deadlock, and another one is 'starvation'.
1. Deadlock: All philosophers could pick up their left chopstick and wait forever for the right one
2. Starvation: Some philosophers might never get to eat if their neighbors are greedy

There are a few solutions to the deadlock and starvation problems, here are some examples below:
1. Number the chopsticks and require philosophers to pick them up in numerical order
2. Use a "waiter" who controls which philosophers can pick up chopsticks
3. Allow only 4 philosophers at the table at once
4. Put down chopsticks if you can't get both within a timeout period


In this project, a few solutions were implemented to prevent deadlock and starvation. Resource hierarchy was used by numbering chopsticks and requiring philosophers to always pick up the lower-numbered chopstick first. Random thinking and eating durations were implemented to naturally stagger philosopher activities. Mutexes ensure exclusive access to chopsticks, preventing simultaneous use. The combination of these techniques guarantees that all philosophers can complete their meals without system deadlock.

After running the project, which one can do by copying the code from all the .cpp and .h files onto their platform, you can see that in the program theres also a possibility of 2 philosophers eating at once, if they are far away from each other and can pick up 2 chopsticks. That also improves the timing of the solution.

In the project, theres also a pretty simple, yet informative menu and display in the terminal about the process of the dinner, and at the start a visualization of the dining table with the philosophers and chopsticks.

Implementation details:
Threads and Their Representation

Philosopher Threads: Each philosopher is represented by a separate thread (std::thread td in the Philosopher class). These threads alternate between thinking and eating operations.
Main Thread: Manages the creation of philosophers and chopsticks, monitors the simulation, and handles program termination.

In the project, mutex and threads were used as the premade/ready functions.

Critical Sections and Solutions:

Chopstick Access (Primary Critical Section)

Problem: Multiple philosophers attempting to use the same chopstick simultaneously.
Solution: Each chopstick has a mutex (std::mutex mtx) that ensures exclusive access. A philosopher must acquire the mutex lock before using the chopstick.
Implementation: Resource hierarchy solution where philosophers always pick up the lower-numbered chopstick first, breaking the circular wait condition necessary for deadlock.

Console Output (Secondary Critical Section)

Problem: Multiple threads (philosophers) writing to the console simultaneously, causing interleaved output.
Solution: A global mutex (console_mutex) ensures that only one philosopher can write to the console at a time.
Implementation: Each philosopher's print method uses a lock guard to ensure exclusive access to the console.


In this project, a few solutions were implemented to prevent deadlock and starvation. Resource hierarchy was used by numbering chopsticks and requiring philosophers to always pick up the lower-numbered chopstick first. Random thinking and eating durations were implemented to naturally stagger philosopher activities. Mutexes ensure exclusive access to chopsticks, preventing simultaneous use. The combination of these techniques guarantees that all philosophers can complete their meals without system deadlock.

Thanks for reading :3
