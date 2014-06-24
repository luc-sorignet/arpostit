#pragma once
#include "ofMain.h"
#include "Menu.h"
#include "CamView.h"
#include "NetworkView.h"
#include "PostItView.h"

/**
* Open Framework Application (MAIN OBJECT)
**/
class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    PostItView piv;
    CamView cam;
    NetworkView netv;
    Menu m;
};

