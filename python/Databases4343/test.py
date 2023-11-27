from concurrent.futures import ThreadPoolExecutor
from itertools import zip_longest
import sqlite3


# Function to retrieve data from the SQLite database
def fetch_data(query):
    connection = sqlite3.connect("DB/Music.db")
    cursor = connection.cursor()
    cursor.execute(query)
    data = cursor.fetchall()
    connection.close()
    return data

# List of queries to execute concurrently
queries = ["SELECT name FROM Musicians", "SELECT name FROM Albums", "SELECT type FROM Instruments"]

# Using ThreadPoolExecutor for parallelism
with ThreadPoolExecutor() as executor:
    # The map function applies the fetch_data function to each query in the list in parallel
    results = list(executor.map(fetch_data, queries))

data_for_printing = list(zip_longest(*results, fillvalue=None))
totals = [sum(1 for row in dataset if row is not None) for dataset in data_for_printing]

# Print the results in columns side by side with totals at the bottom
for row in data_for_printing:
    print("\t".join(str(value) if value is not None else "" for value in row))

# Print the totals at the bottom
print(totals)