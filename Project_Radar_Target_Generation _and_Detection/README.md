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

## Included in this repository 

* The code used to Radar Target Generation
* Radar Target Generation and Detection.m - Matlab file containing the challenge for this project
* Result File with image 
* This README.md file

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

The 2nd FFT is already implemented in the code. It will generate a Range Doppler Map as seen in the image below and be given by variable ‘RDM’. Next task is to implement the CFAR on this Range Doppler Map.

![Doppler](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Radar_Target_Generation%20_and_Detection/Results/Fig_Doppler.jpg)

## 2D CFAR

* Determine the number of Training cells for each dimension. In the same way, pick the number of guard cells.
* Slide the cell under test across the complete matrix. Ensure the CUT has a margin for Training and Guard cells from the edges.
* For every iteration sum the signal level within all the training cells. To sum convert the value from logarithmic to linear using the db2pow function.
* Average the summed values for all of the training cells used. After averaging convert it back to logarithmic using pow2db.
* Further add the offset to it to determine the threshold.
* Next, compare the signal under CUT against this threshold.
* If the CUT level > threshold assign it a value of 1, else equate it to 0.
* 
The process above will generate a thresholded block, which is smaller than the Range Doppler Map as the CUTs cannot be located at the edges of the matrix due to the presence of Target and Guard cells. Hence, those cells will not be thresholded.

* To keep the map size the same as it was before CFAR, equate all the non-thresholded cells to 0.

  ![2D_CFAR](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Radar_Target_Generation%20_and_Detection/Results/Fig_2D_CFAR.jpg)

### Implementation steps for the 2D CFAR process

Lines 137-208 in the script **Radar_Target_Generation_and_Detection.m**

The 2D Constant False Alarm Rate (CFAR) Algorithm, when applied to the output of the 2D FFT, dynamically adjusts the threshold based on the noise level near the Cell Under Test (CUT). The process involves the following key steps:

**1. Iterate through Range and Doppler Cells:**
Loop over all cells in both the range and Doppler dimensions, ensuring that appropriate margins are maintained at the start and end of the indices.

**2. Slice the Training Window:**
Extract the training cells surrounding the CUT, excluding the guard cells.

**3. Zero Non-Training Cells:**
Set all non-training cells within the sliced window to zero.

**4. Convert Decibel Values to Power:**
Convert the values of the training cells from decibels (dB) to power to linearize the data.

**5. Calculate Mean Noise Level:**
Compute the mean noise level from the training cells.

**6. Revert to Decibels:**
Convert this average noise level back from power to dB.

**7. Determine Dynamic Threshold:**
Add a specified offset (in dB) to establish the dynamic threshold.

**8. Apply Threshold to CUT:**
Apply this threshold and store the resulting values in a binary array with the same dimensions as the Range-Doppler Map (RDM).

´´´´
% Use RDM[x,y] from the output of 2D FFT above for implementing CFAR
for range_index = Tr + Gr + 1 : Nr/2 - Tr - Gr
    for doppler_index = Td + Gd + 1 : Nd - Td - Gd
        % Slice the entire window
        training = RDM(range_index - Tr - Gr : range_index + Tr + Gr, ...
                       doppler_index - Td - Gd : doppler_index + Td + Gd);
        % Set all non-training cells to zero
        training(range_index - Gr : range_index + Gr, ...
                 doppler_index - Gd : doppler_index + Gd) = 0;
        % Convert decibel measurements to power
        training = db2pow(training);
        % Calculate the training mean
        training = sum(training) / N_training;
        % Revert average power to decibels
        training = pow2db(training);
        % Use the offset to determine the SNR threshold
        threshold = training + offset;
        % Apply the threshold to the CUT
        if RDM(range_index, doppler_index) > threshold
            CFAR(range_index, doppler_index) = 1;
        end
    end
end
´´´´

