import argparse
import sqlite3

# Parse command-line arguments
parser = argparse.ArgumentParser()
parser.add_argument('--source', default='results.db', help='Source SQLite file name')
parser.add_argument('--destination', default='out.db', help='Destination SQLite file name')
args = parser.parse_args()

# Connect to the source database file
source_conn = sqlite3.connect(args.source)
source_cursor = source_conn.cursor()

# Connect to the destination database file
destination_conn = sqlite3.connect(args.destination)
destination_cursor = destination_conn.cursor()

# Query the simulation table
source_cursor.execute("SELECT * FROM simulation")
simulation_rows = source_cursor.fetchall()

# Create the simulation table in the destination database
destination_cursor.execute("CREATE TABLE IF NOT EXISTS simulation (run INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, description TEXT)")

# Insert the simulation rows into the destination database
destination_cursor.executemany("INSERT INTO simulation (run, name, description) VALUES (?, ?, ?)", simulation_rows)
destination_conn.commit()

# Query the window table
source_cursor.execute("SELECT * FROM window")
window_rows = source_cursor.fetchall()

# Create the window table in the destination database
destination_cursor.execute("CREATE TABLE IF NOT EXISTS window (id INTEGER PRIMARY KEY AUTOINCREMENT, node INTEGER, contact_id INTEGER, told_by_id INTEGER, hop INTEGER, start REAL, end REAL, closed INTEGER, run_id INTEGER, velocity REAL, FOREIGN KEY(run_id) REFERENCES simulation(run))")

# Insert the window rows into the destination database
destination_cursor.executemany("INSERT INTO window (id, node, contact_id, told_by_id, hop, start, end, closed, run_id, velocity) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", window_rows)
destination_conn.commit()

# Close the database connections
source_conn.close()
destination_conn.close()