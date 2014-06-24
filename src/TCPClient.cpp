#include "TCPClient.h"

TCPClient::TCPClient(string ip, int port){
    this->port = port;
    this->ip = ip;
    mtr = "";
    isConnected = sClient.setup(ip,port);
    sClient.setMessageDelimiter("\n");
    connectTime = 0;
	deltaTime = 0;
	//To display some informations
	//sClient.setVerbose(true);


}


void TCPClient::update(){
    //we are connected - lets send our text and check what we get back
	if(isConnected){
		if(sClient.send("")){

			//if data has been sent lets update our text
			string str = sClient.receive();
			if( str.length() > 0 ){
				mtr = str;
			}
		}else if(!sClient.isConnected()){
		    //connection lost
			isConnected = false;
		}
	}else{
		//if we are not connected lets try and reconnect every 5 seconds
		deltaTime = ofGetElapsedTimeMillis() - connectTime;
		if( deltaTime > 5000 ){
			isConnected = sClient.setup(ip, port);
			connectTime = ofGetElapsedTimeMillis();
		}

	}

}
void TCPClient::draw(void){
    stringstream s;
    s <<"TCP Client connect on "<< this->ip <<" at port: "<<this->port;
    ofSetHexColor(0xDDDDDD);
	ofDrawBitmapString(s.str(), 60, 60);

}

void TCPClient::displayInfo(string info,int x, int y){
    ofSetHexColor(0xDDDDDD);
    ofDrawBitmapString(info, x, y);
}



void TCPClient::sendMsg(string msg){

    //we are connected - lets send our text and check what we get back
	if(isConnected){
		if(sClient.send(msg)){

			//if data has been sent lets update our text
			string str = sClient.receive();
			if( str.length() > 0 ){
				mtr = str;
                cout << "Message received: " << mtr ;
			}

		}else if(!sClient.isConnected()){
			isConnected = false;
		}
	} else {
		//if we are not connected lets try and reconnect every 5 seconds
		deltaTime = ofGetElapsedTimeMillis() - connectTime;
		if( deltaTime > 5000 ){
			isConnected = sClient.setup(ip, port);
			connectTime = ofGetElapsedTimeMillis();
		}

	}


}


string TCPClient::getMsg(){
    string ret = mtr;
    mtr = "";

    return ret;
}
