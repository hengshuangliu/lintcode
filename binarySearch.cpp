#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std; 

class Solution {
public:
    /**
     * @param nums: The integer array.
     * @param target: Target number to find.
     * @return: The first position of target. Position starts from 0. 
     */
    int binarySearch(vector<int> &array, int target) {
        // write your code here
        int left = 0, right=array.size() - 1;
        int mid = (left + right) / 2;
        int find = -1;
		while(left <= right){
			if(target > array[mid]){
				left = mid + 1;
				mid = (left + right)/2;
			}
			else if(target < array[mid]){
				right = mid - 1;
				mid = (left + right)/2;
			}
			else{
				find = mid;
			    right = mid - 1;
			    mid = (left + right)/2;
			}
		}
		if(find != -1){
		    return find;
		}
        return -1;
    }
};

int main(){
	int a[7] = {1, 2, 3, 4, 5, 6, 10};
	vector<int> array(a,a + 7);
	Solution solu;
	cout << solu.binarySearch(array, 3) << endl;
	return EXIT_SUCCESS;
}
