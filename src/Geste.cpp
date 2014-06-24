#include "Geste.h"

Geste::Geste(ofPoint h1, ofPoint h2,ofPoint v1,ofPoint v2,ofPoint g){
this->h1 = h1;
this->h2 = h2;
this->v1 = v1;
this->v2 = v2;
this->g = g;
}
string Geste::getType(ofPoint p1,ofPoint p2){

    d = projectionH(p1);
    f = projectionH(p2);
    bool next = (squareDist(h1,d)<squareDist(h1,g)&&squareDist(h2,f)<squareDist(h2,g));
    bool prev = (squareDist(h2,d)<squareDist(h2,g)&&squareDist(h1,f)<squareDist(h1,g));

    if(next){
        return "next";
    }else if(prev){
        return "prev";
        }
    else{
        return "none";
    }

}

ofPoint Geste::projection(ofPoint p,ofPoint v,ofPoint w){
    double segmentLenghtSqr = squareDist(v,w);
    if (segmentLenghtSqr == 0) return v;
    double t = ((p.x - v.x) * (w.x - v.x) + (p.y - v.y) * (w.y - v.y)) / segmentLenghtSqr;
    if (t < 0) return v;
    if (t > 1) return w;
    return  ofPoint(v.x + t * (w.x - v.x), v.y + t * (w.y - v.y));
}
double Geste::squareDist(ofPoint v,ofPoint w){
        return (v.x-w.x)*(v.x-w.x)+(v.y-w.y)*(v.y-w.y);
}

ofPoint Geste::projectionV(ofPoint p){
    return this->projection(p,this->v1,this->v2);
}
ofPoint Geste::projectionH(ofPoint p){
    return this->projection(p,this->h1,this->h2);
}

Geste::~Geste()
{
    //dtor
}
