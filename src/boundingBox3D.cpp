#include <iostream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

const int d = 3;
const int XCoord = 0;
const int YCoord = 1;
const int ZCoord = 2;
const int Grid = 1;

float maxHausdorffDistance = 0.0; //hausdorff

struct point{
 
	int coord[3];
};


string stringPoint(point);
bool compare(int,int);
vector<int> computeInterval(int,int);
vector<point> compute2dSegment(point,point,int,int);
vector<point> reverse(vector<point>);
vector<point> mirrorBack(vector<point>,int);
bool modifiedCompare(int n1, int n2);
vector<point> makeSegment(point, point);
float hausdorffDistance(vector<point>, point, point);


int main(){
  
	point p1, q1, p2, q2;
	p1.coord[XCoord] = 0; p1.coord[YCoord] = 0; p1.coord[ZCoord] = 0;
    q1.coord[XCoord] = 10; q1.coord[YCoord] = 11; q1.coord[ZCoord] = 12; 
    p2.coord[XCoord] = 4; p2.coord[YCoord] = 5; p2.coord[ZCoord] = 6;
    q2.coord[XCoord] = 13; q2.coord[YCoord] = 14; q2.coord[ZCoord] = 1; 
    /*for (int u = 0; u < Grid; u++){
		for (int v = 0; v < Grid; v++){
			for (int r = 0; r < Grid; r++){
				for (int s = 0; s < Grid; s++){
					point p,q;
					p.coord[XCoord] = u;
					p.coord[YCoord] = v;
					q.coord[XCoord] = r;
					q.coord[YCoord] = s;
					if ( (u == r) && (v == s) || (u == r)) ;
					else ;
						//showSegment(compute2dSegment(p,q,XCoord,YCoord),p,q);
     			}
			}
		}
	}*/
	//vector<point> Segment3d = makeSegment(p1, q1); 
	
	vector<point> Segment3d = makeSegment(p1, q1);
	float maxHausdorffDistance = hausdorffDistance(Segment3d, p1, q1);
	cout << "The Hausdorff Distance :" << setiosflags(ios::fixed) << maxHausdorffDistance << endl;

	return 0;
}


float hausdorffDistance(vector<point> Segment3d, point a, point b){
	int _a = a.coord[XCoord] - b.coord[XCoord];
	int _b = a.coord[YCoord] - b.coord[YCoord];
	int _c = a.coord[ZCoord] - b.coord[ZCoord];
	int _d, _e, _f, _g, _h, _i;
	for(int i = 0; i < Segment3d.size(); i++){
		_d = a.coord[XCoord] - Segment3d[i].coord[XCoord];
		_e = a.coord[YCoord] - Segment3d[i].coord[YCoord];
		_f = a.coord[ZCoord] - Segment3d[i].coord[ZCoord];
		_g = (_e * _c) - (_f * _b);
		_h = ( (_d * _c) - (_a * _f) ) * (-1);
		_i = (_d * _b) - (_e * _a);
		float distance = (sqrt(_g * _g + _h * _h + _i * _i)) / (sqrt(_a * _a + _b * _b + _c * _c));
		if(distance > maxHausdorffDistance)
			maxHausdorffDistance = distance;
	}
	return maxHausdorffDistance;
}



vector<point> makeSegment(point a, point b){
	vector<point> returned3Dsegment;
	int iterator = 0;
	point current_point = a;
	for (iterator = a.coord[XCoord]; iterator <= b.coord[XCoord]; iterator++){
		current_point.coord[XCoord]++;
		returned3Dsegment.push_back(current_point);
	} // take all x movements
	
	for (iterator = a.coord[YCoord]; iterator <= b.coord[YCoord]; iterator++){
		current_point.coord[YCoord]++;
		returned3Dsegment.push_back(current_point);
	} // take all y movements
	
	for (iterator = a.coord[ZCoord]; iterator <= b.coord[ZCoord]; iterator++){
		current_point.coord[ZCoord]++;
		returned3Dsegment.push_back(current_point);
	} 
	return returned3Dsegment;
}
