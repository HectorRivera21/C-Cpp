import argparse as ap
import sqlite3 as sql
import sys

def fetch_cols(table):
    con = sql.connect('DB/Music.db')
    cur = con.cursor()
    cur.execute(f'PRAGMA table_info({table})')
    data = cur.fetchall()
    con.close()
    return data
def primary_key(arg):
    col = fetch_cols(arg.table)
    columns = [cols[1] for cols in col]
    for i in range(len(columns)):
        if columns[i] == "id":
            return i
        elif columns[i] == "ssn":
            return i

def update(arg):
    col_info = fetch_cols(arg.table)
    columns = [cols[1] for cols in col_info]

    col = ', '.join(columns)
    values = ', '.join('?' for _ in columns)

    record = tuple(arg.record.split(','))
    prime_key_index = primary_key(arg)
  
    con = sql.connect('DB/Music.db')
    cursor = con.cursor()

    if arg.add:
        cursor.execute(f'INSERT INTO {arg.table} ({col}) VALUES ({values})',record)
        con.commit()
        con.close()
        sys.exit(f'added: {arg.record} to Table: {arg.table}')
    if arg.delete:
        if prime_key_index is not None:
            cursor.execute(f'DELETE FROM {arg.table} WHERE {columns[prime_key_index]} = ?', (record[prime_key_index],))
            con.commit()
            con.close()
            sys.exit(f'deleted: {args.record} from Table: {args.table}')
    
    
parser = ap.ArgumentParser()
parser.add_help
parser.add_argument('--add', action="store_true", default=False, help="add to table")
parser.add_argument('--delete', action="store_true", default=False, help="delete from table")
    
parser.add_argument('--table', type=str, default='', help="target table")
parser.add_argument('--record', type=str, default='', help="Info to be added/deleted \n 'data,adat,atad,dadw' ")

args = parser.parse_args()

if args.add and args.delete:
    sys.exit('Too many arguments. Choose either --add or --delete.')
elif not args.add and not args.delete:
    sys.exit('No arguments provided. Choose either --add or --delete.')
##########
update(args)