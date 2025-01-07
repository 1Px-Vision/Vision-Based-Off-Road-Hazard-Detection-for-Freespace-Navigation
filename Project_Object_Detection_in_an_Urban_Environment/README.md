# Object Detection in Urban Environment

In this project, you will utilize the skills acquired throughout this course to implement a pretrained neural network for detecting and classifying objects in Waymo data. The provided dataset consists of images of urban environments, annotated with cyclists, pedestrians, and vehicles.

![image_p](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace Navigation/tree/main/Project_Object_Detection_in_an_Urban_Environment/Media)

## Dataset
The dataset consists of front camera images from the [Waymo Open Dataset](https://waymo.com/open/challenges), stored in TFRecord format. This format is optimized for storing sequences of binary records, facilitating efficient data reading and processing.

## Methodology
Training & Deployment Process Using AWS:

* **AWS SageMaker:** Used for running Jupyter notebooks, training and deploying the model, and performing inference.
* **AWS Elastic Container Registry (ECR):** Utilized to build Docker images and create the necessary container for executing the project.
* **AWS Simple Storage Service (S3):** Served multiple purposes:
   * Storing logs for creating visualizations.
   * Hosting the project data in a public S3 bucket.
