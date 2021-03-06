#ifndef __DETECTOR_H__
#define __DETECTOR_H__

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <FaceAlignment.h>
#include <string>
#include "mblbp-detect.h"

using namespace std;
using namespace cv;
using namespace INTRAFACE;

enum DETECTOR_TYPE {DSZU, DOPENCV, UNKNOWN};

class Detector{
	public:
		Detector();
		
		//numLandmarks can be 5 or 49 
		Mat detect(const string imgname, int numLandmarks = 49);

		//numLandmarks can be 5 or 49, landmark positions and poses (in the order of roll, yaw, pitch) are returned
		Mat detect(const string imgname, Mat& landmarks, int* pose, int numLandmarks = 49);
		
		//marks an already detected face, return false if no face detected
		bool detect(const Mat& face, Mat& landmarks, int* pose, int numLandmarks = 49);
		
		//align and normalize face to 100x100
		Mat detectNorm(const string imgname); 
	
		//align and normalize face to width x height, output landmarks, no. of landmarks can be 5, 49
		Mat detectNorm(const string imgname, const float width, const float height, const float patchSize, Mat& landmarks, int numLandmarks = 49, bool showLandmark = true);
		
		Mat detect();
	private:
		MBLBPCascade * faceCascade;
		CvHaarClassifierCascade* HaarCascade;
		FaceAlignment *faceLandmark;
		XXDescriptor *xxd;
		DETECTOR_TYPE dtype;
		Mat rotateImage(const Mat& source, double angle);
		void rotatePoint(const Mat& source, double angle, const double& x1, const double& y1, float& x, float& y);
};

#endif