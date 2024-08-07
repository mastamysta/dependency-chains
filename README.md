# Dependency Chains

Superscalar processors use parallel execution to speed up runtimes. The idea is:
- Maintain a list of uops to be executed in upcoming instructions in the currently executing branch.
- Maintain a list of dependencies for each uop. i.e. fetch the value from memory, then add 0x20 to the value. The second uop depends on the first. These dependencies may themselves have dependencies, forming chains.
- For uops where the dependency chain is satisfied, the CPU can begin executing and retiring.

This form of parallelism allows the CPU to speed up program execution, but it cannot work if dependency chains are very long. This example program allows a summation over N elements to run
faster by splitting the summation into 4 dependency chains and then summing them at the end of the loop.

Naive summation:
```
 Performance counter stats for 'src/rolled':

         64,570.88 msec task-clock                       #    1.000 CPUs utilized             
               178      context-switches                 #    2.757 /sec                      
                 0      cpu-migrations                   #    0.000 /sec                      
               324      page-faults                      #    5.018 /sec                      
   241,006,279,521      cycles                           #    3.732 GHz                         (71.43%)
       244,545,410      stalled-cycles-frontend          #    0.10% frontend cycles idle        (71.43%)
   577,049,733,830      instructions                     #    2.39  insn per cycle            
                                                  #    0.00  stalled cycles per insn     (71.43%)
    78,718,711,262      branches                         #    1.219 G/sec                       (71.43%)
         2,140,854      branch-misses                    #    0.00% of all branches             (71.43%)
   367,100,791,043      L1-dcache-loads                  #    5.685 G/sec                       (71.43%)
     1,660,821,049      L1-dcache-load-misses            #    0.45% of all L1-dcache accesses   (71.43%)
   <not supported>      LLC-loads                                                             
   <not supported>      LLC-load-misses                                                       

      64.573259485 seconds time elapsed

      64.568954000 seconds user
       0.001999000 seconds sys
```

Summation under 4 distinct dependency chains:
```
         55,485.69 msec task-clock                       #    1.000 CPUs utilized             
               217      context-switches                 #    3.911 /sec                      
                 5      cpu-migrations                   #    0.090 /sec                      
               324      page-faults                      #    5.839 /sec                      
   214,762,277,211      cycles                           #    3.871 GHz                         (71.43%)
       210,588,811      stalled-cycles-frontend          #    0.10% frontend cycles idle        (71.43%)
   537,650,271,116      instructions                     #    2.50  insn per cycle            
                                                  #    0.00  stalled cycles per insn     (71.43%)
    59,052,041,921      branches                         #    1.064 G/sec                       (71.43%)
         1,786,505      branch-misses                    #    0.00% of all branches             (71.43%)
   327,805,016,297      L1-dcache-loads                  #    5.908 G/sec                       (71.43%)
     1,654,195,788      L1-dcache-load-misses            #    0.50% of all L1-dcache accesses   (71.43%)
   <not supported>      LLC-loads                                                             
   <not supported>      LLC-load-misses                                                       

      55.488644379 seconds time elapsed

      55.484110000 seconds user
       0.001999000 seconds sys
```
