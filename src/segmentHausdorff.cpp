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

const int d = 2;
const int XCoord = 0;
const int YCoord = 1;
const int ZCoord = 2;
const int Grid = 10;

float maxHausdorffDistance = 0.0; //hausdorff

struct point{
 
	int coord[2];
};


string stringPoint(point);
bool compare(int,int);
vector<int> computeInterval(int,int);
vector<point> compute2dSegment(point,point,int,int);
vector<point> reverse(vector<point>);
vector<point> mirrorBack(vector<point>,int);
void showSegment(vector<point> segment, point p1, point p2);
bool modifiedCompare(int n1, int n2);
float computeHausdorff(point, float, point); // hausdorff


int main(){
  
	//cout << "Enter the coordinates of the points." << endl;
  
	
	//int x1,x2,y1,y2;
  
	//cin >> x1 >> y1 >> x2 >> y2;
  
    for (int u = 0; u < Grid; u++){
		for (int v = 0; v < Grid; v++){
			for (int r = 0; r < Grid; r++){
				for (int s = 0; s < Grid; s++){
					point p,q;
					p.coord[XCoord] = u;
					p.coord[YCoord] = v;
					q.coord[XCoord] = r;
					q.coord[YCoord] = s;
					if ( (u == r) && (v == s) || (u == r)) ;
					else 
						showSegment(compute2dSegment(p,q,XCoord,YCoord),p,q);
     			}
			}
		}
	}
	cout << "The Hausdorff Distance :" << setiosflags(ios::fixed) << maxHausdorffDistance << endl;

	return 0;
}

void showSegment(vector<point> segment, point p1, point p2){
   
	/*cout << "Segment from " + stringPoint(p1) + " to " + stringPoint(p2) + ": " << endl;
 
	for(int i=0; i<segment.size(); i++){
		if(i < segment.size()-1)
			cout << stringPoint(segment[i]) + " -> ";
  
		else
			cout << stringPoint(segment[i]);
     
		if((i+1)%14 == 0) cout << endl;
	}
	cout << endl;*/
}


float computeHausdorff(point p, float slope, point p1){ //compute hausdorff distance

	float intercept = p1.coord[YCoord] - (slope * p1.coord[XCoord]);
	float x = (p.coord[XCoord] + p.coord[YCoord] - intercept) / (slope + 1);
	float y = p.coord[XCoord] + p.coord[YCoord] - x;
		
	return sqrt( ( (x - p.coord[XCoord]) * (x - p.coord[XCoord]) ) + ( (y - p.coord[YCoord]) * (y - p.coord[YCoord]) ) );
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
				
				//call for hausdorff distance
				float slope = (float) (p2.coord[YCoord] - p1.coord[YCoord]) / (p2.coord[XCoord] - p1.coord[XCoord]);
				cout << "The slope is :" << slope << endl;
				//cout << "x1 =" << p1.coord[XCoord] << " y1 =" << p1.coord[YCoord] << " x2 =" << p2.coord[XCoord] << " y2 =" << p2.coord[YCoord] << endl;
				//cout << "Segment from " + stringPoint(p1) + " to " + stringPoint(p2) + ": " << endl;
				for(int m = 0; m < segment.size(); m++){
					float hausdorffDistance = computeHausdorff(segment[m], slope, p1); //Hausdorff distance
   
					if (hausdorffDistance > maxHausdorffDistance)
						maxHausdorffDistance = hausdorffDistance;
					/*if(m < segment.size()-1)
						cout << stringPoint(segment[m]) + " -> ";
  
					else
						cout << stringPoint(segment[m]);
     
					if((m+1)%14 == 0) cout << endl;*/
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
