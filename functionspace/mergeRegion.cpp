void labelmerge(int &label1,int &label2,cv::Vec3b colors[],Mat &duplImage,Array2D<int>&markerMap){
#pragma omp parallel for
for(int i=0;i<duplImage.rows;i++){

  for(int j=0;j<duplImage.cols;j++){
	  if(markerMap(i,j)==label2){
             duplImage.at<Vec3b>(i,j)=colors[label1];
	     //cout<<"merge"<<endl;
    }
  }
 }
}
