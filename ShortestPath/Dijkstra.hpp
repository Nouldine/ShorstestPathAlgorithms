
#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <iostream> 
#include <string> 
#include <vector> 
#include <unordered_map>
#include <fstream>  
#include <queue>
#include <random>
#include <list>
#include <climits>
#include <sstream>
#include <climits>
#include <unordered_set>
#include <set>
#include <algorithm>


class Graph 
{
	public:
		Graph() = default; 
		void allocateMemory( int );
		void buildGraph( std::ifstream & my_file );
		void add_edges( int, int, int );
		void DijkstraShortestPath( int , int );
		std::vector<int> randomSourceDest( int );
		void BiDijkstraShortestPath( int, int );
		int num_vert;
		int relaxed_edges;
		int relaxed_edges_1;
		~Graph(){}

	private:
		int vertices;
		std::list< std::pair< int, int > > *adjcancy_list;

		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>>>  min_heap; 	

		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>  min_heap_;

		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>>>  min_heap_reverse;
};

#endif
