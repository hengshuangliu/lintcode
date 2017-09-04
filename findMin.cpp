#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std; 

class Solution {
public:
    /**
     * @param nums: a rotated sorted array
     * @return: the minimum number in the array
     */
    int findMin(vector<int> &nums) {
        // write your code here
        int left = 0, right = nums.size() - 1;
		int mid = (left + right) / 2;
		while(left <= right){
			if(left == right){
				return nums[left];
			}
			else if(right - 1 == left){
				return (nums[left] > nums[right]) ? nums[right] : nums[left];
			}
			if(nums[mid] > nums[right]){
				left = mid;
				mid = (left + right) / 2;
			}
			else{
				right = mid;
				mid = (left + right) / 2;
			}
		}
		return nums[mid];
    }
};

int main(){
	int a[7] = {4, 5, 6, 10, 1, 2, 3 };
	vector<int> array(a,a + 7);
	Solution solu;
	cout << solu.findMin(array) << endl;
	return EXIT_SUCCESS;
}
