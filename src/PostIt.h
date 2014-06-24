#pragma once
#include "ofMain.h"
class PostIt
{
    public:
        PostIt();
        PostIt(string txt,string cont);
         string getContent();
         string getTitle();
         string getColor();
         void setTitle(string txt);
         void setContent(string txt);
         void setColor(string hex);
        virtual ~PostIt();
    protected:
    private:
        string title;
        string content;
        string color;
};

