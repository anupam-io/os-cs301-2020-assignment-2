import csv
import matplotlib.pyplot as plt

cache_size = []
fifo = []
rndm = []
lru = []
applru = []

with open('outputs.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
        if len(row) == 0:
            break
        
        cache_size.append(int(row[0]))
        fifo.append(float(row[1]))
        rndm.append(float(row[2]))
        lru.append(float(row[3]))
        applru.append(float(row[4]))
        line_count += 1

# SHOW THIS GRAPH

  

plt.plot(cache_size, fifo, 'o', label = 'fifo', ls = ('dotted'), linewidth = 1) 
plt.plot(cache_size, rndm, 's', label = 'rndm', ls = ('dotted'), linewidth = 2) 
plt.plot(cache_size, lru, 'd', label = 'lru', ls = ('dotted'), linewidth = 3) 
plt.plot(cache_size, applru, 'v', label = 'applru', ls = ('dotted'), linewidth = 4) 
  
# naming the x-axis 
plt.xlabel('cache-size') 
  
# naming the y-axis 
plt.ylabel('hit rate') 
  
  
# get current axes command 
ax = plt.gca() 
  
# set the interval by  which  
# the x-axis set the marks 
plt.xticks(list(range(0, 110, 10))) 
  
# set the intervals by which y-axis 
# set the marks 
plt.yticks(list(range(0, 110, 10))) 
  
# legend denotes that what color  
# signifies what 
ax.legend(['fifo', 'rndm', 'lru', 'applru']) 

# gives a title to the Graph 
plt.title('Cache Page Replacement policies performance')   
plt.show() 




# plt.plot(cache_size, fifo)
# plt.plot(cache_size, rndm)
# plt.plot(cache_size, lru)
# plt.plot(cache_size, applru)


# plt.xlabel('cache-size') 
# plt.ylabel('hit rate')
# plt.show()