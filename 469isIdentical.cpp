#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>

using namespace std;

class TreeNode {
	public:
		int val;
		TreeNode *left, *right;
		TreeNode(int val) {
			this->val = val;
			this->left = this->right = NULL;
		}
};

class BSTConstructor {
		/**
		* �������򣨵�������������ƽ����������
		* @param nums : ��������
		*/
	public:
		/**
		* �������򣨵�������������ƽ����������
		* @param nums : ��������
		*/
		TreeNode* sortedArrayToBST(vector<int>& nums) {
			return sortedSeqToBST(nums, 0, nums.size() - 1);
		}
		/**
		* �ڴ����
		*/
		void free(TreeNode* root) {
			if(root == NULL) return ;
			free(root->left);
			free(root->right);
			delete root;
		}
	private:
		/**
		* �������򣨵��������е�ĳһ����������ƽ����������
		* @param nums  : ��������
		* @param start : �����п�ʼλ�ã�������
		* @param end   : �����н���λ�ã�������
		*/
		TreeNode* sortedSeqToBST(vector<int>& nums, int start, int end){
			if( start > end ){
				return NULL;
			}
			int mid = (start + end)/2;
			TreeNode * root = new TreeNode(nums[mid]);
			root -> left = sortedSeqToBST(nums, start, mid-1);
			root -> right = sortedSeqToBST(nums, mid+1, end);
			return root;
		}
};



/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 * Example of iterate a tree:
 * BSTIterator iterator = BSTIterator(root);
 * while (iterator.hasNext()) {
 *    TreeNode * node = iterator.next();
 *    do something for node
 */
 
//���ʵ��һ�������������ԵĶ���������ĵ�������
//Ԫ�ذ��յ�����˳�򱻷��ʣ��������������
//next()��hasNext()��ѯ�ʲ���Ҫ���̯ʱ�临�Ӷ���O(1)
class BSTIterator {
public:
	stack<TreeNode *> bstStack;
	
    //@param root: The root of binary tree.
    BSTIterator(TreeNode *root) {
        // write your code here
        while( root!= NULL ){
        	bstStack.push(root);
        	root = root->left;
		}
        
    }

    //@return: True if there has next node, or false
    bool hasNext() {
        // write your code here
        return !bstStack.empty();
    }
    
    //@return: return next node
    TreeNode* next() {
        // write your code here
        TreeNode *tmp = bstStack.top();
        TreeNode *p = bstStack.top()->right;
        bstStack.pop();
        while(p != NULL){
        	bstStack.push(p);
        	p = p->left;
		}
		return tmp;
    }
};

//������ö������Ƿ�ȼۡ��ȼ۵���˼��˵���������ö���������ӵ����ͬ�Ľṹ������ÿ����Ӧλ���ϵĽڵ��ϵ�������ȡ�
//
//����
//    1             1
//   / \           / \
//  2   2   and   2   2
// /             /
//4             4
class Solution {
public:
    /*
     * @param a: the root of binary tree a.
     * @param b: the root of binary tree b.
     * @return: true if they are identical, or false.
     */
    bool isIdentical(TreeNode * a, TreeNode * b) {
        // write your code here
        if(a == NULL && b == NULL){
        	return true;
		}
		else if( a != NULL && b != NULL){
			return (a->val == b->val) && isIdentical(a->left, b->left) && isIdentical(a->right, b->right);
		}
		else{
			return false;
		}
    }
};

int main(){
	int a[10] = {1, 2 ,3 ,4, 5, 6, 7, 8, 9, 10};
	vector<int> i_v(a, a+10);
	BSTConstructor bst;
	TreeNode* root = bst.sortedArrayToBST(i_v);
	Solution so;
	cout << so.isIdentical(root, root) << endl;
	BSTIterator bst_it(root);
	while(bst_it.hasNext()){
		cout << bst_it.next()->val << endl;
	}
	bst.free(root);
	return EXIT_SUCCESS;
}
