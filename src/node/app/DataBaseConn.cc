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

#include "DataBaseConn.h"

DataBaseConn::DataBaseConn() {
    if(sqlite3_open("results.db", &this->myDB) != SQLITE_OK) {
        sqlite3_close(this->myDB);
        throw std::runtime_error("An error occurred during DB connection");
    }
    this->initTables();
}

DataBaseConn::~DataBaseConn() {
//    sqlite3_close(this->myDB);
}


void DataBaseConn::initTables(){
    this->createSimulationTable();
    this->createWindowTable();
}

void DataBaseConn::createSimulationTable(){
    // Create a table
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS simulation (run INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, description TEXT)";
    int rc = sqlite3_exec(this->myDB, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        EV_ERROR << "Failed to execute statement: " << sqlite3_errmsg(this->myDB);
        sqlite3_close(this->myDB);
        throw std::runtime_error("Failed to create table: SIMULATION");
    }
}

void DataBaseConn::createWindowTable(){
    // Create a table
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS window (id INTEGER PRIMARY KEY AUTOINCREMENT, node INTEGER, contact_id INTEGER, told_by_id INTEGER, hop INTEGER, start REAL, end REAL, closed INTEGER, run_id INTEGER, FOREIGN KEY(run_id) REFERENCES simulation(run))";
    int rc = sqlite3_exec(this->myDB, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        EV_ERROR << "Failed to execute statement: " << sqlite3_errmsg(this->myDB);
        sqlite3_close(this->myDB);
        throw std::runtime_error("Failed to create table: WINDOW");
    }
}

void DataBaseConn::insertWindow(int node, ContactWindow* win){
    // Prepare an INSERT statement
    const char *insertSQL = "INSERT INTO window (node, contact_id, told_by_id, hop, start, end, closed, run_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *insertStmt;
    int rc = sqlite3_prepare_v2(this->myDB, insertSQL, -1, &insertStmt, 0);
    if (rc != SQLITE_OK) {
        EV_ERROR << "Failed to execute statement: " << sqlite3_errmsg(this->myDB);
        sqlite3_close(this->myDB);
        throw std::runtime_error("Failed preparing window insert");
    }
    sqlite3_bind_int(insertStmt, 1, node);
    sqlite3_bind_int(insertStmt, 2, win->getContactId());
    sqlite3_bind_int(insertStmt, 3, win->getToldById());
    sqlite3_bind_int(insertStmt, 4, win->getHop());
    sqlite3_bind_double(insertStmt, 5, win->getStartTime());
    sqlite3_bind_double(insertStmt, 6, win->getEndTime());
    sqlite3_bind_int(insertStmt, 7, 1);
    sqlite3_bind_int(insertStmt, 8, this->currentSimulation);
    rc = sqlite3_step(insertStmt);
    if (rc != SQLITE_DONE) {
        EV_ERROR << "Failed to execute statement: " << sqlite3_errmsg(this->myDB);
        sqlite3_finalize(insertStmt);
        sqlite3_close(this->myDB);
        throw std::runtime_error("Failed inserting window");
    }
    sqlite3_finalize(insertStmt);
}

void DataBaseConn::insertSimulation(const char* name, const char* description){
    if(this->currentSimulation==-1){
        const char *insertSQL = "INSERT INTO simulation (name, description) VALUES (?, ?)";
        sqlite3_stmt *insertStmt;
        int rc = sqlite3_prepare_v2(this->myDB, insertSQL, -1, &insertStmt, 0);
        if (rc != SQLITE_OK) {
            EV_ERROR << "Failed to execute statement: " << sqlite3_errmsg(this->myDB);
            sqlite3_close(this->myDB);
            throw std::runtime_error("Failed preparing simulation insert");
        }
        sqlite3_bind_text(insertStmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(insertStmt, 2, description, -1, SQLITE_STATIC);
        rc = sqlite3_step(insertStmt);
        if (rc != SQLITE_DONE) {
            EV_ERROR << "Failed to execute statement: " << sqlite3_errmsg(this->myDB);
            sqlite3_finalize(insertStmt);
            sqlite3_close(this->myDB);
            throw std::runtime_error("Failed inserting simulation");
        }
        this->currentSimulation = static_cast<int>(sqlite3_last_insert_rowid(this->myDB));
        sqlite3_finalize(insertStmt);
    }
}
