#include <iostream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

const int d = 3;
const int XCoord = 0;
const int YCoord = 1;
const int ZCoord = 2;
const int Grid = 100;
string result_matrix_xz[1000][1000];
string result_matrix_xy[1000][1000];

struct point{
	int coord[3];
};

bool compare(int,int);
vector<int> computeInterval(int,int);
vector<point> compute2dSegment(point,point,int,int);
vector<point> reverse(vector<point>);
vector<point> mirrorBack(vector<point>,int);
vector<int> makeFold(int, int, int, int);
int returnIndex(vector<int> interval, int value);
int returnExists2DZ(point t, vector<point> projection);
int returnExists2DY(point t, vector<point> projection);
void checkProjection(vector<int> interval, vector<int> folds, point p, point q, int flag, vector<point> projection, vector<point> projection_other);



int main(){
	
	int x1_min, x1_max, x2_min, x2_max, y1, z1, y2, z2; 
	point a, b;
	vector<point> xz_projection, xy_projection, yz_projection;
		
	x1_min = 0; x1_max = 0; x2_min = 25; x2_max = 47; y1 = 14; z1 = 2; y2 = 114; z2 = 102;
	
	ofstream myfile("data1.xls");
	
	
	//cout << "after computeInterval for yz" << endl;
	int numOfYandZ = 17;
	int y_min, z_min;
	y_min = 15;
	z_min = 30;
	
	for (int u2 = y_min; u2 < y_min + numOfYandZ; u2++){
	for (int u3 = z_min; u3 < z_min + numOfYandZ; u3++){
	  
	  y1 = u2; y2 = y1 + numOfYandZ;
	  z1 = u3; z2 = z1 + numOfYandZ;
	  
	a.coord[YCoord] = y1;
	a.coord[ZCoord] = z1;
	b.coord[YCoord] = y2;
	b.coord[ZCoord] = z2;
	
	
	vector<int> folds = makeFold(y1, z1, y2, z2);
	vector<point> xz_3D_projection, xy_3D_projection;
	vector<int> fold_yz = computeInterval(a.coord[YCoord] + a.coord[ZCoord], b.coord[YCoord] + b.coord[ZCoord]);
	
	  
	for (int u = x1_min; u <= x1_max; u++){
		a.coord[XCoord] = u;
		for (int v = x2_min; v <= x2_max; v++){
			b.coord[XCoord] = v;
			if (v >= u){
				xz_projection = compute2dSegment(a, b, XCoord, ZCoord);
				xy_projection = compute2dSegment(a, b, XCoord, YCoord);
				checkProjection(fold_yz, folds, a, b, 0, xz_projection, xy_projection);
				checkProjection(fold_yz, folds, a, b, 1, xy_projection, xz_projection);
				
			}//if x2 is greater than or equal to x1
		}//iterate through x2
	}//iterate through x1
	
	
	myfile << "x1:" << x1_min << "to" << x1_max << endl;
	myfile << "x2:" << x2_min << "to" << x2_max << endl;
	myfile << "xz-xy" << endl;
	for(int i = x2_min; i <= x2_max; i++){
		myfile << endl;
		for(int j = x1_min; j <= x1_max; j++){
			myfile << result_matrix_xz[i][j] << "   ";
		}
	}
	myfile << endl << endl;
	myfile << endl << "xy-xz" << endl;
	for(int i = x2_min; i <= x2_max; i++){
		myfile << endl;
		for(int j = x1_min; j <= x1_max; j++){
			myfile << result_matrix_xy[i][j] << "   ";
		}
	}
	
	}//end of for loop iterate throught x2
	}//end of for loop iterate throught x1
	
	myfile.close();
	return 0;
}


int returnIndex(vector<int> interval, int value){
	int index;
	for(int j = 0; j<interval.size(); j++){
		if(interval[j] == value){
			index = j;
			break;
		}
	}
	return index;
}


int returnExists2DZ(point t, vector<point> projection){
		int flag = -1;
		for(int i = 0; i < projection.size(); i++){
			if(projection[i].coord[XCoord] == t.coord[XCoord] && projection[i].coord[ZCoord] == t.coord[ZCoord]){
				flag = 1;
			}
		}
	return flag;
}

int returnExists2DY(point t, vector<point> projection){
		int flag = -1;
		for(int i = 0; i < projection.size(); i++){
			if(projection[i].coord[XCoord] == t.coord[XCoord] && projection[i].coord[YCoord] == t.coord[YCoord]){
				flag = 1;
			}
		}
	return flag;
}



void checkProjection(vector<int> yz_interval, vector<int> folds, point p, point q, int flag, vector<point> projection, vector<point> projection_other){
	int dividing = q.coord[YCoord] - p.coord[YCoord], i, j;
	point on_fold_point_xy, on_fold_point_xz;
	int index = returnIndex(yz_interval, p.coord[YCoord] + p.coord[ZCoord]);
	vector<point> xz_projection, xy_projection;
	int previous_y = p.coord[YCoord], previous_z = p.coord[ZCoord], current_z, current_y;
	int fold_iterate = 1, on_fold_point_index;
	point entry_point = p, check_point, exit_point, saved_point, saved_point2;
	int f = -1;
	
	
	if (flag == 0){ //if xz projection first
		if(index < dividing){ 
			f = -2;
			current_z = previous_z;
		} // if first plane is xy
		
		while(fold_iterate < (folds.size() - 1)){
			if (f == -1){ // xz planes are handled
				current_z = previous_z + folds[fold_iterate] - folds[fold_iterate - 1];
				for (i = 0; i < projection.size(); i++){
					if (projection[i].coord[ZCoord] == current_z){
						check_point = projection[i];
						check_point.coord[YCoord] = previous_y;
						break;
					}
				}
				vector<point> xy_projection = compute2dSegment(check_point, q, XCoord, YCoord);
				
				for(int i = 0; i < xy_projection.size() - 1; i++){
					while (xy_projection[i + 1].coord[YCoord] == xy_projection[i].coord[YCoord]){
						i++;
					}	
					exit_point = xy_projection[i];
					break;
				}
				exit_point.coord[ZCoord] = current_z;
				
				vector<point> returnedSegment = compute2dSegment(entry_point, exit_point, XCoord, ZCoord);
				
				int check = returnExists2DZ(check_point, returnedSegment);
				if (check == -1){
					stringstream ss;
					ss << folds[fold_iterate];
					string stringFold;
					ss >> stringFold;
					result_matrix_xz[q.coord[XCoord]][p.coord[XCoord]] += stringFold + ".";
					
				}
			
				if ( (fold_iterate + 1) < ( folds.size() - 1) ){
					fold_iterate = fold_iterate + 1;
				}
				else break;
				entry_point = check_point;
				entry_point.coord[YCoord] = previous_y;
				previous_z = current_z;
				f = -2;
			} // xz planes are handled
			
			else{ //xy planes are handled
				current_y = previous_y + folds[fold_iterate] - folds[fold_iterate - 1];
				for (i = 0; i < projection.size(); i++){
					if ( (projection[i].coord[ZCoord] == current_z) && (projection[i+1].coord[ZCoord] - projection[i].coord[ZCoord] == 1) ){
						saved_point = projection[i];
						saved_point.coord[YCoord] = current_y; 
						break;
					}
				}
				vector<point> xy_segment = compute2dSegment(entry_point, saved_point, XCoord, YCoord);
				for (j = 0; j < xy_segment.size(); j++){
					if (xy_segment[j].coord[YCoord] == current_y){
						check_point = xy_segment[j];
						check_point.coord[ZCoord] = previous_z; 
						break;
					}
				}
				vector<point> xy_projection = compute2dSegment(check_point, q, XCoord, YCoord);
				for (j = 0; j < xy_projection.size(); j++){
					if (xy_projection[j+1].coord[YCoord] - xy_projection[j].coord[YCoord] == 1){
						saved_point2 = xy_projection[j];
						saved_point2.coord[ZCoord] = previous_z + folds[fold_iterate + 1] - folds[fold_iterate]; 
						break;
					}
				}
				vector<point> xz_segment = compute2dSegment(check_point, saved_point2, XCoord, ZCoord);
				for (j = 0; j < xz_segment.size(); j++){
					if (xz_segment[j+1].coord[ZCoord] - xz_segment[j].coord[ZCoord] == 1){
						exit_point = xz_segment[j];
						exit_point.coord[YCoord] = current_y; 
						break;
					}
				}
				vector<point> returnedSegment = compute2dSegment(entry_point, exit_point, XCoord, YCoord);
				
				int check = returnExists2DY(check_point, returnedSegment);
				if (check == -1){
					stringstream ss;
					ss << folds[fold_iterate];
					string stringFold;
					ss >> stringFold;
					result_matrix_xz[q.coord[XCoord]][p.coord[XCoord]] += stringFold + ".";
					
				}
				if ( (fold_iterate + 1) < ( folds.size() - 1) ){
					fold_iterate = fold_iterate + 1;
				}
				else break;
				entry_point = saved_point;
				entry_point.coord[YCoord] = current_y;
				previous_y = current_y;
				f = -1;
			}//xy planes are handled here
		}// while end
	} // if first follow the xz projection
	
	
	else{ //if first follow the xy projection
		if(index > dividing){ 
			f = -2;
			current_y = previous_y;
		} // if first plane is xz
		
		while(fold_iterate < (folds.size() - 1)){
			if (f == -1){ // xy planes are handled
				current_y = previous_y + folds[fold_iterate] - folds[fold_iterate - 1];
				for (i = 0; i < projection.size(); i++){
					if (projection[i].coord[YCoord] == current_y){
						check_point = projection[i];
						check_point.coord[ZCoord] = previous_z;
						break;
					}
				}
				vector<point> xz_projection = compute2dSegment(check_point, q, XCoord, ZCoord);
				
				for(int i = 0; i < xz_projection.size() - 1; i++){
					while (xz_projection[i + 1].coord[ZCoord] == xz_projection[i].coord[ZCoord]){
						i++;
					}	
					exit_point = xz_projection[i];
					break;
				}
				exit_point.coord[YCoord] = current_y;
								
				vector<point> returnedSegment = compute2dSegment(entry_point, exit_point, XCoord, YCoord);
				
				int check = returnExists2DY(check_point, returnedSegment);
				if (check == -1){
					stringstream ss;
					ss << folds[fold_iterate];
					string stringFold;
					ss >> stringFold;
					result_matrix_xz[q.coord[XCoord]][p.coord[XCoord]] += stringFold + ".";
					
				}
			
				if ( (fold_iterate + 1) < ( folds.size() - 1) ){
					fold_iterate = fold_iterate + 1;
				}
				else break;
				entry_point = check_point;
				entry_point.coord[ZCoord] = previous_z;
				previous_y = current_y;
				f = -2;
			} // xy planes are handled
			
			else{ //xz planes are handled
				current_z = previous_z + folds[fold_iterate] - folds[fold_iterate - 1];
				for (i = 0; i < projection.size(); i++){
					if ( (projection[i].coord[YCoord] == current_y) && (projection[i+1].coord[YCoord] - projection[i].coord[YCoord] == 1) ){
						saved_point = projection[i];
						saved_point.coord[ZCoord] = current_z; 
						break;
					}
				}
				
				vector<point> xz_segment = compute2dSegment(entry_point, saved_point, XCoord, ZCoord);
				
				for (j = 0; j < xz_segment.size(); j++){
					if (xz_segment[j].coord[ZCoord] == current_z){
						check_point = xz_segment[j];
						check_point.coord[YCoord] = previous_y; 
						break;
					}
				}
				
				vector<point> xz_projection = compute2dSegment(check_point, q, XCoord, ZCoord);
				
				for (j = 0; j < xz_projection.size(); j++){
					if (xz_projection[j+1].coord[ZCoord] - xz_projection[j].coord[ZCoord] == 1){
						saved_point2 = xz_projection[j];
						saved_point2.coord[YCoord] = previous_y + folds[fold_iterate + 1] - folds[fold_iterate]; 
						break;
					}
				}
				vector<point> xy_segment = compute2dSegment(check_point, saved_point2, XCoord, YCoord);
				
				for (j = 0; j < xy_segment.size(); j++){
					if (xy_segment[j+1].coord[YCoord] - xy_segment[j].coord[YCoord] == 1){
						exit_point = xy_segment[j];
						exit_point.coord[ZCoord] = current_z; 
						break;
					}
				}
				
				vector<point> returnedSegment = compute2dSegment(entry_point, exit_point, XCoord, ZCoord);
				
				int check = returnExists2DZ(check_point, returnedSegment);
				if (check == -1){
					stringstream ss;
					ss << folds[fold_iterate];
					string stringFold;
					ss >> stringFold;
					result_matrix_xz[q.coord[XCoord]][p.coord[XCoord]] += stringFold + ".";
					
				}
				if ( (fold_iterate + 1) < ( folds.size() - 1) ){
					fold_iterate = fold_iterate + 1;
				}
				else break;
				entry_point = saved_point;
				entry_point.coord[ZCoord] = current_z;
				previous_z = current_z;
				f = -1;
			}//xz planes are handled here
		}// while end
	} // if first follow the xy projection
}

vector<int> makeFold(int a1, int b1, int a2, int b2){
	vector<int> fold_yz = computeInterval(a1 + b1, a2 + b2 - 1);
	//cout << "yz-interval" << endl;
	//for(int i = 0; i < fold_yz.size(); i++)
	//			cout << fold_yz[i] << " ";
	//cout << endl;
	
	int current_value = a1 + b1;
	int current_index = 0;
	vector<int> allFolds;
	allFolds.push_back(a1 + b1);
	int dividing = a2 - a1;
	
	for (int i = 0; i < fold_yz.size(); i++){
		if (fold_yz[i] == current_value){
			current_index = i;
			break;
		}
	}
	int previous_value = current_value, previous_index = current_index;
	for (int i = 0; i < fold_yz.size(); i++){
		current_value++;
		for (int j = 0; j < fold_yz.size(); j++){
			if (fold_yz[j] == current_value){
				current_index = j;
				break;
			}
		}
		
		if( (current_index < dividing && previous_index >= dividing) || (current_index >= dividing && previous_index < dividing))
			allFolds.push_back(current_value);
		
		previous_value = current_value;
		previous_index = current_index;
	}
	//allFolds.push_back( a2 + b2);
	return allFolds;	
}
	
vector<point> compute2dSegment(point p1,point p2, int dim1, int dim2){
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
      
		/*cout << endl << "Sorted interval: " << endl;
			for(int i=0; i<interval.size(); i++)
				cout << interval[i] << " ";
 
		cout << endl << endl;*/
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


bool compare(int n1, int n2){ //return true if n1 is less than n2

	while(true)
	{
		int div = 2;
		bool divides1 = true;
		bool divides2 = true;
		
		while(divides1 && divides2)
		{	
			divides1 = n1%div == 0;
			divides2 = n2%div == 0;
			
			div *= 2;
		}
		
		if(divides1 && !divides2)
			return false;
		else if(divides2 && !divides1)
			return true;
		else
		{
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
			if(compare(interval[j],interval[min]))
			min = j;    
		}
  
	int temp = interval[i];
	interval[i] = interval[min];
	interval[min] = temp;
	}
	return interval; 
}
