import matplotlib.pyplot as plt
import numpy as np


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


print("Generating separate speedup graphs for each algorithm...")

for name, values in data.items():
    print(f"  - Processing: {name}")

    fig, ax = plt.subplots(figsize=(10, 7))

    ts = values["Ts"]
    threads = values["p_threads"]
    tp = values["Tp"]

    plot_threads = [1] + threads
    plot_speedup = [1.0] + [ts / t for t in tp]

    max_threads = max(plot_threads)
    ideal_threads = np.arange(1, max_threads + 2) 
    ax.plot(ideal_threads, ideal_threads, 'k--', label='Ideal Linear Speedup', lw=2)
    

    ax.plot(plot_threads, plot_speedup, marker='o', linestyle='-', label=f'{name} Speedup', lw=2, markersize=8)
    ax.set_title(f'Speedup Analysis for {name}', fontsize=16, weight='bold')
    ax.set_xlabel('Number of Threads (p)', fontsize=12)
    ax.set_ylabel('Speedup Factor (Serial Time / Parallel Time)', fontsize=12)
    ax.legend(fontsize=11)
    ax.grid(True, which='both', linestyle='--', linewidth=0.5)
    ax.xaxis.set_major_locator(plt.MaxNLocator(integer=True))
    ax.yaxis.set_major_locator(plt.MaxNLocator(integer=True))
    ax.set_xlim(left=0, right=max_threads + 1)
    ax.set_ylim(bottom=0)
    
    plt.tight_layout()
    filename_safe_name = name.lower().replace(' ', '_').replace('-', '_')
    filename = f"speedup_{filename_safe_name}.png"
    plt.close(fig)
