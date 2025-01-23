# Project: Program a Concurrent Traffic Simulation

This project involves developing a traffic simulation in which vehicles move along streets and navigate through intersections. As traffic density increases within the city, traffic lights become essential for ensuring road safety. Therefore, each intersection is equipped with a traffic light system. A thread-safe communication protocol was designed to complete the simulation, enabling seamless interaction between vehicles and intersections while maintaining concurrency and data integrity.

![traffic](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project%3A%20Program%20a%20Concurrent%20Traffic%20Simulation/traffic_simulation.gif)

## Project Tasks
In the initial boilerplate version of the code, all traffic lights remained green. Upon completing the project, the traffic light blinks randomly between 4 to 6 seconds. To achieve this functionality, the following tasks were completed for successful project submission:

### Task FP.1: Define the TrafficLight Class
* Created a TrafficLight class that inherits from ````TrafficObject````.
* Implemented the following public methods:
     * ````void waitForGreen()```` – waits until the traffic light turns green.
     * ````void simulate()```` – starts the simulation of the traffic light.
* TrafficLightPhase ````getCurrentPhase()```` – retrieves the current phase (red or green).
* Added a private method ````void cycleThroughPhases()```` to handle phase transitions.
* Included a private member variable ````_currentPhase````, which stores the current state (red or green).

### Task FP.2: Implement Phase Switching Logic
* Implemented an infinite loop that:
    * Measures the time between loop cycles.
    * Toggles the _currentPhase between red and green.
    * Sends an update message to a queue using move semantics.
* Ensured the cycle duration is randomized between 4 to 6 seconds.
* Used ````std::this_thread::sleep_for(1ms)```` to prevent excessive CPU usage.
* The cycleThroughPhases method starts in a separate thread when ````simulate()```` is called.
* Leveraged the thread queue from the base class for managing the simulation.

### Task FP.3: Define the MessageQueue Class
* Implemented a ````MessageQueue```` class to manage traffic light state transitions.
* Defined public methods:
      * ````void send(TrafficLightPhase&& phase)```` – sends a traffic light phase update using move semantics.
      * ````TrafficLightPhase receive()```` – waits for and retrieves the next phase.
* Used ````std::deque _queue```` to store ````TrafficLightPhase```` messages.
* Included ````std::condition_variable```` and ````std::mutex```` as private members for synchronization.

### Task FP.4: Implement the send Method
* Implemented send() to:
    * Lock the queue using ````std::lock_guard<std::mutex>````.
    * Add a new traffic light phase message to _queue.
    * Notify one waiting thread using ````_condition.notify_one()````.
* Added a private ````MessageQueue<TrafficLightPhase>```` member inside TrafficLight.
* Used the queue inside the infinite loop to push new traffic light phases into it via ````send()```` with move semantics.

### Task FP.5: Implement the receive Method and waitForGreen
* Implemented receive() to:
    * Use ````std::unique_lock<std::mutex>```` and ````_condition.wait()```` to wait for new messages.
    * Retrieve and return the next TrafficLightPhase from ````_queue```` using move semantics.
* Implemented ````waitForGreen()````, which:
    * Runs an infinite loop, repeatedly calling receive().
    * Returns once a green light phase (````TrafficLightPhase::green````) is received.

### Task FP.6: Integrate TrafficLight into Intersection
* In Intersection, added a private member ````_trafficLight```` of type TrafficLight.
* Inside ````Intersection::simulate()````, started the _trafficLight simulation.
* In Intersection::addVehicleToQueue(), used:
      * ````TrafficLight::getCurrentPhase()```` to check the current phase. 
      * ````TrafficLight::waitForGreen()```` to pause execution until the light turns green before allowing vehicles to proceed.

## Result Traffic Simulate

![result_TS](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project%3A%20Program%20a%20Concurrent%20Traffic%20Simulation/Result_Traffic_Simulate.jpg)

## Included in this repository
The project introduces the following modified files:

CMakeLists.txt
main.cpp (Directory src/)
route_planner.cpp (Directory src/)
