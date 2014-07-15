#include "CamView.h"
    int marginx = 60;
    int marginy = 30;
CamView::CamView(){
    int width = 640;
    int height = 480;
    menu=0;
    ar.loadImage("img/ar_ico.png");
    ar_dis.loadImage("img/ar_ico_dis.png");
    cam_ico.loadImage("img/cam_ico.png");
    cam_ico_dis.loadImage("img/cam_ico_dis.png");
    /** Camera Init**/
    c = CameraCC(width,height);
    arm = ARModule(width,height);

}
  string  CamView::getGeste(){
    return arm.getGeste();
  }
vector<ARMarker> CamView::getARList(){
    return arm.getList();
}

void CamView::update(){
    	c.update();
		arm.update(c);
}

void CamView::draw(){

    switch (menu){
        case 0:
            cam_ico.draw(marginx,5);
            ar_dis.draw(marginx+40,2);
            c.draw(marginx,marginy);
            arm.drawCam(marginx,marginy);
            break;
        case 1:
            cam_ico_dis.draw(marginx,5);
            ar.draw(marginx+40,2);
            arm.drawAR(marginx,marginy);
            break;
    }
}


void CamView::keyPressed(int key){
    switch(key){
    case OF_KEY_PAGE_UP:
        arm.setThreshold(arm.getThreshold()+1);
        break;
    case OF_KEY_PAGE_DOWN:
        arm.setThreshold(arm.getThreshold()-1);
        break;
    case OF_KEY_HOME:
        c.videoSettings();
        break;
    }
}
void CamView::mouseAction(int x, int y ){
    if(x>=marginx&&x<=marginx+26&&y>=5&&y<=21){
            menu=0;

    }else if(x<=marginx+72&&x>=marginx+40&&y>=2&&y<=25){
            menu=1;

    }

}
bool CamView::isGestureChanged(){
    return arm.isGestureChanged();
}
 bool CamView::isAllowToDisplayPost(){
    return this->arm.isAllowedToDisplayedPost();
 }
CamView::~CamView(){}
