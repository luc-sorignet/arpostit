#pragma once
#include "ARMarker.h"
#include "CameraCC.h"
#include "ofxOpenCv.h"
#include "ofxARToolkitPlus.h"
#include "NetPacket.h"
#include "Geste.h"
class ARModule{
    public:

        ARModule();
        ARModule(int width, int height);
        virtual ~ARModule();
        void setThreshold(int t);
        int getThreshold(void);
        void update(CameraCC c);
        void allUpdate(); //IN REFACTORING
        void drawCam(int marginx,int marginy);
        void drawAR(int marginx,int marginy);
        vector<ARMarker> getList();
        bool isAllowedToDisplayedPost();
        string getGeste();
        bool isGestureChanged();

    protected:
    private:

        int width;
        int height;
        string geste;

    /* ARToolKitPlus class */
		ofxARToolkitPlus artk;
		int threshold;
	/* OpenCV images */
		ofxCvColorImage colorImage;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage	grayThres;

		/* Image to distort on to the marker */
		ofImage displayImage;
		/* The four corners of the image */
		vector<ofPoint> displayImageCorners;
        vector<ARMarker> listAR;
        vector <ofPoint> center;
        vector <ofPoint> m; //Mediatrice
        ofPoint g;  // Centre Grav
		bool displayPost;
		bool gestureChanged;
		bool wait;
        bool fingerDetected;
		//GESTURE
		ofPoint *doigt;
		ofPoint *lastp;
        double timer;
        double timerDetected;
        //METHOD
        ofPoint makeGravCenter(vector <ofPoint> pts);
        vector <ofPoint> makeMediatrice(ofPoint v,ofPoint gr);

};


