# Scan Matching Localization
The project aims to accurately localize a car driving in a simulation at least 170 meters from its starting position while ensuring the pose error remains within 1.2 meters. The simulation car is equipped with a LiDAR sensor, which provides LiDAR scans at regular intervals. A pre-existing point cloud map, map.pcd, is available and has been extracted from the CARLA simulator. Localization is achieved by performing point registration and matching between the provided map and the LiDAR scans.

![Carla](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Scan_Matching_Localization/Media/Lidar_Carla.jpg)


## Iterative Closest Point (ICP) alignment between a target and source point cloud.
This function computes the transformation matrix that aligns the source point cloud to the target point cloud using the PCL (Point Cloud Library) ICP implementation. It considers a starting pose for initialization and applies ICP for a specified number of iterations.

![Result_ICP](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Scan_Matching_Localization/Media/Result_Scan.jpg)

## Included in this repository
The project introduces the following modified files:

* CMakeLists.txt
* c3-main.cpp
* helper.cpp
* helper.h
