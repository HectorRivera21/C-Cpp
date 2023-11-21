import pandas as pd
import sqlite3 as sql

# data extraction
Musicians = pd.read_csv('Data/musician.csv')
MusicianAlbum = pd.read_csv('Data/musician-album.csv')
Instruments = pd.read_csv('Data/instrument.csv')
Albums = pd.read_csv('Data/album.csv')
AlbumInstrumnet = pd.read_csv('Data/album-instrument.csv')
# print(Music
Dlist = [Musicians, Instruments, Albums]
Tname = ['Musicians', 'Intruments', 'Albums']
# cleaing up data?
Musicians.columns = Musicians.columns.str.strip()

#connection
connection = sql.connect('DB/Music.db')

# data to SQLite
for i in range(len(Dlist)):
    Dlist[i].to_sql(f'{Tname[i]}', connection, if_exists='replace',index=False)

cur = connection.cursor()

cur.execute('SELECT name FROM Musicians')

rows = cur.fetchall()
i = 1
for row in rows:
    for str in row:
        print(f'{i}. {str}')
        if i == len(rows):
            print(f'Total Musicians: {i}')
        i+=1

#close connection
connection.close()