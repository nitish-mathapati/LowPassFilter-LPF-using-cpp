import pandas as pd
import matplotlib.pyplot as plt


def save_single_plot(x, y, title, xlabel, ylabel, output_path):
    fig, ax = plt.subplots(figsize=(6, 4))
    ax.plot(x, y)
    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.grid(True)
    fig.tight_layout()
    fig.savefig(output_path)
    plt.close(fig)


def plot_all_in_one():
    signal_df = pd.read_csv('data/signal.csv', header=None, names=['Time', 'Amplitude'])
    noise_df = pd.read_csv('data/noise.csv', header=None, names=['Amplitude'])
    noisy_df = pd.read_csv('data/NoisySignal.csv', header=None, names=['Time', 'Amplitude'])
    filtered_df = pd.read_csv('data/FilteredSignal.csv', header=None, names=['Time', 'Amplitude'])

    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    axes = axes.flatten()

    axes[0].plot(signal_df['Time'], signal_df['Amplitude'])
    axes[0].set_title('Sine Wave Signal')
    axes[0].set_xlabel('Time (s)')
    axes[0].set_ylabel('Amplitude')
    axes[0].grid(True)

    axes[1].plot(noise_df.index, noise_df['Amplitude'])
    axes[1].set_title('Noise Signal')
    axes[1].set_xlabel('Sample Number')
    axes[1].set_ylabel('Amplitude')
    axes[1].grid(True)

    axes[2].plot(noisy_df['Time'], noisy_df['Amplitude'])
    axes[2].set_title('Noisy Signal')
    axes[2].set_xlabel('Time (s)')
    axes[2].set_ylabel('Amplitude')
    axes[2].grid(True)

    axes[3].plot(filtered_df['Time'], filtered_df['Amplitude'])
    axes[3].set_title('Low-Pass Filtered Signal')
    axes[3].set_xlabel('Time (s)')
    axes[3].set_ylabel('Amplitude')
    axes[3].grid(True)

    fig.tight_layout()
    fig.savefig('data/all_signals_dashboard.png')
    plt.show()
    plt.close(fig)


# Save each plot separately
signal_df = pd.read_csv('data/signal.csv', header=None, names=['Time', 'Amplitude'])
save_single_plot(signal_df['Time'], signal_df['Amplitude'], 'Sine Wave Signal', 'Time (s)', 'Amplitude', 'data/signal_plot.png')

noise_df = pd.read_csv('data/noise.csv', header=None, names=['Amplitude'])
save_single_plot(noise_df.index, noise_df['Amplitude'], 'Noise Signal', 'Sample Number', 'Amplitude', 'data/noise_plot.png')

noisy_df = pd.read_csv('data/NoisySignal.csv', header=None, names=['Time', 'Amplitude'])
save_single_plot(noisy_df['Time'], noisy_df['Amplitude'], 'Noisy Signal', 'Time (s)', 'Amplitude', 'data/NoisySignal_plot.png')

filtered_df = pd.read_csv('data/FilteredSignal.csv', header=None, names=['Time', 'Amplitude'])
save_single_plot(filtered_df['Time'], filtered_df['Amplitude'], 'Low-Pass Filtered Signal', 'Time (s)', 'Amplitude', 'data/FilteredSignal_plot.png')

# Show all plots in one GUI window
plot_all_in_one()