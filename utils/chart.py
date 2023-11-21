#importo le librerie
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
import create_run_folder as crf

## Create the run folder
runDir = crf.createFolder()
if 'error' in runDir :
    print('Error on create run folder')
    runDir = './results'

filename = runDir + '/matMulFile'
img_filename = runDir + '/matMulImg'


# Set the style
sns.set_style("whitegrid")
# sns.set_context("paper", font_scale=1.5, rc={"lines.linewidth": 2.5})

# Read the data
df = pd.read_csv(filename + '.csv')
# df['wall_clock_time_routine2'].replace(to_replace=0, value=0.0000001, inplace=True)
print(df)
# print(df_block)

# Filter the data
df_test = df[df['compilation_notes'].str.contains('TEST_PARALLELISM')]

# Filter the data
def filter(row):
    cores = row.compilation_notes.split(';')
    # print(cores)
    if cores[1] == 'SERIAL_CODE':
        return 1
    return cores[1]

df_test['cores'] = df_test.apply(lambda row: filter(row), axis=1)


# # Create a line plot
sns.lineplot(x='matrix_size', y='matMul_wallTime[us]', data=df_test, label='Serial', color='red')
sns.lineplot(x='matrix_size', y='matMulPar_wallTime[us]', data=df_test, label='Parallel', color='blue')

# # Add title and axis names
plt.title('Wall time (whit 4 cores)')
plt.xlabel('Size')
plt.ylabel('Time [s]')
# plt.ylabel('$t [us]$')
# plt.xscale('log')
# plt.yscale('log')

ticks = []
ticks_labels = []

for i in range(9, 12):
    ticks.append(2**i)
    ticks_labels.append(str(2**i))
    
plt.xticks(ticks, ticks_labels)
plt.legend()
plt.savefig(img_filename + '-test-par.png')
plt.show()