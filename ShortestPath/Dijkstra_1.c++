
#include "Dijkstra.hpp"

void Graph::allocateMemory( int vertices ) 
{
	std::cout <<"Calling Graph::allocateMemory( int vertices )" << std::endl;
	this->vertices = vertices;
	adjcancy_list = new std::list<std::pair<int, int>>[ vertices ];
}

void Graph::buildGraph( std::ifstream & my_file ) 
{
	//std::cout <<"Calling Grap::buildGraph( std::ifstream & my_file )" << std::endl;	
	//std::string path = "Testfiles"; 
	
	//for( const auto & entry : file_sys::directory_iterator(path) ) {
		
		//my_file.open("Testfiles/East.len", std::ios_base::in );
		//my_file.open( entry.path(), std::ios_base::in );
		int num_vertices, num_edges;
	
		if( my_file.is_open() ) { 

		  	std::cout <<"The file is openned " << std::endl;
		  	if( my_file.good() )
		  	{
				std::string str;
			  	std::getline( my_file, str );
			  	std::istringstream first_line(str);
			  	first_line >> num_vertices >> num_edges;
		  	}

		  	int num_edges_counter = num_edges + 1;
		  	allocateMemory( num_vertices );
		  	std::cout <<"num_vertices: " << num_vertices << std::endl;
		  	num_vert = num_vertices;
		  
		  	while( --num_edges_counter ) 
		  	{
			  	std::string string_len;

			  	if( my_file && std::getline( my_file, string_len )) 
			  	{
				  	int  my_vertex_1, my_vertex_2,  weight;
				  	std::istringstream ss_stream(string_len);

				  	if( ss_stream >> my_vertex_1 >> my_vertex_2 >> weight ) {

					 	 //std::cout <<"my_vertex_1: " << my_vertex_1 << " " << "my_vertex_2: " << my_vertex_2 <<" " <<"weight: " << weight << std::endl;
					  	add_edges( my_vertex_1, my_vertex_2, weight ); 

				  }					  
			  }
		  }
	 //}
	
	
   }
	  /*	
	  std::cout <<"Content_0: " << std::endl;
          for( auto content : *adjcancy_list )
                   std::cout << content.first <<"," << content.second << " ";
          std::cout << std::endl;
	  */


	 //std::cout <<"End function" << std::endl; 
}

void Graph::add_edges( int my_vertex_1, int my_vertex_2, int my_weight )
{
	 //std::cout <<"Calling Graph::add_edges( int my_vertex_1, int my_vertex_2, int my_weight )" << std::endl;
	  //std::cout <<"my_vertex_1: " << my_vertex_1 << " " <<
 	 //"my_vertex_2: " << my_vertex_2 <<" " <<"weight: " << my_weight << std::endl;
	// std::cout <<"Calling Graph::add_edges( int my_vertex_1, int my_vertex_2, int my_weight )" << std::endl;
	adjcancy_list[ my_vertex_1 ].push_back( std::make_pair( my_vertex_2, my_weight ));
	adjcancy_list[ my_vertex_2 ].push_back( std::make_pair( my_vertex_1, my_weight ));

	/*	
	std::cout <<"My test1: " << std::endl;
	for( auto it = adjcancy_list[ my_vertex_1 ].begin(); it != adjcancy_list[ my_vertex_1 ].end(); ++it )
		std::cout <<"Size: "<< adjcancy_list[ my_vertex_1 ].size() <<" "<<"It first: " <<  (*it).first <<" " << (*it).second << std::endl;
	*/
}

void Graph::DijkstraShortestPath( int source , int destination ) 
{
	//std::cout <<"Calling Graph::DijkstraShortestPath( int source, int destination )" << std::endl;
	std::unordered_map< int, int > distance; 
	std::unordered_map< int, int > parent;
	std::unordered_set< int > close_vertex;
	
	for( int i = 0; i < vertices; ++i )
	{
		parent[ i ] = 0; 
		distance[ i ] = INT_MAX;
	}

	distance[ source ] = 0;
	min_heap.push( std::make_pair( distance[ source ] , source ));
	//std::cout <<"Here " << std::endl;
	
	while( !min_heap.empty() ) { 

		//std::cout <<"Here_1 " << std::endl;
		int top_vertex = min_heap.top().second;
		//std::cout <<"Top: " << top_vertex << std::endl;
		min_heap.pop();
		close_vertex.insert(top_vertex);

		if( top_vertex == destination )
		{
			 //std::cout <<"Shortest Path: " << distance[  top_vertex ] << std::endl; 
			 return;
		}
		 // std::cout <<"top_vertex_reverse: " << top_vertex_reverse << std::endl;
                 //std::cout <<"adjacency: " << adjcancy_list[ top_vertex ].size() << std::endl;


		for( auto iter = adjcancy_list[ top_vertex ].begin(); iter != adjcancy_list[ top_vertex ].end(); ++iter ) { 

			int vertex_v = (*iter).first; 
			// std::cout <<"vertex_v: " << vertex_v << std::endl;
			//auto my_close_vertex =  close_vertex.find(vertex_v);
			if( close_vertex.find(vertex_v) == close_vertex.end() ) { 
			 	int length = distance[ top_vertex ] + (*iter).second;
				
				if(  length < distance[ vertex_v ] ) 
				{
					++relaxed_edges;
					distance[ vertex_v  ] = length;
					parent[ vertex_v ] = top_vertex;
					min_heap.push( std::make_pair( distance[ vertex_v ], vertex_v ));
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

void Graph::BiDijkstraShortestPath( int source, int destination )
{
	// std::cout <<"Calling Graph::BiDijkstraShortestPath( int source, int destination )"  << std::endl;
        
	std::unordered_map< int, int > distance;
        std::unordered_map< int, int > reverse_distance;

        std::unordered_set< int > close_forward;
        std::unordered_set< int > close_reverse;

        for( int i = 0; i < vertices; ++i )
        {
                distance[ i ] =  INF; 
                reverse_distance[ i ] = INF;
        }

        distance[ source ] = 0;
        reverse_distance[ destination ] = 0;

        min_heap_.push( std::make_pair( distance[ source ], source ));
        min_heap_reverse.push( std::make_pair( reverse_distance[ destination ], destination ));
	auto mui = INT_MAX;
	
	while( !min_heap_.empty() and !min_heap_reverse.empty() )
	{
		//std::cout <<"HERE" << std::endl;
		int min_distance = min_heap_.top().first;
		int min_distance_reverse = min_heap_reverse.top().first;
		int min_dist = min_distance + min_distance_reverse;

		if( min_dist >= mui ) 
		{
			//std::cout <<"Distance: " << mui << std::endl; 
			return;
		}

		int top_vertex = min_heap_.top().second;
		min_heap_.pop();
		close_forward.insert(top_vertex);
		
		for( auto iter = adjcancy_list[ top_vertex ].begin(); iter != adjcancy_list[ top_vertex ].end(); ++iter ) { 

			int vertex_v = ( *iter ).first;
			int length = distance[ top_vertex ] + ( *iter ).second;

			if( close_forward.find(vertex_v) == close_forward.end() ) {
			if( length < distance[ vertex_v ] )
			{

				distance[ vertex_v ] = length;
				min_heap_.push( std::make_pair( distance[ vertex_v ], vertex_v ));
				//std::cout <<"\n";
				//std::cout <<"reverse_distance[ vertex_v ]: " << reverse_distance[ vertex_v ] << std::endl;
				//std::cout <<"length: " << length << std::endl;
				int new_length = length + reverse_distance[ vertex_v ];
				
				//std::cout <<"new_length: " << new_length << std::endl;
				
				if( new_length < mui ) 
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
		close_reverse.insert(top_vertex_reverse);

		for( auto iter_1 = adjcancy_list[ top_vertex_reverse ].begin(); iter_1 != adjcancy_list[ top_vertex_reverse ].end(); ++iter_1 )
		{
			int vertex_v_reverse = ( *iter_1 ).first;
			int length_1 = reverse_distance[ top_vertex_reverse ] + ( *iter_1 ).second; 
			//if( close_reverse.find(vertex_v_reverse) == close_reverse.end() ) {
			if( length_1 < reverse_distance[ vertex_v_reverse ] )
			{
				
				reverse_distance[ vertex_v_reverse ] = length_1;
				//std::cout <<"\n";
				min_heap_reverse.push( std::make_pair( reverse_distance[ vertex_v_reverse ], vertex_v_reverse ));
				//std::cout <<"distance[ vertex_v_reverse ]: " << distance[ vertex_v_reverse ] << std::endl;
				//std::cout <<"length_1: " << length_1 << std::endl;
				int my_new_length = length_1 + distance[ vertex_v_reverse ]; 

				//std::cout <<"my_new_length: " << my_new_length << std::endl;
				if( my_new_length < mui ) 
				{
					mui = my_new_length; 
					//std::cout <<"mui_1: " << mui << std::endl; 
				}

				++relaxed_edges_1;
			}
		}
	  // }
	}
}

void Graph::eraseContainers() 
{
	std::cout <<"Calling eraseContainters() " << std::endl;
	// Erasing container at each iteration
	while( !min_heap.empty() )
		min_heap.pop(); 
	
	while( !min_heap_.empty() )
		min_heap_.pop();

	while( !min_heap_reverse.empty() )
		min_heap_reverse.pop();
	
	adjcancy_list->clear(); 
}

std::unordered_set<int> Graph::generateSource( int vertices )
{
	 std::cout <<"Calling std::vector<int> Graph::genereateSource( int vertices )" << std::endl;
	 std::unordered_set<int> my_source_set;
	 int source_num = 10;

	 for( int i = 0; i < source_num; ++i )  {
		 
		 int source = rand() % vertices + 1;
		 while( my_source_set.find(source) != my_source_set.end() )
			  source = rand() % vertices + 1;
			  
		  my_source_set.insert(source);
	 }

	 return my_source_set;
}

std::unordered_set<int> Graph::generateDestination( int vertices, std::unordered_set<int> my_source_set )  
{
	std::cout <<"Calling std::unordered_set<int> generateDestination( int vertices ) " << std::endl;
	std::unordered_set<int> my_destination_set;
	int num_destination = 100;
	
	for( int i = 0; i < num_destination; ++i ) { 

		int destination = rand() % vertices + 1; 
		while( my_destination_set.find(destination) != my_destination_set.end() or my_source_set.find(destination) != my_source_set.end() )  
			destination = rand() % vertices + 1;

		my_destination_set.insert(destination);
	}

	return my_destination_set;
}

/*
std::vector<int> Graph::randomSourceDest( int vertices ) 
{
	std::cout <<"Calling Graph::randomSourceDest( int vertices )" << std::endl;
	std::cout <<"num Vertices: " << vertices << std::endl;
	std::vector<int> my_vec;
	int source = rand() % vertices + 1;
	int destination = rand() % vertices + 1;
	my_vec.push_back( source );

	while( source == destination )
		destination = rand() % vertices + 1;

	my_vec.push_back( destination ); 

	std::cout <<"End Graph::randomSourceDest( int vertices ) " << std::endl;
	return my_vec;
}
*/
