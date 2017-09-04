#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std; 

class Solution {
public:
    /**
     * @param A: An integer array.
     * @return: void
     */
    void rerange(vector<int> &A) {
        // write your code here
        int n=A.size();
        int positive=0, nagetive=0;
        for(vector<int>::iterator it=A.begin(); it!=A.end(); ++it){
            if(*it >= 0){ positive++; }
            else{ nagetive++; }
        }
        vector<int>::iterator odd_it=A.begin()+1;
        vector<int>::iterator even_it=A.begin();
        while(odd_it<=A.end() && even_it<=A.end()){
            if(positive >= nagetive){
                if(*even_it<0){
                    if(*odd_it>=0){
                        int tmp= *odd_it;
                        *odd_it = *even_it;
                        *even_it = tmp;
                        odd_it +=2;
                        even_it +=2;
                    }
                    else{
                        odd_it +=2;
                    }
                }
                else{
                    even_it +=2;
                }
            }
            else{
                if(*even_it>=0){
                    if(*odd_it<0){
                        int tmp= *odd_it;
                        *odd_it = *even_it;
                        *even_it = tmp;
                        odd_it +=2;
                        even_it +=2;
                    }
                    else{
                        odd_it +=2;
                    }
                }
                else{
                    even_it +=2;
                }
            }
        }
    }
    
};


int main(){
	int a[6]={-33,-19,30,26,21,-9};
	vector<int> A(a, a+6);
	Solution solu;
	solu.rerange(A);
	for(vector<int>::iterator it=A.begin(); it!=A.end(); ++it){
		cout << *it << " "; 
	}
	cout << endl;
	return EXIT_SUCCESS;
}
