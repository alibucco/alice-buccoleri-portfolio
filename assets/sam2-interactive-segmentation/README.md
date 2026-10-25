# Interactive 3D Reconstruction with SAM 2

### Image Processing & Computer Vision · Python

**[Explore the interactive segmentation code on GitHub](https://github.com/alibucco/sam2-segmentazione-interattiva)**

A Computer Vision project that connects 3D scene reconstruction with interactive object segmentation. The broader workflow reconstructs a real indoor environment from captured imagery, then identifies objects of interest as selectable regions in the source images.

The project was developed with **Daniele Bongiovanni** for the Image Processing and Computer Vision course at Politecnico di Torino.

## Project goal

The aim was to create a bridge between a reconstructed 3D scene and semantic object selection. Starting from room images and videos, the project investigates how individual objects can be identified through masks and later associated with the reconstructed environment for interaction such as highlighting, translation or rotation.

For the reconstruction phase, we compared photogrammetry and LiDAR-based tools, ultimately using **Polycam** for its more coherent representation of the captured room.

## Interactive segmentation with SAM 2

The repository implements the segmentation component with **SAM 2.1 Hiera Tiny**. The application lets the user:

- Load an RGB image from the room dataset.
- Select positive clicks to identify the target object.
- Add negative clicks to remove incorrectly selected regions.
- Produce both a binary mask and an image overlay that highlights the segmentation.

The model was tested on objects with different characteristics, including a poster, a small deodorant bottle, a chair and partially occluded objects. Clear, fully visible objects required few interactions; articulated or occluded objects benefited from additional positive and negative points.

## Technologies

**Python · PyTorch · OpenCV · Segment Anything Model 2 · Polycam**

## Project material

- [Full project report](interactive-3d-reconstruction-sam2-report.pdf)
