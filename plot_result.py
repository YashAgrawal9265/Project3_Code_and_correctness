import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Plot rehash timing results
def plot_rehash():
    df = pd.read_csv('rehash_times.csv')
    plt.figure(figsize=(10,6))
    plt.semilogx(2**df['q'], df['no_rehash'], 'o-', label='No Rehash')
    plt.semilogx(2**df['q'], df['doubling'], 's-', label='Doubling')
    plt.semilogx(2**df['q'], df['addition'], 'd-', label='Add 10000')
    plt.title('Insert Performance by Resizing Strategy')
    plt.xlabel('Initial Size (log scale)')
    plt.ylabel('Time per Insert (µs)')
    plt.legend()
    plt.grid(True)
    plt.savefig('rehash_times.png')

# Plot load factor results
def plot_load_factors():
    df = pd.read_csv('load_factor_times.csv')
    lf = df['load_factor']
    
    # Theoretical curves
    linear_succ = 0.5 + 1/(2*(1 - lf)**2)
    double_succ = -np.log(1 - lf)/lf
    linear_fail = 0.5 + 1/(2*(1 - lf))
    double_fail = 1/(1 - lf)
    
    # Scaling factor
    Q = (0.5 + 1/(2*(1 - 0.5)**2)) / df[df['load_factor'] >= 0.5].iloc[0]['success_time']
    
    plt.figure(figsize=(10,6))
    plt.plot(lf, linear_succ, label='Linear Theoretical')
    plt.plot(lf, double_succ, label='Double Hashing Theoretical')
    plt.plot(lf, Q*df['success_time'], 'o', label='Experimental (scaled)')
    plt.title('Successful Search Performance')
    plt.xlabel('Load Factor')
    plt.ylabel('Probe Count')
    plt.legend()
    plt.grid(True)
    plt.savefig('time_succ.png')
    
    plt.figure(figsize=(10,6))
    plt.plot(lf, linear_fail, label='Linear Theoretical')
    plt.plot(lf, double_fail, label='Double Hashing Theoretical')
    plt.plot(lf, Q*df['fail_time'], 'o', label='Experimental (scaled)')
    plt.title('Unsuccessful Search Performance')
    plt.xlabel('Load Factor')
    plt.ylabel('Probe Count')
    plt.legend()
    plt.grid(True)
    plt.savefig('time_fail.png')

if __name__ == "__main__":
    plot_rehash()
    plot_load_factors()