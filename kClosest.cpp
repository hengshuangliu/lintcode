#include<iostream>
#include<vector>
#include <cstdlib>

using namespace std;

//给定一些 points 和一个 origin，从 points 中找到 k 个离 origin 最近的点。
//按照距离由小到大返回。如果两个点有相同距离，则按照x值来排序；
//若x值也相同，就再按照y值排序。
//
//给出 points = [[4,6],[4,7],[4,4],[2,5],[1,1]], origin = [0, 0], k = 3
//返回 [[1,1],[2,5],[4,4]]

struct Point {
	int x;
	int y;

	Point() : x(0), y(0) {}

	Point(int a, int b) : x(a), y(b) {}
};

class Solution {
	public:
		/**
		 * @param points a list of points
		 * @param origin a point
		 * @param k an integer
		 * @return the k closest points
		 */
		vector<Point> kClosest(vector<Point>& points, Point& origin, int k) {
			// Write your code here
			int n = points.size();
			// build initial heap.
			for(int i = n/2 - 1; i >= 0; --i) {
				adjustHeap(points, i, n, origin);
			}
			// find kClosest.
			vector<Point> result;
			for(int j=0; j<k; ++j) {
				result.push_back(points[0]);
				points[0] = points[n-1-j];
				adjustHeap(points, 0, n-1-j, origin);
			}
			return result;
		}

		void adjustHeap(vector<Point>& points, int k, int n, Point& origin) {  // k is root index, n is the length.
			Point tmp = points[k];
			int p = k;
			int c = 2 * k + 1;
			while(c < n) {
				if(c < n-1 && closer(points[c+1], points[c], origin)) {
					c ++;
				}
				if(closer(tmp, points[c], origin)) {
					break;
				} else {
					points[p] = points[c];
					p = c;
					c = 2 * p + 1;
				}
			}
			points[p] = tmp;
		}

		bool closer(const Point& a, const Point& b, const Point& origin) {
			int a_d = (a.x - origin.x)*(a.x - origin.x) + (a.y - origin.y)*(a.y - origin.y);
			int b_d = (b.x - origin.x)*(b.x - origin.x) + (b.y - origin.y)*(b.y - origin.y);
			if(a_d == b_d) {
				if(a.x < b.x) {
					return true;
				} else if(a.x > b.x) {
					return false;
				} else {
					if(a.y < b.y) {
						return true;
					} else {
						return false;
					}
				}
			} else if(a_d < b_d) {
				return true;
			} else {
				return false;
			}
		}
};


int main() {
	struct Point points[5] = {Point(4, 6), Point(4, 7), Point(4, 4), Point(2, 5), Point(1, 1)};
	struct Point origin(0, 0);
	vector<Point> p(points, points + 5);
	Solution solu;
	vector<Point> result=solu.kClosest(p, origin, 3);
	// show
	for(vector<Point>::iterator it=result.begin(); it != result.end(); ++it) {
		cout << it->x << " " << it->y << endl;
	}
	return EXIT_SUCCESS;
}

