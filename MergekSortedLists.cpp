#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std;



/**
 * Definition of ListNode
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *         this->val = val;
 *         this->next = NULL;
 *     }
 * }
 */
 
class ListNode {
public:
     int val;
     ListNode *next;
     ListNode(int val){
        this->val = val;
        this->next = NULL;
     }
 };
 
class Solution {
public:
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // write your code here
        int n=lists.size();
        ListNode *p = NULL;
        ListNode *p_n = NULL;
        if(n==0){
        	return p;
		}
        for(int i=0; i<n; ++i){
        	if(!lists[i]){
        		if(i < n-1){
        			lists[i] = lists[n-1];
        			--i;
				}
        		n--;
			}
		}
		// creat initial heap.
		for(int j=n/2 - 1; j>=0; --j){
			adjustHeap(lists, j, n);
		}
		// mergeK lists.
		p = lists[0];
		p_n = lists[0];
        while(n >= 1){
        	if(!(lists[0]->next)){
        		lists[0] = lists[n-1];
        		n--;
        		if(n==0){
        			break;
				}
        		adjustHeap(lists, 0, n);	
			}
			else{
				lists[0] = lists[0]->next;
				adjustHeap(lists, 0, n);
			}
			p_n ->next = lists[0];
			p_n = lists[0];
		}
		return p;
    }
    
    void adjustHeap(vector<ListNode *> &lists, int k, int n){   // K root index.
    	ListNode *tmp = lists[k];
    	int i = k;
    	int j = 2 * i + 1;
    	while(j < n){
    		if(j < n-1 && lists[j]->val > lists[j+1]->val){
    			j++;
			}
			if(tmp->val < lists[j]->val){
				break;
			}else{
				lists[i] = lists[j];
				i = j;
				j = 2 * i + 1;
			}
		}
		lists[i] = tmp;
	}
};

int main(){
	ListNode list1(4);
	ListNode *p = &list1;
	for(int i=5; i<10; ++i){
		ListNode *tmp = new ListNode(i);
		p->next = tmp;
		p = tmp;
	}
	ListNode list2(1);
	p = &list2;
	for(int i=1; i<4; ++i){
		ListNode *tmp = new ListNode(2*i);
		p->next = tmp;
		p = tmp;
	}
	p = NULL;
	vector<ListNode *> lists;
	lists.push_back(&list1);
	lists.push_back(&list2);
	lists.push_back(p);
	Solution solu;
	ListNode * result=solu.mergeKLists(lists);
	p = result;
	while(p){
		cout << p->val << endl;
		p = p->next;
	}
	return EXIT_SUCCESS;
}

