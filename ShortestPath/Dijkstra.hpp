
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

namespace file_sys = std::experimental::filesystem;



#define INF 900000000 



class Graph 
{
	public:
		Graph() = default; 
		void allocateMemory( int );
		void buildGraph( std::ifstream & my_file );
		void add_edges( int, int, int );
		void DijkstraShortestPath( int , int );
		std::vector<int> randomSourceDest( int );
		void BiDijkstraShortestPath( int , int );
		void eraseContainers();
		std::unordered_set<int> generateSource( int );
		std::unordered_set<int> generateDestination( int, std::unordered_set<int> ); 
		int num_vert;
		int relaxed_edges;
		int relaxed_edges_1;
		~Graph()
		{
			delete adjacency_list;
		}

	private:
		int vertices;
		std::list< std::pair< int, int > > *adjacency_list;

		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>> >  min_heap; 	

		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>> >  min_heap_;

		std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater< std::pair<int, int>> >  min_heap_reverse;

};

#endif
