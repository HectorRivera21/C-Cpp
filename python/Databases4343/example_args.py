import argparse as AP
import sqlite3 as SQL

parser = AP.ArgumentParser()
parser.add_help
parser.add_argument('--add', action="store_true", default=False, help="add to table")
parser.add_argument('--delete', action="store_true", default=False, help="delete from table")

parser.add_argument('--table', type=str, default='', help="target table")

args = parser.parse_args()

print(args.add)
print(args.delete)
print(args.table)