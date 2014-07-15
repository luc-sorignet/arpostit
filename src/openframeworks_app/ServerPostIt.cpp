
#include "ServerPostIt.h"

ServerPostIt::ServerPostIt(){}
void ServerPostIt::setup(int width, int height,int port){
 /* SERVER INIT */
 this->width = width;
 this->height = height;
    //setup the server to listen on port
	TCP.setup(port);
	//optionally set the delimiter to something else.  The delimiter in the client and the server have to be the same, default being [/TCP]
	TCP.setMessageDelimiter("\n");
}


void ServerPostIt::draw(void){
    ofSetHexColor(0xDDDDDD);
	ofDrawBitmapString("TCP SERVER \n\nconnect on port: "+ofToString(TCP.getPort()), 20, height+20);
	ofSetHexColor(0xDDDDDD);

	//for each connected client lets get the data being sent and lets print it to the screen
	for(unsigned int i = 0; i < (unsigned int)TCP.getLastID(); i++){
		if( !TCP.isClientConnected(i) )continue;
		//give each client its own color
		ofSetColor(255 - i*30, 255 - i * 20, 100 + i*40);
		//calculate where to draw the text
		int xPos = 15;
		int yPos = 80 + (12 * i * 4);
		//get the ip and port of the client
		string port = ofToString( TCP.getClientPort(i) );
		string ip   = TCP.getClientIP(i);
		string info = "client "+ofToString(i)+" -connected from "+ip+" on port: "+port;
		//if we don't have a string allocated yet
		//lets create one
		if(i >= storeText.size() ){
			storeText.push_back( string() );
		}
		//we only want to update the text we have received there is data
		string str = TCP.receive(i);
		if(str.length() > 0){
			storeText[i] = str;
		}
		//draw the info text and the received text bellow it
		ofDrawBitmapString(info, xPos, yPos);
		ofDrawBitmapString(storeText[i], 25, yPos + 20);
	}


}

void ServerPostIt::update(void){
//for each client lets send them a message letting them know what port they are connected on
	for(int i = 0; i < TCP.getLastID(); i++){
		if( !TCP.isClientConnected(i) )continue;
        /** SEND DATA **/
		TCP.send(i, "hello client - you are connected on port - " + ofToString(TCP.getClientPort(i)));
	}
}


ServerPostIt::~ServerPostIt(void){}
