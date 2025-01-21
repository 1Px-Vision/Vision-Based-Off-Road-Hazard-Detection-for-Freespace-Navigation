# 3D Object Detection (Mid-Term Project)

This project utilizes the Waymo Open Dataset, leveraging real-world data collected from LiDAR sensors. The project requirements are outlined below, categorized by sections:

## Section 1: Compute LiDAR Point Cloud from Range Image
1. Convert the "range" and "intensity" channels of the range image to 8-bit format.
2. Visualize the results using OpenCV. (Task ID: S1_EX1)


![opencv_range](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Range_Image_Section_1.png)

3. Visualize the point cloud using the Open3D module.
4. Identify 10 images containing vehicles. (Task ID: S1_EX2)

![Point_PCL](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Section_1_PCL.jpg)

## Section 2: Create Bird's-Eye View (BEV) from LiDAR Point Cloud
1. Transform the LiDAR coordinates from x,y [meters] to x,y [pixels], based on the width and height of the BEV map. (Task ID: S2_EX1)
2. Adjust the intensity values to ensure vehicles are visible. (Task ID: S2_EX2)
3. Compare results from two approaches:
    * Normalizing the height within each BEV map pixel.
    * Filling the "height" channel. (Task ID: S2_EX3)

![BEV](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Section_2.jpg)

## Section 3: Model-Based Object Detection in BEV Images
1. Implement Complex YOLO and extract the output decoding and post-processing code from the GitHub repository. (Task ID: S3_EX1)
2. Transform BEV coordinates and convert the model output to the expected bounding box format. (Task ID: S3_EX2) 

## Section 4: Performance Evaluation for Object Detection
1. Compare ground-truth labels with detected objects to count true positives. (Task ID: S4_EX1)
2. Compute false negatives and false positives based on the Intersection over Union (IoU) and ground-truth labels. (Task ID: S4_EX2)
3. Calculate the precision and recall metrics for all frames. (Task ID: S4_EX3)

# Sensor Fusion and Tracking

In this project, you will integrate measurements from LiDAR and cameras to track vehicles over time. Using real-world data from the [Waymo Open Dataset](https://waymo.com/open/), the objectives include detecting objects in 3D point clouds and implementing an extended Kalman filter for sensor fusion and vehicle tracking.

![tracking](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Tracking.jpg)

The project is divided into two key components:

* **Object Detection:** This component employs a deep learning approach to detect vehicles in LiDAR data, utilizing a bird's-eye view representation of the 3D point cloud. The detection performance is assessed using a series of evaluation metrics to ensure accuracy and reliability.

![Result_obj](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Section_3.jpg)

* **Object Tracking:** This component uses an extended Kalman filter to track vehicles over time by integrating LiDAR detections with camera detections. It also includes data association and track management techniques to maintain robust and accurate tracking.

## Sensor Fusion and Object Tracking

### Tracking
Track objects over time with a Kalman Filter ````filter.py````
* EKF is implemented including appropriate system matrix F and process noise Q for constant velocity motion model.
* EKF is applied to a simple single-target scenario with lidar only.
* The mean RMSE is 0.35 or smaller. Please upload the RMSE plot as png or pdf file.

### Track Management
Initialize, update and delete tracks ````trackmanagement.py````.
* Track initialization from unassigned measurements is implemented.
* A track score is defined and implemented.
* The tracking works properly if you see the following results: After applying the track management to a new sequence (see instructions), the visualization shows that a new track is initialized automatically where unassigned measurements occur, the true track is confirmed quickly, and the track is deleted after it has vanished from the visible range.

### Data Association
Associate measurements to tracks with nearest neighbor association ````association.py````
* Nearest neighbor data association including association matrix is implemented.
* A method that returns nearest track and measurement for association is implemented.
* Gating method with chi-square-distribution is implemented to reduce complexity.
* The association works properly if you see the following results: After applying the data association to a new sequence with multiple targets, multiple tracks are updated with multiple measurements.
* The visualization should show that there are no confirmed “ghost tracks” that do not exist in reality. There may be initialized or tentative “ghost tracks” as long as they are deleted after several frames.

### Sensor Fusión

SWBAT fuse measurements from lidar and camera ````measurements.py````.
* Camera measurements including appropriate covariance matrix R are implemented.
* Nonlinear camera measurement model h(x) is implemented. The Jacobian H is given.
* A method that checks whether an object can be seen by the camera or is outside the field of view is implemented.
* The tracking works properly if you see the following results: The tracking loop now updates all tracks with lidar measurements, then with camera measurements.
* The visualization shows that the tracking performs well, again no confirmed ghost tracks or track losses should occur.

## Results
Result video Video_Tracking.mp4

![Track_det](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_tracking_det.jpg)

![Result_Step_1_1](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Step1_1.png)

![Result_4](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Step4_1.png)
## Project Recap: Sensor Fusion and Tracking
Tracking Pipeline Steps:
### Extended Kalman Filter (EKF):
* Implemented an EKF for state estimation, accounting for non-linear motion models.
* Used measurement updates to correct predictions and refine object state (e.g., position and velocity).
* Delivered consistent tracking performance.
### Track Management:
* Designed a track management system to initialize, update, and delete tracks based on detection confidence and history.
* Tracks were deleted after several consecutive missed detections.
* Ensured robust tracking even in the presence of temporary detection losses.
  
### Data Association:
* Developed a nearest-neighbor association algorithm to link sensor measurements with existing tracks.
* Enhanced the association logic to minimize false matches and handle ambiguous scenarios effectively.
* Improved overall accuracy in multi-object tracking situations.

### Camera-Lidar Sensor Fusion:

* Combined lidar point cloud data with camera-based detections for improved accuracy.
* Performed calibration to align lidar and camera frames and merged data into a unified representation.
* Achieved lower root-mean-square error (RMSE) compared to lidar-only tracking.

## Achievements
* Reliable object tracking with reduced RMSE values over time.
* Sensor fusion significantly outperformed lidar-only tracking, particularly in detecting small or occluded objects.
* Visualizations confirmed improved tracking continuity and fewer false positives.

## Challenges Faced
### Sensor Fusion:
* Handling alignment issues between camera and lidar data due to frame misalignment and sensor differences.
* Developing an accurate calibration pipeline for transforming lidar data into the camera frame.
* Ensuring computational efficiency to process fused data in real time.

## Benefits of Camera-Lidar Fusion
### Theoretical Benefits
* It combines the strengths of both sensors: the lidar provides precise depth information, while the camera offers rich texture and color data.
* Increased robustness in detecting partially occluded or distant objects.
### Concrete Results
* Reduced RMSE in object tracking scenarios.
* Better detection of small or visually complex objects that lidar might miss.

## Challenges in Real-Life Scenarios
* Environmental Conditions: Weather (rain, fog, snow) impacts both camera and lidar performance.
* Sensor Synchronization: Real-time calibration and alignment of sensors are critical to avoid errors.
* Dynamic Environments: Tracking in crowded areas or with highly dynamic objects is complex.
* Computational Demands: High-bandwidth sensor data requires significant computational resources.

## Included in this repository
The project introduces the following modified files (student directory):

### Mid-Term Project: 3D Object Detection
* objdet_pcl.py
* objdet_detect.py
* objdet_eval.py
  
### Final Project: Sensor Funsion and Object Tracking
* loop_over_dataset.py
* filter.py
* trackmanagement.py
* association.py
* measurements.py

