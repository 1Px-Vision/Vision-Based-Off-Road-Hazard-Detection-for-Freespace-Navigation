# Object Detection in Urban Environment

In this project, you will utilize the skills acquired throughout this course to implement a pretrained neural network for detecting and classifying objects in Waymo data. The provided dataset consists of images of urban environments, annotated with cyclists, pedestrians, and vehicles.

![image_p](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Object_Detection_in_an_Urban_Environment/Media/Im_PP.jpg)

## Dataset
The dataset consists of front camera images from the [Waymo Open Dataset](https://waymo.com/open/challenges), stored in TFRecord format. This format is optimized for storing sequences of binary records, facilitating efficient data reading and processing.

## Methodology
Training & Deployment Process Using AWS:

* **AWS SageMaker:** Used for running Jupyter notebooks, training and deploying the model, and performing inference.
* **AWS Elastic Container Registry (ECR):** Utilized to build Docker images and create the necessary container for executing the project.
* **AWS Simple Storage Service (S3):** Served multiple purposes:
   * Storing logs for creating visualizations.
   * Hosting the project data in a public S3 bucket.

## Model Selection

In this project, I evaluated several object detection models using the TensorFlow Object Detection API. The models tested were pre-trained and available in the TensorFlow 2 Object Detection Model Zoo, trained on the COCO 2017 dataset.

To adapt these models for the task, their ````pipeline.config````  files were modified to ensure TensorFlow 2 could locate the required TFRecord and label_map.pbtxt files when loaded from Amazon S3. Additionally, since the Waymo dataset includes only three classes—Cars, Pedestrians, and Cyclists—the pipeline.config files were further customized to accommodate this specific class structure, replacing the original 90 classes from the COCO dataset.

For all three models, I conducted training with a fixed number of 2,000 steps, constrained by my limited AWS budget. The experiments employed the Momentum Optimizer with a batch size of 8, maintaining consistency across all tests due to the same resource limitations.

## Results

Each model was evaluated using the mean Average Precision (mAP) metric, which quantifies the model's accuracy in object detection. The mAP is derived from the precision and recall values across various Intersections over Union (IoU) thresholds.

To monitor the training process, TensorBoard was employed to visualize the training loss and validation mAP for each model. The TensorBoard graphs revealed consistent patterns in training loss among the models, but their generalization performance on the test data varied.

| Metric                     | EfficientNet D1                                                                                      | SSD MobileNet V2 FPNLite                                                                               | SSD ResNet50 V1 FPN                                                                                  |
|----------------------------|-----------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------|
| mAP@ (0.5:0.95) IoU       | 0.0938                                                                                             | 0.09543                                                                                               | 0.05755                                                                                              |
| mAP@.50 IoU               | 0.2253                                                                                             | 0.2234                                                                                                | 0.1248                                                                                               |
| mAP@.75 IoU               | 0.0668                                                                                             | 0.071                                                                                                 | 0.04505                                                                                              |
| mAP (small objects)       | 0.01484                                                                                            | 0.0392                                                                                                | 0.02317                                                                                              |
| mAP (medium objects)      | 0.364                                                                                               | 0.3383                                                                                                | 0.2107                                                                                               |
| mAP (large objects)       | 0.839                                                                                               | 0.4531                                                                                                | 0.1917                                                                                               |
| Video                     | [EfficientNet Video](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Object_Detection_in_an_Urban_Environment/Media/Model_EffecientNet.gif) | [MobileNet Video](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Object_Detection_in_an_Urban_Environment/Media/Model_MobileNet.gif) | [ResNet50 Video](https://github.com/1Px-Vision/Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation/blob/main/Project_Object_Detection_in_an_Urban_Environment/Media/Model_RESNET.gif) |



## Future Work & Possible Improvement
We identified several opportunities to enhance model performance, though implementing them would require additional resources and a higher computing budget. These include:

* **Extending Training Steps:** The models were trained for only 2000 steps, which is relatively limited given the complexity of the data and architecture. Extending training until the loss plateaus could yield significant performance improvements.

* **Applying Data Augmentation:** Basic flipping, scaling, and random cropping techniques can be incorporated. Advanced methods like color jittering, rotation, and translation can also boost the model's accuracy.

* **Hyperparameter Optimization:** Fine-tuning the model's hyperparameters holds the potential for achieving better performance and robustness.

* **Addressing Occlusion and Partial Object Detection:** This project focused on detecting complete objects, but urban environments often feature partially occluded or obstructed objects. Developing strategies to handle partial object detection could further enhance the model's effectiveness.
