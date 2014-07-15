#pragma once
#include "ofMain.h"
#include "CameraCC.h"
#include "ARModule.h"
class CamView
{
    public:
        CamView();
        virtual ~CamView();
        void draw();
        void update();
        void keyPressed(int key);
        void mouseAction(int x, int y );
        bool isAllowToDisplayPost();
        string getGeste();
        bool isGestureChanged();
         vector<ARMarker> getARList();
    protected:
    private:
        CameraCC c;
        ARModule arm;
        int menu;
        ofImage cam_ico;
        ofImage cam_ico_dis;
        ofImage ar;
        ofImage ar_dis;
};

