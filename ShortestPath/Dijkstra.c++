
#include "Dijkstra.hpp"

int Graph::getVertices( std::ifstream & my_file ) {

	std::cout <<"Calling int Graph::getVertices( std::ifstream & my_file )" << std::endl; 
	int my_vertices, num_edges;

	if( my_file.is_open() ) 
	{
		std::cout <<"The file is openned" << std::endl;
		if( my_file.good() ) 
		{
			std::cout <<"The file is good" << std::endl;
			std::string str;
			std::getline( my_file, str );
			std::istringstream my_first_line(str);
			my_first_line >> my_vertices >> num_edges;
			 
			std::cout <<"MyVertices: " << my_vertices << std::endl;
			return my_vertices;
		}
	}
	
	return 0;
}

void Graph::buildGraph(std::ifstream &my_file)
{
	std::cout <<"Calling Grap::buildGraph( std::ifstream & my_file )" << std::endl;
	int num_vertices, num_edges;

	if(my_file.is_open())
	{
		std::cout << "The file is openned " << std::endl;
		if( my_file.good() )
		{
			std::string str;
			std::getline(my_file, str);
			std::istringstream first_line(str);
			first_line >> num_vertices >> num_edges;
		}

		int num_edges_counter = num_edges + 1;
		// allocateMemory(num_vertices);
		vertices = num_vertices;
		std::cout << "num_vertices: " << num_vertices << std::endl;
		// num_vert = num_vertices;

		while( --num_edges_counter )
		{
			std::string string_len;

			if( my_file && std::getline(my_file, string_len ))
			{
				int my_vertex_1, my_vertex_2, weight;
				std::istringstream ss_stream(string_len);

				if( ss_stream >> my_vertex_1 >> my_vertex_2 >> weight )
					add_edges( my_vertex_1, my_vertex_2, weight );
			}
		}
	}
}

void Graph::add_edges( int my_vertex_1, int my_vertex_2, int my_weight )
{
	//std::cout <<"Calling Graph::add_edges( int my_vertex_1, int my_vertex_2, int my_weight )" << std::endl;
	adjacency_list[ my_vertex_1 ].push_back( std::make_pair( my_vertex_2, my_weight ));
	adjacency_list[ my_vertex_2 ].push_back( std::make_pair( my_vertex_1, my_weight ));
}

void Graph::DijkstraShortestPath(int source, int destination)
{
	//std::cout <<"Calling Graph::DijkstraShortestPath( int source, int destination )" << std::endl;
	std::unordered_map<int, int> distance;
	std::unordered_map<int, int> parent;
	std::unordered_set<int> close_vertex;

	for (int i = 0; i < vertices; ++i)
	{
		parent[i] = 0;
		distance[i] = INT_MAX;
	}

	distance[source] = 0;
	min_heap.push(std::make_pair(distance[source], source));
	//std::cout <<"Here " << std::endl;

	while (!min_heap.empty())
	{

		int top_vertex = min_heap.top().second;
		min_heap.pop();
		close_vertex.insert(top_vertex);

		if (top_vertex == destination)
		{
			//std::cout <<"Shortest Path: " << distance[  top_vertex ] << std::endl;
			return;
		}

		for (auto iter = adjacency_list[top_vertex].begin(); iter != adjacency_list[top_vertex].end(); ++iter)
		{
			int vertex_v = (*iter).first;
			if (close_vertex.find(vertex_v) == close_vertex.end())
			{
				int length = distance[top_vertex] + (*iter).second;

				if (length < distance[vertex_v])
				{
					++relaxed_edges;
					distance[vertex_v] = length;
					parent[vertex_v] = top_vertex;
					min_heap.push(std::make_pair(distance[vertex_v], vertex_v));
				}
			}
		}
	}

	/*
	std::cout <<"["; ;
        for( auto content : distance )
                std::cout <<  content.first << " ";
        std::cout << "]" << std::endl;
	std::cout <<"Test"<< std::endl;
	
	std::cout << "Dijkstra Distances" << std::endl;
	std::cout <<"["; ;
	for( auto content : reverse_distance )
		std::cout <<  content.first << " "; 
	std::cout << "]" << std::endl;
	*/
}

void Graph::BiDijkstraShortestPath(int source, int destination)
{
	// std::cout <<"Calling Graph::BiDijkstraShortestPath( int source, int destination )"  << std::endl;
	std::unordered_map<int, int> distance;
	std::unordered_map<int, int> reverse_distance;

	std::unordered_set<int> close_forward;
	std::unordered_set<int> close_reverse;

	for (int i = 0; i < vertices; ++i)
	{
		distance[i] = INF;
		reverse_distance[i] = INF;
	}

	distance[source] = 0;
	reverse_distance[destination] = 0;

	min_heap_.push(std::make_pair(distance[source], source));
	min_heap_reverse.push(std::make_pair(reverse_distance[destination], destination));
	auto mui = INF;

	while (!min_heap_.empty() and !min_heap_reverse.empty())
	{
		//std::cout <<"HERE" << std::endl;
		int min_distance = min_heap_.top().first;
		int min_distance_reverse = min_heap_reverse.top().first;
		int min_dist = min_distance + min_distance_reverse;

		if (min_dist >= mui)
		{
			//std::cout <<"Distance: " << mui << std::endl;
			return;
		}

		int top_vertex = min_heap_.top().second;
		min_heap_.pop();
		close_forward.insert(top_vertex);

		for (auto iter = adjacency_list[top_vertex].begin(); iter != adjacency_list[top_vertex].end(); ++iter)
		{
			int vertex_v = (*iter).first;
			int length = distance[ top_vertex ] + (*iter).second;

			if (close_forward.find(vertex_v) == close_forward.end())
			{
				if (length < distance[vertex_v])
				{

					distance[vertex_v] = length;
					min_heap_.push( std::make_pair( distance[ vertex_v ], vertex_v ));
					int new_length = length + reverse_distance[ vertex_v ];

					if (new_length < mui)
					{
						mui = new_length;
						// std::cout <<"mui_0: " << mui << std::endl;
					}

					++relaxed_edges_1;
				}
			}
		}

		int top_vertex_reverse = min_heap_reverse.top().second;
		min_heap_reverse.pop();
		close_reverse.insert( top_vertex_reverse );

		for( auto iter_1 = adjacency_list[ top_vertex_reverse ].begin(); iter_1 != adjacency_list[ top_vertex_reverse ].end(); ++iter_1)
		{
			int vertex_v_reverse = ( *iter_1 ).first;
			int length_1 = reverse_distance[ top_vertex_reverse ] + ( *iter_1 ).second;
			if ( length_1 < reverse_distance[ vertex_v_reverse ] )
			{
				reverse_distance[ vertex_v_reverse ] = length_1;
				min_heap_reverse.push( std::make_pair(reverse_distance[ vertex_v_reverse ], vertex_v_reverse ));
				int my_new_length = length_1 + distance[ vertex_v_reverse ];

				if( my_new_length < mui )
				{
					mui = my_new_length;
					//std::cout <<"mui_1: " << mui << std::endl;
				}

				++relaxed_edges_1;
			}
		}
	}
}

void Graph::eraseContainers()
{
	// std::cout <<"Calling eraseContainters() " << std::endl;
	// Erasing container at each iteration
	while (!min_heap.empty())
		min_heap.pop();

	while (!min_heap_.empty())
		min_heap_.pop();

	while (!min_heap_reverse.empty())
		min_heap_reverse.pop();

	delete [] adjacency_list;

}

std::unordered_set<int> Graph::generateSource( int vertices )
{
	// std::cout <<"Calling std::vector<int> Graph::genereateSource( int vertices )" << std::endl;
	std::unordered_set<int> my_source_set;
	int source_num = 10;
	std::srand(0);

	for (int i = 0; i < source_num; ++i)
	{
		int source = rand() % vertices + 1;
		while (my_source_set.find(source) != my_source_set.end())
			source = rand() % vertices + 1;

		my_source_set.insert(source);
	}	

	return my_source_set;
}

std::unordered_set<int> Graph::generateDestination( int vertices, std::unordered_set<int> my_source_set )
{
	// std::cout <<"Calling std::unordered_set<int> generateDestination( int vertices ) " << std::endl;
	std::unordered_set<int> my_destination_set;
	int num_destination = 100;
	std::srand(0);

	for( int i = 0; i < num_destination; ++i )
	{
		// std::cout <<"Here " << std::endl;
		int destination = rand() % vertices + 1;
		while( my_destination_set.find(destination) != my_destination_set.end() or my_source_set.find(destination) != my_source_set.end() )
		{
			destination = rand() % vertices + 1;
		}

		my_destination_set.insert(destination);
	}

	return my_destination_set;
}

void Graph::automateProcess() { 

	std::string path = "../../../DataSet";

	for( const auto & entry : file_sys::directory_iterator(path) ) {

		std::cout <<"Test1" << std::endl;
		std::ifstream my_file;
		std::cout <<"Running..." << std::endl;
		my_file.open( entry.path(), std::ios_base::in );
		std::cout <<"File: "<< entry.path() << std::endl;
		vertices = getVertices( my_file );
		my_file.close();
		if( vertices <= 0 )
			break;

		my_file.open( entry.path(), std::ios_base::in );
		adjacency_list = new std::list< std::pair<int, int> >[ vertices ];
		buildGraph( my_file );
		
		// Variables Dijkstra's Algorithm
	        int total_relaxed_edges = 0;
		int av_relaxed_edges = 0;	
		double total_duration = 0.0;
		double average_duration = 0.0;

		// Variables for the Bidirectional Dijkstra's Algorithm
		int total_relaxed_edges_1 = 0;
		int av_relaxed_edges_1 = 0;
		double total_duration_1 = 0.0;
		double average_duration_1 = 0.0;

		// Define containers to gather the appropriate information
		std::vector< std::pair< double, int > > averages;
		std::vector< std::pair< double, int > > averages_1;

		// Define counters
		int counter = 0;
		int counter_1 = 0;

		// Get the source and destination vertices for the simulation
		std::unordered_set< int > my_source_set = generateSource( vertices );
		std::unordered_set< int > my_destinations = generateDestination( vertices, my_source_set ); 

		for( auto iter = my_source_set.begin(); iter != my_source_set.end(); ++iter ) 
		{
			++counter;
		       
			for( auto it = my_destinations.begin(); it != my_destinations.end(); ++it ) 
			{
				 std::cout <<"Counter: "<< counter << " "
					    <<"Counter_1: "<< ++counter_1 << " "
					    <<"Source: "<< *iter << " "
					    <<"Destination: "<< *it << std::endl;

				 clock_t begin_0 = clock();
				 DijkstraShortestPath( *iter, *it );
				 clock_t end_0 = clock();
				 double duration_0 = double( end_0 - begin_0 ) / CLOCKS_PER_SEC;

				 // std::cout << std::endl;
				 // std::cout << "DijkstraShortestPath duration: " << duration_0 << std::endl
				 // std::cout << "Relaxed_edges: " << G.relaxed_edges << std::endl;
				 
				 total_duration += duration_0;
				 total_relaxed_edges += relaxed_edges;
				 relaxed_edges = 0;
				 
				 // std::cout << std::endl;
				 clock_t begin_1 = clock();
				 BiDijkstraShortestPath( *iter, *it );
				 clock_t end_1 = clock();
				 double duration_1 = double( end_1 - begin_1 ) / CLOCKS_PER_SEC;
				 
				 // std::cout << "BiDijkstraShortestPath duration"<< duration_1 << std::endl;
				 // std::cout << "Relaxed_ edges: " << relaxed_edges_1 << std::endl;
				 
				 total_duration_1 += duration_1;
				 total_relaxed_edges_1 += relaxed_edges_1;
				 relaxed_edges_1 = 0;

			}	

			// Getting averages from the Dijkstra's Algorithm
			average_duration = ( total_duration / 100.0 );
			av_relaxed_edges = ( total_relaxed_edges / 100 );
			averages.push_back( std::make_pair( average_duration, av_relaxed_edges ) );
			total_duration = 0;
			total_relaxed_edges = 0;

			// Getting averages from the Bidirectional Dijkstra's Algorithm
			average_duration_1 = ( total_duration_1 / 100.0 );
			av_relaxed_edges_1 = ( total_relaxed_edges_1 /  100 );
			averages_1.push_back( std::make_pair( average_duration_1, av_relaxed_edges_1 ) );
			total_duration_1 = 0;
			total_relaxed_edges_1 = 0;
			counter_1 = 0;
		}

		std::cout << "Dijkstra averages set " << std::endl;
		double total_dur = 0;
		int total_edge = 0;
		
		for( auto iter = averages.begin(); iter != averages.end(); ++iter )
		{
			total_dur += ( *iter ).first; 
			total_edge += ( *iter ).second; 
			// std::cout <<"Average durations: " << ( *iter ).first << " " <<"Average Relaxed edges: "<<(*iter).second << std::endl;
		}

		std::cout << std::endl;
		std::cout <<"Final Average time:" << ( total_dur / 10.0 ) << std::endl;
		std::cout <<"Final Average Edge relaxed: " << ( total_edge / 10 ) << std::endl;

		std::cout << std::endl;
		// Bidirectional averages set 
		std::cout <<"Bidirectional averages set" << std::endl;
		total_dur = 0;
		total_edge = 0;

		for( auto iter = averages_1.begin(); iter != averages_1.end(); ++iter )
		{
			total_dur += ( *iter ).first;
			total_edge += ( *iter ).second;
			//std::cout <<"Average durations: " << ( *iter ).first <<" "<<"Average Relaxed edges: "<<( *iter ).second << std::endl; 
		}

		std::cout << "Final Average time: " << ( total_dur / 10.0 ) << std::endl;
		std::cout << "Final Average relaxed Edge: "<< ( total_edge / 10 ) << std::endl;

		eraseContainers();

	}

}
