#pragma once
#include "ofMain.h"
#include "PostIt.h"
class ListPostIt
{
    public:
        ListPostIt();
        void clearList();
        void addPostit(PostIt p);
        void delPostit(int id);
        void setPostit(int id, PostIt p);
        PostIt getPostit(int id);
        int getNbElement(void);
        string toNetwork();
        virtual ~ListPostIt();
    protected:
    private:
        ofPoint pos;
        vector<PostIt> listPost;
};

