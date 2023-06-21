import argparse
import sqlite3
import time

out_db_conn = sqlite3.connect('out.db')
out_cursor = out_db_conn.cursor()

seeds = [2307, 14498, 22909, 50582, 52778, 53090, 55245, 56497, 91267, 93413, 113514, 123437, 145443, 153498, 156305, 197417]
# seeds = [2307, 14498]

out_cursor.execute("CREATE TABLE IF NOT EXISTS window (id INTEGER PRIMARY KEY AUTOINCREMENT, node INTEGER, contact_id INTEGER, told_by_id INTEGER, hop INTEGER, start REAL, end REAL, closed INTEGER, run_id INTEGER, velocity REAL)")

for seed in seeds:
    out_db_conn = sqlite3.connect('out.db')
    out_cursor = out_db_conn.cursor()
    db_name = f'results_{seed}.db'
    in_db_conn = sqlite3.connect(db_name)
    in_cursor = in_db_conn.cursor()

    # obtengo el maximo final de la base de datos resultante
    out_cursor.execute("SELECT MAX(end) FROM window")
    max_end = out_cursor.fetchone()[0]
    max_end = max_end if max_end is not None else 0
    
    # obtengo las entradas de las de la base de datos original
    in_cursor.execute("SELECT * FROM window")
    original_windows = in_cursor.fetchall() #5 y 6
    for i,window in enumerate(original_windows):
        window = list(window[1:])
        window[5] += max_end
        window[6] += max_end
        original_windows[i] = tuple(window)
    
    out_cursor.executemany("INSERT INTO window (node, contact_id, told_by_id, hop, start, end, closed, run_id, velocity) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)", original_windows)
    out_db_conn.commit()

    in_db_conn.close()
    out_db_conn.close()
    time.sleep(1)
    


