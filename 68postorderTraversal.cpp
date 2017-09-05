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
		TreeNode* sortedSeqToBST(vector<int>& nums, int start, int end) {
			if( start > end ) {
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
			while( root!= NULL ) {
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
			while(p != NULL) {
				bstStack.push(p);
				p = p->left;
			}
			return tmp;
		}
};

//��������� ��-��-��// �ǵݹ飻
class Solution {
	public:
		/*
		 * @param root: A Tree
		 * @return: Preorder in ArrayList which contains node values.
		 */
		void postorderTraversal(TreeNode * root) {
			// write your code here
			stack<TreeNode* > stk;
			TreeNode* p = root;
			if(!p){
			    return result;
			}
			stk.push(p);
			TreeNode* stk_top;
			TreeNode* stk_pre; 
			while(!stk.empty()) {
				stk_top = stk.top();
				if((stk_top->left == NULL && stk_top->right == NULL) || (stk_top->left == stk_pre || stk_top->right == stk_pre)){
					cout << stk_top->val << endl;
					stk.pop();
					stk_pre = stk_top;
				}
				else{
					if(stk_top->right){
						stk.push(stk_top->right);
					}
					if(stk_top->left){
						stk.push(stk_top->left);
					}
				}
			}
		}
};

int main() {
	int a[10] = {1, 2 ,3 ,4, 5, 6, 7, 8, 9, 10};
	vector<int> i_v(a, a+10);
	BSTConstructor bst;
	TreeNode* root = bst.sortedArrayToBST(i_v);
	Solution so;
	so.postorderTraversal(root);
	BSTIterator bst_it(root);
	cout << endl;
	while(bst_it.hasNext()) {
		cout << bst_it.next()->val << endl;
	}
	bst.free(root);
	return EXIT_SUCCESS;
}
