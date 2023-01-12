
     nnglist.push_back(*tempnode);//cycle find
     int tempx=tempnode->x;
     int tempy=tempnode->y;
     int mergesum=tempnode->pixelval+nngnodes[j].pixelval;
     int mergenum=tempnode->pixelnum+nngnodes[j].pixelnum;
     nngnodes[j].x=0;
     nngnodes[j].y=0;
     nngnodes[j].pixelval=0;
     nngnodes[j].pixelnum=0;
     nngnodes[j].ndist=100000000.0;
    // double newdist=0.0;
     // nngNode minnode=(0,0,0,0,10000.0*10000.0);
      nngNode *minnode=(nngNode*)malloc(sizeof(nngNode)*1);
      minnode->x=0;
      minnode->y=0;
      minnode->pixelval=0;
      minnode->pixelnum=0;
      minnode->ndist=10000000;//find the new minimum distance value of neighbour node
      ///////////////////////////////////////////////////////////////////
      nngNode *minneighz=(nngNode*)malloc(sizeof(nngNode)*1);
      minneighz->x=0;
      minneighz->y=0;
      minneighz->pixelval=0;
      minneighz->pixelnum=0;
      minneighz->ndist=10000000;//find the new minimum distance value of neighbour node

     // nngNode minneighz=(0,0,0,0,10000.0*10000.0);
      for(int z=0;z<lnngarr;z++){
	
       if(nngnodes[z].pixelnum!=0){
            // if(minnode.ndist>nngnodes[z].ndist){
	     if(nngnodes[z].y==tempx||nngnodes[z].y==tempy){
               double npowerDis=pow((((double)nngnodes[z].pixelval)/(double)nngnodes[z].pixelnum)-(((double)mergesum)/(double)mergenum),2);
               double nmulelement=((double)nngnodes[z].pixelnum)*((double)mergenum);
               double ndivelement=((double)nngnodes[z].pixelnum)+((double)mergenum);
               double mindist =((nmulelement*npowerDis)/ndivelement)+1.0;
	       tempnode->pixelnum=mergenum;
	       tempnode->pixelval=mergesum;
	       tempnode->x=tempx;
	       tempnode->y=nngnodes[z].x;
               tempnode->ndist=mindist;
                nngnodes[z].ndist=mindist;
                nngnodes[z].y=tempnode->x;
	       if(minnode->ndist>nngnodes[z].ndist){
                         minnode->x=nngnodes[z].x;
			 minnode->y=nngnodes[z].y;
			 minnode->pixelval=nngnodes[z].pixelval;
			 minnode->pixelnum=nngnodes[z].pixelnum;
			 minnode->ndist=nngnodes[z].ndist;//find the new minimum distance value of neighbour node
                            
	       }
                   else if(minnode->ndist<=nngnodes[z].ndist){
                            nngnodes[z].x=0;//j?     
                            nngnodes[z].y=0;
                            nngnodes[z].pixelval=0;
                            nngnodes[z].pixelnum=0;
                            nngnodes[z].ndist=100000000;
                   
                 }
                 
           }//assign the updated value to the nodes which leads to tempnode 
         // }
         }//get the distance of neigh node whicha are updated
             
       }//end the updated loop
                //tempnode.pixelnum=mergenum;
	       //tempnode.pixelval=mergesum;
	       //tempnode.x=tempx;
	       tempnode->y=minnode->y;
                tempnode->ndist=minnode->ndist;//closest distance
		//#pragma omp parallel for reduction(min:minneighz->ndist)
                for(int z=0;z<lnngarr;z++){//find the other distance of neighbour node to tempnode
                  if(nngnodes[z].x==tempnode->y){
                    if(minneighz->ndist>nngnodes[z].ndist){
                       minneighz->pixelnum=nngnodes[z].pixelnum;
	               minneighz->pixelval=nngnodes[z].pixelval;
	               minneighz->x=nngnodes[z].x;
	               minneighz->y=nngnodes[z].y;
                       minneighz->ndist=nngnodes[z].ndist;
                       }
                   }
               }

               if(minneighz->ndist<tempnode->ndist){//if the new updated distance is bigger than original distance between neighbour node and other node,erease the tempnode and the node we choose to start the search
                     nngnodes[i].x=0;
                     nngnodes[i].y=0;
                     nngnodes[i].pixelval=0;
                     nngnodes[i].pixelnum=0;
                     nngnodes[i].ndist=100000000.0;
                     
               }

         break;
    }//for closet cycle
   }//for node[j]
 }//for node[i]
}
