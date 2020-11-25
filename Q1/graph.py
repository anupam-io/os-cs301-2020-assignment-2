import csv
import matplotlib.pyplot as plt

no_threads = []
meter_s = [[], [], []]
meter_rw = [[], [], []]
meter_hoh = [[], [], []]

wl = 'wl'
filename = ['s_lock.csv', 'rw_lock.csv', 'hoh_lock.csv']

flag = False
for i in range(3):
    g = 0
    with open(wl+'/'+filename[i]) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            if len(row) == 0:
                g = g + 1
                if g == 3:
                    break
                else:
                    flag = True
                    continue
            if flag == False:
                no_threads.append(int(row[0]))
            if i == 0:
                meter_s[g].append(float(row[1]))
            elif i == 1:
                meter_rw[g].append(float(row[1]))
            else:
                meter_hoh[g].append(float(row[1]))
                
# SHOW THIS GRAPH

# print(no_threads)
# print(meter_s)

fig, ax = plt.subplots(1, 3)
for i in range(3):
    ax[i].plot(no_threads, meter_s[i],
               linewidth=2)
    ax[i].plot(no_threads, meter_rw[i],
               linewidth=2)
    ax[i].plot(no_threads, meter_hoh[i],
               linewidth=2)
    ax[i].legend(['SINLGE_LOCK', 'RW_LOCK', 'HOH_LOCK'])
    ax[i].set(xlabel='No. of concurrent threads', ylabel='Time(in microseconds)')

ax[0].set_title('READ workload')
ax[1].set_title('WRITE workload')
ax[2].set_title('MIXED workload')
fig.suptitle('Performance of locking techniques on different workloads')

fig.set_size_inches(16, 8)

# plt.show()
plt.savefig('plots/graph.png', dpi=300)
