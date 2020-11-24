import csv
import matplotlib.pyplot as plt

cache_size = [[], [], []]
fifo = [[], [], []]
rndm = [[], [], []]
lru = [[], [], []]
applru = [[], [], []]

g = 0
with open('outputs.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
        if len(row) == 0:
            g = g + 1
            if g == 4:
                break
            else:
                continue

        cache_size[g].append(int(row[0]))
        fifo[g].append(float(row[1]))
        rndm[g].append(float(row[2]))
        lru[g].append(float(row[3]))
        applru[g].append(float(row[4]))
        line_count += 1

# SHOW THIS GRAPH

fig, ax = plt.subplots(1, 3, sharex=True, sharey=True)
for i in range(3):
    ax[i].plot(cache_size[i], fifo[i], label='fifo',
               ls=('dashed'), linewidth=1)
    ax[i].plot(cache_size[i], rndm[i], label='rndm',
               ls=('dotted'), linewidth=1)
    ax[i].plot(cache_size[i], lru[i], label='lru', ls=('dotted'), linewidth=1)
    ax[i].plot(cache_size[i], applru[i], label='applru',
               ls=('dotted'), linewidth=1)
    ax[i].legend(['fifo', 'rndm', 'lru', 'applru'])
    ax[i].set(xlabel='Cache size', ylabel='Hit rate')

ax[0].set_title('LOOP workload')
ax[1].set_title('RANDOM workload')
ax[2].set_title('LOCAL workload')
fig.suptitle('Cache Page Replacement policies performance')

fig.set_size_inches(8, 6)
plt.savefig('plots/hr_graph.png', dpi=500)
