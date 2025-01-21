# Project: Program a Concurrent Traffic Simulation

This project involves the development of a traffic simulation where vehicles move along streets and navigate through intersections. As traffic density increases within the city, traffic lights become essential for ensuring road safety. Therefore, each intersection is equipped with a traffic light system. To complete the simulation, a thread-safe communication protocol was designed, enabling seamless interaction between vehicles and intersections while maintaining concurrency and data integrity.


## Project Tasks
In the initial boilerplate version of the code, all traffic lights remained green. Upon completing the project, the traffic light now blinks at random intervals between 4 to 6 seconds. To achieve this functionality, the following tasks were completed for successful project submission:

### Task FP.1: Define the TrafficLight Class
* Created a TrafficLight class that inherits from TrafficObject.
* Implemented the following public methods:
     * void waitForGreen() – waits until the traffic light turns green.
     * void simulate() – starts the simulation of the traffic light.
* TrafficLightPhase getCurrentPhase() – retrieves the current phase (red or green).
* Added a private method void cycleThroughPhases() to handle phase transitions.
* Included a private member variable _currentPhase, which stores the current state (red or green).
