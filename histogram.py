import matplotlib.pyplot as plt
import numpy as np

values = None
with open('histogram.txt', 'r') as f:
    line = f.read()
    values = list(map(lambda x: int(x), line.split()))
    print(len(line))

counts = np.bincount(values)
max_height, min_height = counts[np.argmax(counts)], counts[np.argmin(counts)]
if min_height != 0 and max_height / min_height > 100:
    _ = plt.hist(values, bins = 'auto', log=True)
else:
    _ = plt.hist(values, bins = 'auto', log=False)
plt.show()