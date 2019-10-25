
#include "Dijkstra.c++"

int main() { 

	Graph G;
	std::ifstream my_file;
	G.buildGraph( my_file );
	std::vector<int>  source_dest = G.randomSourceDest( G.num_vert );
	
	std::cout <<"Source: " << source_dest[ 0 ] << " " << "Destination: "<< source_dest[ 1 ] << std::endl;
	/*
	for( int i = 0; i < G.num_vert; ++i )
		G.DijkstraShortestPath( i );
	*/
	
	clock_t begin_0 = clock();
	G.DijkstraShortestPath(  0 /*source_dest[ 0 ], source_dest[ 1 ] */, 3144927  );
	clock_t end_0 = clock();
	std::cout <<"Relaxed_edges: " <<  G.relaxed_edges << std::endl;
	
	
	double duration_0 = double( end_0 - begin_0 ) / CLOCKS_PER_SEC; 
	std::cout <<"DijkstraShortestPath duration: " <<  duration_0 << std::endl;
	
	clock_t begin_1 = clock();
	G.BiDijkstraShortestPath( 0 /*source_dest[ 0 ]*/ , /*source_dest[ 1 ]*/ 3144927 );
	clock_t end_1 = clock();

	std::cout <<"Relaxed_edges: " <<  G.relaxed_edges_1 << std::endl;
	
	double duration_1 = double( end_1 - begin_1 ) /  CLOCKS_PER_SEC;
	std::cout <<"BiDijkstraShortestPath duration: " << duration_1 << std::endl;
	 
	//G.DijkstraShortestPath( 3, 4 );
	//G.DijkstraShortestPath( 0 , 1048571 );
	
	return 0;
}
