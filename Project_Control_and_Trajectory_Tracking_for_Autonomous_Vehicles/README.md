# Control and Trajectory Tracking for Autonomous Vehicle

## Proportional-Integral-Derivative (PID)
In this project, a PID controller is designed to perform vehicle trajectory tracking. The controller takes a trajectory represented as an array of locations and operates within a simulation environment. Its efficiency is tested using the CARLA simulator, a widely used tool in the industry.

### Installation
Run the following commands to install the code:

Clone the repository:
````
git clone https://github.com/udacity/nd013-c6-control-starter.git
````
### Run Carla Simulator
Open new window
````
su - student
cd /opt/carla-simulator/
SDL_VIDEODRIVER=offscreen ./CarlaUE4.sh -opengl
````

### Compile and Run the Controller
Open new window
````
cd nd013-c6-control-starter/project
./install-ubuntu.sh
cd pid_controller/
rm -rf rpclib
git clone https://github.com/rpclib/rpclib.git
mkdir build
cd build
cmake .
make
````
## Project Instructions

In the previous project, a path planner for the autonomous vehicle was built. Now, a steering and throttle controller is developed to enable the car to follow the planned trajectory.

A PID controller is designed and implemented as outlined.

In the ````/pid_controller```` directory, you will find the files ````pid_controller.cpp```` and ````pid_controller.h````, where you will implement your PID controller. The PID function is invoked in main.cpp.

### Step 1: Build the PID Controller Object

* Complete the TODO tasks in ````pid_controller.h```` and ````pid_controller.cpp````.
* Launch the simulator and switch to desktop mode to view the car in the CARLA simulator.
* Take a screenshot of the simulation and include it in your report. Ensure the car remains stationary in the simulation.

![test_PID](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Control_and_Trajectory_Tracking_for_Autonomous_Vehicles/Media/Test_PID_1.jpg)

### Step 2: Implementing the PID Controller for Throttle
In ````main.cpp````, complete the TODO (Step 2) to calculate the error for the throttle PID controller. The error should represent the difference between the actual speed and the desired speed.

**Useful Variables:**

The last point in the ````v_points```` vector contains the velocity determined by the path planner.
velocity stores the current actual ````velocity````.

**Key Requirements:**

Ensure the output of the controller stays within the range ````[-1, 1]````.
Add comments to your code explaining the reasoning behind your method for calculating the error.

**Tuning:**
Adjust the PID parameters until you achieve satisfactory results. Note that a perfect trajectory is not required—focus on achieving a reasonable outcome.

### Step 3: Implementing the PID Controller for Steering

In ````main.cpp````, complete the TODO (Step 3) to calculate the error for the steering PID controller. The error is defined as the angular difference between the current steering angle and the desired steering angle needed to follow the planned trajectory.

**Helpful Variables:**

* **y_points and x_points:** These represent the desired trajectory planned by the path planner.
* **yaw:** The current rotational angle of the car.
* **x_position, y_position, and z_position:** The current position of the car, if required for additional calculations.

The controller's output must remain within the range ````[-1.2, 1.2]````.

**Instructions:**

* Compute the error based on the difference between the current and desired steering angles.
* Comment your code to explain your approach and reasoning for computing the error.
  
**Tuning:**
Adjust the PID parameters until you achieve satisfactory results. Note that while a perfect trajectory is not expected, the goal is to minimize deviations effectively.

### Step 4: Evaluate PID Efficiency
The error values and PID commands are saved in  ````throttle_data.txt ```` and  ````steer_data.txt ````. To visualize the saved data, use the following command in the Control-and-Trajectory-Tracking-for-Autonomous-Vehicles/project directory:

 ````
 python plot_pid.py
 ````

# Results

![Result_Error_Steering](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Control_and_Trajectory_Tracking_for_Autonomous_Vehicles/Media/Result_Error_Steering.jpg)

![Result_Error_Throttle](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Control_and_Trajectory_Tracking_for_Autonomous_Vehicles/Media/Result_Error_Throttle.jpg)

# Answer the following questions:

**Add the plots to your report and explain them.**
Include the generated plots in your report and describe their contents.

* The plots display the error and control output for throttle and steering.
* Analyze what these plots reveal about the system's behavior.

**What is the effect of the PID according to the plots? How does each part of the PID affect the control command?**

* The P (Proportional) component is directly proportional to the error and responds relative to the current deviation.
* The D (Derivative) component helps reduce oscillations by reacting to the rate of error change.
* The I (Integral) component improves convergence by addressing accumulated errors over time.

**How would you design a method to automatically tune the PID parameters?**

Use the Twiddle (Coordinate Ascent) algorithm to automatically optimize the PID parameters. This algorithm iteratively adjusts the parameters to minimize the error.

**PID controllers are model-free controllers, meaning they do not rely on a model of the system. Could you explain the pros and cons of this type of controller?**

**Pros:**
* Easy to develop and implement, as it does not require a precise model of the car.
* Can be applied to a wide range of systems without extensive modeling efforts.

**Cons:**
* Lacks consideration of the system's dynamics, which may result in suboptimal performance.
* May struggle with complex systems where a model-based approach could yield better results.

**(Optional) What would you do to improve the PID controller?**

We need to accelerate the simulation process. One way to achieve this could be by disabling the graphical components of the simulation, allowing it to run faster while maintaining its realism and accuracy. Simulated time can be stretched or compressed without affecting the outcomes, enabling us to conduct a large number of experiments efficiently. By varying parameters and selecting those with the smallest RMSE, we can optimize the system's performance. Starting from multiple hyperpoints, we can observe where they converge to local optima and, from these, select the best optimum—this process resembles evolution by natural selection.

My approach using vector fields with the average waypoint has proven to be more effective than the approach using vector fields with the closest waypoint, primarily due to its predictive nature. However, I have a new approach I would like to test, time permitting. This approach involves vector fields based on smooth trajectories formed by the closest waypoints. Additionally, I haven't yet explored incorporating a memory of the waypoints. This could help the car recover if it falls significantly behind the waypoints, ensuring it stays on track without losing its path.

# Included in this repository
The project introduces the following modified files (pid_controller/ directory):

* main.cpp
* pid_controller.cpp
* pid_controller.h
