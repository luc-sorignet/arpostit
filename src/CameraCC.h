#pragma once
#include "ofMain.h"


/**
* Class Camera
**/

class CameraCC
{

public:
    CameraCC(void);
	CameraCC(int width, int height);
	void draw(void);
	void draw(int marginx,int marginy);
	void update(void);
	bool isFrameNew(void);
	void videoSettings(void);
	unsigned char * getPixels(void);
	~CameraCC(void);
private:
	ofVideoGrabber 		vidGrabber;
	int 				camWidth;
	int 				camHeight;
};

