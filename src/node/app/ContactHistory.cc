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

ContactHistory::ContactHistory() {
    this->history = new map<int, vector<ContactWindow*>*>();
    this->contactAccumulator = new map<int, double>();
}

ContactHistory::~ContactHistory() {
    // TODO Auto-generated destructor stub

}

ContactWindow* ContactHistory::getLastWindowFor(ContactData &data) {
    map<int, vector<ContactWindow*>*>::iterator it = this->history->find(data.getOwnId());
    if( it == this->history->end()) {
        return nullptr;
    } else {
        return it->second->back();
    }
}

void ContactHistory::createNewEntry(ContactData &data) {
    vector<ContactWindow*> *winList = new vector<ContactWindow*>();
    stringstream vectorName;
    vectorName << "node_" << data.getOwnId();
    this->history->insert(pair<int, vector<ContactWindow*>*>(data.getOwnId(), winList));
}

void ContactHistory::insertWindow(ContactData &data) {
    map<int, vector<ContactWindow*>*>::iterator it = this->history->find(data.getOwnId());
    it->second->push_back(new ContactWindow(data.getOwnId()));
}

void ContactHistory::registerContact(ContactData data) {
    ContactWindow *last = this->getLastWindowFor(data);
    simtime_t currentTime = simTime();
    if(last==nullptr){
        this->createNewEntry(data);
        this->insertWindow(data);
    } else {
        if(last->isClosed()) {
            this->insertWindow(data);
        } else {
            last->updateEndTimestamp(currentTime);
        }
    }
}

void ContactHistory::closeContact(ContactData data) {
    ContactWindow *last = this->getLastWindowFor(data);
    if(last!=nullptr && !last->isClosed()){
        last->setClosed();
    }
}

vector<ContactWindow*>* ContactHistory::getAllWindows() {
    vector<ContactWindow*> *list = new vector<ContactWindow*>();
    for(auto it : *this->history) {
        list->insert(list->end(), it.second->begin(), it.second->end());
    }
    return list;
}
