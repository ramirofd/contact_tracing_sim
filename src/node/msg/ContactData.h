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

#ifndef NODE_MSG_CONTACTDATA_H_
#define NODE_MSG_CONTACTDATA_H_

#include <string>

using namespace std;

class ContactData {
private:
    int ownUUID;
    int seenUUID;
public:
    ContactData();
    ContactData(int oUuid):ContactData(oUuid, -1){};
    ContactData(int oUuid, int sUuid);
    virtual ~ContactData();
    int getOwnId();
    int getSeenId();
};

#endif /* NODE_MSG_CONTACTDATA_H_ */

//ContactTracingMessage* ContactTracingMessage::ctMessageFactory(inet::Coord coord, omnetpp::opp_string uuid){
//    ContactTracingMessage *msg = new ContactTracingMessage();
//    msg->setPosition(coord.x, 0);
//    msg->setPosition(coord.y, 1);
//    msg->setUUID(uuid.c_str());
//    return msg;
//}
