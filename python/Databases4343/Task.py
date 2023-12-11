import pandas as pd
import sqlite3 as sql

DB = 'DB/Music.db'

def createtables():
    connection = sql.connect(DB)
    cursor = connection.cursor()
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS "Musicians" (
	"num"	INTEGER NOT NULL,
	"street"	TEXT NOT NULL,
	"str_type"	TEXT NOT NULL,
	"name"	TEXT NOT NULL,
	"ssn"	INTEGER NOT NULL UNIQUE,
	PRIMARY KEY("ssn")
    )
    """)
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS "Albums" (
	"Name"	TEXT NOT NULL,
	"id"	INTEGER NOT NULL UNIQUE,
	"date"	INTEGER NOT NULL,
	"type"	TEXT NOT NULL,
	PRIMARY KEY("id")
    )
    """)
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS "Instruments" (
	"id"	INTEGER NOT NULL UNIQUE,
	"type"	TEXT NOT NULL,
	"key"	TEXT NOT NULL,
	PRIMARY KEY("id")
    )
    """)
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS "MusicianAlbum" (
	"ssn"	INTEGER NOT NULL,
	"album_id"	INTEGER NOT NULL,
	PRIMARY KEY("ssn","album_id"),
	FOREIGN KEY("ssn") REFERENCES "Musicians"("ssn"),
	FOREIGN KEY("album_id") REFERENCES "Albums"("id")
    )
    """)
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS "AlbumInstruments" (
	"album_id"	INTEGER NOT NULL,
	"instrument_id"	INTEGER NOT NULL,
	FOREIGN KEY("instrument_id") REFERENCES "Instruments"("id"),
	FOREIGN KEY("album_id") REFERENCES "Albums"("id"),
	PRIMARY KEY("album_id","instrument_id")
    )
    """)
    connection.commit()
    connection.close()

def insert_data_sqlite(dataframes, table_names):
    connection = sql.connect(DB)

    for i, dataframe in enumerate(dataframes):
        dataframe.columns = dataframe.columns.str.strip()
        dataframe.to_sql(table_names[i], connection, if_exists='append', index=False)

    connection.close()

Musicians = pd.read_csv('Data/musician.csv')
MusicianAlbum = pd.read_csv('Data/musician-album.csv')
Instruments = pd.read_csv('Data/instrument.csv')
Albums = pd.read_csv('Data/album.csv')
AlbumInstrumnet = pd.read_csv('Data/album-instrument.csv')

# List for simplicity's sake
Dlist = [Musicians, Instruments, Albums, MusicianAlbum, AlbumInstrumnet]
Tname = ['Musicians', 'Instruments', 'Albums', 'MusicianAlbum', 'AlbumInstruments']

# Create tables in SQLite
createtables()

# Insert data into SQLite without affecting constraints
insert_data_sqlite(Dlist, Tname)