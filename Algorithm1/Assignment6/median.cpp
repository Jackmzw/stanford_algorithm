#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

int main(){
    std::ifstream file("Median.txt");
    int item;
    std::priority_queue<int, std::vector<int>, std::greater<int> > minh;
    std::priority_queue<int> maxh; 
    file >> item;
    maxh.push(item);
    int res = item % 10000;
    while(file >> item){
        int temp = maxh.top();
        if(item < temp){
            maxh.push(item);
            if(maxh.size() - minh.size() > 1){
                maxh.pop();
                minh.push(temp);
            }
        } else{
            minh.push(item);
            if(minh.size() > maxh.size()){
                maxh.push(minh.top());
                minh.pop();
            }
        }
        res = (res + maxh.top()) % 10000;
    }
    std::cout << res << std::endl;
    return 0;
}
