import matplotlib.pyplot as plt
import numpy as np

experiment_data = {
    "Ts":  1.104643,  # Time from your sequential C code
    "p_threads": [2, 4, 8, 16],
    "Tp": [ 1.027715,  0.662035 , 0.490151,  0.543763] # Times from parallel code for 1, 2, 4, 8, 16 threads
}

# --- STEP 2: The script calculates speedup and plots the graph ---

print("Generating speedup graph...")

# Extract data from the dictionary
ts = experiment_data["Ts"]
threads = experiment_data["p_threads"]
tp = experiment_data["Tp"]
    
# Create a new figure and axes for the plot
fig, ax = plt.subplots(figsize=(10, 7))
    
# --- Calculate Speedup: S_p = T_s / T_p ---
# Note: We are using the true sequential time (Ts) as the baseline for all calculations.
plot_speedup = [ts / t for t in tp]
    
# --- Plot the Ideal and Actual Speedup ---
max_threads = max(threads)
ideal_threads = np.arange(1, max_threads + 2)
    
# Plot Ideal Linear Speedup line
ax.plot(ideal_threads, ideal_threads, 'k--', label='Ideal Linear Speedup', lw=2)
    
# Plot the algorithm's actual speedup curve
ax.plot(threads, plot_speedup, marker='o', linestyle='-', label=f'Actual Speedup', lw=2, markersize=8)
    
# --- Formatting the Plot ---
ax.set_title(f'Speedup Analysis for Fibonacci', fontsize=16, weight='bold')
ax.set_xlabel('Number of Threads (p)', fontsize=12)
ax.set_ylabel('Speedup Factor (Sequential Time / Parallel Time)', fontsize=12)
ax.legend(fontsize=11)
ax.grid(True, which='both', linestyle='--', linewidth=0.5)
    
# Set integer ticks and axis limits for clarity
ax.xaxis.set_major_locator(plt.MaxNLocator(integer=True))
ax.yaxis.set_major_locator(plt.MaxNLocator(integer=True))
ax.set_xlim(left=0, right=max_threads + 1)
ax.set_ylim(bottom=0)
    
plt.tight_layout()
    
# --- Save the plot to a file ---
filename = "speedup_graph.png"
    
try:
    plt.savefig(filename, dpi=300)
    print(f"Graph successfully saved as '{filename}'")
except Exception as e:
    print(f"Could not save the graph. Error: {e}")
    
plt.show()

