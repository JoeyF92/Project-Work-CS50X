#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int y = 0; y <= width - 1; y++)
        {
            float average_color = round((image[i][y].rgbtRed + image[i][y].rgbtGreen + image[i][y].rgbtBlue) / 3.0);
            image[i][y].rgbtRed = average_color;
            image[i][y].rgbtGreen = average_color;
            image[i][y].rgbtBlue = average_color;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int y = 0; y <= width - 1; y++)
        {

            int sepia_red = round((image[i][y].rgbtRed * .393) + (image[i][y].rgbtGreen * .769) + (image[i][y].rgbtBlue * .189));
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            if (sepia_red < 0)
            {
                sepia_red = 0;
            }
            int sepia_green = round((image[i][y].rgbtRed * .349) + (image[i][y].rgbtGreen * .686) + (image[i][y].rgbtBlue * .168));
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            if (sepia_green < 0)
            {
                sepia_green = 0;
            }
            int sepia_blue = round((image[i][y].rgbtRed * .272) + (image[i][y].rgbtGreen * .534) + (image[i][y].rgbtBlue * .131));
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            if (sepia_blue < 0)
            {
                sepia_blue = 0;
            }
            image[i][y].rgbtRed = sepia_red;
            image[i][y].rgbtGreen = sepia_green;
            image[i][y].rgbtBlue = sepia_blue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    //first check if width is even to dictate at what point we stop swapping from left to right
    if (width % 2 == 0)
    {
        for (int i = 0; i <= height - 1; i++)
        {
            int end_pixel = width - 1;
            for (int y = 0; y <= (width - 1) / 2; y++)
            {
                //use a temp variable to facilitate, we're swapping the left side and the right sides pixels moving outside to inside
                RGBTRIPLE temp_color;
                temp_color = image[i][y];
                image[i][y] = image[i][end_pixel];
                image[i][end_pixel] = temp_color;
                end_pixel -= 1;
            }
        }
    }
    //else width is odd
    else
    {
        for (int i = 0; i <= height - 1; i++)
        {
            int end_pixel = width - 1;
            for (int y = 0; y < (width - 1) / 2; y++)
            {
                //use a temp variable to facilitate, we're swapping the left side and the right sides pixels moving outside to inside
                RGBTRIPLE temp_color;
                temp_color = image[i][y];
                image[i][y] = image[i][end_pixel];
                image[i][end_pixel] = temp_color;
                end_pixel -= 1;
            }
        }
    }



    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create an array to copy the image into so we dont affect the blurring of other pixels
    RGBTRIPLE copy[height][width];

    //loop through the image to select each individual pixel
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            float counter = 0;
            int red = 0;
            int green = 0;
            int blue = 0;

            //once at a pixel - loop again through the 9 pixels surrounding it to average them
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    //check if the neighbouring pixel exists
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        // if the pixel doesnt exist, we continue through the loop
                        continue;
                    }
                    //if neighbouring pixel exists, add the colors up for averaging and add 1 to the counter
                    counter += 1;
                    red += image[currentX][currentY].rgbtRed;
                    green += image[currentX][currentY].rgbtGreen;
                    blue += image[currentX][currentY].rgbtBlue;
                }

            }

            // round up the average reds, greens and blues and insert into the pixel for our copied image
            copy[i][j].rgbtRed = round(red / counter);
            copy[i][j].rgbtGreen = round(green / counter);
            copy[i][j].rgbtBlue = round(blue / counter);
        }
    }

    //finally loop through the image and add our copied values into it
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }

    return;
}
