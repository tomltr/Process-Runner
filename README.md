# Process-Runner

Given a file containing a list of processes the program will generate output files based on different schedule algorithms

The running algorithms are First In First Out, Shortest Job First, Highest Priority and Round Robin(In Progress)

Example:

-- Process#   Arrival   Burst   Priority --

      1         1         6         9
      
      2         5         12        5
      
      3         7         3         4
      
      4         10        7         2
      
      5         30        14        3
      
      6         40        17        8
      
      7         42        15        7
      
      8         44        13        6
      
      9         100       21        5
      
      10        100       57        4
      
  
Result:

-- Process#  Finished --

FIFO:

First process come first process served

      1         7
      2         19
      3         22
      4         29
      5         44
      6         61
      7         76
      8         89    
      9         121
      10        178
      
SJF:

Process within arrival time and has the least burst time will get served first

      1           7
      3           10
      4           17
      2           29
      5           44
      8           57
      7           72
      6           89
      9           121
      10          178
      
Highest Priority:

Process within arrival time and has the highest priority(lower value means higher priority) will get served first
 
      1           7
      3           10
      4           17
      2           29
      5           44
      8           57
      7           72
      6           89
      10         157
      9          178
      
    
Round Robin:

Each process has a share given quantum time from the user.
Processes that come within the running time will be placed on the queue first.
Otherwise process that had run will be placed last on the queue.
      
      1           12
      3           15
      4           27
      2           29
      5           49
      7           84
      8           87
      6           89
      9           141
      10          178
