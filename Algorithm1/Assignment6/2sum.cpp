#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

bool exist_2sum(int t, const std::unordered_set<int64_t>& set){
    for(int64_t k : set){
        if(2*k != t && set.find(t-k) != set.end()){
            return true;
        }
    }
    return false;
}

int main(){
    std::ifstream file("./algo1-programming_prob-2sum.txt");
    int64_t item;
    std::vector<int64_t> vec;
    while(file >> item){
        vec.push_back(item);
     }
    std::cout << vec.size() << std::endl;
    std::unordered_set<int64_t> set(vec.begin(), vec.end());
    std::cout << set.size() << std::endl;
    int count = 0;
    for(int i = -10000; i <= 10000; ++i){
        if(exist_2sum(i, set)){
               count++;
               }
        std::cout << i << std::endl;
    } 
    std::cout << count << std::endl;
    return 0;
}
