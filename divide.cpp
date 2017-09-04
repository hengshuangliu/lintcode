#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std; 

class Solution {
public:
    /*
     * @param dividend: the dividend
     * @param divisor: the divisor
     * @return: the result
     */
    int divide(long long dividend, long long divisor) {
        // write your code here
        long long div = abs(divisor);
        cout << abs(dividend) << endl;
        long long divid = abs(dividend);
        cout << divid << endl;
//        if(div == 0){
//        	return 2147483647;
//		}
//		if(dividend==-2147483648 && divisor==-2147483648){  
//            return 1;  
//        }
//        if(dividend == -2147483648L && div == 1){
//        	return 2147483647;
//		}
		long long result = 0;
		long long r_t = 1;
		while(div <= divid){
		    div = div << 1;
		    r_t = r_t << 1;
		}
		while((r_t = r_t >> 1) >= 1){
			div = div >> 1;
			if(divid >= div){
				result += r_t;
				divid -= div;
			}
		}
		if(dividend < 0 && divisor < 0) return result;
		else if(dividend < 0 && divisor > 0) return -result;
		else if(dividend > 0 && divisor < 0) return -result;
		else return result;
    }
};

int main(){
	Solution solu;
	int a = -2147483648;
	cout << solu.divide(a, 1) << endl;
	return EXIT_SUCCESS;
}
