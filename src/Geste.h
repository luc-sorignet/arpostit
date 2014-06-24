#pragma once
#include "ofMain.h"
class Geste
{
    public:
        Geste(ofPoint h1, ofPoint h2,ofPoint v1,ofPoint v2,ofPoint g);
        string getType(ofPoint p1,ofPoint p2);

        virtual ~Geste();
    protected:
    private:
        ofPoint d;
        ofPoint f;
        ofPoint h1;
        ofPoint h2;
        ofPoint v1;
        ofPoint v2;
        ofPoint g;
//METHOD
        double squareDist(ofPoint v,ofPoint w);
        ofPoint projection(ofPoint p,ofPoint v,ofPoint w);
        ofPoint projectionV(ofPoint p);
        ofPoint projectionH(ofPoint p);
};
