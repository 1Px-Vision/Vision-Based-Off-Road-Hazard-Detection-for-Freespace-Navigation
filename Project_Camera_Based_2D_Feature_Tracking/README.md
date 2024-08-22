# Project: Camera-Based 2D Feature Tracking

This project is the second in a series for Udacity's Sensor Fusion Nanodegree, focusing on the following key concepts:

* Utilizing ring buffers to manage memory efficiently when processing sequences of images
* Implementing keypoint detectors including Shi-Tomasi, Harris, FAST, BRISK, ORB, AKAZE, and SIFT
* Extracting and matching keypoint descriptors using methods such as FLANN and k-NN
  
These techniques lay the groundwork for the subsequent step: estimating time-to-collision.

# Visualization of the results


## Keypoints are visualized with SIFT detectors, indicating keypoint size and orientation.


![Keypoint](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Camera_Based_2D_Feature_Tracking/Results/SIFT_Keypoint.jpg)


Performance benchmarks, sorted by number of matched keypoints. The matching algorithm is brute-force with a filtering descriptor distance ratio set to 0.8.

| Detector type | Descriptor type | Number of matched keypoints | Time detectors (ms) | Time descriptors (ms) | Total time (ms) |
|---------------|-----------------|------------------------------|---------------------|-----------------------|-----------------|
| FAST          | BRIEF           | 332                          | 1.67                | 1.53                  | 2.47            |
| FAST          | BRIEF           | 327                          | 1.93                | 1.18                  | 3.08            |
| FAST          | BRIEF           | 326                          | 1.69                | 1.15                  | 3.14            |
| FAST          | SIFT            | 325                          | 1.61                | 1.3                   | 2.91            |
| FAST          | SIFT            | 324                          | 1.64                | 0.92                  | 2.56            |
| FAST          | BRIEF           | 323                          | 1.55                | 1.13                  | 2.68            |
| FAST          | ORB             | 321                          | 1.65                | 1.07                  | 2.72            |
| FAST          | ORB             | 320                          | 1.53                | 1.03                  | 2.55            |
| FAST          | SIFT            | 316                          | 1.45                | 1.5                   | 2.95            |
| FAST          | BRIEF           | 315                          | 1.62                | 1.06                  | 2.68            |
| FAST          | ORB             | 315                          | 1.48                | 1.09                  | 2.57            |
| FAST          | SIFT            | 315                          | 1.52                | 1.31                  | 2.82            |
| FAST          | ORB             | 311                          | 1.56                | 0.97                  | 2.53            |
| FAST          | SIFT            | 311                          | 1.59                | 1.29                  | 2.88            |
| FAST          | ORB             | 308                          | 1.57                | 0.98                  | 2.54            |
| FAST          | BRIEF           | 307                          | 1.82                | 0.93                  | 2.74            |
| FAST          | ORB             | 307                          | 1.66                | 1.16                  | 2.83            |
| FAST          | ORB             | 302                          | 1.78                | 0.93                  | 2.71            |
| FAST          | SIFT            | 301                          | 1.66                | 1.42                  | 3.08            |
| FAST          | SIFT            | 300                          | 1.67                | 1.6                   | 3.27            |
| FAST          | BRIEF           | 299                          | 1.7                 | 1.02                  | 2.72            |

## Visualization of matched keypoints with FAST detectors and ORB descriptors 

![Fast_detector](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Camera_Based_2D_Feature_Tracking/Results/FAST_detectors_and_ORB.jpg)

## MP.1 Data Buffer Optimization

The standard library container ````std::deque```` provides O(1) complexity for both insertion and deletion operations at either end of the queue. This allows for constant time operations when managing objects. The current size of the deque can also be checked continuously. To add new items, ````.push_back()```` is used, and when the predefined ring buffer size limit is exceeded, older items are removed using ````.pop_front()````. 

## MP.2 Keypoint detection
Lines 81-87 in MidTermProject_Camera_Student.cpp

````
string detectorType = "..."; // Uncomment to set detector selection
        // string detectorType = "SHITOMASI";
        // string detectorType = "HARRIS";
        string detectorType = "FAST";
        // string detectorType = "BRISK";
        // string detectorType = "ORB";
        // string detectorType = "AKAZE";
        // string detectorType = "SIFT";

````
## MP.3 Keypoint removal
Lines 134-144 in MidTermProject_Camera_Student.cpp
````
if (vehicleRect.contains(kp.pt))
    // Keep this keypoint, kp

````

## MP.4 Keypoint descriptors
Lines 180-185 in MidTermProject_Camera_Student.cpp
````
string descriptorType = "...";  // Uncomment to set descriptor selection
// string descriptorType = "BRISK";
// string descriptorType = "BRIEF";
 string descriptorType = "ORB";
// string descriptorType = "FREAK";
// string descriptorType = "AKAZE";  // Fails with all non-AKAZE detectors
// string descriptorType = "SIFT";  // Fails with ORB detectors

````

## MP.5 Descriptor matching
The function matchDescriptors in **matching2D_Student.cpp** employs a decision tree-like structure based on specific string parameters:

* **descriptorCategory can be either:** DES_BINARY (binary) or DES_HOG (histogram of gradients)
* **matcherType can be either:** MAT_FLANN (````cv::FlannBasedMatcher````) or MAT_BF (brute force)
* **selectorType can be either:** SEL_NN (nearest neighbors) or SEL_KNN (k nearest neighbors)
To simplify the process and minimize mismatches related to the descriptor category, I've made the descriptorCategory dependent on the descriptorType. In this context, SIFT is evaluated as the sole descriptor that utilizes a histogram of gradients (HoG) approach.









