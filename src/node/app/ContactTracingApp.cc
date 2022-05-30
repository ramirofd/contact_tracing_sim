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
#include "src/node/msg/ContactTracingMessage_m.h"

using namespace inet;

Define_Module(ContactTracingApp);

void ContactTracingApp::initialize()
{
    scheduleAfter(par("broadcastTime"), new cMessage());
}

void ContactTracingApp::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        ContactTracingMessage *newMsg = new ContactTracingMessage();
        IMobility *mobility = check_and_cast<IMobility *>(this->getParentModule()->getSubmodule("mobility"));
        newMsg->setCoord(mobility->getCurrentPosition());
        this->send(newMsg, gate("data$o"));
        scheduleAfter(par("broadcastTime"), msg);
    } else {
        delete msg;
    }
}
