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
infoFileName = runDir + '/infoFile.csv'

infoFile = open(infoFileName, 'r')
info = infoFile.readline()
infoarr = info.split(',')

# Set the style
sns.set_style("whitegrid")
# sns.set_context("paper", font_scale=1.5, rc={"lines.linewidth": 2.5})

# Read the data
df = pd.read_csv(filename + '.csv')
# print(df)

# Filter the data
def filter(row):
    cores = row.compilation_notes.split(';')
    # print(cores)
    if cores[1] == 'SERIAL_CODE':
        return 0
    return cores[1]
    
df_weak = df[(df['compilation_notes'].str.contains('WEAK_SCALING') == True) & (df['run_notes']==infoarr[1])]
df_weak['cores'] = df_weak.apply(lambda row: filter(row), axis=1)

print('df_strong',df_weak)

# # Create a line plot
sns.lineplot(x=df_weak['cores'].astype(str), y='matMul_wallTime[us]', data=df_weak, color='red', label='Serial')
sns.lineplot(x=df_weak['cores'].astype(str), y='matMulPar_wallTime[us]', data=df_weak, color='blue', label='Parallel')

# # # Add title and axis names
plt.title('Weak scaling')
plt.xlabel('Cores')
plt.ylabel('Time [us]')
# plt.xscale('log')
plt.yscale('log')

ticks = []
ticks_labels = []
ticks.append(0)
ticks_labels.append('Serial')

for i in range(0, 7):
    ticks.append(i+1)
    ticks_labels.append(str(2**i))

plt.xticks(ticks, ticks_labels)
# plt.legend()
plt.savefig(img_filename+ '-weakScaling-' + infoarr[1] + '.png')
plt.show()

# plt.yscale('log')
# plt.savefig(img_filename + '-log.png')
