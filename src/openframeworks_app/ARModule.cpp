#include "ARModule.h"

/**
* Constructor
**/

ARModule::ARModule(){}
ARModule::ARModule(int w, int h){
    gestureChanged=false;
    this->geste="none";
    this->displayPost=false;
    this->width  = w;
    this->height = h;
    displayImage.loadImage("post-it.jpg");
    colorImage.allocate(width, height);
	grayImage.allocate(width, height);
	grayThres.allocate(width, height);
	// Load the corners of the image into the vector
	displayImageCorners.push_back(ofPoint(0, 0));
	displayImageCorners.push_back(ofPoint(displayImage.width, 0));
	displayImageCorners.push_back(ofPoint(displayImage.width, displayImage.height));
	displayImageCorners.push_back(ofPoint(0, displayImage.height));
    artk.setup(width, height);
	// Set the threshold
	threshold = 85;
	artk.setThreshold(threshold);

	//SETUP GESTURE RECO
	doigt = NULL;
	lastp = NULL;
	timer =-1;
	timerDetected=-1;
	fingerDetected = false;
	wait=false;

}
/**
* Set Threshold
*/
void ARModule::setThreshold(int t){
    threshold = t;
}
/**
* Get Threshold
*/
int  ARModule::getThreshold(void){
    return threshold;
}
/**
* Update ARModule in function of Camera new Frame
*/
void ARModule::update(CameraCC c){

    /*CAMERA UPDATE*/
    bool bNewFrame = c.isFrameNew();
    if(bNewFrame) {
		colorImage.setFromPixels(c.getPixels(), width, height);
		// convert our camera image to grayscale
		grayImage = colorImage;
		// apply a threshold so we can see what is going on
		grayThres = grayImage;
		grayThres.threshold(threshold);
		// Pass in the new image pixels to artk
		artk.update(grayImage.getPixels());
	}
	allUpdate();

}

/**
* Get from ARModule the List Of ARMarker detected in Camera position
*/
vector<ARMarker> ARModule::getList(){
    return listAR;
}

/**
* Draw Information about threshold
**/
void ARModule::drawAR(int marginx,int marginy){
	// Threshold image
	ofSetHexColor(0x333333);
	grayThres.draw(marginx, marginy);
	ofSetHexColor(0xFF0000);
    ofDrawBitmapString("Threshold: " + ofToString(threshold), marginx, marginy+10);
	ofDrawBitmapString("Use the Up/Down keys to adjust the threshold", marginx, marginy+30);
	artk.draw(marginx, marginy);
}
/**
* Draw Information about ARMarker detected by the camera
**/

void ARModule::drawCam(int marginx,int marginy){
ofSetHexColor(0xFF0000);
int detect = artk.getNumDetectedMarkers();
    ofDrawBitmapString(ofToString(detect) + " marker(s) found", marginx+500, marginy-5);
int myIndex,i,id;
    for(i=0;i<detect;i++){
        id=artk.getMarkerID(i);
        myIndex = artk.getMarkerIndex(id);
        if(myIndex >= 0) {
            // Get the corners
            vector<ofPoint> corners;
            artk.getDetectedMarkerBorderCorners(myIndex, corners);
            ofSetHexColor(0x0000ff);
            for(int i=0;i<corners.size();i++) {
                ofCircle(corners[i].x+marginx, corners[i].y+marginy, 10);
            }
            // Homography
            // Here we feed in the corners of an image and get back a homography matrix
            ofMatrix4x4 homo = artk.getHomography(myIndex, displayImageCorners);
            homo.getPtr()[12]+=marginx;
            homo.getPtr()[13]+=marginy;
            // We apply the matrix and then can draw the image distorted on to the marker
            ofPushMatrix();
            glMultMatrixf(homo.getPtr());
            ofSetHexColor(0xffffff);
            displayImage.draw(0, 0);
            ofPopMatrix();
        }
    }
    /*
    * IF MARKER ON ARM DETECTED
    */
    if(detect>=2 && center.size()==2){
        for(i=0;i<center.size();i++){
            ofSetHexColor(0xff0000);
            ofCircle(center[i].x+marginx,center[i].y+marginy,5);

        }
       ofSetHexColor(0x00ff00);
       ofCircle(g.x+marginx, g.y+marginy,5);
       ofLine(center[0].x+marginx,center[0].y+marginy,center[1].x+marginx,center[1].y+marginy);
       ofSetHexColor(0x0000FF);


       ofCircle(m[0].x+marginx,m[0].y+marginy,5);
       ofCircle(m[1].x+marginx,m[1].y+marginy,5);
       ofLine(m[0].x+marginx,m[0].y+marginy,m[1].x+marginx,m[1].y+marginy);


    }

}
/**
* allUpdate
**/
void ARModule::allUpdate(){
    //RESET
    listAR.clear();
    center.clear();
//Récupération des Marqueurs
int detect = artk.getNumDetectedMarkers();
//VAR
int myIndex,i,id;
bool change =false;
fingerDetected = false;
    for(i=0;i<detect;i++){
        id=artk.getMarkerID(i);
        myIndex = artk.getMarkerIndex(id);
        if(myIndex >= 0) {
                vector<ofPoint> corners;
            // Get the corners
              artk.getDetectedMarkerBorderCorners(myIndex, corners);
              ofMatrix4x4 matrix = artk.getGLMatrix(myIndex);
              ARMarker ar = ARMarker(id,corners,matrix);
              listAR.push_back(ar);

            if(id==0|id==1){
                    if(id==1 && center.empty()) change = true;
                center.push_back(artk.getDetectedMarkerCenter(myIndex));
            }
            if(id==65){
                if(wait){

                    delete doigt;
                    doigt = NULL;
                    delete lastp;
                    lastp = NULL;

                    if(timer==-1) timer=clock()/(double)CLOCKS_PER_SEC;
                    else if( (clock()/(double)CLOCKS_PER_SEC)-timer>=1){
                        wait =false;
                        timer= -1;
                    }
                }else{
                    if(doigt==NULL){
                        timer=clock()/(double)CLOCKS_PER_SEC;
                        doigt = new ofPoint(artk.getDetectedMarkerCenter(myIndex));
                        cout << "Timer!" <<endl;
                    }
                     if(timer!=-1&&((clock()/(double)CLOCKS_PER_SEC)-timer>=0.75)){
                        if(lastp ==NULL){
                            lastp = new ofPoint(artk.getDetectedMarkerCenter(myIndex));
                        }else{
                             delete doigt;
                            doigt = NULL;
                            delete lastp;
                            lastp = NULL;
                        }
                        cout << "END Timer!" <<endl;
                        timer = -1;
                    }
                }
            }

        }
    }
    /*
    * IF MARKER ON ARM DETECTED
    */

        if(detect>=2 && center.size()==2){
            if (change){
                ofPoint t1 = center[0];
                ofPoint t2 = center[1];
                center.clear();
                center.push_back(t2);
                center.push_back(t1);
            }
            this->displayPost=true;
            g = makeGravCenter(center);
           /* * Computing Vector to display mediatrice * */
            m=makeMediatrice(center[1],g);
           //SI On A un Geste
            if(lastp!=NULL && doigt!=NULL){
                  Geste ge=Geste(center[0],center[1],m[0],m[1], ofPoint(g.x, g.y));
                        //Reco du geste
                        gestureChanged=true;
                    this->geste = ge.getType(*doigt,*lastp);
                        cout << "GESTE RECO :" << this->geste<<endl;
                    wait =true;

            }
        }else{
        this->displayPost=false;
    }

}

/**
* Calcule le centre de gravité
**/
ofPoint ARModule::makeGravCenter(vector <ofPoint> pts){
    ofPoint grav(0,0);
    for(int i=0;i<pts.size();i++){
            grav.x+=pts[i].x;
            grav.y+=pts[i].y;
        }
        grav.x/=pts.size();
        grav.y/=pts.size();
        return grav;
}
/**
* Calcule la mediatrice d'un segment
* avec g le milieu et v la fin du segment
**/
vector <ofPoint> ARModule::makeMediatrice(ofPoint v,ofPoint gr){
    vector <ofPoint> med;
    ofPoint i,j;
    int ni,nj;
   /* * Computing Vector to display mediatrice * */
   i.x = v.x-gr.x;
   i.y = v.y-gr.y;
   j.x=5;
   j.y=-(j.x*i.x)/i.y;

   ni = (int) sqrt(i.x*i.x+i.y*i.y);
   nj =
   (int) sqrt(j.x*j.x+j.y*j.y);
   j.x = (j.x/nj)*ni;
   j.y = (j.y/nj)*ni;

//Mediatrice
    med.push_back(ofPoint(gr.x+(j.x),gr.y+(j.y)));
    med.push_back(ofPoint(gr.x-(j.x),gr.y-(j.y)));
    return med;
}

bool ARModule::isAllowedToDisplayedPost(){
    return this->displayPost;
}
 string ARModule::getGeste(){
       gestureChanged = false;
     return this->geste;
 }
 bool ARModule::isGestureChanged(){return gestureChanged;}

ARModule::~ARModule(){}
