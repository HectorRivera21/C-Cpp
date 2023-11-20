from typing import Literal
import pandas as pd
# import numpy as np
import matplotlib.pyplot as plt

# Step 1: Read the CSV file
df = pd.read_csv('coffee.csv')

# Step 2: Split the 'brew_data' column using the ';' separator
df['brew_data'] = df['brew_data'].apply(lambda x: x.split(';'))

num_plots = len(df)
num_columns = 2  # You can adjust the number of columns as needed
num_rows = (num_plots + num_columns - 1) // num_columns
fig, axs = plt.subplots(num_rows, num_columns, figsize=(12, 4 * num_rows))
# Step 3: Plot the data

brew_data =  0.0
for index, row in df.iterrows():
    tasty = row['tasty']
    brew_data = [float(value) if value != '' else 0.0 for value in row['brew_data']]  # Convert values to float
    
    row_index = 1 # num_columns
    col_index = 1

    axs[row_index, col_index].plot(brew_data, label=tasty)
    axs[row_index, col_index].set_title(tasty)
    axs[row_index, col_index].set_xlabel('Index')
    axs[row_index, col_index].set_ylabel('Brew Data Value')
    axs[row_index, col_index].legend()
    #     plt.plot(brew_data, label='tasty')#multiline
# #plt.plot(brew_data, label='tasty') #singleline

# Step 4: Customize the plot
plt.tight_layout()
plt.show()