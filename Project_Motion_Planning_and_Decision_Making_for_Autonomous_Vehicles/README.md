# Motion Planning and Decision Making for Autonomous Vehicles

![Carla_M](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Motion_Planning_and_Decision_Making_for_Autonomous_Vehicles/Carla_Simulator.jpg)

The goal of this project is to implement two critical components of a traditional hierarchical planner: the Behavior Planner and the Motion Planner. These components will work together to enable the following capabilities:

* **Static Object Avoidance:** The vehicle will detect and avoid static objects (e.g., parked cars, bicycles, and trucks) that encroach on the driving lane. The vehicle will perform either a "nudge" maneuver or a "lane change" to safely navigate around these obstacles without collisions.

* **Intersection Handling:** The vehicle will handle various types of intersections, including 3-way, 4-way, and roundabouts, by stopping at all intersections as the default behavior.

* **Lane Centerline Tracking:** The vehicle will maintain its position along the centerline of the traveling lane for optimal path adherence.

## Tasks to Be Implemented:

* **Behavioral Planning Logic:** Develop a behavioral planning system using Finite State Machines (FSM) to manage transitions between different driving states.

* **Static Object Collision Checking:** Implement a mechanism to detect and evaluate potential collisions with static objects.

* **Path and Trajectory Generation:** Generate paths and trajectories using cubic spirals, ensuring smooth and efficient vehicle movements.

* **Best Trajectory Selection:** Design a cost function to evaluate and select the optimal trajectory. The cost function will:

Perform collision and proximity checks, penalizing trajectories approaching or colliding with objects. Bias the vehicle to remain close to the lane centerline for better adherence to road geometry. This project combines advanced motion planning techniques with robust decision-making to enable autonomous vehicles to navigate complex scenarios safely and efficiently.

In this project, you will implement two main components of a traditional hierarchical planner: The Behavior Planner and the Motion Planner.

Both will work in unison to be able to:

* Avoid static objects (cars, bicycles and trucks) parked on the side of the road (but still invading the lane). The vehicle must avoid crashing with these vehicles by executing either a “nudge” or a “lane change” maneuver.
* Handle any type of intersection (3-way, 4-way intersections and roundabouts) by STOPPING in all of them (by default)
* Track the centerline on the traveling lane.

To accomplish this, you will implement:

* Behavioral planning logic using Finite State Machines - FSM
* Static objects Collision checking.
* Path and Trajectory generation using Cubic Spirals
* Best trajectory selection through a cost function evaluation. This cost function will mainly perform a collision check and a proximity check to bring costs higher as we get closer or collide with objects but maintain a bias to stay closer to the lane center line.

![Carla_R1](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Motion_Planning_and_Decision_Making_for_Autonomous_Vehicles/Carla_Simulator_R.jpg)
# Included in this repository
The project introduces the following modified files:

* behavior_planner_FSM.cpp
* cost_functions.cpp
* motion_planner.cpp
* planning_params.h
* velocity_profile_generator.cpp
