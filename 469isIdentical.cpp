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
 
//设计实现一个带有下列属性的二叉查找树的迭代器：
//元素按照递增的顺序被访问（比如中序遍历）
//next()和hasNext()的询问操作要求均摊时间复杂度是O(1)
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

//检查两棵二叉树是否等价。等价的意思是说，首先两棵二叉树必须拥有相同的结构，并且每个对应位置上的节点上的数都相等。
//
//样例
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
