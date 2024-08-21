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
