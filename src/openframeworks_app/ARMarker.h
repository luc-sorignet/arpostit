#pragma once
#include "ofMain.h"
class ARMarker
{
    public:
        ARMarker();
        ARMarker(int id,vector<ofPoint> corners,ofMatrix4x4 matrix);
        int getID();
        ofMatrix4x4 getMatrix();
        string toString();
        string toNetwork();
        virtual ~ARMarker();

    protected:
    private:
        int id;
        ofMatrix4x4 matrix;
        vector<ofPoint> corners;
};
