# Motion Planning and Decision Making for Autonomous Vehicles

The goal of this project is to implement two critical components of a traditional hierarchical planner: the Behavior Planner and the Motion Planner. These components will work together to enable the following capabilities:

* **Static Object Avoidance:** The vehicle will detect and avoid static objects (e.g., parked cars, bicycles, and trucks) that encroach on the driving lane. The vehicle will perform either a "nudge" maneuver or a "lane change" to safely navigate around these obstacles without collisions.

* **Intersection Handling:** The vehicle will handle various types of intersections, including 3-way, 4-way, and roundabouts, by stopping at all intersections as the default behavior.

* **Lane Centerline Tracking:** The vehicle will maintain its position along the centerline of the traveling lane for optimal path adherence.

## Tasks to Be Implemented:

* **Behavioral Planning Logic:** Develop a behavioral planning system using Finite State Machines (FSM) to manage transitions between different driving states.

* **Static Object Collision Checking:** Implement a mechanism to detect and evaluate potential collisions with static objects.

* **Path and Trajectory Generation:** Generate paths and trajectories using cubic spirals, ensuring smooth and efficient vehicle movements.

* **Best Trajectory Selection:** Design a cost function to evaluate and select the optimal trajectory. The cost function will:

Perform collision and proximity checks, penalizing trajectories that approach or collide with objects. Bias the vehicle to remain close to the lane centerline for better adherence to road geometry. This project combines advanced motion planning techniques with robust decision-making to enable autonomous vehicles to navigate complex scenarios safely and efficiently.
