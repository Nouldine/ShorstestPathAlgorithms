
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
#include <experimental/filesystem>
#include <memory>
#include <cstdlib>

#define INF 900000000 

namespace file_sys = std::experimental::filesystem;

class Graph 
{
	public:
		Graph() = default; 
		void buildGraph( std::ifstream & my_file );
		void add_edges( int, int, int );
		void DijkstraShortestPath( int , int );
		std::vector<int> randomSourceDest( int );
		void BiDijkstraShortestPath( int , int );
		void eraseContainers();
		std::unordered_set<int> generateSource( int );
		std::unordered_set<int> generateDestination( int, std::unordered_set<int> ); 
		void automateProcess();
		int getVertices( std::ifstream & ); 
		
		~Graph(){ }

	private:
		int vertices = 0;
		int relaxed_edges = 0;
		int relaxed_edges_1 = 0;
		std::list< std::pair< int, int > > *adjacency_list;
		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>> >  min_heap; 	
		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>> >  min_heap_;
		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>> >  min_heap_reverse;

};

#endif
