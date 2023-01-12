#include "../headerspace/WatershedAlg.h"
#include<vector>
#include<math.h>
#include<cmath>
#include <limits>
#include<list>
using namespace cv;
#define NUMSIZE 8
#define NSIZE 4




struct Pixel {
    int val;
    int x;
    int y;

    Pixel(int val, int x, int y) : val(val), x(x), y(y) {}


};


struct cmp1{

   bool operator()(Pixel &para1, Pixel &para2) {
        return para1.val < para2.val;
    }

};


struct nngNode{

int x;
int y;
int pixelval;
int pixelnum;
double ndist;
nngNode(int x, int y, int pixelval,int pixelnum,double ndist) : x(x), y(y), pixelval(pixelval),pixelnum(pixelnum),ndist(ndist) {}

};

struct cmp2{

   bool operator()(nngNode &para1, nngNode &para2) {
        return para1.ndist > para2.ndist;
    }

};


Mat WatershedAlg::watershed(Array2D<int> &image, Array2D<int>& markers,Mat &duplImage,int &rows,int &cols,Array2D<bool> &inprioq,Array2D<int>& markerMap,Array2D<int>&temp,Array2D<int>& nextSet, int &id_num){


       int msize=0;
  
       int dx[NUMSIZE]={-1, 1, 0, 0, -1, -1, 1, 1};
       int dy[NUMSIZE]={0, 0, -1, 1, -1,  1, 1, -1};

        // Put markers in priority queue
        int id = 1;
        Mat testDuplicate;
        duplImage.copyTo(testDuplicate);
        Mat dstImage(duplImage.rows,duplImage.cols,CV_8UC3,Scalar::all(0));


int tempcounter=0;

   for(int y=0;y<rows;y++){

      for(int z=0;z<cols;z++){
 
           if(markers(y,z)==2){    
            markerMap(y,z) = id;
//	    image(y,z)=image(y,z)+25;
           // msize++;
             for(int i = 0; i < 4; i++) {

                int newX =y + dx[i];
                int newY =z + dy[i];
                if(newX < 0 || newY < 0 || newX >= rows || newY >= cols) {
                    continue;
                }

	       temp(tempcounter,0)=image(newX,newY);
               temp(tempcounter,1)=newX;
               temp(tempcounter,2)=newY;
              // prioq.push(temp(tempcounter));
	       tempcounter++;

                
             }

             id++;
           }
        }
   }

         id_num=id;
	 /////////////////////////////////////
         Array2D<int> idArr(id,id,0);
//	 Array2D<double> neighDis(id,id,0);
         int pixelSum[id]={0};
	 int pixelNum[id]={0};
       //  memset(pixelNum,-10,sizeof(pixelNum));

         



         cv::Vec3b colors[id];
         #pragma omp parallel for
         for(int i = 0; i <= id; i++) {
           Vec3b vecColor;
           vecColor[0] = rand()%255+0;
           vecColor[1] = rand()%255+1;
           vecColor[2] = rand()%255+2;          
           colors[i]=vecColor;
        }


int ptcounter=0;
Vec3b boundColor;
boundColor[0] = 0;
boundColor[1] = 0;
boundColor[2] = 0;

#pragma omp parallel for reduction(+:pixelSum[:id],pixelNum[:id])
for(int i=0;i<tempcounter;i++){
   Pixel origin = Pixel( temp(i,0),temp(i,1),temp(i,2));
  //int originx=;
  //int originy=;
  //int originval=;
  priority_queue<Pixel,vector<Pixel>,cmp1>prioq;
  prioq.push(origin);
  while(!prioq.empty()){
    int CrtX=prioq.top().x;
    int CrtY=prioq.top().y;
	  
	  
    // int curpoint[3]={prioq.top()[0],prioq.top()[1],prioq.top()[2]};
    //int curpointx=temp(i,1);
    //int curpointx=temp(i,2);
    prioq.pop();
    //int CrtX=curpoint[1];
    //int CrtY=curpoint[2];
    bool canLabel = true;
    int neighboursLabel = 0;
    for(int i = 0; i < 8; i++) {
       int nextX = CrtX + dx[i];
       int nextY = CrtY + dy[i];
       if(nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols) {
         continue;
       }


        if(markerMap(nextX,nextY) != 0 && image(nextX,nextY)!=0){
                    if(neighboursLabel == 0) {
                        neighboursLabel = markerMap(nextX,nextY);//using id value,all strats from their closest neighbour
			//idArr(neighboursLabel,neighboursLabel)=neighboursLabel;
                    } else {//this part tells us that if there is two points at the boundary to see if they are in the same classification,
                    //two classification there is no merge
                        if(markerMap(nextX,nextY) != neighboursLabel ) {
                            canLabel = false;
			    duplImage.at<Vec3b>(CrtX,CrtY)=boundColor;
                            idArr(neighboursLabel-1,markerMap(nextX,nextY)-1)=1;
			    //idSum++;


                   //         Vec3b vecColor;
                     //       vecColor[0] = rand()%255+0;
                       //     vecColor[1] = rand()%255+1;
                         //   vecColor[2] = rand()%255+2;

                        }
                    }
                } 
	 else {
                if(inprioq(nextX,nextY) == false) {
                        inprioq(nextX,nextY) = true;//aviod duplicate point is chosen,point does not exist in marker or background
                        Pixel next=Pixel(image(nextX,nextY),nextX,nextY);
			
			prioq.push(next);
                        //the most important expending step,//only the point whose pixel value is 0 in Markermap
                    }
                }
                

	    }//inner for

             if(canLabel&&image(CrtX,CrtY)!=0) {
                 markerMap(CrtX,CrtY) = neighboursLabel;//in this way it tells us that the points in same region share the same id or label
                // idArr[neighboursLabel-1][neighboursLabel-1][0][2]=idArr[neighboursLabel-1][neighboursLabel-1][0][2]+image(CrtX,CrtY);//sum of pixel value
		// idArr[neighboursLabel-1][neighboursLabel-1][0][1]=idArr[neighboursLabel-1][neighboursLabel-1][0][1]+1;//num
		 
		 pixelSum[neighboursLabel-1]=pixelSum[neighboursLabel-1]+image(CrtX,CrtY);
		 pixelNum[neighboursLabel-1]=pixelNum[neighboursLabel-1]+1;
                 duplImage.at<Vec3b>(CrtX,CrtY)=colors[ markerMap(CrtX,CrtY) ];
            }
    }//while
}//for

int ragNode=0;


priority_queue<nngNode,vector<nngNode>,cmp2>nngprioq;

Array2D<double> neighDist(id,id,0);
//#pragma omp parallel for //reduction(+:ragNode) 
for(int i=0;i<id;i++){
   for(int j=0;j<id;j++){
    if(idArr(i,j)==1&&pixelNum[i]>0&&pixelNum[j]>0){
   // ragNode++;
   // double powerDis=((pixelSum[i]/pixelNum[i]-pixelSum[j]/pixelNum[j])/(rows*cols))*((pixelSum[i]/pixelNum[i]-pixelSum[j]/pixelNum[j])/(rows*cols));
    double powerDis=pow((((double)pixelSum[i])/(double)pixelNum[i]-((double)pixelSum[j])/(double)pixelNum[j]),2);
    double mulelement=((double)pixelNum[i])*((double)pixelNum[j]);
    double divelement=(double)(pixelNum[i]+pixelNum[j]);

    neighDist(i,j)=((mulelement*powerDis)/divelement)+1.0;
    nngNode newnode=nngNode(i,j,pixelSum[i],pixelNum[i],neighDist(i,j));
    nngprioq.push(newnode);
       }
     }
}
//cout<<"---------------------nng queue---------------------------"<<endl;
int ngnum=0;
vector<nngNode>nngvec;
//nngNode prenode=(nngprioq.top().x,nngprioq.top().y,nngprioq.top().pixelval,nngprioq.top().pixelnum,nngprioq.top().ndist);
while(!nngprioq.empty()){
	 
        nngNode prenode=nngNode(nngprioq.top().x,nngprioq.top().y,nngprioq.top().pixelval,nngprioq.top().pixelnum,nngprioq.top().ndist);	    nngprioq.pop();

    	 
	if(!nngprioq.empty()){
         if(prenode.ndist==nngprioq.top().ndist&&prenode.y==nngprioq.top().x&&prenode.x==nngprioq.top().y){
            nngvec.push_back(prenode);
	    nngvec.push_back(nngprioq.top());
     	 }else{

            //  vistNode(nngvec,nngprioq);
                 for(int h=0;h<nngvec.size();h++){
                    if(nngvec.at(h).x==nngprioq.top().x){
                        nngprioq.pop();
			break;
		    }
		    else{
		      	nngvec.push_back(nngprioq.top());    
			nngprioq.pop();
			break;
		    }

		 }
	   }
	}
}



nngNode *nngnodes=(nngNode*)malloc(sizeof(nngNode)*nngvec.size());

for(int i=0;i<nngvec.size();i++){

            nngnodes[i].x=nngvec.at(i).x;
	    nngnodes[i].y=nngvec.at(i).y;
	    nngnodes[i].pixelval=nngvec.at(i).pixelval;
	    nngnodes[i].pixelnum=nngvec.at(i).pixelnum;
            nngnodes[i].ndist=nngvec.at(i).ndist;


}

int lnngarr=nngvec.size();

list<nngNode> nnglist;
while(){

for(int i=0;i<lnngarr;i++){
   nngNode tempnode=(nngnodes[i].x,nngNode[i].y,nngnodes[i].pixelval,nngnodes[i].pixelnum,nngnodes[i].ndist);
   for(int j=0;j<lnngarr;j++){
   if(i!=j&&tempnode.pixelnum!=0&&nngnodes[j].pixenum!=0&&tempnode.ndist==nngnodes[j].ndist&&tempnode.x=nngnodes[j].y&&nngnodes[j].x=tempnode.y){
     nnglist.push_back(tempnode);//cycle find
     int tempx=tempnode.x;
     int tempy=tempnode.y;
     int mergesum=tempnode.pixelval+nngnodes[j].pixelval;
     int mergenum=tempnode.pixelnum+nngnodes[j].pixelnum;
     nngnodes[j].x=0;//j?
     nngnodes[j].y=0;
     nngnodes[j].pixelval=0;
     nngnodes[j].pixelnum=0;
     nngnodes[j].ndist=10000.0*10000.0;
    // double newdist=0.0;
      nngNode minnode=(0,0,0,0,10000.0*10000.0);
      nngNode minneighz=(0,0,0,0,10000.0*10000.0);
      for(int z=0;z<lnngarr;z++){
	
       if(nngnodes[z].pixelnum!=0){
            // if(minnode.ndist>nngnodes[z].ndist){
	     if(nngnodes[z].y==tempx||nngnodes[z].y==tempy){
               double npowerDis=pow((((double)nngnodes[z].pixelval)/(double)nngnodes[z].pixelnum)-(((double)mergesum)/(double)mergenum),2);
               double nmulelement=((double)nngnodes[z].pixelnum[z])*((double)mergenum);
               double ndivelement=((double)nngnodes[z].pixelnum[z])+((double)mergenum);
               double mindist =((mulelement*powerDis)/divelement)+1.0;
	       tempnode.pixelnum=mergenum;
	       tempnode.pixelval=mergesum;
	       tempnode.x=tempx;
	       tempnode.y=nngnodes[z].x;
                tempnode.ndist=mindist;
                nngnodes[z].ndist=mindist;
                nngnodes[z].y=tempnode.x;
	       if(minnode.ndist>.ndist){
                            minnode.x=nngnodes[z].x
			 minnode.y=nngnodes[z].y
			 minnode.pixelval=nngnodes[z].pixelval;
			 minnode.pixelnum=nngnodes[z].pixelnum;
			 minnode.ndist=nngnodes[z].ndist;//find the new minimum distance value of neighbour node
                            
	       }
                   else if(minnode.ndist<=nngnodes[z].ndist){
                            nngnodes[z].x=0;//j?     
                            nngnodes[z].y=0;
                            nngnodes[z].pixelval=0;
                            nngnodes[z].pixelnum=0;
                            nngnodes[z].ndist=10000.0*10000.0;
                   
                 }
                 
           }//assign the updated value to the nodes which leads to tempnode 
         // }
         }//get the distance of neigh node whicha are updated
             
       }//end the updated loop
                //tempnode.pixelnum=mergenum;
	       //tempnode.pixelval=mergesum;
	       //tempnode.x=tempx;
	       tempnode.y=minnode.y;
                tempnode.ndist=minnode.ndist;//closest distance
                for(int z=0;z<lnngarr;z++){//find the other distance of neighbour node to tempnode
                  if(nngnodes[z].x==tempnode.y){
                    if(minneighz.ndist>nngnodes[z].ndist){
                        minneighz.pixelnum=nngnodes[z].pixelnum;
	               minneighz.pixelval=nngnodes[z].pixelval;
	               minneighz.x=nngnodes[z].x;
	               minneighz.y=nngnodes[z].y;
                        minneighz.ndist=nngnodes[z].ndist;
                       }
                   }
               }

               if(minneighz.ndist<tempnode.ndist){//if the new updated distance is bigger than original distance between neighbour node and other node,erease the tempnode and the node we choose to start the search
                     nngnodes[i].x=0;
                     nngnodes[i].y=0;
                     nngnodes[i].pixelval=0;
                     nngnodes[i].pixelnum=0;
                     ngnodes[i].ndist=10000.0*10000.0;
                     
               }

         break;
    }//for closet cycle
   }//for node[j]
 }//for node[i]
nnglist.clear();

}



//priority_queue<nngNode,vector<nngNode>,cmp2>nngpq;


       cv::addWeighted(duplImage,0.25,testDuplicate,0.75,0,dstImage);

    
        duplImage.release();
        testDuplicate.release();
        return dstImage;
    }
