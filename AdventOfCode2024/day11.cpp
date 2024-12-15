#include "splitter.hpp"
#include<iostream>
using namespace std;

template<typename T> void printM(vector<T>& matrix)
{
    for(const T &ele: matrix)
    {
        cout<<ele<<" ";
    }
    cout<<endl; 
}

int main()
{
    vector<vector<string>> matrix = aoc::get_matrix("input_exp.txt", " ");
    vector<string> input = matrix[0];
    vector<long> input_vec;

    for(const string& nums : input)
    {
        input_vec.push_back(stol(nums));
    }

    int iter = 75; 

    for(int i = 0; i<iter; i++)
    {
        vector<long> new_vec;

        for(auto &nums : input_vec)
        {
            if(nums==0)
                new_vec.push_back(1);
            else if (to_string(nums).length()%2==0)
            {
                int length = to_string(nums).length();
                //cout<<nums.substr(0,length/2)<<" "<<nums.substr(length/2)<<'\n';
                int num1 = stoi(to_string(nums).substr(0,length/2));
                int num2 = stoi(to_string(nums).substr(length/2));
                new_vec.push_back(num1);
                new_vec.push_back(num2);
            }
            else 
            {
                new_vec.push_back(nums*2024);
            }
        }

        input_vec = new_vec;
        //printM(input_vec);
        new_vec.clear();
         
    }

    cout<<"Size of stone line : "<< input_vec.size()<<endl;
}
