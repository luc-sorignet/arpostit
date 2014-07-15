#include "NetPacket.h"

NetPacket::NetPacket(string type)
{

    /* OPTIONS SETTING**/
    this->delimiter="__:__";
    this->endDelimiter="__;__";
    this->type=type;
    cOption<<"trame"<<this->delimiter<<"trashing"<<this->endDelimiter<<this->type<<this->endDelimiter;
    this->packet.push_back(cOption.str());
    cOption.str("");
}


void NetPacket::addOption(){
    cOption<<this->endDelimiter;
    this->packet.push_back(cOption.str());
     cOption.str("");
}

string NetPacket::getMessage(){
 stringstream msg;
 for(int i=0;i<packet.size();i++){
    msg <<packet[i];
 }
 return msg.str();
}
NetPacket::~NetPacket(){}
