import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Read the CSV file
df = pd.read_csv('coffee.csv')

# Step 2: Split the 'brew_data' column using the ';' separator
df['brew_data'] = df['brew_data'].apply(lambda x: x.split(';'))

# Step 3: Plot the data
brew_data =  0.0
for index, row in df.iterrows():
    tasty = row['tasty']
    brew_data = [float(value) if value != '' else 0.0 for value in row['brew_data']]
    time_points = [i/10 for i in range(len(brew_data))]
    print(time_points)

    plt.plot(time_points,brew_data, label=tasty) #if you want multilines
    plt.xlabel('Index')
    plt.ylabel('Brew Data Value')
    plt.title('Brew Data for Different Tasty')
    plt.legend()
    plt.show()
    # plt.savefig('${}.png', bbox_inches='tight')
#plt.plot(brew_data, label=tasty) #single line