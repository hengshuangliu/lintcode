#include<iostream>
#include<vector>
#include <cstdlib>
#include <algorithm>
#include<stack>

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

class Solution {
	public:
		/**
		 * @param root: The root of the binary search tree.
		 * @param node: insert this node into the binary search tree
		 * @return: The root of the new binary search tree.
		 */
		//给定一棵二叉查找树和一个新的树节点，将节点插入到树中。
		//给出如下一棵二叉查找树，在插入节点6之后这棵二叉查找树可以是这样的：
		//
		//  2             2
		// / \           / \
		//1   4   -->   1   4
		//   /             / \ 
		//  3             3   6
		TreeNode* insertNode(TreeNode* root, TreeNode* node) {
			// write your code here
			if(root == NULL) {
				return node;
			}
			TreeNode* p = root;
			while(1) {
				if(node->val < p->val) {
					if(p->left == NULL) {
						p->left = node;
						break;
					}
					p = p->left;
				} else {
					if(p->right == NULL) {
						p->right = node;
						break;
					}
					p = p->right;
				}
			}
			return root;
		}
		
		
		// 验证二叉树的正确性; 
		bool isValidBST(TreeNode * root) {
			// write your code here
			if(root == NULL) {
				return true;
			}
			if(root->left != NULL ){
				if( (root->left->val >= root->val) || !isValidBST(root->left)){
					return false;
				}
			}
			if(root->right != NULL){
				if( (root->right->val <= root->val) || !isValidBST(root->right))
				return false;	
			}
			return true;
		}
		
		bool isValidBSTs(TreeNode * root, int& min, int& max){
			if(root == NULL) {
				return true;
			}
			int min_t, max_t;
			if(root->left != NULL ){
				if( !isValidBSTs(root->left, min_t, max_t) || (max_t >= root->val) ){
					return false;
				}
				min = min_t;
			}
			else{
				min = root->val;
			}
			if(root->right != NULL){
				if( !isValidBSTs(root->right, min_t, max_t) || (min_t <= root->val) ){
					return false;
				}
				max = max_t;	
			}
			else{
				max = root->val;
			}
			return true;
	}	
};

int main() {

	return EXIT_SUCCESS;
}
