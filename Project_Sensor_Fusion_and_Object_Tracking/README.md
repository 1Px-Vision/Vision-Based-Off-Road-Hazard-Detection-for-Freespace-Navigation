# Sensor Fusion and Tracking

In this project, you will integrate measurements from LiDAR and cameras to track vehicles over time. Using real-world data from the [Waymo Open Dataset](https://waymo.com/open/), the objectives include detecting objects in 3D point clouds and implementing an extended Kalman filter for sensor fusion and vehicle tracking.

![tracking](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Tracking.jpg)


The project is divided into two key components:

* **Object Detection:** This component employs a deep learning approach to detect vehicles in LiDAR data, utilizing a bird's-eye view representation of the 3D point cloud. The detection performance is assessed using a series of evaluation metrics to ensure accuracy and reliability.

* **Object Tracking:** This component uses an extended Kalman filter to track vehicles over time by integrating LiDAR detections with camera detections. It also includes data association and track management techniques to maintain robust and accurate tracking.

