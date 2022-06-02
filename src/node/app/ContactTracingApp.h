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

#ifndef __CONTACT_TRACING_SIM_CONTACTTRACINGAPP_H_
#define __CONTACT_TRACING_SIM_CONTACTTRACINGAPP_H_

#include <omnetpp.h>
#include "src/node/msg/ContactTracingMessage_m.h"
#include "inet/mobility/contract/IMobility.h"

using namespace omnetpp;
using namespace std;
using namespace inet;

/**
 * TODO - Generated class
 */
class ContactTracingApp : public cSimpleModule
{
private:
    vector<cModule*> *nodes;
    IMobility *mobility;

    void discoverNetworkNodes();
    void broadcastMsg(ContactTracingMessage *msg);
    bool isInRange(ContactTracingMessage *msg);
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
