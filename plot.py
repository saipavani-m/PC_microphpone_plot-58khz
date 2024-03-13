import numpy as np
import matplotlib.pyplot as plt

# Load recorded sound
raw_data = np.fromfile('recorded_sound.raw', dtype=np.float32)

# Plot the sound wave
plt.plot(raw_data)
plt.title('Recorded Sound')
plt.xlabel('Sample')
plt.ylabel('Amplitude')
plt.show()
