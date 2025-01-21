# Writeup: Track 3D-Objects Over Time

![Result_Point](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Point_Sensor.gif)

**1. Write a short recap of the four tracking steps and what you implemented there (filter, track management, association, camera fusion). Which results did you achieve? Which part of the project was most difficult for you to complete, and why?**

### Filter Implementation

* Implemented the ````predict()```` function for an Extended Kalman Filter (EKF).
* Developed the ````F()```` and ````Q()```` functions to compute the system matrix for a constant velocity process model in 3D and determine the corresponding process noise covariance based on the current timestep (dt).
* Implemented the update() function along with gamma() and S() to compute the residual and residual covariance.
* At the end of the update step, the resulting ````state (x)```` and ````covariance (P)```` are saved using the ````set_x()```` and ````set_P()```` functions from ````student/trackmanagement.py````.

### Track Management
    * Replace the fixed track initialization values with dynamic initialization of ````track.x```` and ````track.P```` using the input meas, an unassigned LiDAR measurement object of type Measurement.
    * Transform the unassigned measurement from sensor coordinates to vehicle coordinates using the sens_to_veh transformation matrix implemented in the Sensor class.

### Association Algorithm
* In the Association class, implemented the ````associate()```` function to:
    * Compute the association matrix using Mahalanobis distance for all tracks (track_list) and measurements (meas_list).
    * Used the MHD() function to determine the Mahalanobis distance between a track and a measurement.
    * Applied the gating() function to verify whether a measurement is within a track's gate. If not, the function sets the corresponding association matrix entry to infinity.
    * Updated the lists of unassigned measurements (unassigned_meas) and unassigned tracks (unassigned_tracks) by including indices of measurements and tracks that were not associated.

* Implemented ````get_closest_track_and_meas()```` to:
    * Identify the minimum entry in association_matrix.
    * Remove the corresponding row and column from the matrix.
    * Update ````unassigned_tracks```` and unassigned_meas by removing associated elements.
    * Return the ````track-measurement```` association pair. If no valid association remains (i.e., the lowest entry is infinity), return ````numpy.nan```` for both the track and measurement.


### Camera Fusion
* In the Sensor class, implemented the ````in_fov()```` function to determine whether an object's state ````vector (x)```` is visible to the sensor.
    * First, the state vector is transformed from vehicle coordinates to sensor coordinates.
    * The function returns True if the object lies within the sensor's field of view (````fov````); otherwise, it returns False.
    
* Implemented ````get_hx()```` to define the nonlinear camera measurement function (h):
   * Transform position estimates from vehicle to camera coordinates.
   * Project from camera to image coordinates.
   * Handle division by zero errors gracefully, raising an error if necessary.
   * Return the transformed state vector ````h(x)````.

* Modified ````generate_measurement()```` in the Sensor class to include camera measurements, removing the restriction to LiDAR-only data.
* In the Measurement class, initialized camera measurement objects with:
      * Measurement vector (````z````)
      * Measurement noise covariance (````R````)
      * Sensor object (````sensor````)
### Challenges & Debugging Notes

* **Step 2:** Track Management was particularly challenging. The Root Mean Square Error (RMSE) in this step is quite high (~0.78). Additionally, the green bounding boxes in the visualization do not align properly with the vehicles in the image.

* **Step 3: Association**
    * The console output indicates that a single measurement was used multiple times, suggesting an error in the association matrix or in the deletion of used rows/columns.
    *  Further debugging is required by printing the association matrix to examine incorrect associations.
   
**2. Do you see any benefits in camera-lidar fusion compared to lidar-only tracking (in theory and in your concrete results)?**

![RMSE](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Step1_1.png)

The visualization is intended to demonstrate that no confirmed "ghost tracks" exist in reality. While initialized or tentative ghost tracks may appear temporarily, they should be removed after a few frames. If any remain, sensor fusion with a camera can be used to invalidate them. The console output displays LiDAR updates followed by camera updates, reinforcing that the tracking system performs well. No confirmed ghost tracks or track losses should occur. The RMSE plot should confirm at least three tracked objects, with two of them continuously tracked from the start (0s) to the end (200s) of the sequence without interruption. The mean RMSE for these two tracks should remain below 0.25.

**3. Which challenges will a sensor fusion system face in real-life scenarios? Did you see any of these challenges in the project?**

**At Step 2:** Track Management, the RMSE is relatively high in this scenario (approximately 0.78). Additionally, the green bounding boxes do not accurately align with the car in the image. This discrepancy highlights a common real-world challenge: our assumptions about the data are not always perfectly met. However, we can mitigate this offset through sensor fusion by integrating additional sensor inputs. To further diagnose the issue, there may be an error in the association matrix or in the process of removing used rows and columns. Printing the association matrix for further debugging will help identify and resolve the problem.

**4. Can you think of ways to improve your tracking results in the future?**

Fine-tune the parameterization and explore how low the RMSE can be reduced! Utilize the standard deviation values for LiDAR obtained from the mid-term project. The parameters in ````student/params.py```` should allow for an initial tracking run, but significant improvements can be achieved through careful parameter tuning. Enhance the data association by implementing a more advanced method, such as Global Nearest Neighbor (GNN) or Joint Probabilistic Data Association (JPDA). Integrate camera detections from Project 1 into the tracking pipeline to improve accuracy and robustness. Modify the Kalman filter to estimate an object's width, length, and height, rather than relying solely on unfiltered LiDAR detections as done previously. Replace the linear motion model with a non-linear approach, such as a bicycle model, which better represents vehicle dynamics by accounting for the fact that a vehicle moves forward or backward rather than in arbitrary directions.   
