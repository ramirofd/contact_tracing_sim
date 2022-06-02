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
#include "inet/mobility/contract/IMobility.h"

using namespace inet;

Define_Module(ContactTracingApp);

void ContactTracingApp::discoverNetworkNodes() {
    cModule *network = cSimulation::getActiveSimulation()->getSystemModule();
    for (SubmoduleIterator it(network); !it.end(); ++it) {
        cModule *node = *it;
        cModule *nodeApp = node->getSubmodule("app");
        if (nodeApp != nullptr) {
            // check whether it is the same host
            if (this != nodeApp) {
                this->nodes->push_back(nodeApp);
            }
        }
    }
}

void ContactTracingApp::broadcastMsg(ContactTracingMessage *msg) {
    for(cModule *node : *this->nodes)
        this->sendDirect(new ContactTracingMessage(*msg), node->gate("ble"));
}

double ContactTracingApp::calculateDistance(ContactTracingMessage *msg) {
    return msg->getCoord().distance(this->mobility->getCurrentPosition());
}
bool ContactTracingApp::isInRange(ContactTracingMessage *msg) {
    return this->calculateDistance(msg)<=par("range").doubleValue();
}

void ContactTracingApp::initialize()
{
    this->nodes = new vector<cModule*>();
    this->discoverNetworkNodes();
    this->mobility = check_and_cast<IMobility *>(this->getParentModule()->getSubmodule("mobility"));
    scheduleAfter(par("broadcastTime"), new cMessage());
}

void ContactTracingApp::handleMessage(cMessage *msg)
{

    if(msg->isSelfMessage()){
        ContactTracingMessage *newMsg = new ContactTracingMessage();
        newMsg->setCoord(this->mobility->getCurrentPosition());
        this->broadcastMsg(newMsg);
        scheduleAfter(par("broadcastTime"), msg);
    } else {
        ContactTracingMessage *cpy = check_and_cast<ContactTracingMessage*>(msg);
        EV << "Soy: " << this->getParentModule()->getFullName() << " y "<<((this->isInRange(cpy)==true)?"SI":"NO")<< " veo a " << cpy->getSenderModule()->getParentModule()->getFullName() << " porque esta a: " <<this->calculateDistance(cpy)<<"m"<<endl;
        if(this->isInRange(cpy)){
            EV << "Recibido de: " << cpy->getSenderModuleId() << " Soy: " << this->getId();
        }
        delete msg;
    }
}
