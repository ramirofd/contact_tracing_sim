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
#include <string>
#include "src/node/msg/ContactTracingMessage_m.h"
#include "src/node/app/ContactHistory.h"
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
    ContactHistory *history;
    cMessage *broadcast;
    cMessage *logPos;
    int id;

    void discoverNetworkNodes();
    void broadcastMsg(ContactTracingMessage *msg);
    double calculateDistance(ContactTracingMessage *msg);
    bool isInRange(ContactTracingMessage *msg);
    string strUuid();
    double getRandomDelay();

  protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;

  public:
    int getNodeId();
    string getNodeName();
};

#endif
