#pragma once
#include "ofxNetwork.h"
#include "ofMain.h"
class ServerPostIt{
public:
    ServerPostIt();
    void setup(int width, int height,int port);
	void draw(void);
	void update(void);
	~ServerPostIt(void);
private:
    int width;
    int height;
	/* Communication TCP SERVER**/
		ofxTCPServer TCP;
		ofTrueTypeFont  mono;
		ofTrueTypeFont  monosm;
		vector <string> storeText;
};


