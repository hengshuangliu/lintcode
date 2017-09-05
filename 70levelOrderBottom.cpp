#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <queue>
#include <algorithm>

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

//给出一棵二叉树，返回其节点值从底向上的层次序遍历
//（按从叶节点所在层到根节点所在的层遍历，然后逐层从左往右遍历）
//给出一棵二叉树 {3,9,20,#,#,15,7},
//
//    3
//   / \
//  9  20
//    /  \
//   15   7
//按照从下往上的层次遍历为：
//
//[
//  [15,7],
//  [9,20],
//  [3]
//]
class Solution {
	public:
		/*
		 * @param root: A tree
		 * @return: buttom-up level order a list of lists of integer
		 */
		vector<vector<int> > levelOrderBottom(TreeNode * root) {
			// write your code here
			vector<vector<int> > result;
			vector<int> lever;
			queue<TreeNode* > q;
			TreeNode* lever_s;
			TreeNode* lever_n;
			if(root) {
				q.push(root);
				lever_s = root;
				lever_n = root;
			} else {
				return result;
			}
			while(!q.empty()) {
				if(!lever.empty() && q.front() == lever_s) {
					result.push_back(lever);
					lever.clear();
				}
				if(q.front()->left || q.front()->right) {
					if(q.front()->left) {
						q.push(q.front()->left);
						if(q.front() == lever_n) {
							lever_s = q.front()->left;
							lever_n = lever_s;
						}
					}
					if(q.front()->right) {
						q.push(q.front()->right);
						if(q.front() == lever_n) {
							lever_s = q.front()->right;
							lever_n = lever_s;
						}
					}
					lever.push_back(q.front()->val);
					q.pop();
				} else {
					lever.push_back(q.front()->val);
					q.pop();
					lever_n = q.front();
				}

			}
			result.push_back(lever);
			reverse(result.begin(), result.end());
			return result;
		}
};

int main() {
	int a[10] = {1, 2 ,3 ,4, 5, 6, 7, 8, 9, 10};
	vector<int> i_v(a, a+10);
	BSTConstructor bst;
	TreeNode* root = bst.sortedArrayToBST(i_v);
	Solution so;
	vector<vector<int> > result = so.levelOrderBottom(root);
	for(int i=0; i<result.size(); ++i) {
		for(int j=0; j<result[i].size(); ++j) {
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	BSTIterator bst_it(root);
	cout << endl;
	while(bst_it.hasNext()) {
		cout << bst_it.next()->val << endl;
	}
	bst.free(root);
	return EXIT_SUCCESS;
}
