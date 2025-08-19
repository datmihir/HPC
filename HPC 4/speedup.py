import matplotlib.pyplot as plt
import numpy as np

experiment_data = {
    "Ts":  1.104643,  
    "p_threads": [2, 4, 8, 16],
    "Tp": [ 1.027715,  0.662035 , 0.490151,  0.543763]
}

print("Generating speedup graph...")

ts = experiment_data["Ts"]
threads = experiment_data["p_threads"]
tp = experiment_data["Tp"]

fig, ax = plt.subplots(figsize=(10, 7))

plot_speedup = [ts / t for t in tp]
max_threads = max(threads)
ideal_threads = np.arange(1, max_threads + 2)

ax.plot(ideal_threads, ideal_threads, 'k--', label='Ideal Linear Speedup', lw=2)
    
ax.plot(threads, plot_speedup, marker='o', linestyle='-', label=f'Actual Speedup', lw=2, markersize=8)

ax.set_title(f'Speedup Analysis for Fibonacci', fontsize=16, weight='bold')
ax.set_xlabel('Number of Threads (p)', fontsize=12)
ax.set_ylabel('Speedup Factor (Sequential Time / Parallel Time)', fontsize=12)
ax.legend(fontsize=11)
ax.grid(True, which='both', linestyle='--', linewidth=0.5)
ax.xaxis.set_major_locator(plt.MaxNLocator(integer=True))
ax.yaxis.set_major_locator(plt.MaxNLocator(integer=True))
ax.set_xlim(left=0, right=max_threads + 1)
ax.set_ylim(bottom=0)
    
plt.tight_layout()
filename = "speedup_graph.png"   
plt.show()

