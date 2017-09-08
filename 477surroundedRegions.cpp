#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>

using namespace std;

//给一个二维的矩阵，包含 'X' 和 'O', 找到所有被 'X' 围绕的区域，并用 'X' 填充满
//样例
//给出二维矩阵：
//
//X X X X
//X O O X
//X X O X
//X O X X
//把被 'X' 围绕的区域填充之后变为：
//
//X X X X
//X X X X
//X X X X
//X O X X

class Solution {
	public:
		/**
		 * @param board a 2D board containing 'X' and 'O'
		 * @return void
		 */
		void surroundedRegions(vector<vector<char> >& board) {
			// Write your code here
			int n = board.size();
			int m = board[0].size();
			for(int i=0; i<n; ++i) {
				if(board[i][0] == 'O') {
					dfs(board, i, 0, n, m);
				}
				if(board[i][m-1] == 'O') {
					dfs(board, i, m-1, n, m);
				}
			}
			for(int j=0; j<m; ++j) {
				if(board[0][j] == 'O') {
					dfs(board, 0, j, n, m);
				}
				if(board[n-1][j] == 'O') {
					dfs(board, n-1, j, n, m);
				}
			}
			
			for(int i=0; i<n; ++i) {
				for(int j=0; j<m; ++j) {
					if(board[i][j] == 'Y') {
						board[i][j] = 'O';
					} else if(board[i][j] == 'O') {
						board[i][j] = 'X';
					}
				}
			}
		}

		void dfs(vector<vector<char> >& board, int x, int y, int n, int m) {
			board[x][y] = 'Y';
			if( x>=0 && x+1<n && y>=0 && y<m && board[x+1][y] == 'O' ) {
				dfs(board, x+1, y, n, m);
			}
			if( x>=1 && x<n && y>=0 && y<m && board[x-1][y] == 'O' ) {
				dfs(board, x-1, y, n, m);
			}
			if( x>=0 && x<n && y>=0 && y+1<m && board[x][y+1] == 'O' ) {
				dfs(board, x, y+1, n, m);
			}
			if( x>=0 && x<n && y>=1 && y<m && board[x][y-1] == 'O' ) {
				dfs(board, x, y-1, n, m);
			}
		}
};

int main() {
	char b[16] = {'X', 'X', 'X', 'X',\
	              'X', 'O', 'O', 'X',\
	              'X', 'X', 'O', 'X',\
	              'X', 'O', 'X', 'X'
	             };
	vector<vector<char> > board;
	for(int i=0; i<4; ++i) {
		board.push_back(vector<char>(b+4*i, b+4*i+4));
	}
	int n=board.size();
	int m=board[0].size();
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			cout << board[i][j];
		}
		cout << endl;
	}
	Solution so;
	so.surroundedRegions(board);
	cout << endl;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			cout << board[i][j];
		}
		cout << endl;
	}
	return EXIT_SUCCESS;
}
