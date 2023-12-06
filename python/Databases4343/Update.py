import argparse as AP
import sqlite3 as SQL
import sys

parser = AP.ArgumentParser()
parser.add_help
parser.add_argument('--add', action="store_true", default=False, help="add to table")
parser.add_argument('--delete', action="store_true", default=False, help="delete from table")
    
parser.add_argument('--table', type=str, default='', help="target table")
parser.add_argument('--record', type=str, default='', help="Info to be added/deleted \n 'data,adat,atad,dadw' ")

args = parser.parse_args()

if args.add == True and args.delete == True:
    sys.exit('to many args')

if args.add == True:
    
    sys.exit(f"added: {args.record} to Table: {args.table}")

if args.delete == True:

    sys.exit(f"deleted: {args.record} from Table: {args.table}")