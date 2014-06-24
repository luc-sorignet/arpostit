#include "NetworkView.h"

/**
* Constructeur
**/
NetworkView::NetworkView(){
    int port = 1337;
    string host = "127.0.0.1";
    enable = false;
    client = new TCPClient(host,port);
        led_dis.loadImage("img/led_dis.png");
        led_r.loadImage("img/led_r.png");
        led_g.loadImage("img/led_g.png");
        led_y.loadImage("img/led_y.png");
}
/**
* Set LIST (AR, POSTIT)
**/
void NetworkView::setListAR( vector<ARMarker> l){
    this->listAR.clear();
    this->listAR=l;
}

void NetworkView::setListPostIt( ListPostIt listlp){
        allPostIt = listlp;
}
/**
* Draw Method
**/
void NetworkView::draw(){
ofSetHexColor(0x000000);
 ofRect(50,40,660,470);
    if(enable){
        client->draw();
        ofSetHexColor(0xFFFFFF);
        led_g.draw(50,10);
        ofSetHexColor(0xFFFFFF);
        led_dis.draw(50+25,10);
     }else{
          ofSetHexColor(0xFFFFFF);
          led_r.draw(50,10);
          ofSetHexColor(0xFFFFFF);
          led_dis.draw(50+25,10);
         ofSetHexColor(0xDDDDDD);
         ofDrawBitmapString("NETWORK Disabled", 60, 60);
     }

        for(int i=0;i<listAR.size();i++) {

                if(enable){
                     try{
                         //IMAGE
                          ofSetHexColor(0xFFFFFF);
                          led_y.draw(50+25,10);
                         client->sendMsg(listAR[i].toNetwork());
                         ofSetHexColor(0xFFFFFF);
                         led_dis.draw(50+25,10);
                    }catch(exception& e){
                        cout<<endl << "Error Sending : "<< e.what() <<endl;
                         ofSetHexColor(0xFFFFFF);
                         led_r.draw(50+25,10);
                    }
                    if(i<4){client->displayInfo(listAR[i].toString(), 60, 85+i*100);}

                }else{
                    if(i<4){
                        ofSetHexColor(0xDDDDDD);
                        ofDrawBitmapString(listAR[i].toString(), 60, 85+i*100);
                    }
                }
        }


}

void NetworkView::update(bool postit,bool allowDisplay){
    if(enable){
      client->update();
      if(postit){
            try{
                 //IMAGE
                  ofSetHexColor(0xFFFFFF);
                  led_y.draw(50+25,10);
                 client->sendMsg(allPostIt.toNetwork());
                 ofSetHexColor(0xFFFFFF);
                 led_dis.draw(50+25,10);



            }catch(exception& e){
                cout<<endl << "Error Sending : "<< e.what() <<endl;
                 ofSetHexColor(0xFFFFFF);
                 led_r.draw(50+25,10);
            }

      }
       if(allowDisplay){
                   NetPacket p("action");
                   p.addValue("display");
                   p.addOption();
                   client->sendMsg(p.getMessage());

                 }else{
                   NetPacket p("action");
                   p.addValue("nodisplay");
                   p.addOption();
                   client->sendMsg(p.getMessage());

                 }
	}
}

/* BUTTON ACTIVE NETWORK* */
void NetworkView::mouseAction(int x, int y ){
     if(x>=50&&x<=74&&y>=10&&y<=34){
            enable=!enable;
    }

}


void NetworkView::keyboardAction(int key){
    if(enable){
     switch(key){
     case OF_KEY_RIGHT:
          sendGeste("next");
         break;
     case OF_KEY_LEFT:
          sendGeste("prev");
         break;

     }

     //cout << "MSG ACTION:"<< p.getMessage();

    }

}

void NetworkView::sendGeste(string geste){
    if (geste!="none" && enable){
        NetPacket p("action");
        p.addValue(geste);
        p.addOption();
        client->sendMsg(p.getMessage());
    }
}



NetworkView::~NetworkView(){}
