#pragma once
#include <iostream>
#include <string.h>
#include "ofxNetwork.h"
#include "ofMain.h"


class TCPClient
{
    public:
        TCPClient(string ip, int port);
        void sendMsg(string msg); // send message to server
        string getMsg(); //get server message
        void update();
        void draw();
        void displayInfo(string info,int x, int y);

    private:
        ofxTCPClient sClient;
        string mtr; // Message to receive Client <==== Server
        bool isConnected;
        float counter;
        int connectTime;
        int deltaTime;
        int port;
        string ip;
};


