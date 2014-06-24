#include "ARMarker.h"
#include "NetPacket.h"
ARMarker::ARMarker(){}
ARMarker::ARMarker(int id,vector<ofPoint> corners,ofMatrix4x4 matrix){
   this->id =id;
   this->corners=corners;
   this->matrix=matrix;
}

 int ARMarker::getID(){}
ofMatrix4x4 ARMarker::getMatrix(){}


string ARMarker::toString(){
    stringstream str;
    str << "MARKER ID :"<< id <<endl;

    str<<"CORNER "<<endl;
    for(int i=0;i<corners.size();i++) {
        ofCircle(corners[i].x, corners[i].y, 10);
        str<<i<<":"<<"x="<<corners[i].x <<"y="<<corners[i].y<<endl;
    }

     str<<"MATRIX"<<endl;
    for(int i=0;i<4;i++) {
        str<<"[ "<<matrix.getPtr()[i]<<" "<<matrix.getPtr()[i+4]<<" "<<matrix.getPtr()[i+8]<<" | "<<matrix.getPtr()[i+12]<<" ]"<<endl;
    }

    return str.str();
}
string ARMarker::toNetwork(){
NetPacket p("armarker");
        p.addValue(id);
        p.addOption();
		for(int i=0;i<corners.size();i++) {
            p.addValue(i);
            p.addValue(corners[i].x);
            p.addValue(corners[i].y);
		}
		p.addOption();
        for(int i=0;i<4;i++) {
                 p.addValue(matrix.getPtr()[i]);
                 p.addValue(matrix.getPtr()[i+4]);
                 p.addValue(matrix.getPtr()[i+8]);
                 p.addValue(matrix.getPtr()[i+12]);
        }
        p.addOption();

        return p.getMessage();
}

ARMarker::~ARMarker(){}
