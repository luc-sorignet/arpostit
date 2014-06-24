#include "PostIt.h"

PostIt::PostIt(){
    this->title="";
    this->content="";
    this->color="#00FFFF";
}
PostIt::PostIt(string txt,string cont){this->title=txt;this->content=cont;this->color="#00FFFF";}
void PostIt::setTitle(string txt){this->title=txt;}
void PostIt::setColor(string hex){this->color=hex;}
void PostIt::setContent(string txt){this->content=txt;}
string PostIt::getTitle(void){return this->title;}
string PostIt::getContent(void){return this->content;}
string PostIt::getColor(void){return this->color;}
PostIt::~PostIt(){}


