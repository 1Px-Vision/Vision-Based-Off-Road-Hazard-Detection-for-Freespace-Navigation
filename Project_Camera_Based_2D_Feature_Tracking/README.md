# Project: Camera-Based 2D Feature Tracking

This project is the second in a series for Udacity's Sensor Fusion Nanodegree, focusing on the following key concepts:

* Utilizing ring buffers to manage memory efficiently when processing sequences of images
* Implementing keypoint detectors including Shi-Tomasi, Harris, FAST, BRISK, ORB, AKAZE, and SIFT
* Extracting and matching keypoint descriptors using methods such as FLANN and k-NN
  
These techniques lay the groundwork for the subsequent step: estimating time-to-collision.

## Included in this repository 

* The code used to Camera based 2D feature tracking on src directory with MidTermProject_Camera_Student.cpp, dataStructures.h, matching2D.hpp, matching2D_Student.cpp file containing the challenge for this project
* Result File with image SIFT_Keypoint and FAST_detectors_and_ORB
* Task_MP7.csv and Task_MP8_MP9.csv
* This README.md file

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

Lines 205-214 in **MidTermProject_Camera_Student.cpp**

````
/* For descriptor type, select binary (BINARY) or histogram of gradients (HOG) */
/* BINARY descriptors include: BRISK, BRIEF, ORB, FREAK, and (A)KAZE. */
/* HOG descriptors include: SIFT (and SURF and GLOH, all patented). */
string descriptorCategory {};
if (0 == descriptorType.compare("SIFT")) {
    descriptorCategory = "DES_HOG";
}
else {
    descriptorCategory = "DES_BINARY";
}
````

In the performance benchmarks detailed below (MP.7-9), the matcherType was configured to ````MAT_BF```` and the selectorType to ````SEL_KNN````. This setup enables match filtering according to the descriptor distance ratio.


## MP.6 Descriptor Distance Ratio
Lines 75-82 in **matching2D_Student.cpp**

I encountered some challenges in debugging this section, which involved understanding the structure of the data returned by ````cv::DescriptorMatcher::knnMatch````. It returns a vector of vectors of DMatch objects, where some nested vectors may have fewer than two elements.

The distance ratio filter compares the distances (SSD) between two potential matches for keypoint descriptors. A threshold value of 0.8 is set to select the match with the minimum distance, identifying it as the correct match. This approach effectively reduces the number of false-positive matches in keypoints.


## MP.7 Performance Evaluation 1

We assessed the number of keypoints located within the bounding box of the preceding vehicle for each type of detector. Refer to the Results directory in: Task_MP7.csv

Among the evaluated detectors, Harris detected the fewest relevant keypoints. The top three performers based on this metric were:

* **FAST:** Consistently generated approximately 400 keypoints per image.
* **BRISK:** Produced between 254 and 297 keypoints per image.
* **AKAZE:** Yielded between 155 and 179 keypoints per image.
  
## MP.8 Performance Evaluation 2

We counted the number of matched keypoints for each valid combination of detector type and descriptor type, totaling 35 combinations. It's important to note that SIFT descriptors could not be extracted when using ORB detectors, and AKAZE descriptors were only compatible with **AKAZE** detectors. Refer to the results in the file in the Result directory: ````Task_MP8_MP9.csv````. The FAST detectors, when paired with BRIEF, SIFT, and ORB descriptors, consistently yielded the highest number of matched keypoints, averaging around 300 per image.

## MP.9 Performance Evaluation 3

Using FAST detectors, which are generally the quickest, the three fastest descriptors identified were:

* BRISK
* BRIEF
* ORB
  
All these combinations consistently achieved execution times under ````3 ms````. Refer to the results in: ````Task_MP8_MP9.csv````. However, it's crucial to consider the trade-off between processing speed and the number of keypoints successfully matched. The most effective combinations for this project were:

* FAST detectors with ORB descriptors
* FAST detectors with BRIEF descriptors
* FAST detectors with SIFT descriptors
  
There are two main drawbacks to using SIFT: patent costs and potential delays in processing. In some instances, SIFT combinations reached execution times up to ````6 ms````. In contrast, the runtime distribution for combinations of FAST with ORB and BRIEF descriptors was more consistently under ````3 ms````.
