# General
## Question 1: Explain a recent project you've worked on. Why did you choose this project?, What difficulties did you run into this project that you did not expect, and how did you solve them?

I worked on a project involving control, fusion sensors, and tracking with UAVs for rescue applications. The project had a strict timeline, and the initial development phase had already begun. There was no existing documentation, and the large code base required updates and adaptations to meet specific requirements. To address this, I used Doxygen to generate documentation directly from the codebase. I also resolved issues daily by employing a simulator to handle various events and messages and writing C++ code to support them.

# Mandatory
## Question 2: What are some of the advantages & disadvantages of cameras, lidar and radar? What combination of these (and other sensors) would you use to ensure the appropriate and accurate perception of the environment?

* **Camera:** A camera is essentially a sensor that captures an array of color points in space, forming what is known as an image array. This image array is then converted into a digital signal, which is transmitted to hardware that performs sensor fusion and scene understanding.

* **LiDAR:** LiDAR (Light Detection and Ranging) uses a laser-based, point-and-shoot approach to sense the environment. A LiDAR transmitter emits a pulse of light, waits for the light to reflect off an object, and calculates the distance based on the time it takes for the light to return, knowing the speed of light. To expand its field of view, LiDAR can use multiple lasers that rotate, or more recently, a fixed array of lasers spread across the field of view, known as "Solid State LiDAR." Once all the light signals are received, the LiDAR system generates a "point cloud," containing an array of directional and distance information, which is sent to the hardware for sensor fusion and scene understanding.

* **Radar:** Radar technology has been in use for a long time. Similar to LiDAR, it employs a point-and-shoot method, but it uses radio waves (electromagnetic waves) instead of light. Radar is particularly effective for long-distance object detection but generally lacks precision compared to LiDAR. Testing radar technology follows a similar process to LiDAR testing. Given its lower cost and wider familiarity, some companies have already developed specialized tools for radar testing.

![](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Autonomous-Systems-Interview-Practice-Project/Sensor_Fusion_Table.jpg)

-- Fig.1. Evaluation of Autonomous Vehicle Sensors  --



