import argparse as ap
import sqlite3 as sql
import sys
import re

def is_valid_record_format(argument):
    pattern = r'^[A-Z]+,\d+,\d{4},[A-Z]{2}$'
    return re.match(pattern, argument) is not None
    
def add_Record(arg):
    con = sql.connect('DB/Music.db')
    con.cursor().execute(f'INSERT INTO {arg.table}')
    con.commit
    con.close()
    

def delete_Record(arg):   
    con = sql.connect('DB/Music.db')
    con.cursor().execute('')
    con.commit()
    con.close()
    
parser = ap.ArgumentParser()
parser.add_help
parser.add_argument('--add', action="store_true", default=False, help="add to table")
parser.add_argument('--delete', action="store_true", default=False, help="delete from table")
    
parser.add_argument('--table', type=str, default='', help="target table")
parser.add_argument('--record', type=str, default='', help="Info to be added/deleted \n 'data,adat,atad,dadw' ")

args = parser.parse_args()

if args.add and args.delete:
    sys.exit('Too many arguments. Choose either --add or --delete.')
##########
if args.add:
    if not is_valid_record_format(args.record):
        sys.exit(f'wrong format {args.record}')
    add_Record(args)
    sys.exit(f'added: {args.record} to Table: {args.table}')
##########
if args.delete:
    if not is_valid_record_format(args.record):
        sys.exit(f'wrong format {args.record}')
    delete_Record(args)
    sys.exit(f'deleted: {args.record} from Table: {args.table}')