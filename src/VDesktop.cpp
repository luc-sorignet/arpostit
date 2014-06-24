#include "VDesktop.h"

VDesktop::VDesktop(){
    c=NULL;
    p1=NULL;
    p2=NULL;
    mP = ofMatrix4x4();

}



bool VDesktop::isMarker(ARMarker a){
    if ((a.getID()==ID1)||(a.getID()==ID2)||(a.getID()==ID3)){
        return true;
    }
    return false;
}

void VDesktop::setMarker(ARMarker a){
   switch(a.getID()){
    case ID1:
            c=&a;
        break;

    case ID2:
             p1=&a;
        break;

    case ID3:
            p2=&a;
        break;
    }
    this->calibrate();
}

void VDesktop::calibrate(){
    if(p1!=NULL&&p2!=NULL&&c!=NULL){
        vecX=(p1->getMatrix().getTranslation()-c->getMatrix().getTranslation()).normalize();
        vecY=(p2->getMatrix().getTranslation()-c->getMatrix().getTranslation()).normalize();
        vecZ = vecX.cross(vecY);
        double mat[16];
        mat[0]=vecX.x;  mat[4]=vecY.x;  mat[8]=vecZ.x;   mat[12]=c->getMatrix().getTranslation().x;
        mat[1]=vecX.y;  mat[5]=vecY.y;  mat[9]=vecZ.y;   mat[13]=c->getMatrix().getTranslation().y;
        mat[2]=vecX.z;  mat[6]=vecY.z;  mat[10]=vecZ.z;  mat[14]=c->getMatrix().getTranslation().z;
        mat[3]=0;       mat[7]=0;       mat[11]=0;       mat[15]=1;
        mP.set(mat);

    }
}

ofVec4f  VDesktop::convertCam2VD(ofVec4f pi){

   return mP.getInverse().preMult(pi);
}

ofVec4f  VDesktop::convertVD2Cam(ofVec4f pi){
   return mP.preMult(pi);
}

VDesktop::~VDesktop(){}
