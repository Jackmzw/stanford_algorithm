#include <iostream>
#include <fstream>
#include <vector>

uint64_t count_inversion(std::vector<int>& vec, int left, int right){
	if(left == right){
		return 0;
	}  // initializer
	int mid = (left + right) / 2;
	uint64_t count1 = count_inversion(vec, left, mid);
	uint64_t count2 = count_inversion(vec, mid+1, right);
	// merge sort and count inversions
	int i = 0, j = 0;
	uint64_t count = 0;
	std::vector<int> temp;
	while((i < mid - left + 1) && (j < right - mid)){
		if(vec[i+left] <= vec[j+mid+1]){
			count += j;
			temp.push_back(vec[i+left]);
			i++;
		} else{
			temp.push_back(vec[j+mid+1]);
			j++;
		}
	}

	if(i == mid - left + 1){
		while(j < right - mid){
			temp.push_back(vec[j+mid+1]);
			j++;
		}
	} 
	if(j == right - mid){
		count += (mid - left + 1 - i) * j;
		while(i < mid - left + 1){
			temp.push_back(vec[i+left]);
			i++;
		}
	}
	for(int k = 0; k < right - left + 1; ++k){
		vec[k+left] = temp[k];
	}
	uint64_t sum = count1 + count2 + count;
	return sum;
}

int main(){
	std::ifstream f("./IntegerArray.txt");
	int m;
	std::vector<int> vec;

	while(f >> m){
		vec.push_back(m);
	} 
	uint64_t res = count_inversion(vec, 0, vec.size()-1);
	std::cout << res << std::endl;
	return 0;
}


