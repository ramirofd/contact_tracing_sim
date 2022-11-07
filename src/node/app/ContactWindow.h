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

#ifndef NODE_APP_CONTACTWINDOW_H_
#define NODE_APP_CONTACTWINDOW_H_

#include <omnetpp.h>

using namespace std;
using namespace omnetpp;

class ContactWindow {
private:
    int contactId;
    int toldById;
    int hop;
    simtime_t start;
    simtime_t end;
    bool closed;
public:
    ContactWindow(int ctId, int tbId = -1, int hop = 1, simtime_t start = simTime(), bool closed = false);
    virtual ~ContactWindow();
    void updateEndTimestamp(simtime_t end);
    double getWindowLength();
    double getEndTime();
    bool isClosed();
    void setClosed();
    string asCsv();
};

#endif /* NODE_APP_CONTACTWINDOW_H_ */
