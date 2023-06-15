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

#include <iomanip>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "ContactTracingApp.h"
#include "src/node/msg/ContactData.h"
#include "inet/mobility/contract/IMobility.h"

using namespace inet;
using namespace std;

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
    delete msg;
}

double ContactTracingApp::calculateDistance(ContactTracingMessage *msg) {
    return msg->getCoord().distance(this->mobility->getCurrentPosition());
}
bool ContactTracingApp::isInRange(ContactTracingMessage *msg) {
    return this->calculateDistance(msg)<=par("range").doubleValue();
}

string ContactTracingApp::strUuid(){
    std::stringstream ss;
    ss << std::setw(32) << std::setfill('0') << this->getNodeId();
    string uuid = ss.str();
    uuid = uuid.insert(20, "-");
    uuid = uuid.insert(16, "-");
    uuid = uuid.insert(12, "-");
    uuid = uuid.insert(8, "-");
    return uuid;
}

void ContactTracingApp::finish() {
    cModule *network = cSimulation::getActiveSimulation()->getSystemModule();
    stringstream folderName;
}

double ContactTracingApp::getRandomDelay() {
    double time = par("broadcastTime").doubleValue();
    return time;
}

string ContactTracingApp::getNodeName() {
    std::stringstream ss;
    ss << "Node" << this->getNodeId();
    string uuid = ss.str();
    return uuid;
}

int ContactTracingApp::getNodeId(){
    int id = par("UUID").intValue();
    if(!id) {
        string fullName = this->getParentModule()->getFullName();
        unsigned first = fullName.find("[");
        unsigned last = fullName.find_last_of("]");
        string idstr = fullName.substr(first+1, last-first-1);
        id = stoi(idstr);
    }

    return id+1;
}

void ContactTracingApp::initialize()
{
    cModule *network = cSimulation::getActiveSimulation()->getSystemModule();
    this->nodes = new vector<cModule*>();
    this->discoverNetworkNodes();
    this->mobility = check_and_cast<IMobility *>(this->getParentModule()->getSubmodule("mobility"));
    this->id = this->getNodeId();
    this->history = new ContactHistory(network->par("simName").stringValue(), network->par("simDesc").stringValue());
    this->broadcast = new cMessage();
    this->logPos = new cMessage();
    scheduleAfter(this->getRandomDelay(), this->broadcast);
    if(par("logpos").boolValue())
        scheduleAfter(par("logPosPeriod").doubleValue(), this->logPos);
}

void ContactTracingApp::handleMessage(cMessage *msg)
{

    if(msg->isSelfMessage() && msg==this->broadcast)
    {
        ContactTracingMessage *newMsg = new ContactTracingMessage();
        newMsg->setCoord(this->mobility->getCurrentPosition());
        newMsg->setData(ContactData(this->id));

        this->broadcastMsg(newMsg);
        scheduleAfter(this->getRandomDelay(), msg);
    } else if (msg->isSelfMessage() && msg==this->logPos) {
//        this->logPosition();
        scheduleAfter(par("logPosPeriod").doubleValue(), msg);
    } else {
        ContactTracingMessage *cpy = check_and_cast<ContactTracingMessage*>(msg);
        if(this->isInRange(cpy)){
            this->history->registerContact(cpy->getData());
        } else {
            this->history->closeContact(this->id, cpy->getData());
        }
        delete msg;
    }
}

Define_Module(ContactTracingApp);
