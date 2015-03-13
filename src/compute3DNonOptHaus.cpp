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
vector<point> makeSegment(point, point, vector<point>, vector<point>);
float hausdorffDistance(vector<point>, point, point);

int main(){
  
	point p1, q1, p2, q2;
	p1.coord[XCoord] = 0; p1.coord[YCoord] = 1; p1.coord[ZCoord] = 2;
    q1.coord[XCoord] = 8; q1.coord[YCoord] = 9; q1.coord[ZCoord] = 7; 
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
	vector<point> XYSegment = compute2dSegment(p1, q1, XCoord, YCoord);
	cout << "xy_projection" << endl;
	for (int i = 0; i < XYSegment.size(); i++)
		cout << XYSegment[i].coord[XCoord] << " " << XYSegment[i].coord[YCoord] << " " << XYSegment[i].coord[ZCoord] << endl;
	cout << endl;
	vector<point> ZXSegment = compute2dSegment(p1, q1, XCoord, ZCoord);
	cout << "zx_projection" << endl;
	for (int i = 0; i < ZXSegment.size(); i++)
		cout << ZXSegment[i].coord[XCoord] << " " << ZXSegment[i].coord[YCoord] << " " << ZXSegment[i].coord[ZCoord] << endl;
	cout << endl;
	vector<point> Segment3d = makeSegment(p1, q1, XYSegment, ZXSegment);
	cout << "segment" << endl;
	for (int i = 0; i < Segment3d.size(); i++)
		cout << Segment3d[i].coord[XCoord] << " " << Segment3d[i].coord[YCoord] << " " << Segment3d[i].coord[ZCoord] << endl;
	cout << endl;
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

vector<point> makeSegment(point a, point b, vector<point> XYSegment, vector<point> ZXSegment){
	vector<point> returned3DSegment;
	point current_point = a;
	int iterator = 0, XY_iterator = 0, ZX_iterator = 0;
	returned3DSegment.push_back(current_point);
	for(iterator = a.coord[XCoord] + a.coord[YCoord] + a.coord[ZCoord]; iterator < b.coord[XCoord] + b.coord[YCoord] + b.coord[ZCoord]; iterator++){
		if(XYSegment[XY_iterator + 1].coord[XCoord] - XYSegment[XY_iterator].coord[XCoord] == 1){
			if(ZXSegment[ZX_iterator + 1].coord[XCoord] - ZXSegment[ZX_iterator].coord[XCoord] == 1){
				current_point.coord[XCoord]++;
				returned3DSegment.push_back(current_point);
				XY_iterator++; ZX_iterator++;
			} // if first projection has X and second projection has also X
			else{
				if (a.coord[ZCoord] < b.coord[ZCoord])
					current_point.coord[ZCoord]++;
				else
					current_point.coord[ZCoord]--;
				returned3DSegment.push_back(current_point);
				ZX_iterator++;
			} // if first projection has X and second projection has Z
		} // if first projection has X
		else{
			current_point.coord[YCoord]++;
			returned3DSegment.push_back(current_point);
			XY_iterator++;
		} // if first projection has Y
	}
	return returned3DSegment;
}

vector<point> compute2dSegment(point p1,point p2, int dim1, int dim2){
  
	//cout << "in compute2dSegment" << endl;
  
	if(p1.coord[dim1] == p2.coord[dim1] && p1.coord[dim2] == p2.coord[dim2]){
    
		vector<point> segment;
		segment.push_back(p1);
		return segment;
	}  
	else if(p1.coord[dim1] >= p2.coord[dim1] && p1.coord[dim2] >= p2.coord[dim2]){
    
		return reverse(compute2dSegment(p2,p1,dim1,dim2));
	}
	else if(p2.coord[dim1] < p1.coord[dim1] && p2.coord[dim2] > p1.coord[dim2]){
   
		p1.coord[dim1] *= -1;
		p2.coord[dim1] *= -1;
    
		return mirrorBack(compute2dSegment(p1,p2,dim1,dim2),dim1);
	}
	else if(p1.coord[dim1] < p2.coord[dim1] && p2.coord[dim2] < p1.coord[dim2]){
    
		p1.coord[dim1] *= -1;
		p2.coord[dim1] *= -1;
    
		return reverse(mirrorBack(compute2dSegment(p2,p1,dim1,dim2),dim1));
	}
	else{
       
		vector<int> interval = computeInterval(p1.coord[dim1] + p1.coord[dim2], p2.coord[dim1] + p2.coord[dim2]-1);//(p1.coord[XCoord]+p1.coord[YCoord]+p1.coord[ZCoord],p2.coord[XCoord]+p2.coord[YCoord]+p2.coord[ZCoord]-1);//
      
		//cout << endl << "Sorted interval: " << endl;
			//for(int i=0; i<interval.size(); i++)
				//cout << interval[i] << " ";
 
				//cout << endl << endl;
      
				int dividingLine = p2.coord[dim1] - p1.coord[dim1];
      
				vector<point> segment;
				point currentPoint = p1;
      
				segment.push_back(p1);
      
				for(int i = p1.coord[dim1] + p1.coord[dim2]; i<p2.coord[dim1] + p2.coord[dim2]; i++){//(int i = p1.coord[XCoord]+p1.coord[YCoord]+p1.coord[ZCoord]; i<p2.coord[XCoord]+p2.coord[YCoord]+p2.coord[ZCoord]; i++){//
	
					int index;
					for(int j = 0; j<interval.size(); j++){
	
						if(interval[j] == i){
							index = j;
							break;
						}
					}
      
					if(index < dividingLine)
						currentPoint.coord[dim1]++;
					else
						currentPoint.coord[dim2]++;
      
					segment.push_back(currentPoint);
	
				}
				
				return segment;
			}
}

vector<point> reverse(vector<point> seg){
  
	vector<point> revSeg;
	for(int i=seg.size()-1; i>=0; i--)
		revSeg.push_back(seg[i]);
  
	return revSeg;
}

vector<point> mirrorBack(vector<point> seg,int dim){
  
	for(int i=0; i<seg.size(); i++)
		seg[i].coord[dim] *= -1;
    return seg;
}


string stringPoint(point p){
  
	string output = "(";
  
	stringstream s;
	s << p.coord[0];
	output += s.str();
  
	for(int i =1; i<d; i++){
		stringstream ss;
		ss << p.coord[i];
		output = output + ", " + ss.str();
	}
  
	output += ")";
  
	return output;
}

bool modifiedCompare(int n1, int n2){//Adding 32 to odd numbers
    
	if(n1%2 == 1 || n1%2 == -1) n1 += 32;
	if(n2%2 == 1 || n2%2 == -1) n2 += 32;
  
	return compare(n1,n2);
}

bool compare(int n1, int n2){ //return true if n1 is less than n2

	while(true){

		int div = 2;
		bool divides1 = true;
		bool divides2 = true;
		
		while(divides1 && divides2){	
			
			divides1 = n1%div == 0;
			divides2 = n2%div == 0;
			
			div *= 2;
		}
		
		if(divides1 && !divides2)
			return false;
		else if(divides2 && !divides1)
			return true;
		else{
			n1--;
			n2--;
		}
	}
}


vector<int> computeInterval(int a,int b){
  
	vector<int> interval;
	int size = b-a+1;
 
	for(int i=a; i<=b; i++)
		interval.push_back(i);
 
	for(int i=0; i<size; i++){
   
		int min = i;
   
		for(int j=i+1; j<size; j++){
    
			if(modifiedCompare(interval[j],interval[min]))
				min = j;    
		}
  
		//cout << "Min: " << interval[min] << endl;
		int temp = interval[i];
		interval[i] = interval[min];
		interval[min] = temp;
	}
 
	return interval;  
}

