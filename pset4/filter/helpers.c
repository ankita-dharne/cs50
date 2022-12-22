#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double change_color;
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            change_color = (image [i][j].rgbtBlue + image [i][j].rgbtGreen + image [i][j].rgbtRed) / 3.0;
            image [i][j].rgbtBlue = image [i][j].rgbtGreen = image [i][j].rgbtRed = round(change_color);

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalBlue = image [i][j].rgbtBlue;
            int originalGreen = image [i][j].rgbtGreen;
            int originalRed = image [i][j].rgbtRed;

            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            if (sepiaRed > 255)
            {
                image [i][j].rgbtRed = 255;
            }
            else
            {
                image [i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image [i][j].rgbtGreen = 255;
            }
            else
            {
                image [i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image [i][j].rgbtBlue = 255;
            }
            else
            {
                image [i][j].rgbtBlue = sepiaBlue;
            }

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        //adding condition for j to divide the image in 2 part left & right
        for (int j = 0; j < width / 2 ; j++)
        {
            //Swapping the left with the right
            RGBTRIPLE temp = image [i] [j];
            image[i][j] = image [i][width - (j + 1)];
            image [i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original_image[i][j] = image[i][j];
        }
    }

    int red, green, blue, counter;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = green = blue = counter = 0;
            if (i >= 0 && j >= 0)
            {
                red += original_image[i][j].rgbtRed;
                green += original_image[i][j].rgbtGreen;
                blue += original_image[i][j].rgbtBlue;
                counter++;
            }
            if (i >= 0 && j - 1 >= 0)
            {
                red += original_image[i][j - 1].rgbtRed;
                green += original_image[i][j - 1].rgbtGreen;
                blue += original_image[i][j - 1].rgbtBlue;
                counter++;
            }
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1  < width))
            {
                red += original_image[i][j + 1].rgbtRed;
                green += original_image[i][j + 1].rgbtGreen;
                blue += original_image[i][j + 1].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j >= 0)
            {
                red += original_image[i - 1][j].rgbtRed;
                green += original_image[i - 1][j].rgbtGreen;
                blue += original_image[i - 1][j].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += original_image[i - 1][j - 1].rgbtRed;
                green += original_image[i - 1][j - 1].rgbtGreen;
                blue += original_image[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                red += original_image[i - 1][j + 1].rgbtRed;
                green += original_image[i - 1][j + 1].rgbtGreen;
                blue += original_image[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                red += original_image[i + 1][j - 1].rgbtRed;
                green += original_image[i + 1][j - 1].rgbtGreen;
                blue += original_image[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                red += original_image[i + 1][j].rgbtRed;
                green += original_image[i + 1][j].rgbtGreen;
                blue += original_image[i + 1][j].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                red += original_image[i + 1][j + 1].rgbtRed;
                green += original_image[i + 1][j + 1].rgbtGreen;
                blue += original_image[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            image[i][j].rgbtRed = round(red / (counter * 1.0));
            image[i][j].rgbtGreen = round(green / (counter * 1.0));
            image[i][j].rgbtBlue = round(blue / (counter * 1.0));
        }
    }
    return;
}
