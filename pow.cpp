#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std; 

class Solution {
public:
    /**
     * @param x the base number
     * @param n the power number
     * @return the result
     */
    double myPow(double x, int n) {
        // Write your code here
        double pow=1.0;
        double base = x;
        int n_p = abs(n);
        pow = (n_p&1) ? x : pow;
        while(n_p=(n_p>>1)){
        	cout << n_p << endl;
            base *= base;
            if(n_p&1){
                pow *= base;
            }
        }
        return (n<0)?(1.0/pow):pow;
    }
};


int main(){;
	Solution solu;
	cout << solu.myPow(2, 10) << endl;
	return EXIT_SUCCESS;
}
