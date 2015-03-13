#include <iostream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

const int d = 3;
const int XCoord = 0;
const int YCoord = 1;
const int ZCoord = 2;

const int DimLength = 75;

struct point{
 
  int coord[3];
  
};



string stringPoint(point);
bool compare(int,int);
vector<int> computeInterval(int,int);
int min(int, int);
vector<point> compute2dSegment(point,point,int,int);
vector<point> reverse(vector<point>);
vector<point> mirrorBack(vector<point>,int);
vector<point> compute3dSegment(point,point);
vector<point> moreY(point,point);
vector<point> moreZ(point,point);
void showSegment(vector<point>,point,point);
int countSingleZs(vector<point>, int);
void checkIntersections(vector<point>,vector<point>);
int getNextSplitNode(vector<point> seg, int index);
int getNextMultiMove(vector<point> seg, int index);
int getEndOfMultiMove(vector<point> seg, int index);
vector<point> newMoreZ(point p1, point p2);
bool modifiedCompare(int n1, int n2);
vector<point> transitionSegments(point p1, point p2);


int main(){
  
 point p1,p2;
 /*p1.coord[XCoord] = 4;
 p1.coord[YCoord] = 4;
 p1.coord[ZCoord] = 0;
 
 p2.coord[XCoord] = 3;
 p2.coord[YCoord] = 2;
 p2.coord[ZCoord] = 4;
 
    compute3dSegment(p1,p2);*/
 
 //cout << stringPoint(p1) << endl << stringPoint(p2) << endl;
    
 /*vector<vector<point> > segments;
 
 for(int x1 = 0; x1 < DimLength; x1++){
   for(int y1 = 0; y1<DimLength; y1++){
     for(int x2 = 0; x2 < DimLength; x2++){
      for(int y2 = 0; y2<DimLength; y2++){
	
	  p1.coord[XCoord] = x1;
	  p1.coord[YCoord] = y1;
	  p1.coord[ZCoord] = 0;
      
	  p2.coord[XCoord] = x2;
	  p2.coord[YCoord] = y2;
	  p2.coord[ZCoord] = DimLength-1;
     
	  //vector<point> segment = compute3dSegment(p1,p2);
          segments.push_back(transitionSegments(p1,p2));
	  
          //cout << endl;// << endl;
	  
      }
     }
   }
     
     cout << "All segs computed for x1 = " << x1 << endl;
 }
    
    for(int i=0; i<segments.size(); i++){
        
        for(int j = i+1; j<segments.size(); j++){
            
            checkIntersections(segments[i],segments[j]);
        }
    }*/
    
    cout << "Enter the coordintes: ";
    cin >> p1.coord[XCoord] >> p1.coord[YCoord] >> p1.coord[ZCoord] >> p2.coord[XCoord] >> p2.coord[YCoord] >> p2.coord[ZCoord];
    showSegment(transitionSegments(p1,p2),p1,p2);
    
    
    
    /*point p3, p4;
    p3.coord[XCoord] = 0;
    p3.coord[YCoord] = 0;
    p3.coord[ZCoord] = 3;
    
    p4.coord[XCoord] = 0;
    p4.coord[YCoord] = 4;
    p4.coord[ZCoord] = 0;
    
    vector<point> yzProj = compute2dSegment(p3,p4,YCoord,ZCoord);
    for (int i=0; i<yzProj.size(); i++) {
        cout << stringPoint(yzProj[i]) << "   ";
    }
    cout << endl << endl;
    
    int split = getNextSplitNode(yzProj,0);
    
    if(split > -1)
      cout << "Next split node: " << stringPoint(yzProj[split]) << " at index " << split << endl;
    else
      cout << "No Split Nodes." << endl;
 
    int multiMove = getNextMultiMove(yzProj,0);
    
    if(multiMove < yzProj.size()){
      
      int end = getEndOfMultiMove(yzProj,multiMove);
      cout << "Next multi move: " << stringPoint(yzProj[multiMove]) << " at index " << multiMove << " and ends at " << stringPoint(yzProj[end]) << endl;
    }
    else
      cout << "No multi moves." << endl;*/
 
 return 0; 
  
}

void checkIntersections(vector<point> seg1,vector<point> seg2){
    
    //cout << "In intersections" << endl;
    vector<point> intersection;
    
    for(int i=0; i<seg1.size(); i++){
        
        point p = seg1[i];
        
        for(int j=0; j<seg2.size(); j++){
            
            point q = seg2[j];
            
            if(p.coord[XCoord] == q.coord[XCoord] && p.coord[YCoord] == q.coord[YCoord] && p.coord[ZCoord] == q.coord[ZCoord]){
                intersection.push_back(p);
                break;
            }
        }
    }
    
    //cout << "have intersection size: " << intersection.size()-2 << " - "<< intersection.size() << endl;
    
    for(int i=0; i+2<=intersection.size(); i++){
        
        int distance = 0;
        for(int j=0; j<d; j++){
            //cout << "adding distance: i = " << i << ", intersect length: " << intersection.size() << endl;
            distance += abs(intersection[i].coord[j] - intersection[i+1].coord[j]);
            //cout << "distance added" << endl;
        }
        
        if(distance != 1){
            
            cout << "NOT CONSISTENT!" << endl;
            cout << "Segments: " << endl;
            cout << "(1): " + stringPoint(seg1[0]) + " to " + stringPoint(seg1[seg1.size()-1]) << endl;
            cout << "(2): " + stringPoint(seg2[0]) + " to " + stringPoint(seg2[seg2.size()-1]) << endl;
            cout << "Witness: " + stringPoint(intersection[i]) + " and " + stringPoint(intersection[i+1]) << endl << endl << endl;
        }
    }
    
    //cout << "leaving intersection" << endl;
}

vector<point> transitionSegments(point p1, point p2){
  
    if(p1.coord[XCoord] > p2.coord[XCoord])
        return reverse(transitionSegments(p2,p1));
    
    vector<point> segment;
    
  int yMoves = abs(p1.coord[YCoord] - p2.coord[YCoord]);
  int zMoves = abs(p1.coord[ZCoord] - p2.coord[ZCoord]);
  
    if(yMoves/zMoves >= 64){
        cout << "Using moreY" << endl;
        segment = moreY(p1,p2);
    }
    else {//if(zMoves/yMoves >= 64)
        cout << "Using moreZ" << endl;
        segment = moreZ(p1,p2);
    }
  /*else{
    
    vector<point> segment;
    vector<point> yzProj = compute2dSegment(p1,p2,YCoord,ZCoord);
    vector<point> xyProj = compute2dSegment(p1,p2,XCoord,YCoord);
    vector<point> xzProj = compute2dSegment(p1,p2,XCoord,ZCoord);
    
    point currentPoint = p1;
    segment.push_back(currentPoint);
    
    bool atP2 = true;
    for(int i=0; i<d; i++){
      if(currentPoint.coord[i] != p2.coord[i])
	atP2 = false;
    }
    
    int yzIndex = 0;
    int xyIndex = 0;
      
      int zSlopeType;
      if(p1.coord[ZCoord] - p2.coord[ZCoord] > 0)
	  zSlopeType = -1;
      else
	  zSlopeType = 1;
    
    while(!atP2){
     
      
      
    }
    
    
    
  }*/
    
    //showSegment(segment,p1,p2);
    return segment;
  
  
}



vector<point> moreY(point p1, point p2){
  
  vector<point> segment;
  vector<point> yzProj = compute2dSegment(p1,p2,YCoord,ZCoord);
  vector<point> xyProj = compute2dSegment(p1,p2,XCoord,YCoord);
    
    /*cout << "yz projection:";
    for (int i=0; i<yzProj.size(); i++) {
        cout << stringPoint(yzProj[i]) << "   ";
    }
    cout << endl << endl;
    
    cout << "xy projection:";
    for (int i=0; i<xyProj.size(); i++) {
        cout << stringPoint(xyProj[i]) << "   ";
    }
    cout << endl << endl;*/
  
  point currentPoint = p1;
  segment.push_back(currentPoint);
  
  bool atP2 = true;
  for(int i=0; i<d; i++){
    if(currentPoint.coord[i] != p2.coord[i])
      atP2 = false;
  }
  
  int yzIndex = 0;
  int xyIndex = 0;
    
    int zSlopeType;
    if(p1.coord[ZCoord] - p2.coord[ZCoord] > 0)
        zSlopeType = -1;
    else
        zSlopeType = 1;
  
  while(!atP2){
    
    //if(currentPoint.coord[XCoord] == currentPoint.coord[
    
   if(yzIndex < yzProj.size()-1 && yzProj[yzIndex].coord[ZCoord] != yzProj[yzIndex+1].coord[ZCoord]){
     
    //Next movement in yzProj is in Z direction.
    //Calculate how many X we need to make prior to next Y movement.
    
      int numOfXMoves = 0;
      while(xyIndex < xyProj.size()-1 && xyProj[xyIndex].coord[XCoord] != xyProj[xyIndex+1].coord[XCoord]){
	
	numOfXMoves++;
	xyIndex++;
      }
      
      point nextPoint;
      nextPoint.coord[XCoord] = currentPoint.coord[XCoord] + numOfXMoves;
      nextPoint.coord[YCoord] = currentPoint.coord[YCoord];
      nextPoint.coord[ZCoord] = currentPoint.coord[ZCoord] + zSlopeType;
      
       //cout << "Computing seg from " + stringPoint(currentPoint) + " to " + stringPoint(nextPoint) << endl;
      //Get the segment from currentPoint to nextPoint in XZ plane and append.
      vector<point> xzSeg = compute2dSegment(currentPoint,nextPoint,XCoord,ZCoord);
      for(int i=1; i<xzSeg.size(); i++){
	segment.push_back(xzSeg[i]);
      }
      
      currentPoint = nextPoint;
      yzIndex++;
     
   }
   else{
     
     //Next movement(s) in yzProj is in Y.
     //Move according to xyProj until we reach next XZ plane.
     
     while(yzIndex < yzProj.size()-1 && yzProj[yzIndex].coord[YCoord] != yzProj[yzIndex+1].coord[YCoord]){
     
       xyIndex++;
       
       point nextPoint;
       nextPoint.coord[XCoord] = xyProj[xyIndex].coord[XCoord];
       nextPoint.coord[YCoord] = xyProj[xyIndex].coord[YCoord];
       nextPoint.coord[ZCoord] = currentPoint.coord[ZCoord];
       
       if(currentPoint.coord[YCoord] != xyProj[xyIndex].coord[YCoord])
	 yzIndex++;
       
       segment.push_back(nextPoint);
       currentPoint = nextPoint;
       
     }
   }
   
   atP2 = true;
   for(int i=0; i<d; i++){
     if(currentPoint.coord[i] != p2.coord[i])
       atP2 = false;
   }
      
      if(!atP2 && yzIndex == yzProj.size()-1){
          
          point nextPoint;
          nextPoint.coord[XCoord] = currentPoint.coord[XCoord] + 1;
          nextPoint.coord[YCoord] = currentPoint.coord[YCoord];
          nextPoint.coord[ZCoord] = currentPoint.coord[ZCoord];
          
          segment.push_back(nextPoint);
          currentPoint = nextPoint;
          
      }
    
    
  }  
  
  return segment;
  
}

vector<point> newMoreZ(point p1, point p2){
   //cout << "In moreZ" << endl;
   //cout << "3D segment from " + stringPoint(p1) + " to " + stringPoint(p2) + ": " << endl;
  vector<point> segment;
  vector<point> yzProj = compute2dSegment(p1,p2,YCoord,ZCoord);
  vector<point> xzProj = compute2dSegment(p1,p2,XCoord,ZCoord);
  vector<point> xyProj = compute2dSegment(p1,p2,XCoord,YCoord);
  
  point currentPoint = p1;
  segment.push_back(currentPoint);
  
  bool atP2 = true;
  for(int i=0; i<d; i++){
    if(currentPoint.coord[i] != p2.coord[i])
      atP2 = false;
  }
  
  int yzIndex = 0;
  int xzIndex = 0;
  int xyIndex = 0;
    
    int ySlopeType;
    if(p1.coord[YCoord] - p2.coord[YCoord] > 0)
        ySlopeType = -1;
    else
        ySlopeType = 1;
    
    int zSlopeType;
    if(p1.coord[ZCoord] - p2.coord[ZCoord] > 0)
        zSlopeType = -1;
    else
        zSlopeType = 1;
  
    
  while(!atP2){
    
    int nextSplit = getNextSplitNode(yzProj,yzIndex);
    int nextMultiMove = getNextMultiMove(yzProj,yzIndex);
    
    if(nextMultiMove < nextSplit){
      
	int endOfMultiMove = getEndOfMultiMove(yzProj,nextMultiMove);

	vector<point> subseg;
	point target;
	
	if(yzProj[nextMultiMove].coord[YCoord] != yzProj[nextMultiMove+1].coord[YCoord]){
	  
	  subseg = moreY(currentPoint,target);
	}
	else{
	  
	 subseg = moreZ(currentPoint,target); 
	}
      
      
    }
    else{
      
	bool intoSplitFromY = true;
	if(yzProj[nextSplit].coord[ZCoord] != yzProj[nextSplit-1].coord[ZCoord])
	  intoSplitFromY = false;
    
    }
    
    
  }
  
}

vector<point> moreZ(point p1, point p2){
   //cout << "In moreZ" << endl;
   //cout << "3D segment from " + stringPoint(p1) + " to " + stringPoint(p2) + ": " << endl;
  vector<point> segment;
  vector<point> yzProj = compute2dSegment(p1,p2,YCoord,ZCoord);
  vector<point> xzProj = compute2dSegment(p1,p2,XCoord,ZCoord);
  
    /*cout << "yz projection:";
    for (int i=0; i<yzProj.size(); i++) {
        cout << stringPoint(yzProj[i]) << "   ";
    }
    cout << endl << endl;
    
    cout << "xz projection:";
    for (int i=0; i<xzProj.size(); i++) {
        cout << stringPoint(xzProj[i]) << "   ";
    }
    cout << endl << endl;*/
    
  point currentPoint = p1;
  segment.push_back(currentPoint);
  
  bool atP2 = true;
  for(int i=0; i<d; i++){
    if(currentPoint.coord[i] != p2.coord[i])
      atP2 = false;
  }
  
  int yzIndex = 0;
  int xzIndex = 0;
    
    int ySlopeType;
    if(p1.coord[YCoord] - p2.coord[YCoord] > 0)
        ySlopeType = -1;
    else
        ySlopeType = 1;
    
    int zSlopeType;
    if(p1.coord[ZCoord] - p2.coord[ZCoord] > 0)
        zSlopeType = -1;
    else
        zSlopeType = 1;
  
  while(!atP2){
   // cout << "not yet to destination" << endl;
   if(yzIndex < yzProj.size()-1 && yzProj[yzIndex].coord[YCoord] != yzProj[yzIndex+1].coord[YCoord]){
     
      //cout << "Next movement in yzProj is in Y direction." << endl;
      //Next movement in yzProj is in Y direction.
      //Determine how many of the following Z movements are singles before next multiple Z movement.
      
      yzIndex++;
       //showSegment(segment,p1,p2);
      int oneZs = countSingleZs(yzProj,yzIndex);
      // cout << "oneZs: " << oneZs << endl;
       /*0, yzInc = 0;
      bool foundMultZ = false;
      bool onZ;
      while(yzIndex + yzInc < yzProj.size()-1 && !foundMultZ){
	
	if(yzProj[yzIndex].coord[YCoord] != yzProj[yzIndex+1].coord[YCoord]){
	  onZ = false;
	  oneZs++;
	  yzInc++;
	}
	else if(onZ == true){
	 //Multiple Z movement found 
	 foundMultZ = true;
	}
	else{
	  onZ = true;
	  yzInc++;
	}
	
      }//End While*/
      
      if(false){//oneZs > 0){
	
         // cout << "single Zs ahead" << endl;
          //cout << "yzIndex: " << yzIndex << endl;
	//We use the "moreY" method of connecting through the single Z movements.
	//We know the y and z coordiantes of our new target.
	
	point nextPoint;
	nextPoint.coord[YCoord] = currentPoint.coord[YCoord] + ySlopeType*(oneZs + 1);
	nextPoint.coord[ZCoord] = currentPoint.coord[ZCoord] + zSlopeType*oneZs;
	
	//Now we need to compute the x-coordinate.
	int foundZ = 0, xInc = 0;
	while(xzIndex < xzProj.size()-1 && foundZ <= oneZs){
	 
	  if(xzProj[xzIndex].coord[XCoord] != xzProj[xzIndex+1].coord[XCoord])
	    xInc++;
	  else
	    foundZ++;
	  
	  xzIndex++;
	}
          
          //cout << "xInc: " << xInc << endl;
	
	xzIndex--;
	yzIndex += (2*oneZs);
	
	nextPoint.coord[XCoord] = currentPoint.coord[XCoord] + xInc;
	
          //cout << "Computing moreY segment from " + stringPoint(currentPoint) + " to " + stringPoint(nextPoint) << endl;
	//Now compute the "moreY" segment and append.
	vector<point> subseg = moreY(currentPoint,nextPoint);
          //showSegment(subseg,currentPoint,nextPoint);
	for(int i=1; i<subseg.size(); i++)
	  segment.push_back(subseg[i]);	
	
	//nextPoint.coord[YCoord] + ySlopeType;
	//segment.push_back(nextPoint);
	
	currentPoint = nextPoint;
          //cout << "yzIndex: " << yzIndex << ", xzIndex: " << xzIndex << endl;
	
      }
      else{
	
          //cout << "multiple Zs ahead" << endl;
          //cout << "currentPoint: " + stringPoint(currentPoint) + ", yzIndex: " << yzIndex << endl;
	//Next Z movement (if it exists) is a multiple Z.
	//Calculate how many X we need to make prior to next Z movement.
    
	  int numOfXMoves = 0;
	  while(xzIndex < xzProj.size()-1 && xzProj[xzIndex].coord[XCoord] != xzProj[xzIndex+1].coord[XCoord]){
	    
	    numOfXMoves++;
	    xzIndex++;
	  }
          
          //cout << "numOfXMoves: " << numOfXMoves << endl;
          
	  
	  point nextPoint;
	  nextPoint.coord[XCoord] = currentPoint.coord[XCoord] + numOfXMoves;
	  nextPoint.coord[YCoord] = currentPoint.coord[YCoord] + ySlopeType;
	  nextPoint.coord[ZCoord] = currentPoint.coord[ZCoord];
	  
	  //Get the segment from currentPoint to nextPoint in XY plane and append.
	  vector<point> xySeg = compute2dSegment(currentPoint,nextPoint,XCoord,YCoord);
	  for(int i=1; i<xySeg.size(); i++){
	    segment.push_back(xySeg[i]);
	  }
          
          //showSegment(segment,p1,p2);
	  
	  currentPoint = nextPoint;
	  //yzIndex++;
      }
    
   }
   else{
     
       //if(currentPoint.coord[XCoord] <= DimLength) cout << "Next Movement is in Z direction" << endl;
    //Next Movement is in Z direction
     
     if(yzIndex < yzProj.size() - 2 && false){//yzProj[yzIndex+1].coord[YCoord] != yzProj[yzIndex+2].coord[YCoord]){
      
         //cout << "Single Z" << endl;
       //This is a single Z movement
       int oneZs = countSingleZs(yzProj,yzIndex+1);
         //cout << "oneZs: " << oneZs << endl;
       
       //We use the "moreY" method of connecting through the single Z movements.
	//We know the y and z coordinates of our new target
       
	point nextPoint;
	nextPoint.coord[YCoord] = currentPoint.coord[YCoord] + ySlopeType*oneZs;
	nextPoint.coord[ZCoord] = currentPoint.coord[ZCoord] + zSlopeType*oneZs;
	
	//Now we need to compute the x-coordinate.
	int foundZ = 0, xInc = 0;
	while(foundZ <= oneZs){
	 
	  if(xzProj[xzIndex].coord[XCoord] != xzProj[xzIndex+1].coord[XCoord])
	    xInc++;
	  else
	    foundZ++;
	  
	  xzIndex++;
	}
	
	xzIndex--;
	yzIndex += (2*oneZs);
	
	nextPoint.coord[XCoord] = currentPoint.coord[XCoord] + xInc;
	
        // cout << "Computing moreY segment from " + stringPoint(currentPoint) + " to " + stringPoint(nextPoint) << endl;
	//Now compute the "moreY" segment and append.
	vector<point> subseg = moreY(currentPoint,nextPoint);
	for(int i=1; i<subseg.size(); i++)
	  segment.push_back(subseg[i]);	
	
	//nextPoint.coord[YCoord] + ySlopeType;
	//segment.push_back(nextPoint);
	
	currentPoint = nextPoint;
         //cout<<"curentPoint: " + stringPoint(currentPoint) + ", yzIndex: " << yzIndex << endl;
       
     }
     else{
         
         //cout << "yzIndex: " << yzIndex << endl;
         //showSegment(segment,p1,p2);
      
        // if(currentPoint.coord[XCoord] <= DimLength) cout << "making multi z moves from " + stringPoint(currentPoint) << endl;
         //cout << "yzIndex: " << yzIndex << ", xzIndex: " << xzIndex << endl;
	//Multiple Z movement.  Follow XZ proj until we reach XY plane.
	while(yzIndex < yzProj.size()-1 && yzProj[yzIndex].coord[ZCoord] != yzProj[yzIndex+1].coord[ZCoord]){
      
	  xzIndex++;
	  
	  point nextPoint;
	  nextPoint.coord[XCoord] = xzProj[xzIndex].coord[XCoord];
	  nextPoint.coord[YCoord] = currentPoint.coord[YCoord];
	  nextPoint.coord[ZCoord] = xzProj[xzIndex].coord[ZCoord];
	  
	  if(currentPoint.coord[ZCoord] != xzProj[xzIndex].coord[ZCoord])
	    yzIndex++;
	  
	  segment.push_back(nextPoint);
	  currentPoint = nextPoint;
        
        //cout << "yzIndex: " << yzIndex << endl;
       
	}
     }
     
     
   }
    
    
    atP2 = true;
    for(int i=0; i<d; i++){
     if(currentPoint.coord[i] != p2.coord[i])
       atP2 = false;
     }
      
      while(!atP2 && yzIndex == yzProj.size()-1){
          
          point nextPoint;
          nextPoint.coord[XCoord] = currentPoint.coord[XCoord] + 1;
          nextPoint.coord[YCoord] = currentPoint.coord[YCoord];
          nextPoint.coord[ZCoord] = currentPoint.coord[ZCoord];
          
          segment.push_back(nextPoint);
          currentPoint = nextPoint;
          
          atP2 = true;
          for(int i=0; i<d; i++){
              if(currentPoint.coord[i] != p2.coord[i])
                  atP2 = false;
          }
          
      }
    
  }
  
  
  return segment;
  
}

int getNextSplitNode(vector<point> seg, int index){
  
  int ySlopeType,zSlopeType;
  
  if(seg[0].coord[YCoord] > seg[seg.size()-1].coord[YCoord])
    ySlopeType = -1;
  else
    ySlopeType = 1;
  
  if(seg[0].coord[ZCoord] > seg[seg.size()-1].coord[ZCoord])
    zSlopeType = -1;
  else
    zSlopeType = 1;
  
  for(int i=index; i<seg.size()-1; i++){
    
    if(seg[i].coord[YCoord] != seg[i+1].coord[YCoord]){
     
      //Segment moves in Y direction.
      //Check Z direction for split node.
      
      point check;
      check.coord[YCoord] = seg[i+1].coord[YCoord];
      check.coord[ZCoord] = seg[i+1].coord[ZCoord] - zSlopeType;
      
      vector<point> newSeg = compute2dSegment(check,seg[seg.size()-1],YCoord,ZCoord);
      
      if(newSeg[0].coord[ZCoord] != newSeg[1].coord[ZCoord])
	return i+1;
      
    }
    else{
      
      //Segment moves in Z direction.
      //Check Y direction for split node.
      
      point check;
      check.coord[YCoord] = seg[i+1].coord[YCoord] - ySlopeType;
      check.coord[ZCoord] = seg[i+1].coord[ZCoord];
      
      vector<point> newSeg = compute2dSegment(check,seg[seg.size()-1],YCoord,ZCoord);
      
      //cout << "Checking: " << stringPoint(newSeg[0]) << " and " << stringPoint(newSeg[1]) << endl;
      
      if(newSeg[0].coord[YCoord] != newSeg[1].coord[YCoord])
	return i+1;
    }
    
  }
  
  //If we make it here, there are no split nodes (i.e. on same plane as destination).
  
  return -1;
  
}

int getNextMultiMove(vector<point> seg, int index){
  
  bool previousMoveY = true;
  if(seg[index].coord[ZCoord] != seg[index+1].coord[ZCoord])
    previousMoveY = false;
  
  for(int i=index+1; i<seg.size()-1; i++){
    
    if(seg[i].coord[YCoord] != seg[i+1].coord[YCoord]){
      
     if(previousMoveY) 
       return i-1;
     else
       previousMoveY = true;
      
    }
    else{
      
      if(!previousMoveY) 
       return i-1;
     else
       previousMoveY = false;
      
    }
  }
  
  //If we get here, there are no multi moves.
  return std::numeric_limits<int>::max();
}

int getEndOfMultiMove(vector<point> seg, int index){
  
  bool previousMoveY = true;
  if(seg[index].coord[ZCoord] != seg[index+1].coord[ZCoord])
    previousMoveY = false;
  
  for(int i=index+1; i<seg.size()-1; i++){
   
    if(!previousMoveY && seg[i].coord[YCoord] != seg[i+1].coord[YCoord])
      return i;
    else if(previousMoveY && seg[i].coord[ZCoord] != seg[i+1].coord[ZCoord])
      return i;
  }
  
  //Multi move ends at destination.
  return seg.size()-1;
  
}

int countSingleZs(vector<point> yzProj, int yzIndex){
  
  int oneZs = 0;
  bool foundMultZ = false;
  bool onZ=false;
  while(yzIndex < yzProj.size()-1 && !foundMultZ){
    
    if(yzProj[yzIndex].coord[YCoord] != yzProj[yzIndex+1].coord[YCoord]){
      onZ = false;
      oneZs++;
    }
    else if(onZ == true){
    //Multiple Z movement found 
    foundMultZ = true;
    }
    else{
      onZ = true;
    }
      
      yzIndex++;
    
  }//End While
  
  return oneZs;
}

vector<point> compute3dSegment(point p1, point p2){
 
    //cout << "in 3dSegment" << endl;
  if(p1.coord[XCoord] > p2.coord[XCoord])
    return reverse(compute3dSegment(p2,p1));

    //cout << "yMoves" << abs(p1.coord[YCoord] - p2.coord[YCoord]) << ", zMoves:" << endl;
  vector<point> segment;
  
  if(abs(p1.coord[YCoord] - p2.coord[YCoord]) >= abs(p1.coord[ZCoord] - p2.coord[ZCoord])){
      //cout << "calling moreY" << endl;
    segment = moreY(p1,p2);
    
  }
  else{
      //cout << "Calling moreZ" << endl;
    segment = moreZ(p1,p2);
  }
  
  showSegment(segment,p1,p2);
  return segment;
  
}

void showSegment(vector<point> segment, point p1, point p2){
  
 cout << "*3D segment from " + stringPoint(p1) + " to " + stringPoint(p2) + ": " << endl;
 for(int i=0; i<segment.size(); i++){
   
   if(i < segment.size()-1)
    cout << stringPoint(segment[i]) + " -> ";
   else
     cout << stringPoint(segment[i]);
   
   if(((i+1)%10) == 0) cout << endl;
 }
	
 cout << endl;
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
    
	if(n1%2 != 0) n1 += 32;
	if(n2%2 != 0) n2 += 32;
  
	return compare(n1,n2);
}


bool compare(int n1, int n2) //return true if n1 is less than n2
{
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

int min(int a, int b){
 
  if(a < b)
    return a;
  else
    return b;
  
}