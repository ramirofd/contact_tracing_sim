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

#include "ContactHistory.h"

using namespace std;

ContactHistory::ContactHistory(){
    // TODO Auto-generated constructor stub
}

ContactHistory::ContactHistory(const char* dbName, const char* name, const char* desc) {
    this->history = new map<int, ContactWindow*>();
    this->dbName = dbName;
    DataBaseConn::getInstance(dbName).insertSimulation(name, desc);
}

ContactHistory::~ContactHistory() {
    // TODO Auto-generated destructor stub

}

ContactWindow* ContactHistory::getLastWindowFor(ContactData &data) {
    map<int, ContactWindow*>::iterator it = this->history->find(data.getOwnId());
    if( it == this->history->end()) {
        return nullptr;
    } else {
        return it->second;
    }
}

void ContactHistory::setEmpty(ContactData &data) {
    map<int, ContactWindow*>::iterator it = this->history->find(data.getOwnId());
    if( it != this->history->end()) {
        it->second = nullptr;
    }
}

void ContactHistory::createNewEntry(ContactData &data) {
    map<int, ContactWindow*>::iterator it = this->history->find(data.getOwnId());
    if( it == this->history->end()) {
        this->history->insert(pair<int, ContactWindow*>(data.getOwnId(), new ContactWindow(data.getOwnId())));
    } else {
        it->second = new ContactWindow(data.getOwnId());
    }

}

void ContactHistory::registerContact(ContactData data) {
    ContactWindow *last = this->getLastWindowFor(data);
    simtime_t currentTime = simTime();
    if(last==nullptr){
        EV<<"New";
        this->createNewEntry(data);
    } else {
        EV<<"Update";
        last->updateEndTimestamp(currentTime);
    }
}

void ContactHistory::closeContact(int node, ContactData data, double node_velocity) {
    ContactWindow *last = this->getLastWindowFor(data);
    if(last!=nullptr){
        EV<<"Stored";
        DataBaseConn::getInstance(this->dbName.c_str()).insertWindow(node,last, node_velocity);
        this->setEmpty(data);
    }
}

vector<ContactWindow*>* ContactHistory::getAllWindows() {
    vector<ContactWindow*> *list = new vector<ContactWindow*>();
//    for(auto it : *this->history) {
//        list->insert(list->end(), it.second->begin(), it.second->end());
//    }
    return list;
}
