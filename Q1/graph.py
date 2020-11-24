import csv
import sys
import matplotlib.pyplot as plt



no_threads = [[], [], []]
time_elapsed = [[], [], []]
g = 0

with open(sys.argv[1]) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        if len(row) == 0:
            g = g + 1
            if g == 3:
                break
            else:
                continue

        no_threads[g].append(int(row[0]))
        time_elapsed[g].append(float(row[1]))

# SHOW THIS GRAPH

fig, ax = plt.subplots(1, 3, sharex=True, sharey=True)
for i in range(3):
    ax[i].plot(no_threads[i], time_elapsed[i], label='fifo',
               ls=('dashed'), linewidth=1)


ax[0].set_title('READ workload')
ax[1].set_title('WRITE workload')
ax[2].set_title('MIXED workload')
fig.suptitle('Performance of locking techniques on different workloads')

fig.set_size_inches(8, 6)

plt.show()
#plt.savefig('plots/tm_graph.png', dpi=500)
