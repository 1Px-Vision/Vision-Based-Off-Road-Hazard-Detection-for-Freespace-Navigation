# Writeup: Track 3D-Objects Over Time

![Result_Point](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Point_Sensor.gif)

**1. Write a short recap of the four tracking steps and what you implemented there (filter, track management, association, camera fusion). Which results did you achieve? Which part of the project was most difficult for you to complete, and why?**

### Filter Implementation

* Implemented the predict() function for an Extended Kalman Filter (EKF).
* Developed the F() and Q() functions to compute the system matrix for a constant velocity process model in 3D and determine the corresponding process noise covariance based on the current timestep (dt).
* Implemented the update() function along with gamma() and S() to compute the residual and residual covariance.
* At the end of the update step, the resulting state (x) and covariance (P) are saved using the set_x() and set_P() functions from ````student/trackmanagement.py````.

### Track Management
* In the Track class, replaced fixed track initialization values with dynamic initialization based on an unassigned LiDAR measurement (meas) of type Measurement.
* Transformed the measurement from sensor coordinates to vehicle coordinates using the sens_to_veh transformation matrix from the Sensor class.
   
**2. Do you see any benefits in camera-lidar fusion compared to lidar-only tracking (in theory and in your concrete results)?**

![RMSE](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Step1_1.png)

The visualization is intended to demonstrate that no confirmed "ghost tracks" exist in reality. While initialized or tentative ghost tracks may appear temporarily, they should be removed after a few frames. If any remain, sensor fusion with a camera can be used to invalidate them. The console output displays LiDAR updates followed by camera updates, reinforcing that the tracking system performs well. No confirmed ghost tracks or track losses should occur. The RMSE plot should confirm at least three tracked objects, with two of them continuously tracked from the start (0s) to the end (200s) of the sequence without interruption. The mean RMSE for these two tracks should remain below 0.25.

**3. Which challenges will a sensor fusion system face in real-life scenarios? Did you see any of these challenges in the project?**

**At Step 2:** Track Management, the RMSE is relatively high in this scenario (approximately 0.78). Additionally, the green bounding boxes do not accurately align with the car in the image. This discrepancy highlights a common real-world challenge: our assumptions about the data are not always perfectly met. However, we can mitigate this offset through sensor fusion by integrating additional sensor inputs. To further diagnose the issue, there may be an error in the association matrix or in the process of removing used rows and columns. Printing the association matrix for further debugging will help identify and resolve the problem.

**4. Can you think of ways to improve your tracking results in the future?**

Fine-tune the parameterization and explore how low the RMSE can be reduced! Utilize the standard deviation values for LiDAR obtained from the mid-term project. The parameters in ````student/params.py```` should allow for an initial tracking run, but significant improvements can be achieved through careful parameter tuning.
 Enhance the data association by implementing a more advanced method, such as Global Nearest Neighbor (GNN) or Joint Probabilistic Data Association (JPDA). Integrate camera detections from Project 1 into the tracking pipeline to improve accuracy and robustness. Modify the Kalman filter to estimate an object's width, length, and height, rather than relying solely on unfiltered LiDAR detections as done previously. Replace the linear motion model with a non-linear approach, such as a bicycle model, which better represents vehicle dynamics by accounting for the fact that a vehicle moves forward or backward rather than in arbitrary directions.   
