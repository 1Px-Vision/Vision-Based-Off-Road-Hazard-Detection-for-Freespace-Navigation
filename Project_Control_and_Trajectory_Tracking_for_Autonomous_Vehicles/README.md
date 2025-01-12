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

 ````python plot_pid.py  ````
