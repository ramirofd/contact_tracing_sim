//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __CONTACT_TRACING_INTERFACE_H_
#define __CONTACT_TRACING_INTERFACE_H_

#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

/**
 * TODO - Generated class
 */
class Interface : public cSimpleModule
{
private:
    vector<cModule*> *nodes;

    void discoverNetworkNodes();
    void broadcastMsg(cMessage *msg);

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif

//ContactTracingMessage* ContactTracingMessage::ctMessageFactory(int xpos, int ypos, omnetpp::opp_string uuid){
//    ContactTracingMessage *msg = new ContactTracingMessage();
//    msg->setPosition(xpos, 0);
//    msg->setPosition(ypos, 1);
//    msg->setUUID(uuid.c_str());
//    return msg;
//}
