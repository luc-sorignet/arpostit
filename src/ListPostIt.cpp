#include "ListPostIt.h"
#include "NetPacket.h"
ListPostIt::ListPostIt(){
     listPost = vector <PostIt>();

}

void ListPostIt::addPostit(PostIt p){
 this->listPost.push_back(p);
}
void ListPostIt::delPostit(int id){
    if(listPost.size()>0 && listPost.begin()+id<=listPost.end()){
        if(listPost.begin()+id !=listPost.end()){
              this->listPost.erase(listPost.begin()+id);
        }else{
            this->listPost.pop_back();
        }

    }

}
void ListPostIt::setPostit(int id,PostIt p){
 this->listPost[id]=p;
}
PostIt ListPostIt::getPostit(int id){
    return this->listPost[id];
}
int ListPostIt::getNbElement(){
    return this->listPost.size();
}
void ListPostIt::clearList(){
    this->listPost.clear();
}
 string ListPostIt::toNetwork(){
    stringstream msg,postit;
    NetPacket p("listpostit");
		for(int i=0;i<listPost.size();i++) {
                p.addValue(listPost[i].getTitle());
                p.addValue(listPost[i].getContent());
                p.addValue(listPost[i].getColor());
		}
		p.addOption();

        return p.getMessage();

 }

ListPostIt::~ListPostIt(){}
