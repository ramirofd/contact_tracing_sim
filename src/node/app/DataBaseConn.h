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

#ifndef NODE_APP_DATABASECONN_H_
#define NODE_APP_DATABASECONN_H_

#include <omnetpp.h>
#include <sqlite3.h>
#include "ContactWindow.h"

using namespace omnetpp;
class DataBaseConn {
public:
    static DataBaseConn& getInstance(const char* dbName){
        static DataBaseConn instance(dbName);
        return instance;
    }
    void insertWindow(int node, ContactWindow* win, double velocity);
    void insertSimulation(const char* name,const char* description);

private:
    //Con-Destructors
    DataBaseConn(const char* dbName);
    virtual ~DataBaseConn();

    // Operators
    DataBaseConn(const DataBaseConn&) = delete;
    DataBaseConn& operator=(const DataBaseConn&) = delete;

    //atts
    sqlite3* myDB;
    int currentSimulation = -1;

    //methods
    void initTables();
    void createSimulationTable();
    void createWindowTable();

};

#endif /* NODE_APP_DATABASECONN_H_ */
