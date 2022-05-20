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
    for(cModule *node : *this->nodes)
        this->sendDirect(new cMessage(*msg), node->gate("ble"));
}

void Interface::initialize()
{
    this->nodes = new vector<cModule*>();
    discoverNetworkNodes();
    broadcastMsg(new cMessage("holis"));
}

void Interface::handleMessage(cMessage *msg)
{
    cGate *inGate = msg->getArrivalGate();
    if ( inGate == gate("ble")) {
        cMessage *copy = msg->dup();
        this->send(copy, gate("data$o"));
        delete msg;
    } else {

    }

}
