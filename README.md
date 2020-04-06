## To compile:

type "make"

## To execute:

"./ord edgelist.txt order order.txt"
- "edgelist.txt" should contain an undirected unweighted graph: one edge on each line (two unsigned long (ID of the 2 nodes) separated by a space);
- "order"= rand (for a random ordering), core (for a k-core ordering), icore (for an inverse k-core ordering), df (for a density friendly ordering), deg (for a degree ordering);
- "order.txt" will contain the resulting order: the new ID of the node with the old ID u is on line u.

## Initial contributors:  

Maximilien Danisch  
April 2020  
http://bit.ly/danisch  
maximilien.danisch@gmail.com

