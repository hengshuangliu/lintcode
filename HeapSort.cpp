#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std;

class Solution {
public:
    void heapSort(vector<int> &lists) {
        int n = lists.size();
        // creat initial heap;
        for(int i=(n-2)/2; i>=0; i--){
        	adjustHeap(lists, i, n);
		}
		// heap sort.
		int tmp;
		for(int j=n-1; j>0; j--){
			tmp = lists[0];
			lists[0] = lists[j];
			lists[j] = tmp;
			adjustHeap(lists, 0, --n);
		}
    }
    
    void adjustHeap(vector<int> &lists, int k, int n){  // k is root index, n is length of lists.
    	int parent_v = lists[k];  
    	int child = 2 * k + 1;   // left children at initial state.
    	int parent = k;
    	while(child < n){
    		if(child < n - 1 && lists[child] < lists[child + 1]){ // choose bigger one between two children.
    			child ++;
			}
			if(parent_v >= lists[child]){
				break;
			}
			else{
				lists[parent] = lists[child];
				parent = child;
				child = 2 * parent + 1;
			}
		}
		lists[parent] = parent_v;
	}
};


int main(){
	vector<int> int_v;
	int tmp;
	while(cin >> tmp){
		int_v.push_back(tmp);
		if(cin.get() == '\n'){
			break;
		}
	}
	Solution sol;
	sol.heapSort(int_v);
	for(vector<int>::iterator it=int_v.begin(); it!=int_v.end(); ++it){
		cout << *it << " ";
	}
	return EXIT_SUCCESS;
}
