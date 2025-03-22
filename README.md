# SO2_Project-PWr
Projekt na przedmiot Systemy Operacyjne 2, semestr 6, IGM, komentarze/readme po angielsku


This project has code for the Dining Philosophers Problem. 
The idea of the problem is that there are some philosophers around the table (for the sake of the example, we will say there are 5 of them)
5 philosophers are hungry and they are sitting at the table
On each side of the Philosophers, aka between each 2 Philosophers, there are chopsticks/fork. In the middle of the table theres a bowl of food. The philisophers are hungry and to eat, they require both chopsticks, both from left and right. But they cant eat when one of the chopsticks is being used. The idle state of philisopher is usually called "thinking". After eating, they put their forks down and return to thinking, letting others use the forks. 

The main problem is that if all philosophers pick up their left chopstick simultaneously, no one can pick up their right chopstick, and everyone is stuck waiting forever (deadlock).

Below is the Philosophers life-cycle:
Philosopher thinks for some time
Philosopher gets hungry
Philosopher attempts to acquire the left chopstick
Philosopher attempts to acquire the right chopstick
If both acquired, philosopher eats for some time
Philosopher puts down both chopsticks
Philosopher returns to thinking
Cycle repeats

As in each project, there might be some potential problems, in this instance it's a phenomenon called deadlock, and another one is 'starvation'.
Deadlock: All philosophers could pick up their left chopstick and wait forever for the right one
Starvation: Some philosophers might never get to eat if their neighbors are greedy

There are a few solutions to the deadlock and starvation problems, here are some examples below:
Number the chopsticks and require philosophers to pick them up in numerical order
Use a "waiter" who controls which philosophers can pick up chopsticks
Allow only 4 philosophers at the table at once
Put down chopsticks if you can't get both within a timeout period


In this project, a few solutions were implemented to prevent deadlock and starvation. Resource hierarchy was used by numbering chopsticks and requiring philosophers to always pick up the lower-numbered chopstick first. Random thinking and eating durations were implemented to naturally stagger philosopher activities. Mutexes ensure exclusive access to chopsticks, preventing simultaneous use. The combination of these techniques guarantees that all philosophers can complete their meals without system deadlock.

After running the project, which one can do by copying the code from all the .cpp and .h files onto their platform, you can see that in the program theres also a possibility of 2 philosophers eating at once, if they are far away from each other and can pick up 2 chopsticks. That also improves the timing of the solution.

In the project, theres also a pretty simple, yet informative menu and display in the terminal about the process of the dinner, and at the start a visualization of the dining table with the philosophers and chopsticks.

Thanks for reading :3
