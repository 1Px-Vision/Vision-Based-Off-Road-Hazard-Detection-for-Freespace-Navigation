# Writeup: Track 3D-Objects Over Time

![Result_Point](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Sensor_Fusion_and_Object_Tracking/Media/Result_Point_Sensor.gif)

**1. Write a short recap of the four tracking steps and what you implemented there (filter, track management, association, camera fusion). Which results did you achieve? Which part of the project was most difficult for you to complete, and why?**

   
**2. Do you see any benefits in camera-lidar fusion compared to lidar-only tracking (in theory and in your concrete results)?**

**3. Which challenges will a sensor fusion system face in real-life scenarios? Did you see any of these challenges in the project?**

**At Step 2:** Track Management, the RMSE is relatively high in this scenario (approximately 0.78). Additionally, the green bounding boxes do not accurately align with the car in the image. This discrepancy highlights a common real-world challenge: our assumptions about the data are not always perfectly met. However, we can mitigate this offset through sensor fusion by integrating additional sensor inputs. To further diagnose the issue, there may be an error in the association matrix or in the process of removing used rows and columns. Printing the association matrix for further debugging will help identify and resolve the problem.

**4. Can you think of ways to improve your tracking results in the future?**

Fine-tune the parameterization and explore how low the RMSE can be reduced! Utilize the standard deviation values for LiDAR obtained from the mid-term project. The parameters in ````student/params.py```` should allow for an initial tracking run, but significant improvements can be achieved through careful parameter tuning.
 Enhance the data association by implementing a more advanced method, such as Global Nearest Neighbor (GNN) or Joint Probabilistic Data Association (JPDA). Integrate camera detections from Project 1 into the tracking pipeline to improve accuracy and robustness. Modify the Kalman filter to estimate an object's width, length, and height, rather than relying solely on unfiltered LiDAR detections as done previously. Replace the linear motion model with a non-linear approach, such as a bicycle model, which better represents vehicle dynamics by accounting for the fact that a vehicle moves forward or backward rather than in arbitrary directions.   
