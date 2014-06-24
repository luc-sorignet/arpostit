#pragma once
#include "ofMain.h"

class NetPacket
{
    public:
        NetPacket(string type);
        template <typename T>
        void addValue(T val){
            cOption << val;
            cOption << delimiter;
        }
        void addOption(void);
        string getMessage();
        virtual ~NetPacket();
    protected:
    private:
        string type;
        string endDelimiter;
        string delimiter;
        stringstream cOption;
        vector <string> packet;
};


