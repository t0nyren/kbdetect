#include "recognizer.h"
#include <iostream>
#include <fstream>
using namespace std;

Recognizer::Recognizer(int patchSize, int cellSize, int descrSize){
	this->detector = new Detector();
	this->encoder = new Encoder(patchSize, cellSize, descrSize);
}

void Recognizer::buildModel(const char* dirname, const char* filename, const char* outdir){
	if (outdir != NULL){
		mkdir(outdir, S_IRWXU);
	}
	
	DIR *pDIR;
	struct dirent *entry;
	struct stat buf;
	pDIR = opendir(dirname);
	if( pDIR == NULL){
		std::cout<<"Cannot open image directory"<<std::endl;
		exit(1);
	}
	
	entry = readdir(pDIR);
    int id = 1;
	while(entry != NULL)
	{
		if(0 == strcmp( ".", entry->d_name) || 0 == strcmp( "..", entry->d_name) ){
			entry = readdir(pDIR);
			continue;
		}
		char * name = entry->d_name;
		stat(name, &buf);
		std::cout << name<<std::endl;
		std::string s1 = outdir;
		std::string s2 = name;
		fout<<id<<','<<name<<',';
		int goodCount = 0;
		char buf[10];
		sprintf(buf, "%d", id);
		std::string dir_path = s1 + '/' + buf;
		std::cout<<dir_path<<std::endl;
		string failpath = string("fail/") + buf;
		string fppath = string("fp/") + buf;
		mkdir(dir_path.data(), S_IRWXU);
		mkdir(failpath.data(), S_IRWXU);
		mkdir(fppath.data(), S_IRWXU);
		
		DIR* pDIR2;
		std::string s3 = argv[1];
		std::string origin_path = s3 + '/' + s2;
		pDIR2 = opendir(origin_path.data());
		struct dirent *entry2;
		entry2 = readdir(pDIR2);
		while(entry2 != NULL){
			if(0 == strcmp( ".", entry2->d_name) || 0 == strcmp( "..", entry2->d_name) ){
				entry2 = readdir(pDIR2);
				continue;
			}
			//std::cout<<"\t"<<entry2->d_name<<std::endl;
			std::string s4 = entry2->d_name;
			std::string img_path = dir_path + '/' + s4;
			std::string img_origin_path = origin_path + '/' + s4;
			//Mat originalImage = imread( img_origin_path, CV_LOAD_IMAGE_GRAYSCALE );
			 // input image
			IplImage *frame = cvLoadImage(img_origin_path.data());
			if (frame != NULL)
			{
			  // convert image to grayscale
				IplImage *frame_bw = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 1);
				cvConvertImage(frame, frame_bw);
				if (detectFaceInImage(frame, frame_bw, faceCascade, model, bbox, landmarks, entry2->d_name, dir_path, failpath, fppath))
					goodCount++;
				cvReleaseImage(&frame_bw);
			}
			cvReleaseImage(&frame);
			if (goodCount > 5)
				break;
			entry2 = readdir(pDIR2);
		}
		fout<<goodCount<<endl;
		id++;
		closedir(pDIR2);
		entry = readdir(pDIR);             //Next person in directory        
	}
	closedir(pDIR);
	fout.close();		
}