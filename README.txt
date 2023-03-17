In regular mode, after running it 10 times. The average is: 83242
In multithreading mode, after running it 10 times the average is: 83314

Compile the file with "make"

To run in regular mode: ./data_av
To run in multithreading mode: ./data_av -m
anything else will throw an error and not execute.

Both averages for times are quite close. From my understanding, multithreading should be much faster as we are working with 10 distinct threads. Rather than the 1 regular thread the program automatically creates and writes over each time. 

Running my program on both Mac and Windows produce similar elapsed times. It is a little slower on linux, by around 30000 clocks on average. 

My program only considers values if the line is in the form '%f %f'. Otherwise, they are skipped.