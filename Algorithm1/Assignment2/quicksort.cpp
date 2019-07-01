;// Example program
#include <iostream>
#include <fstream>
#include <vector>

int partition(std::vector<int>& vec, int l, int r)
{
    int i = l + 1;
    int temp;
    for(int j=i; j<=r; j++)
    {
        if(vec[j] < vec[l])
        {
            int temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
        }
    }
    temp = vec[l];
    vec[l] = vec[i-1];
    vec[i-1] = temp;
    
    return (i - 1);
}

int median_index(std::vector<int>& vec, int l, int r, int m){
    if(vec[l] < vec[r]){
        if(vec[m] < vec[l]){
            return l;
        } else{
            if(vec[m] < vec[r]){
                return m;
            } else{
                return r;
            }
        }
    } else{
        if(vec[m] < vec[r]){
            return r;
        } else{
            if(vec[m] < vec[l]){
                return m;
            } else{
                return l;
            }
        }
    }
}

uint64_t count_quicksort(std::vector<int>& vec, int l, int r)
{
    if(l >= r)
    {
        return 0;
    }
    
    uint64_t res = r - l;

    /*
    // Final element as pivot
    std::swap(vec[l], vec[r]);
    */

    // median of three
    int m = (l + r) / 2;
    int m_ind = median_index(vec, l, r, m);
    std::swap(vec[l], vec[m_ind]);
    
    int p = partition(vec, l, r); 
    uint64_t res1 = count_quicksort(vec, l, p-1);
    uint64_t res2 = count_quicksort(vec, p+1, r);
    
    res += res1 + res2;
    return res;
}

int main()
{
    std::ifstream f("./QuickSort.txt");
    int m;
    std::vector<int> vec;

    while(f >> m){
        vec.push_back(m);
    } 
    uint64_t res = count_quicksort(vec, 0, vec.size()-1);
    std::cout << res << std::endl;
    return 0;
}
