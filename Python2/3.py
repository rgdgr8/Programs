import sqlite3
from random import randint

conn = sqlite3.connect('hospital.sqlite')
cur = conn.cursor()

cur.executescript('''
CREATE TABLE IF NOT EXISTS DOCTOR(
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
    name TEXT,
    hos_id INTEGER,
    spec_id INTEGER,
    exp INTEGER
);

CREATE TABLE IF NOT EXISTS HOSPITAL(
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
    name TEXT
);

CREATE TABLE IF NOT EXISTS SPECIALITY(
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
    name TEXT
);''')

for _ in range(1,5):
    name = f'hospital{_}'
    cur.execute('INSERT INTO HOSPITAL (name) VALUES (?)',(name,))
for _ in range(1,9):
    name = f'speciality{_}'
    cur.execute('INSERT INTO SPECIALITY (name) VALUES (?)',(name,))
for _ in range(1,13):
    name = f'doctor{_}'
    hos_id = randint(1,4)
    spec_id = randint(1,8)
    exp = randint(1,30)
    cur.execute('INSERT INTO DOCTOR (name,hos_id,spec_id,exp) VALUES (?,?,?,?)',(name,hos_id,spec_id,exp))

cur.execute('SELECT DOCTOR.name,SPECIALITY.name,DOCTOR.exp,HOSPITAL.name FROM DOCTOR JOIN SPECIALITY JOIN HOSPITAL ON DOCTOR.spec_id = SPECIALITY.id AND DOCTOR.hos_id = HOSPITAL.id ORDER BY DOCTOR.exp DESC')

'''cur.execute('SELECT * FROM DOCTOR')
res = cur.fetchall()
for _ in res:
    print(_)
cur.execute('SELECT * FROM HOSPITAL')
res = cur.fetchall()
for _ in res:
    print(_)
cur.execute('SELECT * FROM SPECIALITY')'''
res = cur.fetchall()
for _ in res:
    print(_)
