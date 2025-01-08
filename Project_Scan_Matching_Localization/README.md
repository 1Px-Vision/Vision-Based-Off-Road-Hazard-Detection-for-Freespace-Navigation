# Scan Matching Localization
The goal of the project is to accurately localize a car driving in a simulation over a distance of at least 170 meters from its starting position, while ensuring the pose error remains within 1.2 meters. The simulation car is equipped with a LiDAR sensor, which provides LiDAR scans at regular intervals. A pre-existing point cloud map, map.pcd, is available and has been extracted from the CARLA simulator. Localization is achieved by performing point registration and matching between the provided map and the LiDAR scans.

![Carla](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Scan_Matching_Localization/Media/Lidar_Carla.jpg)
