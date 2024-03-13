To accomplish this task in C, you can use a library like PortAudio for audio input and then save the recorded samples to a file. 
However, plotting the recorded sound graphically directly in C is not feasible as C doesn't have built-in plotting capabilities. 
Instead, you can save the recorded samples to a file and then use another tool, like Python with libraries such as NumPy and Matplotlib, to plot the graph.
Note:Ensure you have NumPy and Matplotlib installed (pip install numpy matplotlib). This script loads the recorded sound from the file recorded_sound.raw and plots it using Matplotlib.
