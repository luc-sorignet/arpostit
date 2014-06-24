#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
#include "ListPostIt.h"
#include "PostIt.h"

class PostItView
{
    public:
        PostItView();
        virtual ~PostItView();
        void draw();
        void guiEvent(ofxUIEventArgs &e);
        void topEvent(ofxUIEventArgs &e);
        void setVisible(bool v);
        void refresh();
        void exporting();
        void loading();
       ListPostIt getListPostIt();
        void setChanged(bool c);
        bool isChanged();
    protected:
    private:
        ofxUIScrollableCanvas *gui;
        ofxUICanvas *top;
        bool visible;
        bool change;
        ListPostIt allItem;
};

