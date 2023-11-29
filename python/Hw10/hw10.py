import sqlite3
import os.path

print('SQLite version:')
print(sqlite3.version)

print('Loading the Database')
con = sqlite3.connect('hw10.db')
cur = con.cursor()
print('Success!')
print('Print the Whole Dataset:')

t = cur.execute('SELECT * FROM Sailor')
names = list(map(lambda x: x[0], t.description))
print(names)
print('--------------------')
for row in t : print(row)
print('--------------------')

t = cur.execute('SELECT * FROM Boat')
names = list(map(lambda x: x[0], t.description))
print(names)
print('--------------------')
for row in t: print(row)
print('--------------------')

t = cur.execute('SELECT * FROM Reserve')
names = list(map(lambda x: x[0], t.description))
print(names)
print('--------------------')
for row in t: print(row)
print('--------------------')




print('Q1: Find the name of the sailor who reserved all boats')

print('Your answer should include (sname)')
'''
Please Write Down Your Query for Q1 Below:
'''

answer = "SELECT Sailor.sname FROM Sailor WHERE NOT EXISTS (SELECT Boat.bid FROM Boat WHERE NOT EXISTS(SELECT Reserve.bid FROM Reserve WHERE Reserve.bid = Boat.bid AND Reserve.sid = Sailor.sid))"


t = cur.execute(answer)
names = list(map(lambda x: x[0], t.description))
print(names)
print('--------------------')
for row in t : print(row)
print('--------------------')


print('Q2: For each sailor who previously reserved a boat, find the total number of boats reserved by he/she')


print('Your answer should include (sid, counts)')
'''
Please Write Down Your Query for Q1 Below:
'''

answer = 'SELECT sid, COUNT(bid) AS count FROM Reserve GROUP BY sid'

t = cur.execute(answer)

names = list(map(lambda x: x[0], t.description))
print(names)
print('--------------------')
for row in t : print(row)
print('--------------------')



print('Q3: For the boat that is reserved the most, please return the bid and the counts')

print('Your answer should include (bid, counts)')

'''
Please Write Down Your Query for Q3 Below:
'''

answer = "SELECT bid, COUNT(bid) AS most_reserved FROM Reserve GROUP BY bid ORDER BY most_reserved DESC LIMIT 1"

t = cur.execute(answer)
names = list(map(lambda x: x[0], t.description))
print(names)
print('--------------------')
for row in t : print(row)
print('--------------------')
