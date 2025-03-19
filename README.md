
# **CUDAatScaleForTheEnterprise**

## Overview

This project demonstrates the use of the NVIDIA Performance Primitives (NPP) library with CUDA to perform image blurring. The goal is to leverage GPU acceleration for efficient image processing. This project is part of the **CUDA at Scale for the Enterprise** course and serves as a template to understand how to implement basic image processing operations using CUDA and NPP.

## Code Organization

### `bin/`
Contains all binary/executable files generated during the build process. These files will have the platform-specific extensions (e.g., `.exe` for Windows). This folder also holds the output JPEG files produced by the program.

### `data/`
Stores the input images for the project. You can add your own images here to be processed by the executable.

### `lib/`
Contains any libraries that are not installed via the operating system's package manager. This makes it easier to include and link them during the build process.

### `logs/`
Contains a proof of execution for a small and large image.

### `src/`
Contains the source code.

### `README.md`
This file provides an overview of the project and instructions for usage. So that anyone cloning or deciding if they want to clone this repository can understand its purpose.

### `Makefile`
A rudimentary script for automatically building the project.

## Key Concepts

- Performance Optimization
- Image Processing
- NPP Library

## Supported SM Architectures

- [SM 3.5](https://developer.nvidia.com/cuda-gpus)  
- [SM 3.7](https://developer.nvidia.com/cuda-gpus)  
- [SM 5.0](https://developer.nvidia.com/cuda-gpus)  
- [SM 5.2](https://developer.nvidia.com/cuda-gpus)  
- [SM 6.0](https://developer.nvidia.com/cuda-gpus)  
- [SM 6.1](https://developer.nvidia.com/cuda-gpus)  
- [SM 7.0](https://developer.nvidia.com/cuda-gpus)  
- [SM 7.2](https://developer.nvidia.com/cuda-gpus)  
- [SM 7.5](https://developer.nvidia.com/cuda-gpus)  
- [SM 8.0](https://developer.nvidia.com/cuda-gpus)  
- [SM 8.6](https://developer.nvidia.com/cuda-gpus)

## Supported OSes

This project was developed and tested on Windows. Modifications are provided to enable usage on Linux systems.

## Dependencies and Prerequisites

1. Download and install the [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads) for your platform.  
2. Set the environment variable as follows:  
   ```sh
   CUDA_PATH = "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v*\bin"
   ```
3. This project uses the free [stb library](https://github.com/nothings/stb) to read and write images.  
   Be sure to check the [README.md](lib/stb-master/README.md) and [LICENSE](lib/stb-master/LICENSE) before using it.

4. You may need `make` to clean and rebuild the project. I used [MSYS2](https://www.msys2.org/) to run `make`.

## Provided data

There is 2 small format image 

## Build and Run

### **Windows**

The Windows build uses a `Makefile`.

Depending on your system configuration, you may need to use either `mingw32-make.exe` or `make.exe`.

#### Usage

##### **clean**
```bash
mingw32-make clean
```
This will remove all files from the `bin/` directory.

##### **build**
To build the project, run:
```bash
mingw32-make build
```

##### **run**
Once the build is complete, run the program with:
```bash
mingw32-make run  # Uses the default image
```

To run with a custom input image, place the image in the `data/` folder and run:
```bash
mingw32-make run "image_name.jpg"
```

### **Linux**

The Linux version also uses a `Makefile`.  
Rename the current `Makefile` to `Makefile_Windows` and the Linux-specific `Makefile` to `Makefile`.

Ensure you have a supported host compiler for Linux. Refer to the [Linux Installation Guide](http://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#system-requirements).

To build on Linux, first run:
```bash
$ make HOST_COMPILER=g++
```

#### Usage

##### **clean**
```bash
make clean
```

##### **build**
```bash
make build
```

##### **run**
To run the program with the default image:
```bash
make run
```

For custom input files, place the image in the `data/` folder and run:
```bash
make run "image_name.jpg"
```
