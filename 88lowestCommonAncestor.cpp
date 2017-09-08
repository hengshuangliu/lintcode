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
		* 根据有序（递增）序列生成平衡二叉查找树
		* @param nums : 递增序列
		*/
	public:
		/**
		* 根据有序（递增）序列生成平衡二叉查找树
		* @param nums : 递增序列
		*/
		TreeNode* sortedArrayToBST(vector<int>& nums) {
			return sortedSeqToBST(nums, 0, nums.size() - 1);
		}
		/**
		* 内存回收
		*/
		void free(TreeNode* root) {
			if(root == NULL) return ;
			free(root->left);
			free(root->right);
			delete root;
		}
	private:
		/**
		* 根据有序（递增）序列的某一子序列生成平衡二叉查找树
		* @param nums  : 递增序列
		* @param start : 子序列开始位置（包含）
		* @param end   : 子序列结束位置（包含）
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

class Solution {
	public:
		/**
		 * @param root: The root of the binary search tree.
		 * @param A and B: two nodes in a Binary.
		 * @return: Return the least common ancestor(LCA) of the two nodes.
		 */
		TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *A, TreeNode *B) {
			// write your code here
			stack<TreeNode* > stk_a;
			stack<TreeNode* > stk_b;
			bool a_success = false, b_success = false;
			TreeNode* p = root;
			TreeNode* pre = root;
			stk_a.push(p);
			stk_b.push(p);
			while(1) {
				if(p == A && !a_success) {
					a_success = true;
				}
				if(p == B && !b_success) {
					b_success = true;
				}
				if(a_success && b_success) {
					break;
				}
				if(p->left && pre != p->left && pre != p->right) {
				    if(!a_success){
				        stk_a.push(p->left);
				    }
					if(!b_success){
					    stk_b.push(p->left);
					}
					p = p->left;
				} else if(p->right && pre != p->right) {
				    if(!a_success){
				        stk_a.push(p->right);
				    }
					if(!b_success){
					    stk_b.push(p->right);
					}
					p = p->right;
				} else {
					pre = p;
					if(!a_success){
					    stk_a.pop();
					    p = stk_a.top();
					}
					if(!b_success){
					    stk_b.pop();
					    p = stk_b.top();
					}
				}
			}
			while(stk_a.size() != stk_b.size()) {
				if(stk_a.size() > stk_b.size()){
					stk_a.pop();
				}else{
					stk_b.pop();
				}
			}
			while( stk_a.top() != stk_b.top() ){
				stk_a.pop();
				stk_b.pop();
			}
			return stk_a.top();
		}
};


int main() {
	int a[10] = {1, 2 ,3 ,4, 5, 6, 7, 8, 9, 10};
	vector<int> i_v(a, a+10);
	BSTConstructor bst;
	TreeNode* root = bst.sortedArrayToBST(i_v);
	Solution so;
	TreeNode* result = so.lowestCommonAncestor(root, root->left, root->left->right);
	cout << result->val << endl;
	BSTIterator bst_it(root);
	cout << endl;
	while(bst_it.hasNext()) {
		cout << bst_it.next()->val << endl;
	}
	bst.free(root);
	return EXIT_SUCCESS;
}
