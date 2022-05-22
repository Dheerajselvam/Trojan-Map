EE 538 Project

Dheeraj Panneer Selvam & Rashaad Hussain

Please open link to view report in proper format!!!

[EE538_report.docx](https://github.com/ee538/final-project-Dheerajselvam/files/7674271/EE538_report.docx)

Report
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
University of Southern California

EE538 PROJECT

On

Trojan Map



Dheeraj Panneer Selvam
Rashaad Hussain
Step 1 – Autocomplete
 

In this function a string is taken and gives out all the location names based in the starting characters of the string. In the figure we first convert the string to lower case as the input can be case sensitive. As all the names in the given CSV file start with the upper case we are converting them to lower case. A vector of strings is then created called results and it is iterated through all the nodes. It is then checking if the size of the given string is greater than the size of the names this is done there are a lot a locations in the CSV file without names. This step helps to eliminate such places. Next the string is then compared to find if the number of characters in the string are same as the number of characters in the name. If this matches the names are pushed into the result vector.
The time complexity for this function is O(N) where N is the number of places.

  
The above images show the output along with the run time for each example. The first figure shows that the input entered was “r” and the program autocompleted and suggested Residence Inn, Ralphs etc. The runtime of this function was 931 microseconds. In the second  image the input entered by the user is “ch” with using the autocomplete function the program was able to suggest “chickfilA” and “Chipotle Mexican Grill” as the results. And the runtime taken for this was 1092 microseconds

Step 2 – Location Coordinates
 e

In this function the location’s name is entered and its position is returned in latitude and longitudes. The position is also plotted on the map with a red dot to visualize the function. First, the helper function called GetID is implemented as seen in the figure above. In this function the input is the name of the location and returns the ID. We iterate through all the nodes and check if the name is available. If available the ID is returned of else -1 is returned.
The runtime complexity of this function is O(N)
 
In the main function the ID of the given name is first retrieved. If it is a valid name, then the latitude and the longitude is printed or else -1 is returned.

 
The figure above shows the program window where the user input Martin Luther King and the output was returned as the Position of the place in coordinates. The run time for this function was 523 microseconds
 
The above image shows the position of the input entered. This helps in visualization of the output of the function.
Step 3 – Shortest Path
For the Shortest Path function the first implementation was the Dijkstra algorithm. This was done with the usage of minimum heap to decide the shortest distance from the starting point so that the algorithm runs faster and the time complexity is O (v+e)(logV) where v is the number of  the vertices and e is the number of edges. The distance map was inserted in the Min heap and the djikstra algorithm was implemented. The algorithm basically pops the minimum from the min heap, adjusts the weights according to the nodes around it and push it back to the heap. This is rinsed and repeated until the destination is reached.
 
The above figure is an example of Dijkstra implementation where the input location is Ralphs and the destination is Troy view swimming pool. The image shows the path taken and the nodes in between the destination

The next implementation for the shortest path function was the Bellman-Ford algorithm. Here we tried to do relaxation on all the edges until no further relaxation was possible. This is started from all the edges hence the time complexity was O(VE) where v is the number of  the vertices and e is the number of edges. The above example had the same results when running Bellman-Ford algorithm. The number of nodes and the distance remain the same but the time taken to run the algorithm was significantly longer than Dijkstra. To better visualize this a table is used to record the differences in time taken by the 2 algorithms and it is clear that Dijkstra is much faster than Bellman-ford.




Start	Destination	Distance
(miles)	Time taken (microseconds)
(Dijkstra)	Time taken
(microseconds)
(Bellman-Ford)
Ralphs	ChickfilA	1.538	54068	53154425
Ralphs	Troy Swimming	0.521	59558	55190437
Target	ChickfilA	0.841	70805	55392527
7eleven	USC Parking	0.515	67432	57610002
Ralphs	Metro 40	2.089	55436	57272846
Target	7eleven	0.788	72991	54877410
CVS	Metro 40	1.124	62543	53427981

Step 4 – Travelling Salesperson
The first implementation for this function was using DFS. Here we enumerate all the possible routes and find the shortest path so that the time complexity is O(N!)  this is the brute force method. Though this gives the outcome we need it is not efficient. So the second implementation done was the 2- opt algorithm where here the path can be swapped with another path until a shorter path is found. This is done on the entire operation until all the paths are swapped and new improved ones are found.
The time complexity of this algorithm is 0(n^2)
 
 
The above 2 images show the path taken when brute force was applied, the distance for the 4 places was 2.607 miles and the run time was 1935 microseconds
 
The above image shows the optimal path taken when 2-opt was implemented for 4 places and the figure below shows the run time of this function which was 395 microseconds.


 
To better compare the time differences in the TSP algorithm values for different number of places and their distances are tabulated along with the run time for each method implemented.
Number of places	Brute force
(microseconds)	Distance
(Miles)	2-opt
(microseconds)	Distance
(miles)
4	1935	2.607	395	4.553
5	5857	2.503	2335	4.321
6	66262	4.229	26994	4.314
7	26811	3.339	119778	4.157



Step-5 Cycle detection

 
In this function we traverse the graph and mark each node that is visited and once visited then search for already visited nodes. Once all nodes are visited it means the cycle is completed. We have implemented DFS and the graph here is undirected. Therefore, when re-visiting a node that was not the last visited one a cycle will exist. The time complexity of this function is o(N+E) where N is the number of nodes and E is the number of edges.

 
The above image shows an example where a cycle exists in the subgraph and the run time of this program is 1942 Microseconds

Step 6 – Delivering Trojan
For this function a topological sort was implemented. This was done using DFS. First an adjacency map was created with all the appropriate dependencies fill in them. Then all the locations on the map are set to be not visited. Then TraversalDFS is called to look through all the location dependencies recursively and return an error if a location has dependencies on its path.  The time complexity of the algorithm is O(V+E) where v is the number of vertices and E is the number of Edges.
  
The above image shows the output of the topological sort with 4 points and the run time of this program was 79 microseconds
Step 7 – K closest points
In this function we go over all the nodes and calculate the distances between the nodes and the start location. The nodes and the distances are then added to a max heap then every new node is checked if its distance is less than the max value in the heap and if it is then the top value is replaced with the new value. This is done again until no lesser value is found for the nodes and the results are the k closest points
The time complexity of the function was O(N)
  
The example above shows the output of the K nearest point function where the user inputs “ChickfilA” and 15 of its nearest neighbors.
The graph plots its nearest neighbors and shows as output. The Run time for this program was 2818 Microseconds
Discussion
Autocomplete and Find Position where basic function which helped other function. Dijkstra performed better than Bellman ford has this application doesn’t have negative cycles it’s better to use Dijkstra. The thing with brute force technique in TSP is though it is very slow compared to other algorithms it always gives the right results as it goes through the entire search space. On the other hand 2-opt was significantly faster than brute force, its results are not always efficient as the distance increases faster as the number of places are increased. We implemented the 3 opt but as it was not optimized properly, we couldn’t get proper results and it took more time than 2 opt. Cycle detection worked properly. Topological sort was implemented as suggested and proper results were obtained. K neighbors was a simple implementation but will be an effective application.

Conclusion
In the end all the objectives were achieved in this project and successfully tested. We have learned almost all basics and intermediate stuff about c++. From data types, function, STL, trees, graphs and sorts. We have applied the knowledge in creating this application and successful completed all requirements. Further study and improvement will be done after this course to strengthen our skills.

Lessons Learned

This project has helped us in building solid foundations in C++ programing , algorithms and data structures. The concepts learned in class, assignments, and project are very helpful in interviewing for  electrical engineering jobs or even Software Development roles. This course has taught us to build the habit of writing unit tests as they are very important to make sure the code does not break at any point
