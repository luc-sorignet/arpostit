#pragma once
#include "ARMarker.h"
#include "ofMain.h"
/**Define the different id for landmark**/
#define ID1 519
#define ID2 2144
#define ID3 2013
class VDesktop
{
    public:
        VDesktop();
        bool isMarker(ARMarker a);
        void setMarker(ARMarker a);
        ofVec4f convertCam2VD(ofVec4f pi);
        ofVec4f convertVD2Cam(ofVec4f pi);
        virtual ~VDesktop();
    protected:
    private:
        ofVec3f vecX;
        ofVec3f vecY;
        ofVec3f vecZ;
        ARMarker* c;
        ARMarker* p1;
        ARMarker* p2;
        ofMatrix4x4 mP;
        void calibrate();

};
