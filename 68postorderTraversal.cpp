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

//设计实现一个带有下列属性的二叉查找树的迭代器：
//元素按照递增的顺序被访问（比如中序遍历）
//next()和hasNext()的询问操作要求均摊时间复杂度是O(1)
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

//后序遍历： 左-右-根// 非递归；
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
