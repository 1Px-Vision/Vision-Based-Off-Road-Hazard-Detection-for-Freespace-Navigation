# Project: Unscented Kalman Filter

In this final project, the scene focuses on the green ego car, while the target vehicles to be tracked are depicted in blue. The traffic cars exhibit dynamic behaviors, such as accelerating, decelerating, and changing lanes by altering their yaw angle. Each traffic vehicle is tracked using an independent Unscented Kalman Filter (UKF) instance.

![](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Unscented_Kalman_Filter_Highway/ukf_fast.gif)

Key visual elements include:

* Red Spheres: Represent the centroids of the (noisy) lidar detection clusters.
* Purple Lines: Indicate radar measurements, displaying the velocity magnitude along the detected angle.
* Green Spheres: Show the UKF's estimation of the vehicle's current position and its projected position several timesteps into the future.
* It’s important to note that the future position projection might initially fluctuate and take some time to stabilize after a lane change. This behavior arises from the assumptions within the Constant Turn Rate and Velocity (CTRV) motion model employed in this project.

## Included in this repository 

* The code used to UKF on src directory with main.cpp, ukf.cpp, tools.cpp, render.cpp file containing the challenge for this project
* src directory with code cpp project UKF
* Files describing all the packages required to set up the environment
* This README.md file

## Overview of the Unscented Kalman Filter (UKF) Algorithm

A typical Kalman filter operates as a Bayesian filter, which is effective when variables are normally distributed and undergo linear transitions at each time step. However, the Unscented Kalman Filter (UKF) extends this capability to handle non-linear transitions. The UKF achieves this by sampling multiple points (called sigma points) around the mean state estimate, distributed according to a spreading factor, 𝜆. The UKF algorithm follows these steps:

**1. Generate Sigma Points:** Create sigma (sampling) points in the augmented state space.

**2. Predict Sigma Point Motion:** Forecast the movement of each sigma point based on the Constant Turn Rate and Velocity (CTRV) model.

**3. Predict the Next State:** Estimate the next state's mean and covariance matrices.

**4. Lidar Measurement Prediction:** Predict the measurement mean and covariance, then calculate the Kalman gain 𝐾.

**5. Radar Measurement Prediction:** Predict the measurement mean ($𝑧_{pred}$) and the innovation covariance 𝑆.

**6. State Update:** Update the state by applying the Kalman gain to the residual (the difference between the measurement and the prediction).

**7. Repeat the Process:** Continue iterating these steps to refine the state estimate over time.

## Visualization of the results 
