import csv
import matplotlib.pyplot as plt

data = {}
with open('timing.csv') as f:
    reader = csv.DictReader(f)
    for row in reader:
        N = int(row['size'])
        T = int(row['threads'])
        t = float(row['time'])
        data.setdefault(N, {})[T] = t

for N, times in sorted(data.items()):
    Ts = sorted(times.keys())
    t1 = times[1]
    speedups = [t1 / times[T] for T in Ts]

    plt.plot(Ts, speedups, marker='o', label=f'{N}×{N}')

plt.xlabel('Number of threads')
plt.ylabel('Speedup over 1 thread')
plt.xticks([1,2,4,8])
plt.legend(title='Matrix size')
plt.grid(True)
plt.title('Matrix Addition Speedup')
plt.tight_layout()
plt.show()
