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

#include "Interface.h"
#include "inet/mobility/contract/IMobility.h"
#include "src/node/msg/ContactTracingMessage_m.h"

using namespace inet;

Define_Module(Interface);

void Interface::discoverNetworkNodes() {
    cModule *network = cSimulation::getActiveSimulation()->getSystemModule();
    for (SubmoduleIterator it(network); !it.end(); ++it) {
        cModule *node = *it;
        cModule *nodeApp = node->getSubmodule("iface");
        if (nodeApp != nullptr) {
            // check whether it is the same host
            if (this != node && getParentModule() != node) {
                this->nodes->push_back(nodeApp);
            }
        }
    }
}

void Interface::broadcastMsg(cMessage *msg) {
    ContactTracingMessage *copy = check_and_cast<ContactTracingMessage *>(msg);
    IMobility *mobility = check_and_cast<IMobility *>(this->getParentModule()->getSubmodule("mobility"));
    copy->setCoord(mobility->getCurrentPosition());
    for(cModule *node : *this->nodes)
        this->sendDirect(new ContactTracingMessage(*copy), node->gate("ble"));
}

void Interface::initialize()
{
    this->nodes = new vector<cModule*>();
    discoverNetworkNodes();
    broadcastMsg(new ContactTracingMessage());
}

void Interface::handleMessage(cMessage *msg)
{
    ContactTracingMessage *copy = check_and_cast<ContactTracingMessage *>(msg);
    EV<<"He is at x:"<<copy->getCoord().getX()<<" y: "<<copy->getCoord().getY()<<endl;
    cGate *inGate = msg->getArrivalGate();
    if ( inGate == gate("ble")) {
        cMessage *copy = msg->dup();
        this->send(copy, gate("data$o"));
        delete msg;
    } else {

    }

}
