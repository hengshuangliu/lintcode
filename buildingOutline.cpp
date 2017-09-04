#include<iostream>
#include<vector>
#include <cstdlib>
#include <algorithm>
#include <queue>

using namespace std;
//样例
//给出三座大楼：
//[
//  [1, 3, 3],
//  [2, 4, 4],
//  [5, 6, 1]
//]
//外轮廓线为：
//[
//  [1, 2, 3],
//  [2, 4, 4],
//  [5, 6, 1]
//]

//将大楼的边按照进楼和出楼的方式存储，然后按照X坐标大小从小到大排列，
//并开始从左至右扫描edges，当遇到边edge是进楼时，则往堆中插入该栋大楼，
//并扫描将堆顶元素中无效元素进行删除（该楼的右侧小于当前edge），
// 然后依次找到上次的edge与当前edge以及当前最大高度的大楼轮廓，
// 如果上次的高度与本次高度一致则只需要延续上个edge的右侧。

struct heightCmp {
	bool operator()(const vector<int>& a, const vector<int>& b) {
		return a[2] < b[2] ? true : (a[2] == b[2] ? (a[1] < b[1]) : false);
	}
};

struct indexCmp {
	bool operator()(const vector<int>& a, const vector<int>& b) {
		if(a[0] < b[0]){
			return true;
		}
		else if(a[0] == b[0]){
			if( a[3] == b[3]){
				return a[2] > b[2];
			}
			else{
				return a[3] == 0;
			}
		}
		else{
			return false;
		}
	}
};

class Solution {
	public:
		/**
		 * @param buildings: A list of lists of integers
		 * @return: Find the outline of those buildings
		 */
		vector<vector<int> > buildingOutline(vector<vector<int> > &buildings) {
			// write your code here
			vector<vector<int> > result;
			if(buildings.size() == 0) {
				return result;
			}
			vector<vector<int> > edges;
			vector<int> edge(4, 0);
			for(int i=0; i<buildings.size(); ++i) {
				edge[0] = buildings[i][0];
				edge[1] = buildings[i][1];
				edge[2] = buildings[i][2];
				edge[3] = 0;                 // first wall.
				edges.push_back(edge);
				edge[0] = buildings[i][1];
				edge[3] = 1;                 // last wall.
				edges.push_back(edge);
			}
			sort(edges.begin(), edges.end(), indexCmp());
			for(int j=0; j<edges.size(); ++j) {
				cout << edges[j][0] << " " << edges[j][1] << " " << edges[j][2] << " " << edges[j][3] <<endl;
			}
			cout << endl;
			priority_queue<vector<int>, vector<vector<int> >, heightCmp> p_q;
			vector<int> res(3, 0);
			for(vector<vector<int> >::iterator it = edges.begin(); it!=edges.end(); ++it) {
				if(!p_q.empty()){
					cout << p_q.top()[0] << " " << p_q.top()[1] << " " << p_q.top()[2] << " " << p_q.top()[3] << endl;
				}

				if((*it)[3] == 0) {
					p_q.push((*it));
					if((*it)[2] > res[2]) {
						if(res[2] != 0 && res[0] != (*it)[0]) {
							res[1] = (*it)[0];
							result.push_back(res);
							res[0] = (*it)[0];
							res[2] = (*it)[2];
						} else {
							res[0] = (*it)[0];
							res[2] = (*it)[2];
						}
					}
				} else {
					if( !p_q.empty() && (*it)[2] == p_q.top()[2]) {
						if( (*it)[0] == p_q.top()[1] ) {
							p_q.pop();
							res[1] = (*it)[0];
							result.push_back(res);
							while( !p_q.empty() && (*it)[0] >= p_q.top()[1] ) {
								p_q.pop();
							}
							res[0] = (*it)[0];
							res[2] = p_q.empty() ? 0 : p_q.top()[2];
						}
					}
				}
			}
			return result;
		}
};

int main() {
	int tmp[15] = {1,2,2,2,3,2,3,4,2,4,5,2,5,6,7};
	vector<vector<int> > buildings;
	for(int i=0; i<5; ++i) {
		vector<int> t(tmp+3*i, tmp+3*i+3);
		buildings.push_back(t);
	}
	for(int j=0; j<buildings.size(); ++j) {
		cout << buildings[j][0] << " " << buildings[j][1] << " " << buildings[j][2] << endl;
	}
	Solution so;
	vector<vector<int> > result = so.buildingOutline(buildings);
	cout << endl;
	for(int j=0; j<result.size(); ++j) {
		cout << result[j][0] << " " << result[j][1] << " " << result[j][2] << endl;
	}
	return EXIT_SUCCESS;
}

