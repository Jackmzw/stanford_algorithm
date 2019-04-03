#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

typedef std::pair<double, int> ip;

int main(){
    std::ifstream file("jobs.txt");
    int n;
    file >> n;
    std::vector<std::pair<double, int>> vec(n);
    int weight, length;
    while(file >> weight){
	file >> length;
	vec.push_back(std::make_pair(static_cast<double>(weight) / length, weight));
    }
    std::sort(vec.begin(), vec.end(), std::greater<ip>());
    int cumlen = 0;
    uint64_t completion = 0;
    for(auto& p: vec){
	cumlen += int(p.second / p.first + 0.5);
	completion += cumlen * p.second;
    }
    std::cout << completion << std::endl;
    return 0;
} 
