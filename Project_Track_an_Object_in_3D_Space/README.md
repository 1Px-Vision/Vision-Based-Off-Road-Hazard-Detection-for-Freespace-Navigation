# Project: Track an Object in 3D Space

This project marks the culmination of the camera unit in Udacity's Sensor Fusion Nanodegree, covering the following key concepts:

* Keypoint detection and description techniques
* Object detection using the pre-trained YOLO deep learning framework
* Object tracking by matching key points and bounding boxes across consecutive images
* Associating regions in camera images with corresponding lidar points in 3D space

## Included in this repository 

* The code used to Camera based 2D feature tracking on src directory with MidTermProject_Camera_Student.cpp, dataStructures.h, matching2D.hpp, matching2D_Student.cpp file containing the challenge for this project
* Result File with image Near-side outlier, Far-side outlier, and Multiple-side outlier
* results.csv test FP.6
* This README.md file

![3D_track](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Track_an_Object_in_3D_Space/ttc_estimation.png)
 
The flowchart below outlines the structure of the final project. The steps within the orange box were completed in the previous project, 2D Feature Tracking. This project builds upon that foundation by implementing the steps in the blue box and beyond. Objects detected by the YOLO deep neural network are tracked across frames by evaluating the strength of keypoint correspondences within their bounding boxes. Finally, a robust estimation of time-to-collision (TTC) is performed using data from both the lidar and camera sensors.

![TCC](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Track_an_Object_in_3D_Space/course_code_structure.png)

## FP.1 Match 3D objects
Lines 224-284 in **camFusion_Student.cpp** function ````void matchBoundingBoxes````

Following the suggestion, I utilized a ````std::multimap<int, int>```` to keep track of pairs of bounding box IDs. By counting the keypoint correspondences for each bounding box pair, I identified the best matches between frames.

## FP.2 Compute lidar-based TTC

Lines 202-221 in **camFusion_Student.cpp:** For each frame, I used the median x-distance to minimize the influence of outlier lidar points on the TTC estimate. Using the constant velocity model, the main equation is as follows:

````
// Compute time-to-collision (TTC) based on relevant lidar points
void computeTTCLidar
 TTC = d1 * (1.0 / frameRate) / (d0 - d1);
````

Lines 192-199 in **camFusion_Student.cpp**
To calculate the median, I built a helper function to sort the vector of lidar points.

````
void sortLidarPointsX(std::vector<LidarPoint> &lidarPoints)
{
    // This std::sort with a lambda mutates lidarPoints, a vector of LidarPoint
    std::sort(lidarPoints.begin(), lidarPoints.end(), [](LidarPoint a, LidarPoint b) {
        return a.x < b.x;  // Sort ascending on the x coordinate only
    });
}
````

## FP.3 Associate keypoint matches with bounding boxes

The algorithm involves the following steps:

* Initialize two empty vectors: matches_selected and matches_distance. These vectors will store the selected matches and their respective distances.
* Loop through each match in the kptMatches vector.
* For each match, retrieve the corresponding keypoints from the previous and current frames. Check if the current keypoint lies within the bounding box.
* If the current keypoint is inside the bounding box, add the match to the matches_selected vector and calculate the distance between the keypoints.
* Store the calculated distance in the matches_distance vector.
* Compute the mean distance of all selected matches.
* Iterate over the matches_selected vector again. For each match, if the distance between the keypoints is less than the calculated mean distance, add the match and its corresponding keypoint to the BoundingBox object

````
// associate a given bounding box with the keypoints it contains
void clusterKptMatchesWithROI(BoundingBox &boundingBox, std::vector<cv::KeyPoint> &kptsPrev, std::vector<cv::KeyPoint> &kptsCurr, std::vector<cv::DMatch> &kptMatches)
{ 
  	
    std::vector<cv::DMatch> matches_selected;
    std::vector<double> matches_distance;

  	// check the keypoints are within the bounding boxes
    for (int i = 0; i < kptMatches.size(); ++i)
    {
      	auto distance=cv::norm(kptsCurr[kptMatches[i].trainIdx].pt - kptsPrev[kptMatches[i].queryIdx].pt);
        if (boundingBox.roi.contains(kptsCurr[kptMatches[i].trainIdx].pt))
        {	
            matches_selected.push_back(kptMatches[i]);
            matches_distance.push_back(distance);
        }
      	else{
        	continue;
        }
    }
  	
	// calculate the mean of the match distances to fileter the points
  	// https://stackoverflow.com/questions/28574346/find-average-of-input-to-vector-c
    double meanDistance = std::accumulate(matches_distance.begin(), matches_distance.end(), 0.0) / matches_distance.size();
  	
    for (int i = 0; i < matches_distance.size(); ++i)
    {
        if (matches_distance[i] < meanDistance) // if near to the mean it's okey else continue;
        {
            boundingBox.kptMatches.push_back(matches_selected[i]);
          	boundingBox.keypoints.push_back(kptsCurr[matches_selected[i].trainIdx]);
        }
      	else{
        	continue;
        }
    } 
}
````

## FP.4 Compute mono camera-based TTC
Lines 133-142 in **camFusion_Student.cpp** contain a function that processes each bounding box by iterating through all matched keypoint pairs in an image. If a keypoint is located within the region-of-interest (ROI) of the current frame's bounding box, the keypoint match is linked to the current ````BoundingBox```` data structure.

````
TTC = (-1.0 / frameRate) / (1 - medianDistRatio);
````

## FP.5 Performance evaluation, lidar outliers

I did not encounter any frames where the lidar estimated TTC was unreasonable, with estimates consistently ranging from approximately ````8 to 15 seconds````. Using the median point instead of the closest point effectively mitigated issues caused by outliers. Below, I've included some examples of the lidar top-view.

_Figure 1. Near-side outlier_

![Near_det](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Track_an_Object_in_3D_Space/results/Fig_Near-side%20outlier.jpg)

_Figure 2. Far-side outlier_

![Far_det](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Track_an_Object_in_3D_Space/results/Fig_Far-side%20outlier.jpg)


_Figure 3. Multiple-side outlier_


![Mul_det](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Track_an_Object_in_3D_Space/results/Fig_Multiple-side%20outlier.jpg)
    

## FP.6 Performance evaluation, detector/descriptor combinations
Some detector/descriptor combinations, particularly the Harris and ORB detectors, resulted in unreliable camera TTC estimates. In contrast, detectors like SIFT, FAST, and AKAZE provided consistent results that aligned closely with the TTC estimates from the lidar sensor. Below is a sample of the results matrix, ranked by the difference in TTC estimates between the camera and lidar systems.

| Detector  | Descriptor | Frame index | TTC lidar | TTC camera | TTC difference |
|-----------|------------|-------------|-----------|------------|----------------|
| FAST      | ORB        | 17          | 9.55      | 9.68       | 0.13           |
| ORB       | FREAK      | 15          | 8.57      | 8.68       | 0.11           |
| ORB       | BRISK      | 9           | 13.02     | 13.13      | 0.10           |
| BRISK     | FREAK      | 11          | 12.81     | 12.88      | 0.07           |
| SIFT      | SIFT       | 16          | 9.52      | 9.58       | 0.06           |
| SIFT      | BRISK      | 9           | 13.02     | 13.06      | 0.03           |
| SIFT      | BRISK      | 13          | 9.96      | 9.99       | 0.02           |
| SIFT      | BRIEF      | 9           | 13.02     | 13.04      | 0.02           |
| SHITOMASI | ORB        | 7           | 11.98     | 11.97      | -0.01          |
| FAST      | FREAK      | 2           | 12.61     | 12.60      | -0.01          |
| ORB       | BRISK      | 14          | 9.60      | 9.59       | -0.01          |
| ORB       | SIFT       | 16          | 9.52      | 9.50       | -0.02          |
| SIFT      | FREAK      | 16          | 9.52      | 9.50       | -0.02          |
| FAST      | SIFT       | 3           | 14.09     | 14.06      | -0.03          |
| SIFT      | BRISK      | 17          | 9.55      | 9.52       | -0.03          |
| SIFT      | BRISK      | 14          | 9.60      | 9.55       | -0.05          |
| SIFT      | SIFT       | 2           | 12.61     | 12.56      | -0.05          |
| FAST      | SIFT       | 17          | 9.55      | 9.44       | -0.10          |

````
$ ./3D_object_tracking

Detector,Descriptor,Frame index,TTC lidar,TTC camera,TTC difference

AKAZE,AKAZE,1,12.5156,12.3444,-0.171208,
AKAZE,AKAZE,2,12.6142,14.0983,1.48408,
AKAZE,AKAZE,3,14.091,12.8828,-1.20818,
AKAZE,AKAZE,4,16.6894,14.4781,-2.21132,
AKAZE,AKAZE,5,15.9082,16.7468,0.838524,
AKAZE,AKAZE,6,12.6787,13.8675,1.18879,
AKAZE,AKAZE,7,11.9844,15.3448,3.36044,
AKAZE,AKAZE,8,13.1241,14.1378,1.01365,
AKAZE,AKAZE,9,13.0241,13.8398,0.815652,
AKAZE,AKAZE,10,11.1746,11.5483,0.373644,
AKAZE,AKAZE,11,12.8086,12.1341,-0.674506,
AKAZE,AKAZE,12,8.95978,11.0554,2.09557,
AKAZE,AKAZE,13,9.96439,11.2852,1.32083,
AKAZE,AKAZE,14,9.59863,10.5842,0.985564,
AKAZE,AKAZE,15,8.57352,10.1989,1.62537,
AKAZE,AKAZE,16,9.51617,9.81256,0.296389,
AKAZE,AKAZE,17,9.54658,9.06452,-0.482057,
AKAZE,AKAZE,18,8.3988,8.97386,0.575053,

````
