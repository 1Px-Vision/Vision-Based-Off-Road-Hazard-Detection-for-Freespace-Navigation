# General
## Question 1: Explain a recent project you've worked on. Why did you choose this project?, What difficulties did you run into this project that you did not expect, and how did you solve them?

I worked on a project involving control, fusion sensors, and tracking with UAVs for rescue applications. The project had a strict timeline, and the initial development phase had already begun. There was no existing documentation, and the large code base required updates and adaptations to meet specific requirements. To address this, I used Doxygen to generate documentation directly from the codebase. I also resolved issues daily by employing a simulator to handle various events and messages and writing C++ code to support them.

# Mandatory
## Question 2: What are some of the advantages & disadvantages of cameras, lidar and radar? What combination of these (and other sensors) would you use to ensure the appropriate and accurate perception of the environment?

* **Camera:** A camera is essentially a sensor that captures an array of color points in space, forming what is known as an image array. This image array is then converted into a digital signal, which is transmitted to hardware that performs sensor fusion and scene understanding.

* **LiDAR:** LiDAR (Light Detection and Ranging) uses a laser-based, point-and-shoot approach to sense the environment. A LiDAR transmitter emits a pulse of light, waits for the light to reflect off an object, and calculates the distance based on the time it takes for the light to return, knowing the speed of light. To expand its field of view, LiDAR can use multiple lasers that rotate, or more recently, a fixed array of lasers spread across the field of view, known as "Solid State LiDAR." Once all the light signals are received, the LiDAR system generates a "point cloud," containing an array of directional and distance information, which is sent to the hardware for sensor fusion and scene understanding.

* **Radar:** Radar technology has been in use for a long time. Similar to LiDAR, it employs a point-and-shoot method, but it uses radio waves (electromagnetic waves) instead of light. Radar is particularly effective for long-distance object detection but generally lacks precision compared to LiDAR. Testing radar technology follows a similar process to LiDAR testing. Given its lower cost and wider familiarity, some companies have already developed specialized tools for radar testing.

![](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Autonomous-Systems-Interview-Practice-Project/Sensor_Fusion_Table.jpg)

*Fig.1. Evaluation of Autonomous Vehicle Sensors*

## Question 3: Describe the overall process of how a basic Kalman Filter works. Where might a basic Kalman Filter be less than sufficient? How can you improve the basic algorithm to improve performance in such a situation?

Kalman Filters, also known as Linear Quadratic Estimation (LQE), are algorithms that provide more reliable estimates from a sequence of observed measurements, such as sensor data. They can be used to track the position and velocity of a moving pedestrian over time, as well as to quantify the associated uncertainty. The Kalman Filter operates as a two-step iterative process. A key component of this process is the Kalman Gain, a parameter that determines the weight given to the predicted value versus the measured value. It assesses the uncertainty in both the predicted and measured values, then adjusts the actual estimate accordingly, bringing it closer to either the predicted or measured value based on their respective uncertainties.

````
K = Error In Prediction / (Error in Prediction + Error in Measurement)
````

Measurement Error is typically provided by sensor manufacturers. When we purchase a new sensor, the manufacturer specifies the standard deviation of the measurements it will produce. On the other hand, Prediction Error is calculated mathematically. We usually start with an incorrect assumption (resulting in a large error), which is then gradually reduced after taking the first few measurements from the sensor, using the Kalman Gain.

## Question 4: How does an Extended Kalman Filter differ from a regular Kalman Filter? Provide an example of where an EKF would be necessary or improvement, and detail why it would be needed in that situation.

The Extended Kalman Filter (EKF) uses a linear approximation approach, unlike the regular Kalman Filter. EKF is applied when the results are not Gaussian, such as in radar or lidar scenarios, and the standard Kalman Filter equations are insufficient. This is achieved through a Taylor series expansion. Lidar provides distance measurements in a Cartesian coordinate system, whereas radar supplies both distance and velocity in a polar coordinate system.

## Question 5: What is the difference between an Extended Kalman Filter and an Unscented Kalman Filter? In what situations would there be larger differences between the two approaches?

The primary difference between the Extended Kalman Filter (EKF) and the Unscented Kalman Filter (UKF) lies in their approach to approximation. In EKF, we use only a single point, the mean, for approximation. In contrast, UKF employs multiple points, known as sigma points, for approximation. The rationale is that using a larger number of points results in a more accurate approximation. Additionally, these sigma points are assigned weights, making them weighted sigma points. By adjusting these weights, we can give more or less preference to certain points, thereby enhancing the accuracy of our approximation.

## Question 6 :[Code] Explain the steps behind how an Extended Kalman Filter is implemented.

Please refer to the extended Kalman filter implementation based on the provided code. Sensor fusion involves combining data from different sources. In this case, data from sources like Lidar and Radar are organized into matrices and initialized. The necessary include files for the Kalman filter implementation can be found in the header file. The extended Kalman filter processes non-linear data received from the Radar, approximating it into a linear form using a Gaussian approach. This approximation is achieved with the help of a Taylor series expansion.

### Prediction Step
The prediction step is identical to that of the Kalman Filter, regardless of whether the data comes from LIDAR or RADAR. The source of the data does not affect the prediction step.

````
x′ = F.x + B.μ + νP′ = FPFᵀ + Q
````

### Update Step (Only in case of EKF i.e. Non-Linear Measurements coming from RADAR)

#### Equation 1:

````
y= z - h(x′)
````
* z: Actual measurement in polar coordinates
* ℎ : Function that maps speed and position to polar coordinates
* 𝑥′: Predicted value
* 𝑦: Difference between the measured value and the actual value

This function defines the mapping between our predicted values in Cartesian coordinates and the measurements in Polar coordinates. This mapping is necessary because our predictions are made in Cartesian coordinates, while the sensor-provided measurements (z) are in Polar coordinates.

$$
h(x') = 
\begin{pmatrix}
\rho \\
\phi \\
\dot{\rho}
\end{pmatrix} = 
\begin{pmatrix}
\sqrt{{p'_x}^2 + {p'_y}^2} \\
\arctan\left(\frac{p'_y}{p'_x}\right) \\
\frac{p'_x v'_x + p'_y v'_y}{\sqrt{{p'_x}^2 + {p'_y}^2}}
\end{pmatrix}
$$

#### Equation 2:
````
S= HⱼP′Hⱼᵀ + R K= P′HⱼᵀS⁻¹
````
* R Measurement Noise
* K Kalman Gain
* S-> Total Error
* S⁻¹ -> The inverse of S
* Hⱼ -> The Jacobian Matrix

$H_{j}$ represents the Jacobian matrix, which is the first-order derivative that we previously discussed in the context of the Taylor Series. In our case, since we are working with matrices, we need to compute the differential in matrix form. The Jacobian matrix element $J_{kl}$ is defined as:

$$J_{kl}=\frac{\partial F_{k}}{\partial x_{l}}$$

Here, $J_{kl}$ is the (𝑘,𝑙) element of the Jacobian matrix, $F_{k}$ denotes the kth component of the vector function 𝐹, and $X_{l}$ represents the 
𝑙 lth element of the vector variable 𝑋. Specifically, we have:

* $$F_{k}=[\rho,\phi,\dot{\rho}]$$ representing the radial distance, angle, and radial velocity, respectively.
* $$X_{l}=[px,py,vx,vy]$$ where $px$ and $py$ are position coordinates, and $vx$ and $vy$ are velocity components.

Since we are dealing with RADAR measurements, which provide four values (two for position and two for velocity), the Jacobian matrix is essential for linearizing the non-linear measurement function around the current state estimate.

$$ H_j = \begin{bmatrix}
\frac{\partial \rho}{\partial p_x} & \frac{\partial \rho}{\partial p_y} & \frac{\partial \rho}{\partial v_x} & \frac{\partial \rho}{\partial v_y} \\
\frac{\partial \phi}{\partial p_x} & \frac{\partial \phi}{\partial p_y} & \frac{\partial \phi}{\partial v_x} & \frac{\partial \phi}{\partial v_y} \\
\frac{\partial \dot{\rho}}{\partial p_x} & \frac{\partial \dot{\rho}}{\partial p_y} & \frac{\partial \dot{\rho}}{\partial v_x} & \frac{\partial \dot{\rho}}{\partial v_y}
\end{bmatrix}
$$

$$ H_j = \begin{bmatrix}
\frac{p_x}{\sqrt{p_x^2 + p_y^2}} & \frac{p_y}{\sqrt{p_x^2 + p_y^2}} & 0 & 0 \\
-\frac{p_y}{p_x^2 + p_y^2} & \frac{p_x}{p_x^2 + p_y^2} & 0 & 0 \\
\frac{p_y(v_x p_y - v_y p_x)}{(p_x^2 + p_y^2)^{3/2}} & \frac{p_x(v_y p_x - v_x p_y)}{(p_x^2 + p_y^2)^{3/2}} & \frac{p_x}{\sqrt{p_x^2 + p_y^2}} & \frac{p_y}{\sqrt{p_x^2 + p_y^2}}
\end{bmatrix}
$$

## Results & Discussion
This Extended Kalman Filter (EKF) models the following characteristics of the object's state $x:(p_{x},p_{y},v_{x},v_{y})$, where $𝑝$ represents the position and $v$ represents the velocity. The state is initialized with the values 𝑥=(meas1_px, meas1_py,0.5,0.5), where meas1_px,meas1_px, and meas1_py, meas1_py are set using the first received measurement. The covariance matrix 𝑃 is initialized with variances (1,1,500,500) along the diagonal to reflect the relative certainty in the initial position and the uncertainty in the initial velocity.

![](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Autonomous-Systems-Interview-Practice-Project/Result_EKF.jpg)

The overall RMSE value for the position is higher when only one sensor is used compared to when both sensors are utilized. Specifically, the RADAR sensor alone provides poor position estimation due to its sensing mechanism, which primarily relies on the Doppler effect to measure velocity directly. On the other hand, while the LIDAR sensor performs relatively better at estimating position, it struggles with accurate velocity measurements in the absence of RADAR data. This highlights the effectiveness of an Extended Kalman Filter (EKF), which can take noisy measurements from multiple sensor types and generate a more accurate state estimation. The EKF achieves this by combining the Gaussian probability distributions of the sensor measurements with its prediction, also represented as a Gaussian distribution, to determine the likely location of the tracked object.



