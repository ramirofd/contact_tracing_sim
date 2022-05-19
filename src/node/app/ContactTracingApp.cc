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

#include "ContactTracingApp.h"

Define_Module(ContactTracingApp);

void ContactTracingApp::discoverNetworkNodes() {
    cModule *network = cSimulation::getActiveSimulation()->getSystemModule();
    for (SubmoduleIterator it(network); !it.end(); ++it) {
        cModule *node = *it;
        cModule *nodeApp = node->getSubmodule("app");
        if (nodeApp != nullptr) {
            // check whether it is the same host
            if (this != node && getParentModule() != node) {
                this->nodes->push_back(nodeApp);
            }
        }
    }
}

void ContactTracingApp::initialize()
{
    this->nodes = new vector<cModule*>();
    discoverNetworkNodes();
}

void ContactTracingApp::broadcastMsg(cMessage msg) {
    for(cModule *node : *this->nodes)
        this->sendDirect(new cMessage(msg), node->gate("ble"));
}

void ContactTracingApp::handleMessage(cMessage *msg)
{
    EV<<"I'm "<< this->getFullPath() << " and received: " << msg <<endl;
}
