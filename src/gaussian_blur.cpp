#include <iostream>
#include <string>
#include <cuda_runtime.h>
#include <npp.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

enum gaussian_weight
{
    light,
    moderate,
    strong
};

void _checkCudaError(cudaError_t err, const char *msg)
{
    if (err != cudaSuccess)
    {
        std::cerr << "CUDA Error: " << msg << " - " << cudaGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

void _nppFilterGauss(int width, int height, int channels,
                     unsigned char *d_image,
                     unsigned char *d_result,
                     unsigned char *h_result,
                     int step,
                     NppiSize imgSize, NppiMaskSize maskSize,
                     const char *outputName)
{
    nppiFilterGauss_8u_C3R(
        d_image, step,
        d_result, step,
        imgSize,
        maskSize);

    // Copy result back to host
    h_result = new unsigned char[step * height];
    _checkCudaError(cudaMemcpy(h_result, d_result, step * height, cudaMemcpyDeviceToHost), "Error while copying result");

    // Save output image
    stbi_write_jpg(outputName, width, height, channels, h_result, 100);
}

int main(int argc, char *argv[])
{
    std::string imageName = "outer_wilds_fanart.jpg"; // default one
    if (argc >= 2)
    {
        std::string input = argv[1]; // Get the first argument passed to the program

        try
        {
            // Try converting the input to an integer
            int imageNumber = std::stoi(input);

            // Switch based on the image number
            switch (imageNumber)
            {
            case 1:
                imageName = "outer_wilds_fanart.jpg";
                break;
            case 2:
                imageName = "gnar_lol_fanart.jpg";
                break;
            case 3:
                imageName = "kvacm_wallpaper.jpg";
                break;
            default:
                std::cerr << "The input image number does not exist!" << std::endl;
                break;
            }
        }
        catch (const std::invalid_argument &e)
        {
            // If conversion fails, treat it as a string
            imageName = input;
        }
        catch (const std::out_of_range &e)
        {
            // Handle out of range errors
            std::cerr << "The input number is out of range!" << std::endl;
        }
    }

    std::cout << "Creating a Gaussian blur on the selected image: " << imageName << std::endl;

    // Load image using stb_image
    int width, height, channels;
    unsigned char *h_image = stbi_load(imageName.c_str(), &width, &height, &channels, 0);
    if (!h_image)
    {
        std::cerr << "Error loading image!" << std::endl;
        return -1;
    }

    // Allocate GPU memory
    NppiSize imgSize = {width, height};
    int step = width * channels;
    unsigned char *d_image;
    _checkCudaError(cudaMalloc(&d_image, step * height), "Allocating device memory");
    _checkCudaError(cudaMemcpy(d_image, h_image, step * height, cudaMemcpyHostToDevice), "Copying to device");

    // Apply Gaussian Blur
    int kernelSize = 5;
    Npp32s maskSize = kernelSize * kernelSize;
    Npp32f *d_kernel;
    _checkCudaError(cudaMalloc(&d_kernel, maskSize * sizeof(Npp32f)), "Allocating kernel memory");

    // Weighted sum for a Gaussian Blur smoothing
    Npp32f kernel[] = {
        1, 4, 6, 4, 1,
        4, 16, 24, 16, 4,
        6, 24, 36, 24, 6,
        4, 16, 24, 16, 4,
        1, 4, 6, 4, 1};
    _checkCudaError(cudaMemcpy(d_kernel, kernel, maskSize * sizeof(Npp32f), cudaMemcpyHostToDevice), "Copying kernel");

    unsigned char *d_result;
    _checkCudaError(cudaMalloc(&d_result, step * height), "Allocating output memory");

    unsigned char *h_result = new unsigned char[step * height];

    // Light blur
    _nppFilterGauss(width, height, channels, d_image, d_result, h_result, step, imgSize, NPP_MASK_SIZE_5_X_5, "bin\\output_light.jpg");

    // Moderate blur
    _nppFilterGauss(width, height, channels, d_image, d_result, h_result, step, imgSize, NPP_MASK_SIZE_9_X_9, "bin\\output_moderate.jpg");

    // Strong blur
    _nppFilterGauss(width, height, channels, d_image, d_result, h_result, step, imgSize, NPP_MASK_SIZE_15_X_15, "bin\\output_strong.jpg");

    // Cleanup
    stbi_image_free(h_image);
    delete[] h_result;
    cudaFree(d_image);
    cudaFree(d_result);
    cudaFree(d_kernel);

    std::cout << "Processing completed. Output saved as output.jpg" << std::endl;
    return 0;
}