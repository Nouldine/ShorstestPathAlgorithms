
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
	my_file.open("DataDIMACS/Testfiles/East.len", std::ios_base::in );
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
		  //std::cout <<"num_vertices: " << num_vertices << std::endl;
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

void Graph::DijkstraShortestPath( int source, int destination ) 
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
			 std::cout <<"Shortest Path: " << distance[  top_vertex ] << std::endl; 
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
	*/
	std::cout << "Dijkstra Distances" << std::endl;
	std::cout <<"["; ;
	for( auto content : distance )
		std::cout <<  content.second << " "; 
	std::cout << "]" << std::endl;
}

void Graph::BiDijkstraShortestPath( int source, int destination ) 
{
	// std::cout <<"Graph::BiDijkstraShortestPath( int source, it destination )" << std::endl;
	// std::cout <<"Content_1: " << std::endl;
	std::unordered_map< int, int > distance;	
	std::unordered_map< int, int > reverse_distance;
	//int reverse_source = destination;
	
	std::unordered_set<int> close_forward;
	std::unordered_set<int> close_reverse;	

	for( int i = 0; i < vertices; ++i )
	{
		distance[ i ] = INT_MAX;
		reverse_distance[ i ] = INT_MAX;
	}

	distance[ source ] = 0; 
	reverse_distance[ destination ] = 0; 

	min_heap_.push( std::make_pair( distance[ source ] , source ) );
 	min_heap_reverse.push( std::make_pair( reverse_distance[ destination ], destination ) );
	auto mui =  INT_MAX;
				    
	std::cout <<"min_heap_size_0: " << min_heap_.size() << std::endl;
	std::cout <<"min_heap_reverse_size_0: " << min_heap_reverse.size() << std::endl;

	while( !min_heap_.empty() and !min_heap_reverse.empty() )
	{
		 std::cout <<"min_heap_size: " << min_heap_.size() << std::endl;
		 std::cout <<"min_heap_reverse_size: " << min_heap_reverse.size() << std::endl;
		 //std::cout <<"Here " << std::endl;
		 int min_distance = min_heap_.top().first; 
		 int min_distance_reverse = min_heap_reverse.top().first;
		 int min_dist = min_distance + min_distance_reverse; 
		
		 // std::cout <<"My mui: " << mui << std::endl; 
		 // std::cout <<"min_distance_1: " << min_dist << std::endl;
		 
		 if( min_dist >= mui ) { 
			 std::cout <<"min_distance: " << min_dist << std::endl;
			 return;
		 }

		 std::cout <<"min_distance: " << min_distance << std::endl;
		 std::cout <<"min_heap_: " << min_heap_.top().first << std::endl; 
		 int top_vertex = min_heap_.top().second;
		 min_heap_.pop();
		 close_forward.insert(top_vertex);
		 /*
		 //std::cout <<"Content_1: " << std::endl;
		 for( auto content : *adjcancy_list )
                         std::cout << content.first <<"," << content.second << " ";
                 std::cout << std::endl;
		 */

                 for( auto iter = adjcancy_list[ top_vertex ].begin(); iter != adjcancy_list[ top_vertex ].end(); ++iter ) {
			  
			 // std::cout <<"Here_1" << std::endl;
			 int vertex_v = (*iter).first;
			 //std::cout <<"Vertex_v'': " << vertex_v << std::endl;
			 
			 //if( close_forward.find(vertex_v) == close_forward.end() ) {
				int length = distance[ top_vertex ] + (*iter).second;
			 
			 	if( length < distance[ vertex_v ] ) 
			  	{
				  	// std::cout <<"Here0" << std::endl;
				  	distance[ vertex_v ] = length;
					// std::cout <<"Lenght_1: " << length << std::endl;
				  	min_heap_.push( std::make_pair( distance[ vertex_v ], vertex_v ) );
					// std::cout <<"Push " << std::endl;
				  	int new_length = length + reverse_distance[ vertex_v ];
				  	if( new_length < mui )
					{
						mui = new_length;
						std::cout <<"mui_2: " << mui << std::endl;
					}
					
					++relaxed_edges_1;
			    }
		 //}

			 // std::cout <<"End here_1" << std::endl;
		 }
		 //std::cout <<"Ultimate Test " << std::endl;

		 int top_vertex_reverse = min_heap_reverse.top().second;
		 min_heap_reverse.pop(); 
		 close_reverse.insert(top_vertex_reverse);

		 // std::cout <<"top_vertex_reverse: " << top_vertex_reverse << std::endl;
		 std::cout <<"adjacency: " << adjcancy_list[top_vertex_reverse ].size() << std::endl;
		 for( auto iter_1 = adjcancy_list[ top_vertex_reverse ].begin(); iter_1 != adjcancy_list[ top_vertex_reverse ].end(); ++iter_1 ) {

			 // std::cout <<"Here_2" << std::endl;

			 int vertex_v_reverse = (*iter_1).first;
			 std::cout <<"vertex_v_reverse: "<< vertex_v_reverse << std::endl; 
			 //if( close_reverse.find(vertex_v_reverse) == close_reverse.end() ) {
			 	//std::cout <<"vertex_v_reverse: "<< vertex_v_reverse << std::endl;
			 	int length_2 = reverse_distance[ top_vertex_reverse ] + (*iter_1).second;
			 	if( length_2 < reverse_distance[ vertex_v_reverse ] )
			 	{
				 	// std::cout <<"Here1 " << std::endl;
				 	reverse_distance[ vertex_v_reverse ] = length_2;
					// std::cout <<"Length_2: " << length_2 << std::endl;
				 	min_heap_reverse.push( std::make_pair( reverse_distance[ vertex_v_reverse ], vertex_v_reverse ));
				 	int my_new_length = length_2 + distance[ vertex_v_reverse ];
				 
				 	if( my_new_length < mui )
					{
						mui = my_new_length;
						std::cout <<"mui_1: " << mui << std::endl; 
					}
					++relaxed_edges_1;
			 	}
			 }
		 //}

		 //std::cout <<"End function " << std::endl;
	}

	/*
	std::cout <<"Distance BiDijkstraShortestPath" << std::endl;
	std::cout <<"["; ;
        for( auto content : distance )
                std::cout <<  content.first << " ";
        std::cout << "]" << std::endl;

	std::cout <<"Reverse Distance BiDijkstraShortestPath" << std::endl;
        std::cout <<"["; ;
        for( auto content : reverse_distance )
                std::cout <<  content.first << " ";
        std::cout << "]" << std::endl;
	*/
}
 
std::vector<int> Graph::randomSourceDest( int vertices ) 
{
	//std::cout <<"Calling Graph::randomSourceDest( int vertices )" << std::endl;
	//std::cout <<"num Vertices: " << vertices << std::endl;
	std::vector<int> my_vec;
	int source = rand() % vertices + 1;
	int destination = rand() % vertices + 1;
	my_vec.push_back( source );

	while( source == destination )
		destination = rand() % vertices + 1;

	my_vec.push_back( destination ); 

	//std::cout <<"End Graph::randomSourceDest( int vertices ) " << std::endl;
	return my_vec;
}

