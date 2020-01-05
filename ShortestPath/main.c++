
//#include "Dijkstra.c++"
#include "Dijkstra.c++"

int main()
{

	Graph G;
	std::string path = "DataFile";
	std::ifstream my_file;

	for (const auto &entry : file_sys::directory_iterator(path))
	{
		my_file.open(entry.path(), std::ios_base::in);
		std::cout << "File: " << entry.path() << std::endl;
		G.buildGraph(my_file);

		int counter = 0;
		int total_relaxed_edges = 0;
		int av_relaxed_edges = 0;
		double total_duration = 0.0;
		double average_duration = 0.0;

		// Variables for Bidirectional Dijkstra algorithm
		int total_relaxed_edges_1 = 0;
		int av_relaxed_edges_1 = 0;
		double total_duration_1 = 0.0;
		double average_duration_1 = 0.0;

		std::set<std::pair<double, int>> averages;
		std::set<std::pair<double, int>> averages_1;
		int counter_1 = 0;
		std::unordered_set<int> my_source_set = G.generateSource(G.num_vert);
		std::unordered_set<int> my_destinations = G.generateDestination(G.num_vert, my_source_set);

		for (auto iter = my_source_set.begin(); iter != my_source_set.end(); ++iter)
		{
			++counter;

			for (auto it = my_destinations.begin(); it != my_destinations.end(); ++it)
			{
				//std::cout <<"Running" << std::endl;
				std::cout << "Counter: " << counter << " "
						  << "Counter_1: " << ++counter_1 << " "
						  << "Source: " << *iter << " "
						  << "Destination: " << *it << std::endl;

				clock_t begin_0 = clock();
				G.DijkstraShortestPath(*iter, *it);
				clock_t end_0 = clock();
				double duration_0 = double(end_0 - begin_0) / CLOCKS_PER_SEC;

				//std::cout << std::endl;
				//std::cout <<"DijkstraShortestPath duration: " <<  duration_0 << std::endl;
				//std::cout <<"Relaxed_edges: " << G.relaxed_edges << std::endl;

				total_duration += duration_0;
				total_relaxed_edges += G.relaxed_edges;
				G.relaxed_edges = 0;

				//std::cout << std::endl;
				clock_t begin_1 = clock();
				G.BiDijkstraShortestPath(*iter, *it);
				clock_t end_1 = clock();

				double duration_1 = double(end_1 - begin_1) / CLOCKS_PER_SEC;
				//std::cout <<"BiDijkstraShortestPath duration: " << duration_1 << std::endl;
				//std::cout <<"Relaxed_edges: " <<  G.relaxed_edges_1 << std::endl;

				total_duration_1 += duration_1;
				total_relaxed_edges_1 += G.relaxed_edges_1;
				G.relaxed_edges_1 = 0;
			}

			// Getting averages from the Dijkstra algorithm
			average_duration = (total_duration / 100.0);
			av_relaxed_edges = (total_relaxed_edges / 100);
			averages.insert(std::make_pair(average_duration, av_relaxed_edges));
			total_duration = 0;
			total_relaxed_edges = 0;

			// Getting averages from then Bidirectional Dijkstra algorithm
			average_duration_1 = (total_duration_1 / 100.0);
			av_relaxed_edges_1 = (total_relaxed_edges_1 / 100);
			averages_1.insert(std::make_pair(average_duration_1, av_relaxed_edges_1));
			total_duration_1 = 0;
			total_relaxed_edges_1 = 0;
			counter_1 = 0;
		}

		std::cout << "Dijkstra averages set " << std::endl;
		double total_dur_0 = 0;
		int total_edge_0 = 0;
		for (auto iter = averages.begin(); iter != averages.end(); ++iter)
		{

			total_dur_0 += (*iter).first;
			total_edge_0 += (*iter).second;
			// std::cout <<"Average durations: " << (*iter).first <<" " <<"Average Relaxed edges: "<< (*iter).second << std::endl;
		}

		std::cout << std::endl;
		std::cout << "Final Average time: " << (total_dur_0 / 10) << std::endl;
		std::cout << "Final Average Edges relaxed: " << (total_edge_0 / 10) << std::endl;
		std::cout << std::endl;

		// Bidirectiona averages set
		std::cout << "Bidirectional averages set" << std::endl;
		double total_dur = 0;
		int total_ed = 0;
		for (auto iter = averages_1.begin(); iter != averages_1.end(); ++iter)
		{

			total_dur += (*iter).first;
			total_ed += (*iter).second;
			//std::cout <<"Average durations: " << (*iter).first <<" " <<"Average Relaxed edges: "<< (*iter).second << std::endl;
		}

		std::cout << std::endl;
		std::cout << "Final Average time: " << (total_dur / 10) << std::endl;
		std::cout << "Final Average Edge relaxed: " << (total_ed / 10) << std::endl;
		/*
		double duration_0 = double( end_0 - begin_0 ) / CLOCKS_PER_SEC; 
		std::cout <<"DijkstraShortestPath duration: " <<  duration_0 << std::endl;
	
		clock_t begin_1 = clock();
		G.BiDijkstraShortestPath( source_dest[ 0 ] , source_dest[ 1 ] );
		clock_t end_1 = clock();

		std::cout <<"Relaxed_edges: " <<  G.relaxed_edges_1 << std::endl;
	
		double duration_1 = double( end_1 - begin_1 ) /  CLOCKS_PER_SEC;
		std::cout <<"BiDijkstraShortestPath duration: " << duration_1 << std::endl;
	
		//G.DijkstraShortestPath( 3, 4 );
		//G.DijkstraShortestPath( 0 , 1048571 );
		*/

		break;
		std::cout << std::endl;
		// G.eraseContainers();
		// break;
	}

	return 0;
}
