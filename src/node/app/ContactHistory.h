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

#ifndef NODE_APP_CONTACTHISTORY_H_
#define NODE_APP_CONTACTHISTORY_H_

#include "ContactWindow.h"
#include "src/node/msg/ContactTracingMessage_m.h"
#include "src/node/app/DataBaseConn.h"

using namespace std;

class ContactHistory {
private:
    string dbName;
    map<int, ContactWindow*> *history;
    ContactWindow* getLastWindowFor(ContactData &data);
    void setEmpty(ContactData &data);
    void updateContactAccumulator(ContactData &data);
    void createNewEntry(ContactData &data);
public:
    ContactHistory();
    ContactHistory(const char* dbName, const char* name, const char* desc);
    virtual ~ContactHistory();
    void registerContact(ContactData data);
    void closeContact(int node, ContactData data, double node_velocity);
    vector<ContactWindow*>* getAllWindows();
};

#endif /* NODE_APP_CONTACTHISTORY_H_ */
