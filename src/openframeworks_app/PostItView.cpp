#include "PostItView.h"


/**
* Constructor
**/
PostItView::PostItView(){
    change =false;
    visible =false;
    gui = new ofxUIScrollableCanvas(40,40,660,480);
    top = new ofxUICanvas(40,0,680,40);
    top->addWidget(new ofxUIButton("ADD",false,50,30,75,0,OFX_UI_FONT_MEDIUM));
    top->addWidget(new ofxUIButton("LOAD",false,50,30,150,0,OFX_UI_FONT_MEDIUM));
    top->addWidget(new ofxUIButton("EXPORT",false,50,30,250,0,OFX_UI_FONT_MEDIUM));
    top->setDrawWidgetPadding(true);
    refresh();
    gui->setVisible(false);
    top->setVisible(false);


    // ADD EVENTS
    ofAddListener(gui->newGUIEvent,this, &PostItView::guiEvent);
    ofAddListener(top->newGUIEvent,this, &PostItView::topEvent);
}

void PostItView::setVisible(bool v){
     visible=v;
     gui->setVisible(visible);
     top->setVisible(visible);
}

void PostItView::guiEvent(ofxUIEventArgs &e){
    string s = e.getName();
    string nbutton = s.substr(0,s.find(":"));
    string id = s.substr(s.find(":")+1,s.size());
    int pos = ofToInt(id);
    cout << "button : "<<nbutton <<" ID  : "<<id<<" ID INT "<<pos <<endl;
    if(nbutton == "EDIT_BUTTON")
    {
        ofxUIImageButton *button = (ofxUIImageButton *)e.widget;
        cout << "";
    }else if(nbutton =="DEL_BUTTON"){

            ofxUIImageButton *button = (ofxUIImageButton *)e.widget;
            if(button->getValue()==1){
                    allItem.delPostit(pos);
                    refresh();
            }

    }
}

void PostItView::topEvent(ofxUIEventArgs &e){
        if(e.getName()=="ADD"){ }
        else if(e.getName()=="LOAD"){
            ofxUIImageButton *button = (ofxUIImageButton *)e.widget;
            if(button->getValue()==1){
                    loading();
            }
        }
        else if(e.getName()=="EXPORT"){
            ofxUIImageButton *button = (ofxUIImageButton *)e.widget;
            if(button->getValue()==1){
                    exporting();
            }
        }
}

void PostItView::draw(){}

void PostItView::refresh(){
 cout << "DEBUG OK1:"<<endl;
gui->removeWidgets();
//SET ARRAY TITLE
  gui->addWidget(new ofxUILabel(10,0,"#ID",OFX_UI_FONT_MEDIUM));
  gui->addWidget(new ofxUILabel(100,0,"| Title",OFX_UI_FONT_MEDIUM));
  gui->addWidget(new ofxUILabel(200,0,"| Content",OFX_UI_FONT_MEDIUM));
  gui->addWidget(new ofxUILabel(300,0,"| Color",OFX_UI_FONT_MEDIUM));
  gui->addWidget(new ofxUILabel(400,0,"| Actions",OFX_UI_FONT_MEDIUM));
//-----
 cout << "DEBUG OK1:"<<endl;
  int h=22;
if(allItem.getNbElement()>0){
 cout << "DEBUG NOT EPTY:"<<endl;
    for(int i = 0;i<allItem.getNbElement(); i++)
    {
         cout << "DEBUG FOR:"<<i<<endl;
          gui->addWidget(new ofxUILabel(10,h+i*h-17,"__________________________________________________",OFX_UI_FONT_MEDIUM));
          gui->addWidget(new ofxUILabel(10,h+i*h,"# "+ofToString(i),OFX_UI_FONT_MEDIUM));
          gui->addWidget(new ofxUILabel(100,h+i*h,"|",OFX_UI_FONT_MEDIUM));
          gui->addWidget(new ofxUILabel(115,h+i*h, ofToString(allItem.getPostit(i).getTitle()),OFX_UI_FONT_MEDIUM));
          gui->addWidget(new ofxUILabel(200,h+i*h,"|",OFX_UI_FONT_MEDIUM));
          gui->addWidget(new ofxUILabel(215,h+i*h,ofToString(allItem.getPostit(i).getContent()),OFX_UI_FONT_MEDIUM));
       //IMAGE
          gui->addWidget(new ofxUILabel(300,h+i*h,"|",OFX_UI_FONT_MEDIUM));
          gui->addWidget(new ofxUILabel(315,h+i*h,ofToString(allItem.getPostit(i).getColor()),OFX_UI_FONT_MEDIUM));
          gui->addWidget(new ofxUILabel(400,h+i*h,"|",OFX_UI_FONT_MEDIUM));
          gui->addWidget(new ofxUIMultiImageButton(415,h+i*h,16,16,true,"img/edit.png","EDIT_BUTTON:"+ofToString(i),OFX_UI_FONT_SMALL));
          gui->addWidget(new ofxUIMultiImageButton(435,h+i*h,16,16,true,"img/delete.png","DEL_BUTTON:"+ofToString(i),OFX_UI_FONT_SMALL));
         cout << "DEBUG END FOR:"<<i<<endl;
    }
}else{
     gui->addWidget(new ofxUILabel(10,h-17,"__________________________________________________",OFX_UI_FONT_MEDIUM));
     gui->addWidget(new ofxUILabel(10,h,"EMPTY LIST",OFX_UI_FONT_MEDIUM));
}
    gui->setScrollableDirections(false, true);
    gui->setDrawBack(false);
    gui->autoSizeToFitWidgets();
    gui->getRect()->setWidth(ofGetWidth());


}

void PostItView::exporting(){
    ofxXmlSettings xml;
    xml.addTag("listPostIt");
    xml.pushTag("listPostIt");
    PostIt p;
        for(int j = 0; j < allItem.getNbElement(); j++){
             p = allItem.getPostit(j);
              xml.addTag("postit");
              xml.pushTag("postit",j);
              xml.addValue("color",p.getColor());
              xml.addValue("title", p.getTitle());
              xml.addValue("content",p.getContent());
              xml.popTag();//pop listPostIt
        }

        xml.popTag();//pop listPostIt
    xml.saveFile("all_lst.xml");
}

void PostItView::loading(){
    change = true;
    ofxXmlSettings xml;
    if(xml.loadFile("all_lst.xml")){
        allItem.clearList();
        xml.pushTag("listPostIt");
            int nbpost = xml.getNumTags("postit");
             for(int j = 0; j < nbpost; j++){
                    PostIt p = PostIt();
                    xml.pushTag("postit",j);
                    p.setContent(xml.getValue("content",""));
                    p.setColor(xml.getValue("color",""));
                    p.setTitle(xml.getValue("title",""));
                    xml.popTag();//pop postit
                    allItem.addPostit(p);
             }
            xml.popTag();//pop listPostIt
        refresh();
    }else{
        ofLogError("all_lst.xml file did not load!");
    }
}

void PostItView::setChanged(bool c){change=c;}
bool PostItView::isChanged(){return change;}
ListPostIt PostItView::getListPostIt(){

    return allItem;
}

PostItView::~PostItView(){}
