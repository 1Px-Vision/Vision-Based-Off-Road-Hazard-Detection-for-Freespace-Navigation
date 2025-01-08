# Motion Planning and Decision Making for Autonomous Vehicles

The goal of this project is to implement two critical components of a traditional hierarchical planner: the Behavior Planner and the Motion Planner. These components will work together to enable the following capabilities:

* **Static Object Avoidance:** The vehicle will detect and avoid static objects (e.g., parked cars, bicycles, and trucks) that encroach on the driving lane. The vehicle will perform either a "nudge" maneuver or a "lane change" to safely navigate around these obstacles without collisions.

* **Intersection Handling:** The vehicle will handle various types of intersections, including 3-way, 4-way, and roundabouts, by stopping at all intersections as the default behavior.

* **Lane Centerline Tracking:** The vehicle will maintain its position along the centerline of the traveling lane for optimal path adherence.
