#pragma once
#include "ofMain.h"
#include "TCPClient.h"
#include "ARMarker.h"
#include "ListPostIt.h"
#include "NetPacket.h"
class NetworkView
{
    public:
        NetworkView();
        virtual ~NetworkView();
        void draw();
        void update(bool postit,bool allowDisplay);
        void setListAR( vector<ARMarker> listAR);
        void setListPostIt( ListPostIt listlp);
        void mouseAction(int x, int y );
        void keyboardAction (int key);
        void sendGeste(string geste);
    protected:
    private:
        bool enable;
        TCPClient *client;
        vector<ARMarker> listAR;
        ListPostIt allPostIt;
        ofImage led_dis;
        ofImage led_r;
        ofImage led_g;
        ofImage led_y;

};

