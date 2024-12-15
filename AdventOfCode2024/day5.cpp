#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
int main (int argc, char *argv[]) {
	std::vector<std::string> prob_inputs;
	std::ifstream input_stream("input_exp.txt");
	if(!input_stream) std::cerr << "Can't open";
	std::string line = "";
	std::vector<std::string> map_inputs;
	std::vector<std::string> *vector_ptr = &prob_inputs;
	while(getline(input_stream, line))
	{
		if(line == "<PAGE BREAK>")
		{
			vector_ptr = &map_inputs;
			continue;
		}
		vector_ptr->push_back(line);
		
	}

////for(int i=0; i<map_inputs.size(); i++ ) 
////{
////	std::cout<< map_inputs[i]<<std::endl;
////}
	std::set<std::string> set_value(map_inputs.begin(), map_inputs.end());
	for(const std::string &elem : set_value)
	{
		std::cout<< elem;
	}

	
}
