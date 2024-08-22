# Project: Track an Object in 3D Space

This project marks the culmination of the camera unit in Udacity's Sensor Fusion Nanodegree, covering the following key concepts:

* Keypoint detection and description techniques
* Object detection using the pre-trained YOLO deep learning framework
* Object tracking by matching key points and bounding boxes across consecutive images
* Associating regions in camera images with corresponding lidar points in 3D space

![3D_track](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Track_an_Object_in_3D_Space/ttc_estimation.png)
 
The flowchart below outlines the structure of the final project. The steps within the orange box were completed in the previous project, 2D Feature Tracking. This project builds upon that foundation by implementing the steps in the blue box and beyond. Objects detected by the YOLO deep neural network are tracked across frames by evaluating the strength of keypoint correspondences within their bounding boxes. Finally, a robust estimation of time-to-collision (TTC) is performed using data from both the lidar and camera sensors.
