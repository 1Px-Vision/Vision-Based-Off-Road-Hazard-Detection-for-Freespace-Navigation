# Vision-Based-Off-Road-Hazard-Detection-for-Freespace-Navigation

Off-road freespace detection poses greater challenges compared to on-road scenarios due to the indistinct boundaries of navigable areas. Traditionally, state-of-the-art methods have utilized a fusion of Infrared
images and LiDAR data to address this issue. However, the significant increase in inference time when generating surface normal maps from LiDAR data makes these multi-modal methods unsuitable for real-time 
applications. This project introduces a novel approach for off-road freespace detection, named ROD, which leverages infrared images and eliminates the dependency on LiDAR data and its computational overhead.
By employing a pre-trained Vision Transformer (ViT), our method extracts rich features from Infrared images, enhancing both precision and inference speed.
