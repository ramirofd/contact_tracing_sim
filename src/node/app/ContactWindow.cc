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

#include "ContactWindow.h"

ContactWindow::ContactWindow(int ctId, int tbId, int hop, simtime_t start, bool closed) {
    // TODO Auto-generated constructor stub
    this->contactId = ctId;
    this->toldById = tbId;
    this->hop = hop;
    this->start = start;
    this->end = start;
    this->closed = closed;
}

ContactWindow::~ContactWindow() {
    // TODO Auto-generated destructor stub

}

void ContactWindow::updateEndTimestamp(simtime_t end) {
    this->end = end;
}

double ContactWindow::getWindowLength() {
    return this->end.dbl()-this->start.dbl();
}

bool ContactWindow::isClosed() {
    return closed;
}

void ContactWindow::setClosed() {
    this->closed=true;
}

string ContactWindow::asCsv() {
    std::stringstream ss;
    ss << this->contactId <<',' << this->toldById <<','
            << this->hop <<',' << this->start <<',' << this->end;
    return ss.str();
}

int ContactWindow::getContactId(){
    return this->contactId;
}
int ContactWindow::getToldById(){
    return this->toldById;
}
int ContactWindow::getHop(){
    return this->hop;
}
double ContactWindow::getStartTime(){
    return this->start.dbl();
}

double ContactWindow::getEndTime() {
    return this->end.dbl();
}
