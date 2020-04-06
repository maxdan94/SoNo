## To compile:

type "make"

## To execute:

In order to perform a non-mandatory pre-processing step that consists to re-number the nodes from 0 to n-1, where n is the number of nodes of degree one or more in the input graph (that is nodes that belong to at least one edge).

"./ord edgelist.txt order order.txt"
- "input_edgelist.txt" should contain an undirected unweighted graph: one edge on each line (two unsigned long (ID of the 2 nodes) separated by a space).
- "order"= rand (for a random ordering), core (for a k-core ordering), icore (for an inverse k-core ordering), df (for a density friendly ordering), deg (for a degree ordering)
- "order.txt" will contain the resulting order: the new ID of node old ID is on line old ID

## Initial contributors:  

Maximilien Danisch  
April 2020  
http://bit.ly/danisch  
maximilien.danisch@gmail.com

