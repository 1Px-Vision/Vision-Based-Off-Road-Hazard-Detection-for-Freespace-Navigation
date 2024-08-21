# Radar Target Generation and Detection

This project utilizes Matlab to explore frequency-modulated continuous-wave (FMCW) radar and associated post-processing techniques. The key topics covered include:

![Project_RADAR](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Radar_Target_Generation%20_and_Detection/Project_RADAR.jpg)

* Fast Fourier Transforms (FFT) and 2D FFT
* Distinguishing between clutter and targets
* Optimizing chirp bandwidth to meet system requirements for range resolution
* Phased array beam steering for the angle of arrival (AoA) estimation
* Constant False Alarm Rate (CFAR) noise suppression
* Signal-to-noise ratio (SNR) analysis and dynamic thresholding


System requirements play a crucial role in defining the design of a radar system. The sensor fusion design for various driving scenarios demands different system configurations from the radar. In this project, you will design a radar based on the specified system requirements. Key parameters such as maximum range and range resolution are essential considerations for waveform design. The sweep bandwidth can be determined based on the desired range resolution, and the sweep slope is calculated using both the sweep bandwidth and sweep time.

 $B_{sweep}=\frac{c}{2\cdot RangeResolution}$

Where 𝑐 is the speed of light.

The sweep time can be calculated based on the time required for the signal to travel the unambiguous maximum range. Typically, for an FMCW radar system, the sweep time should be at least 5 to 6 times the round trip time. In this example, a factor of 5.5 is used:

$T_{chirp}=\frac{5.5\cdot 2\cdot R_{max}}{c}$

This gives the slope of the chirp signal as:

$Slope=\frac{BW}{T_{chirp}}$

Initial Range and Velocity of the Target
You will provide the initial range and velocity of the target. The range cannot exceed a maximum value of 200 meters, and the velocity can be any value within the range of -70 to +70 m/s.

## FFT Operation

![Range](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Radar_Target_Generation%20_and_Detection/Results/Fig_Range.jpg)

* Implement the 1D FFT on the Mixed Signal
* Reshape the vector into Nr*Nd array.
* Run the FFT on the beat signal along the range bins dimension (Nr)
* Normalize the FFT output.
* Take the absolute value of that output.
* Keep one half of the signal
* Plot the output
* There should be a peak at the initial position of the target

The 2nd FFT is already implemented in the code. It will generate a Range Doppler Map as seen in the image below and it will be given by variable ‘RDM’. Next task is to implement the CFAR on this Range Doppler Map.


