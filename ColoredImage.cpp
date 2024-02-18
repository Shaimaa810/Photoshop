// FCI – Programming 1 – 2022 - Assignment 3
//Program Name :  Colored Image Processor
//Last Modification Date: 23 / 4 / 2022
#include<bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE][RGB], merge_image[SIZE][SIZE][RGB], image2[SIZE][SIZE][RGB], shrink_image[SIZE][SIZE][RGB],
        enlarge_image[SIZE][SIZE][RGB], quarter1[SIZE][SIZE][RGB], quarter2[SIZE][SIZE][RGB], quarter3[SIZE][SIZE][RGB],
        quarter4[SIZE][SIZE][RGB], shuffle_image[SIZE][SIZE][RGB];
int filter_number;
char image_name[50], new_image[50], image2_name[50];
//---------------------------------------------------------------------------------------------------------------------
void load_image()
{
    cout << "please enter file name of the image to process:";
    cin >> image_name;
    strcat(image_name, ".bmp");
    readRGBBMP(image_name, image);
    if(filter_number == 3)
    {
        cout << "Enter second image name:";
        cin >> image2_name;
        strcat(image2_name, ".bmp");
        readRGBBMP(image2_name, image2);
    }
}
//----------------------------------------------------------------------------------------------------------------------
void save_image()
{
    if(filter_number == 3)
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeRGBBMP(new_image, merge_image);
    }
    else if(filter_number == 9)
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeRGBBMP(new_image, shrink_image);
    }
    else if(filter_number == 8)
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeRGBBMP(new_image, enlarge_image);

    }
    else if(filter_number == 11)
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeRGBBMP(new_image, shuffle_image);
    }
    else
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeRGBBMP(new_image, image);
    }
}
//---------------------------------------------------------------------------------------------------------------------
void display_filters()
{
    cout << "Ahlan ya user ya habibi\n";
    cout << "please, enter a number of filter that you want to apply or 0 to exit:\n";
    cout << "1 - Black & White Filter\n";
    cout << "2 - Invert Filter\n";
    cout << "3 - Merge Filter\n";
    cout << "4 - Flip Image\n";
    cout << "5 - Darken and Lighten Image\n";
    cout << "6 - Rotate Image\n";
    cout << "7 - Detect Image Edges\n";
    cout << "8 - Enlarge Image\n";
    cout << "9 - Shrink Image\n";
    cout << "10 - Mirror 1/2 Image\n";
    cout << "11 - Shuffle Image\n";
    cout << "12 - Blur Image\n";
    cin >> filter_number;
}
//---------------------------------------------------------------------------------------------------------------------
void merge_images()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            for(int k = 0; k < RGB; ++k)
                merge_image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void shrink_images()
{
    int choice;
    cout << "please, enter a number of shrink that you want to do\n";
    cout << "2 - shrink the image to 1/2\n";
    cout << "3 - shrink the image to 1/3\n";
    cout << "4 - shrink the image to 1/4\n";
    cin >> choice;
    int i, j, x, y;
    for(i = 0, x = 0; i < SIZE; i += choice, x++)
    {
        for(j = 0, y = 0; j < SIZE; j += choice, y++)
        {
            for(int k = 0; k < RGB; ++k)
                shrink_image[x][y][k] = image[i][j][k];
        }
    }
    for(int m = 1; m < x; ++m)
    {
        for(int n = y; n < SIZE-1; ++n)
        {
            for(int k = 0; k < RGB; ++k)
                shrink_image[m][n][k] = 255;
        }
    }
    for(int m = x; m < SIZE-1; ++m)
    {
        for(int n = 1; n < SIZE-1; ++n)
        {
            for(int k = 0; k < RGB; ++k)
                shrink_image[m][n][k] = 255;
        }

    }
}
//----------------------------------------------------------------------------------------------------------------------
void darken_lighten_image()
{
    string choice;
    cout << "if you want to make the image darker enter darker but if you want to make the image lighter enter lighter:";
    cin >> choice;
    if(choice == "darker")
    {
        for(int i = 0; i < SIZE; ++i)
        {
            for(int j = 0; j < SIZE; ++j)
            {
                for(int k = 0; k < RGB; ++k)
                    image[i][j][k] *= 0.5;
            }
        }
    }
    else
    {
        for(int i = 0; i < SIZE; ++i)
        {
            for(int j = 0; j < SIZE; ++j)
            {
                for(int k = 0; k < RGB; ++k)
                    image[i][j][k] = (image[i][j][k]+255) / 2;
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void blur_filter()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            for(int k = 0; k < RGB; ++k)
            {
                if(i == 0 && j == 0)
                    image[i][j][k] = (image[i][j][k]+image[i][j+1][k]+image[i][j+2][k]+image[i][j+3][k]+image[i][j+4][k]+image[i][j+5][k]+image[i+1][j][k]+
                                      image[i+2][j][k]+image[i+3][j][k]+image[i+4][j][k]+image[i+5][j][k]) / 11;
                else if(i == SIZE-1 && j == 0)
                    image[i][j][k] = (image[i][j][k]+image[i-1][j][k]+image[i-2][j][k]+image[i-3][j][k]+image[i-4][j][k]+image[i-5][j][k]+image[i][j+1][k]
                                      +image[i][j+2][k]+image[i][j+3][k]+image[i][j+4][k]+image[i][j+5][k]) / 11;
                else if(j == 0 && (i > 5 && i < 250))
                    image[i][j][k] = (image[i][j][k]+image[i-1][j][k] + image[i-2][j][k] + image[i-3][j][k]+image[i-4][j][k]+image[i-5][j][k]+
                                      image[i+1][j][k]+image[i+2][j][k]+image[i+3][j][k]+image[i+4][j][k]+image[i+5][j][k]+image[i][j+1][k]+image[i][j+2][k]+
                                      image[i][j+3][k]+image[i][j+4][k]+image[i][j+5][k]) / 16;
                else if(j == 0)
                    image[i][j][k] = (image[i][j][k]+image[i+1][j][k]+image[i-1][j][k]+image[i][j+1][k]) / 4;
                else if(i == 0 && j == SIZE-1)
                    image[i][j][k] = (image[i][j][k]+image[i][j-1][k] + image[i][j-2][k]+image[i][j-3][k]+image[i][j-4][k]+image[i][j-5][k]+image[i+1][j][k]+
                                      image[i+2][j][k]+image[i+3][j][k]+image[i+4][j][k]+image[i+5][j][k]) / 11;
                else if(i == SIZE-1 && j == SIZE-1)
                    image[i][j][k] = (image[i][j][k]+image[i][j-1][k] + image[i][j-2][k]+image[i][j-3][k]+image[i][j-4][k]+image[i][j-5][k]+
                                      image[i-1][j][k]+image[i-2][j][k]+image[i-3][j][k]+image[i-4][j][k]+image[i-5][j][k]) / 11;
                else if(j == SIZE-1 && (i > 5 && i < 250))
                    image[i][j][k] = (image[i][j][k]+image[i-1][j][k] + image[i-2][j][k] + image[i-3][j][k]+image[i-4][j][k]+image[i-5][j][k]+
                                      image[i+1][j][k]+image[i+2][j][k]+image[i+3][j][k]+image[i+4][j][k]+image[i+5][j][k]+image[i][j-1][k]+image[i][j-2][k]+
                                      image[i][j-3][k]+image[i][j-4][k]+image[i][j-5][k]) / 16;
                else if(j == SIZE-1)
                    image[i][j][k] = (image[i][j][k]+image[i+1][j][k]+image[i-1][j][k]+image[i][j-1][k]) / 4;
                else if(i == 0 && (j > 5 && j < 250))
                    image[i][j][k] = (image[i][j][k]+image[i+1][j][k] + image[i+2][j][k] + image[i+3][j][k]+image[i+4][j][k]+image[i+5][j][k]+image[i][j+1][k]+
                                      image[i][j+2][k]+image[i][j+3][k]+image[i][j+4][k]+image[i][j+5][k]+image[i][j-1][k]+image[i][j-2][k]+
                                      image[i][j-3][k]+image[i][j-4][k]+image[i][j-5][k]) / 16;
                else if(i == 0)
                    image[i][j][k] = (image[i][j][k]+image[i+1][j][k]+image[i][j+1][k]+image[i][j-1][k]) / 4;
                else if(i == SIZE-1 && (j > 5 && j < 250))
                    image[i][j][k] = (image[i][j][k]+image[i-1][j][k] + image[i-2][j][k] + image[i-3][j][k]+image[i-4][j][k]+image[i-5][j][k]+
                                      image[i][j+1][k]+image[i][j+2][k]+image[i][j+3][k]+image[i][j+4][k]+image[i][j+5][k]+image[i][j-1][k]+image[i][j-2][k]+
                                      image[i][j-3][k]+image[i][j-4][k]+image[i][j-5][k]) / 16;
                else if(i == SIZE-1)
                    image[i][j][k] = (image[i][j][k]+image[i-1][j][k]+image[i][j+1][k]+image[i][j-1][k]) / 4;
                else if(i > 5 && j > 5)
                    image[i][j][k] = (image[i][j][k]+image[i][j+1][k]+image[i][j+2][k]+image[i][j+3][k]+image[i][j+4][k]+image[i][j+5][k]+image[i][j-1][k]+
                                      image[i][j-2][k]+image[i][j-3][k]+image[i][j-4][k]+image[i][j-5][k]+image[i+1][j][k]+image[i+2][j][k]+image[i+3][j][k]+image[i+4][j][k]+
                                      image[i+5][j][k]+image[i-1][j][k]+image[i-2][j][k]+image[i-3][j][k]+image[i-4][j][k]+image[i-5][j][k])/21;
                else
                    image[i][j][k] = (image[i][j][k]+image[i][j+1][k] + image[i][j-1][k] + image[i+1][j][k] + image[i-1][j][k]) / 5;
            }

        }
    }

}
//----------------------------------------------------------------------------------------------------------------------
void invert_image()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            for(int k = 0; k < RGB; ++k)
            {
                if(image[i][j][k] == 0)
                    image[i][j][k] = 255;
                else if(image[i][j][k] == 255)
                    image[i][j][k] = 0;
                else
                    image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void enlarge_filter()
{
    int choice;
    cout << "please, enter a number of quarter that you want to enlarge it\n";
    cout << "1 - first quarter\n";
    cout << "2 - second quarter\n";
    cout << "3 - third quarter\n";
    cout << "4 - fourth quarter\n";
    cin >> choice;
    if(choice == 1)
    {
        for(int i = 0, x = 0; i < SIZE; i += 2, x++)
        {
            for(int j = 0, y = 0; j < SIZE; j+=2, y++)
            {
                for(int k = 0; k < RGB; ++k)
                {
                    enlarge_image[i][j][k] = image[x][y][k];
                    enlarge_image[i+1][j][k] = image[x][y][k];
                    enlarge_image[i][j+1][k] = image[x][y][k];
                    enlarge_image[i+1][j+1][k] = image[x][y][k];
                }

            }
        }
    }
    else if(choice == 2)
    {
        for(int i = 0, x = 0; i < SIZE; i += 2, x++)
        {
            for(int j = 0, y = 128; j < SIZE; j+=2, y++)
            {
                for(int k = 0; k < RGB; ++k)
                {
                    enlarge_image[i][j][k] = image[x][y][k];
                    enlarge_image[i+1][j][k] = image[x][y][k];
                    enlarge_image[i][j+1][k] = image[x][y][k];
                    enlarge_image[i+1][j+1][k] = image[x][y][k];
                }

            }
        }
    }
    else if(choice == 3)
    {
        for(int i = 0, x = 128; i < SIZE; i += 2, x++)
        {
            for(int j = 0, y = 0; j < SIZE; j+=2, y++)
            {
                for(int k = 0; k < RGB; ++k)
                {
                    enlarge_image[i][j][k] = image[x][y][k];
                    enlarge_image[i+1][j][k] = image[x][y][k];
                    enlarge_image[i][j+1][k] = image[x][y][k];
                    enlarge_image[i+1][j+1][k] = image[x][y][k];
                }
            }
        }
    }
    else if(choice == 4)
    {
        for(int i = 0, x = 128; i < SIZE; i += 2, x++)
        {
            for(int j = 0, y = 128; j < SIZE; j+=2, y++)
            {
                for(int k = 0; k < RGB; ++k)
                {
                    enlarge_image[i][j][k] = image[x][y][k];
                    enlarge_image[i+1][j][k] = image[x][y][k];
                    enlarge_image[i][j+1][k] = image[x][y][k];
                    enlarge_image[i+1][j+1][k] = image[x][y][k];
                }
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
void rotate_90_degrees()
{
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = i; j < SIZE - i - 1; j++)
        {
            for(int k = 0; k < RGB; ++k)
            {
                int temp = image[i][j][k];
                image[i][j][k] = image[SIZE - 1 - j][i][k];
                image[SIZE - 1 - j][i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                image[SIZE - 1 - i][SIZE - 1 - j][k] = image[j][SIZE - 1 - i][k];
                image[j][SIZE - 1 - i][k] = temp;

            }
        }
    }
}
void rotate_filter()
{
    int choice;
    cout << "if you want to rotate the image by 90 degrees enter 90, if you want to rotate the image by 180 degrees enter 180, "
            "if you want to rotate the image by 270 degrees enter 270: ";
    cin >> choice;
    if(choice == 90)
    {
        rotate_90_degrees();
    }
    else if(choice == 180)
    {
        rotate_90_degrees();
        rotate_90_degrees();
    }
    else if(choice == 270)
    {
        rotate_90_degrees();
        rotate_90_degrees();
        rotate_90_degrees();
    }
}
//----------------------------------------------------------------------------------------------------------------------
void shuffle_filter()
{
    int q1, q2, q3, q4;
    cout << "Enter the order of quarters:";
    cin >> q1 >> q2 >> q3 >> q4;
    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < 128; j++)
        {
            for(int k = 0; k < RGB; ++k)
                quarter1[i][j][k] = image[i][j][k];
        }
    }
    for(int i = 0; i < 128; i++)
    {
        for(int j = 128; j < SIZE; j++)
        {
            for(int k = 0; k < RGB; ++k)
                quarter2[i][j][k] = image[i][j][k];
        }
    }
    for(int i = 128; i < SIZE; i++)
    {
        for(int j = 0; j < 128; j++)
        {
            for(int k = 0; k < RGB; ++k)
                quarter3[i][j][k] = image[i][j][k];
        }
    }
    for(int i = 128; i < SIZE; i++)
    {
        for(int j = 128; j < SIZE; j++)
        {
            for(int k = 0; k < RGB; ++k)
                quarter4[i][j][k] = image[i][j][k];
        }
    }
    if(q1 == 1)
    {
        for(int i = 0; i < 128; i++)
        {
            for(int j = 0; j < 128; j++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[i][j][k] = quarter1[i][j][k];
            }
        }
    }
    else if(q1 == 2)
    {
        for(int i = 0, x = 0; i < 128; i++, x++)
        {
            for(int j = 128, y = 0; j < SIZE; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter2[i][j][k];
            }
        }
    }
    else if(q1 == 3)
    {
        for(int i = 128, x = 0; i < SIZE; i++, x++)
        {
            for(int j = 0, y = 0; j < 128; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter3[i][j][k];
            }
        }
    }
    else if(q1 == 4)
    {
        for(int i = 128, x = 0; i < SIZE; i++, x++)
        {
            for(int j = 128, y = 0; j < SIZE; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter4[i][j][k];
            }
        }
    }
    if(q2 == 1)
    {
        for(int i = 0, x = 0; i < 128; i++, x++)
        {
            for(int j = 0, y = 128; j < 128; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter1[i][j][k];
            }
        }
    }
    else if(q2 == 2)
    {
        for(int i = 0; i < 128; i++)
        {
            for(int j = 128; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[i][j][k] = quarter2[i][j][k];
            }
        }
    }
    else if(q2 == 3)
    {
        for(int i = 128, x = 0; i < SIZE; i++, x++)
        {
            for(int j = 0, y = 128; j < 128; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter3[i][j][k];
            }
        }
    }
    else if(q2 == 4)
    {
        for(int i = 128, x = 0; i < SIZE; i++, x++)
        {
            for(int j = 128, y = 128; j < SIZE; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter4[i][j][k];
            }
        }
    }
    if(q3 == 1)
    {
        for(int i = 0, x = 128; i < 128; i++, x++)
        {
            for(int j = 0, y = 0; j < 128; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter1[i][j][k];
            }
        }
    }
    else if(q3 == 2)
    {
        for(int i = 0, x = 128; i < 128; i++, x++)
        {
            for(int j = 128, y = 0; j < SIZE; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter2[i][j][k];
            }
        }
    }
    else if(q3 == 3)
    {
        for(int i = 128; i < SIZE; i++)
        {
            for(int j = 0; j < 128; j++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[i][j][k] = quarter3[i][j][k];
            }
        }
    }
    else if(q3 == 4)
    {
        for(int i = 128, x = 128; i < SIZE; i++, x++)
        {
            for(int j = 128, y = 0; j < SIZE; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter4[i][j][k];
            }
        }
    }
    if(q4 == 1)
    {
        for(int i = 0, x = 128; i < 128; i++, x++)
        {
            for(int j = 0, y = 128; j < 128; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter1[i][j][k];
            }
        }
    }
    else if(q4 == 2)
    {
        for(int i = 0, x = 128; i < 128; i++, x++)
        {
            for(int j = 128, y = 128; j < SIZE; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter2[i][j][k];
            }
        }
    }
    else if(q4 == 3)
    {
        for(int i = 128, x = 128; i < SIZE; i++, x++)
        {
            for(int j = 0, y = 128; j < 128; j++, y++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[x][y][k] = quarter3[i][j][k];
            }
        }
    }
    if(q4 == 4)
    {
        for(int i = 128; i < SIZE; i++)
        {
            for(int j = 128; j < SIZE; j++)
            {
                for(int k = 0; k < RGB; ++k)
                    shuffle_image[i][j][k] = quarter4[i][j][k];
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
void black_white_image()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            for(int k = 0; k < RGB; k+=3)
            {
                if(image[i][j][k] > 127)
                {
                    image[i][j][k] = 255;
                    image[i][j][k+1] = 255;
                    image[i][j][k+2] = 255;

                }
                else
                {
                    image[i][j][k] = 0;
                    image[i][j][k+1] = 0;
                    image[i][j][k+2] = 0;
                }

            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
void  detect_edges()
{
    black_white_image();
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for(int k = 0; k < RGB; ++k)
            {
                if (image[i+1][j][k]==image[i-1][j][k]&&image[i][j+1][k]==image[i][j-1][k]&&image[i+1][j][k]==image[i][j-1][k])
                    image2[i][j][k]=255;
                else
                    image2[i][j][k]=0;
            }
        }
    }
    // for loop to save th image after has  been changed in the second array
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for(int k = 0; k < RGB; ++k)
            {
                image[i][j][k]=image2[i][j][k];
            }

        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
// filter to flip the image either vertical or horizontal
void flip_vertical()
{
    for(int i =0; i<(SIZE/2); i++)
    {
        for(int j = 0; j<(SIZE); j++)
        {
            for(int k = 0; k < RGB; ++k)
                swap(image[i][j][k],image[256-i-1][j][k]);
        }
    }

}
void flip_horizontal()
{
    for(int i =0; i<(SIZE); i++)
    {
        for(int j = 0; j<(SIZE/2); j++)
        {
            for(int k = 0; k < RGB; ++k)
                swap(image[i][j][k],image[i][256-j-1][k]);
        }
    }

}
void flip_filter()
{
    int choice;
    cout << "please, enter a number of flip that you want to do:\n";
    cout << "1 - flip horizontal\n";
    cout << "2 - flip vertical\n";
    cin >> choice;
    if(choice == 1)
        flip_horizontal();
    else if(choice == 2)
        flip_vertical();
}
//----------------------------------------------------------------------------------------------------------------------
void mirror_right()
{
    int n=255;
    for(int row=0;row<SIZE;row++)
    {
        for(int col=255;col>128;col--)
        {
            for(int k = 0; k < RGB; ++k)
            {
                image[row][col-n][k] = image[row][col][k] ;
            }
            n = n - 2;
        }
        n=255;
    }

}

void mirror_left()
{
    int n = 255;
    for(int row=0;row<SIZE;row++)
    {
        for(int col=255;col>128;col--)
        {
            for(int k = 0; k < RGB; ++k)
            {
                image[row][col][k] = image[row][col-n][k];
            }
            n = n - 2;
        }
        n = 255;
    }
}


void mirror_up(){
    int    n=255;
    for(int col=0;col<SIZE;col++)
    {
        for(int row=255;row>128;row--)
        {
            for(int k = 0; k < RGB; ++k)
            {
                image[row][col][k] = image[row-n][col][k] ;
            }
            n=n-2;
        }
        n=255;
    }
}
void mirror_down(){
    int    n=255;
    for(int col=0;col<SIZE;col++)
    {
        for(int row=255;row>128;row--)
        {
            for(int k = 0; k < RGB; ++k)
            {
                image[row-n][col][k] = image[row][col][k]  ;
            }
            n=n-2;
        }
        n=255;
    }
}
void mirror_image(){
    int num;
    cout<<"please enter the number of type of mirroring\n";
    cout << "1 - mirror left\n";
    cout << "2 - mirror right\n";
    cout << "3 - mirror up\n";
    cout << "4 - mirror down\n";
    cin>>num;
    if(num==1)
    {
        mirror_left();
    }
    if (num==2){
        mirror_right();}
    if (num==3){
        mirror_up();}
    if (num==4){
        mirror_down();}
}
//----------------------------------------------------------------------------------------------------------------------
int main()
{
    display_filters();
    load_image();
    if(filter_number == 1)
        black_white_image();
    else if(filter_number == 2)
        invert_image();
    else if(filter_number == 3)
        merge_images();
    else if(filter_number == 4)
        flip_filter();
    else if(filter_number == 5)
        darken_lighten_image();
    else if(filter_number == 6)
        rotate_filter();
    else if(filter_number == 7)
        detect_edges();
    else if(filter_number == 8)
        enlarge_filter();
    else if(filter_number == 9)
        shrink_images();
    else if(filter_number == 10)
        mirror_image();
    else if(filter_number == 11)
        shuffle_filter();
    else if(filter_number == 12)
        blur_filter();
    save_image();
    return 0;
}

