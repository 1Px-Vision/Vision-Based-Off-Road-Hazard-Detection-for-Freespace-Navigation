# Project: Unscented Kalman Filter

In this final project, the scene focuses on the green ego car, while the target vehicles to be tracked are depicted in blue. The traffic cars exhibit dynamic behaviors, such as accelerating, decelerating, and changing lanes by altering their yaw angle. Each traffic vehicle is tracked using an independent Unscented Kalman Filter (UKF) instance.

Key visual elements include:

* Red Spheres: Represent the centroids of the (noisy) lidar detection clusters.
* Purple Lines: Indicate radar measurements, displaying the velocity magnitude along the detected angle.
* Green Spheres: Show the UKF's estimation of the vehicle's current position and its projected position several timesteps into the future.
* It’s important to note that the future position projection might initially fluctuate and take some time to stabilize after a lane change. This behavior arises from the assumptions within the Constant Turn Rate and Velocity (CTRV) motion model employed in this project.
