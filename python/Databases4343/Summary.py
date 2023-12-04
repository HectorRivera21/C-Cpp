from numpy import sort
import pandas as pd
import sqlite3 as sql
from concurrent.futures import ThreadPoolExecutor
from itertools import zip_longest

#taDataClean extraction
Musicians = pd.read_csv('Data/musician.csv')
MusicianAlbum = pd.read_csv('Data/musician-album.csv')
Instruments = pd.read_csv('Data/instrument.csv')
Albums = pd.read_csv('Data/album.csv')
AlbumInstrumnet = pd.read_csv('Data/album-instrument.csv')

#list for simplitcity sake
Dlist = [Musicians, Instruments, Albums, MusicianAlbum, AlbumInstrumnet]
Tname = ['Musicians', 'Instruments', 'Albums','MusicianAlbum','AlbumInstruments']

#open DB connection
connection = sql.connect('DB/Music.db')
# data to SQLite
for i in range(len(Dlist)):
    #supposed cleaning up data ?????
    Dlist[i].columns = Dlist[i].columns.str.strip()
    #inject to the SQL DB
    Dlist[i].to_sql(f'{Tname[i]}', connection, if_exists='replace',index=False)
#close the connection
connection.close()


#func to retrieve data from DB using queries supplied
def fetch_data(query):
    connection = sql.connect("DB/Music.db")
    cursor = connection.cursor()
    cursor.execute(query)
    data = cursor.fetchall()
    connection.close()
    return data

#list of queries i want to use
queries = ["SELECT name FROM Musicians", "SELECT name FROM Albums", "SELECT type FROM Instruments"]

#extract all data through parallelism 
with ThreadPoolExecutor() as executor:
    Data = list(executor.map(fetch_data, queries))

totals = [sum(1 for row in dataset) for dataset in Data]

print("Musicans\tAlbums\tInstruments")
print("----------------------------------------------------------")

for row in zip_longest(*Data, fillvalue=""):
    print("\t ".join(map(str,row)))
print("\t".join(f"Total: {total}"for total in totals))
print("----------------------------------------------------------\n")

Data = fetch_data("SELECT name, count(name)AS total_albums FROM Musicians NATURAL JOIN MusicianAlbum GROUP BY name ORDER BY total_albums DESC")
print("name\t total_albums")
print('--------------------')
for row in Data : print(row)
print('--------------------')