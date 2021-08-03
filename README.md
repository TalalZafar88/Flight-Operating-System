# Flight-Operating-System
We were given the scenario where we had to read the source cities of flight from the file and then we had to read the cities of destination from the file too along with the flight Fare, duration and other aspects too. The approach was possible in two ways to make a graph for the provided scenario, one to come up with a adjacency matrix but it is space consuming and when we look at the space complexity, we have to keep in view that we have to keep the space for those flights too which are not in the scenario in order to maintain the order of the matrix.


Hence we opted to go for the adjacency list where we read the source cities and made a separate array for them and  then for each element city array we pointer it towards all the destinations where flight went from the source city i.e making it a list within list. This approach was useful for us because it had no space trade as for every given scenario of different cities, different number of flights take off for different destinations.

Once done with the making of the graph ,we were given five scenarios where we had to find the flight for our customer depending on the query that he presented. We had to use two different approached to solve the queries depending on its type
