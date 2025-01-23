#include <iostream>
#include <random>

#include <chrono>
#include <future>

#include "TrafficLight.h"

using namespace std::literals::chrono_literals;
using Clock=std::chrono::high_resolution_clock;
using TimePoint=std::chrono::high_resolution_clock::time_point;
using Milliseconds=std::chrono::milliseconds;
/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use 
  std::unique_lock<std::mutex> lck(_mutex);
    // to wait for and receive new messages and pull them from the queue using move semantics. 
  _cond.wait(lck,[this]{ return !_queue.empty();});
    // The received object should then be returned by the receive function. 
  T msg=std::move(_queue.back());
  _queue.pop_back();
  return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms
  std::lock_guard<std::mutex> lck(_mutex);
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
  _queue.push_back(std::move(msg));
  _cond.notify_one();
  
}


/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight():
_lightPhases{std::make_unique<MessageQueue<TrafficLightPhase>>()}  
{
    _currentPhase = red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
   while(true)
   {
        auto lightPhase{_lightPhases->receive()};
        if (lightPhase==green)
        {
           return;
        }
   }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));

}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
  
  std::random_device randomDevice;
  std::mt19937 mersenneTwisterEngine(randomDevice());
  std::uniform_int_distribution<> distribution(4000,6000);
  
  int targetCycleDuration{distribution(mersenneTwisterEngine)};
  TimePoint lastSwitch{Clock::now()};
  
      while(true)
    {
        std::this_thread::sleep_for(1ms);

        TimePoint currentTime{Clock::now()};

        auto currentCycleDuration{std::chrono::duration_cast<Milliseconds>( currentTime - lastSwitch ).count()};

        if(currentCycleDuration >= targetCycleDuration)
        {
            // toggle current phase of the traffic light
            _currentPhase = _currentPhase == red ? green : red;

            auto msg = _currentPhase;

            auto isSwitched{std::async(std::launch::async, &MessageQueue<TrafficLightPhase>::send, _lightPhases, std::move(msg))};

            isSwitched.wait();
            
            // update switch time
            lastSwitch = Clock::now();

            // setting target duration for next cycle
            targetCycleDuration = distribution(mersenneTwisterEngine);
        }
    }
  
  
  
}
