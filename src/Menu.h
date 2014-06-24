#pragma once
#include "ofMain.h"

class Menu
{
    public:
        Menu();
        virtual ~Menu();
        int getMenu();
        void draw();
        void mouseAction(int x, int y );
    protected:
    private:
        int menu;
        ofImage network;
        ofImage network_dis;
        ofImage camera;
        ofImage camera_dis;
        ofImage postit;
        ofImage postit_dis;
};

