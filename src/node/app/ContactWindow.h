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
    string UUID;
    string toldByUUID;
    int hop;
    simtime_t start;
    simtime_t end;
public:
    ContactWindow();
    virtual ~ContactWindow();
};

#endif /* NODE_APP_CONTACTWINDOW_H_ */
