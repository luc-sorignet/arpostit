#include "CameraCC.h"

CameraCC::CameraCC(){}
CameraCC::CameraCC(int width, int height){
	camWidth 		= width;
	camHeight 		= height;


	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
	ofSetVerticalSync(true);
}

void CameraCC::draw(void){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(0,0);
}
void CameraCC::draw(int mariginx,int marginy){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(mariginx,marginy);
}
void CameraCC::update(void){
	vidGrabber.update();
}

bool CameraCC::isFrameNew(void){
	return vidGrabber.isFrameNew();
}
void CameraCC::videoSettings(void){
	 vidGrabber.videoSettings();
}

unsigned char * CameraCC::getPixels(void){
	return vidGrabber.getPixels();
}
CameraCC::~CameraCC(void){}
