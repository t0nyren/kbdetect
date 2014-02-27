#include <opencv2/highgui/highgui.hpp>
#include "detector.h"
#include <vector>
#include <ctime>
#include <sys/time.h>
using namespace std;

int main(){
	Detector detector;
	
	//test 1, detect landmarks, save to tmp/face1.jpg
	cout<<"--------------test 1--------------"<<endl;
	string img1= "./data/rola.jpg";
	Mat face1 = detector.detect(img1);
	imwrite( "./tmp/face1.jpg" , face1 );
	cout<<"Image saved to ./tmp/face1.jpg"<<endl;
	//test 2, detect landmarks, save to tmp/face2.jpg
	cout<<endl<<"--------------test 2--------------"<<endl;
	string img2= "./data/wangdongcheng.jpg";
	Mat landmarks;
	int* pose = new int[3];
	Mat face2 = detector.detect(img2, landmarks, pose);
	imwrite( "./tmp/face2.jpg" , face2 );
	cout<<"Roll: "<<pose[0]<<" Yaw: "<<pose[1]<<" Pitch: "<<pose[2]<<endl;
	cout<<"Position of Nose Tip: "<<landmarks.at<float>(0, 14)<<" "<<landmarks.at<float>(1,14)<<endl;
	cout<<"Image saved to ./tmp/face2.jpg"<<endl;
	//test 3, detect landmarks, normalized it to 144 x 192, with 25 buffer size to the bound
	cout<<endl<<"--------------test 3--------------"<<endl;
	string img3= "./data/liuyifei.jpg";
	Mat face3 = detector.detectNorm(img3, 144, 192, 50, landmarks, 5, true);
	imwrite( "./tmp/face3.jpg" , face3 );
	cout<<"Image saved to ./tmp/face3.jpg"<<endl;
	return 0;
}
