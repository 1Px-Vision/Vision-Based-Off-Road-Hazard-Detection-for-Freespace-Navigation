# Project: Track an Object in 3D Space

This project marks the culmination of the camera unit in Udacity's Sensor Fusion Nanodegree, covering the following key concepts:

* Keypoint detection and description techniques
* Object detection using the pre-trained YOLO deep learning framework
* Object tracking by matching key points and bounding boxes across consecutive images
* Associating regions in camera images with corresponding lidar points in 3D space

## Included in this repository 

* The code used to Camera based 2D feature tracking on src directory with MidTermProject_Camera_Student.cpp, dataStructures.h, matching2D.hpp, matching2D_Student.cpp file containing the challenge for this project
* Result File with image SIFT_Keypoint and FAST_detectors_and_ORB
* Task_MP7.csv and Task_MP8_MP9.csv
* This README.md file

![3D_track](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Track_an_Object_in_3D_Space/ttc_estimation.png)
 
The flowchart below outlines the structure of the final project. The steps within the orange box were completed in the previous project, 2D Feature Tracking. This project builds upon that foundation by implementing the steps in the blue box and beyond. Objects detected by the YOLO deep neural network are tracked across frames by evaluating the strength of keypoint correspondences within their bounding boxes. Finally, a robust estimation of time-to-collision (TTC) is performed using data from both the lidar and camera sensors.

![TCC](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Track_an_Object_in_3D_Space/course_code_structure.png)

## FP.1 Match 3D objects

## FP.2 Compute lidar-based TTC

## FP.3 Associate keypoint matches with bounding boxes

## FP.4 Compute mono camera-based TTC

## FP.5 Performance evaluation, lidar outliers

## FP.6 Performance evaluation, detector/descriptor combinations
Some detector/descriptor combinations, particularly the Harris and ORB detectors, resulted in highly unreliable camera TTC estimates. In contrast, detectors like SIFT, FAST, and AKAZE provided consistent results that aligned closely with the TTC estimates from the lidar sensor. Below is a sample of the results matrix, ranked by the difference in TTC estimates between the camera and lidar systems.

| Detector  | Descriptor | Frame index | TTC lidar | TTC camera | TTC difference |
|-----------|------------|-------------|-----------|------------|----------------|
| FAST      | ORB        | 17          | 9.55      | 9.68       | 0.13           |
| ORB       | FREAK      | 15          | 8.57      | 8.68       | 0.11           |
| ORB       | BRISK      | 9           | 13.02     | 13.13      | 0.10           |
| BRISK     | FREAK      | 11          | 12.81     | 12.88      | 0.07           |
| SIFT      | SIFT       | 16          | 9.52      | 9.58       | 0.06           |
| SIFT      | BRISK      | 9           | 13.02     | 13.06      | 0.03           |
| SIFT      | BRISK      | 13          | 9.96      | 9.99       | 0.02           |
| SIFT      | BRIEF      | 9           | 13.02     | 13.04      | 0.02           |
| SHITOMASI | ORB        | 7           | 11.98     | 11.97      | -0.01          |
| FAST      | FREAK      | 2           | 12.61     | 12.60      | -0.01          |
| ORB       | BRISK      | 14          | 9.60      | 9.59       | -0.01          |
| ORB       | SIFT       | 16          | 9.52      | 9.50       | -0.02          |
| SIFT      | FREAK      | 16          | 9.52      | 9.50       | -0.02          |
| FAST      | SIFT       | 3           | 14.09     | 14.06      | -0.03          |
| SIFT      | BRISK      | 17          | 9.55      | 9.52       | -0.03          |
| SIFT      | BRISK      | 14          | 9.60      | 9.55       | -0.05          |
| SIFT      | SIFT       | 2           | 12.61     | 12.56      | -0.05          |
| FAST      | SIFT       | 17          | 9.55      | 9.44       | -0.10          |
