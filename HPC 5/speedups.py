import matplotlib.pyplot as plt
import numpy as np

# --- STEP 1: ENTER YOUR MEASURED DATA HERE ---
#
# Replace these sample values with your actual measured execution times in seconds.
# Ts = The execution time of your serial code (or parallel code with 1 thread).
# p_threads = A list of the thread counts you tested (e.g., 2, 4, 8...).
# Tp = A list of the parallel execution times corresponding to each thread count.

data = {
    "Matrix-Matrix Multiplication": {
        "Ts": 0.954248,
        "p_threads": [2, 4, 8, 16],
        "Tp": [0.515183, 0.295255 , 0.200832, 0.206391]
    },
    "Matrix-Scalar Multiplication": {
        "Ts": 0.012,
        "p_threads": [2, 4, 8, 16],
        "Tp": [0.014,  0.003871, 0.008036,0.019883]
    },
    "Matrix-Vector Multiplication": {
        "Ts": 0.026671,
        "p_threads": [2, 4, 8, 16],
        "Tp": [0.014107,  0.009234, 0.012763,  0.018062]
    },
    "Prefix Sum": {
        "Ts":0.149181,
        "p_threads": [2, 4, 8, 16],
        "Tp": [0.071085,  0.053053, 0.061066, 0.071845]
    }
}

# --- STEP 2: The script loops through your data, creating a separate plot for each entry ---

print("Generating separate speedup graphs for each algorithm...")

# Loop through each algorithm in the data dictionary
for name, values in data.items():
    print(f"  - Processing: {name}")
    
    # Create a new, separate figure and set of axes for each plot
    fig, ax = plt.subplots(figsize=(10, 7))
    
    # --- Calculate Speedup for the current algorithm ---
    ts = values["Ts"]
    threads = values["p_threads"]
    tp = values["Tp"]
    
    # We include the 1-thread case where speedup is always 1.
    plot_threads = [1] + threads
    plot_speedup = [1.0] + [ts / t for t in tp]
    
    # --- Plot the Ideal and Actual Speedup for this algorithm ---
    max_threads = max(plot_threads)
    ideal_threads = np.arange(1, max_threads + 2) # Extend line slightly
    
    # Plot Ideal Linear Speedup line
    ax.plot(ideal_threads, ideal_threads, 'k--', label='Ideal Linear Speedup', lw=2)
    
    # Plot the algorithm's actual speedup curve
    ax.plot(plot_threads, plot_speedup, marker='o', linestyle='-', label=f'{name} Speedup', lw=2, markersize=8)
    
    # --- Formatting the Plot ---
    ax.set_title(f'Speedup Analysis for {name}', fontsize=16, weight='bold')
    ax.set_xlabel('Number of Threads (p)', fontsize=12)
    ax.set_ylabel('Speedup Factor (Serial Time / Parallel Time)', fontsize=12)
    ax.legend(fontsize=11)
    ax.grid(True, which='both', linestyle='--', linewidth=0.5)
    
    # Set integer ticks and axis limits for clarity
    ax.xaxis.set_major_locator(plt.MaxNLocator(integer=True))
    ax.yaxis.set_major_locator(plt.MaxNLocator(integer=True))
    ax.set_xlim(left=0, right=max_threads + 1)
    ax.set_ylim(bottom=0)
    
    plt.tight_layout()
    
    # --- Save the plot to a unique file ---
    # Create a clean filename (e.g., "matrix_matrix_multiplication")
    filename_safe_name = name.lower().replace(' ', '_').replace('-', '_')
    filename = f"speedup_{filename_safe_name}.png"
    
    try:
        plt.savefig(filename, dpi=300)
        print(f"    Graph saved as '{filename}'")
    except Exception as e:
        print(f"    Could not save the graph. Error: {e}")
    
    # Close the current plot figure to free up memory before creating the next one
    plt.close(fig)

print("\nAll individual graphs have been generated.")
