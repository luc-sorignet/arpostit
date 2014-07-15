#include "ofApp.h"

  enum enumMen{Network,Camera,Postit};
  enumMen menuID;
//--------------------------------------------------------------

void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    netv.setListPostIt(piv.getListPostIt());
    netv.update(piv.isChanged(),cam.isAllowToDisplayPost());
    //cout << cam.isAllowToDisplayPost();
    piv.setChanged(false);
    int w = ofGetWidth();
	int h = ofGetHeight();
	if(w != 720 || h != 520) ofSetWindowShape(720, 520);
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor(140,140,140), ofColor(33,33,33), OF_GRADIENT_CIRCULAR);
    menuID=(enumMen)m.getMenu();
    m.draw();
    if(cam.isGestureChanged()){
        netv.sendGeste(cam.getGeste());
    }
    switch(menuID){
        case Network:
            piv.setVisible(false);
            netv.setListAR(cam.getARList());
            netv.draw();
            break;
        case Camera:
              piv.setVisible(false);
            cam.draw();
            break;
        case Postit:
            piv.setVisible(true);
            piv.draw();
            break;
    }



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //Interaction
    netv.keyboardAction(key);
    switch(menuID){
        case Network:
             break;
        case Camera:
               cam.keyPressed(key);
            break;
        case Postit:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    m.mouseAction(x,y);
        switch(menuID){
        case Network:
            netv.mouseAction(x,y);
             break;
        case Camera:
             cam.mouseAction(x,y);
            break;
        case Postit:
           // piv.mouseAction(x,y);
            break;
    }
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
//--------------------------------------------------------------
void ofApp::exit(){}
