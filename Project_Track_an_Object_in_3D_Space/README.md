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
