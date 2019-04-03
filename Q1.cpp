#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

template <typename T1, typename T2>
bool pairSort(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2)
{
    return p1.first > p2.first || (!(p1.first < p2.first) && (p1.second > p2.second));
}	

int main(){
    std::ifstream file("jobs.txt");
    int n;
    file >> n;
    std::vector<std::pair<int, int>> vec(n);
    int weight, length;
    while(file >> weight){
	file >> length;
	vec.push_back(std::make_pair(weight - length, weight));
    }
    std::sort(vec.begin(), vec.end(), pairSort<int, int>);
    int cumlen = 0;
    uint64_t completion = 0;
    for(auto& p: vec){
	cumlen += p.second - p.first;
	completion += cumlen * p.second;
    }
    std::cout << completion << std::endl;
    return 0;
} 
