// FCI – Programming 1 – 2022 - Assignment 3
//Program Name : Gray Scale Image Processor
//Last Modification Date: 23 / 4 / 2022
#include<bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;
int filter_number;
char image_name[50], new_image[50], image2_name[50];
unsigned char image[SIZE][SIZE], image2[SIZE][SIZE], merge_image[SIZE][SIZE], shrink_image[SIZE][SIZE],
        enlarge_image[SIZE][SIZE], quarter1[SIZE][SIZE], quarter2[SIZE][SIZE], quarter3[SIZE][SIZE],
        quarter4[SIZE][SIZE], shuffle_image[SIZE][SIZE];
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
void load_image()
{
    cout << "please enter file name of the image to process:";
    cin >> image_name;
    strcat(image_name, ".bmp");
    readGSBMP(image_name, image);
    if(filter_number == 3)
    {
        cout << "Enter the second image name:";
        cin >> image2_name;
        strcat(image2_name, ".bmp");
        readGSBMP(image2_name, image2);
    }
}
//--------------------------------------------------------------------------------------------------------------------
void save_image()
{
    if(filter_number == 3)
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeGSBMP(new_image, merge_image);
    }
    else if(filter_number == 9)
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeGSBMP(new_image, shrink_image);
    }
    else if(filter_number == 8)
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeGSBMP(new_image, enlarge_image);
    }
    else if(filter_number == 11)
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeGSBMP(new_image, shuffle_image);
    }
    else
    {
        cout << "Enter new image name: ";
        cin >> new_image;
        strcat(new_image, ".bmp");
        writeGSBMP(new_image, image);
    }
}
//---------------------------------------------------------------------------------------------------------------------
void merge_images()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            merge_image[i][j] = (image[i][j] + image2[i][j]) / 2;
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
                image[i][j] *= 0.5;
        }
    }
    else
    {
        for(int i = 0; i < SIZE; ++i)
        {
            for(int j = 0; j < SIZE; ++j)
                image[i][j] = (image[i][j]+255) / 2;
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
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
            shrink_image[x][y] = image[i][j];
    }
    for(int m = 1; m < x; ++m)
    {
        for(int n = y; n < SIZE-1; ++n)
            shrink_image[m][n] = 255;
    }
    for(int m = x; m < SIZE-1; ++m)
    {
        for(int n = 1; n < SIZE-1; ++n)
            shrink_image[m][n] = 255;
    }

}
//----------------------------------------------------------------------------------------------------------------------
void blur_filter()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            if(i == 0 && j == 0)
                image[i][j] = (image[i][j]+image[i][j+1]+image[i][j+2]+image[i][j+3]+image[i][j+4]+image[i][j+5]+image[i+1][j]+
                               image[i+2][j]+image[i+3][j]+image[i+4][j]+image[i+5][j]) / 11;
            else if(i == SIZE-1 && j == 0)
                image[i][j] = (image[i][j]+image[i-1][j]+image[i-2][j]+image[i-3][j]+image[i-4][j]+image[i-5][j]+image[i][j+1]
                               +image[i][j+2]+image[i][j+3]+image[i][j+4]+image[i][j+5]) / 11;
            else if(j == 0 && (i > 5 && i < 250))
                image[i][j] = (image[i][j]+image[i-1][j] + image[i-2][j] + image[i-3][j]+image[i-4][j]+image[i-5][j]+
                               image[i+1][j]+image[i+2][j]+image[i+3][j]+image[i+4][j]+image[i+5][j]+image[i][j+1]+image[i][j+2]+
                               image[i][j+3]+image[i][j+4]+image[i][j+5]) / 16;
            else if(j == 0)
                image[i][j] = (image[i][j]+image[i+1][j]+image[i-1][j]+image[i][j+1]) / 4;
            else if(i == 0 && j == SIZE-1)
                image[i][j] = (image[i][j]+image[i][j-1] + image[i][j-2]+image[i][j-3]+image[i][j-4]+image[i][j-5]+image[i+1][j]+
                               image[i+2][j]+image[i+3][j]+image[i+4][j]+image[i+5][j]) / 11;
            else if(i == SIZE-1 && j == SIZE-1)
                image[i][j] = (image[i][j]+image[i][j-1] + image[i][j-2]+image[i][j-3]+image[i][j-4]+image[i][j-5]+
                               image[i-1][j]+image[i-2][j]+image[i-3][j]+image[i-4][j]+image[i-5][j]) / 11;
            else if(j == SIZE-1 && (i > 5 && i < 250))
                image[i][j] = (image[i][j]+image[i-1][j] + image[i-2][j] + image[i-3][j]+image[i-4][j]+image[i-5][j]+
                               image[i+1][j]+image[i+2][j]+image[i+3][j]+image[i+4][j]+image[i+5][j]+image[i][j-1]+image[i][j-2]+
                               image[i][j-3]+image[i][j-4]+image[i][j-5]) / 16;
            else if(j == SIZE-1)
                image[i][j] = (image[i][j]+image[i+1][j]+image[i-1][j]+image[i][j-1]) / 4;
            else if(i == 0 && (j > 5 && j < 250))
                image[i][j] = (image[i][j]+image[i+1][j] + image[i+2][j] + image[i+3][j]+image[i+4][j]+image[i+5][j]+image[i][j+1]+
                               image[i][j+2]+image[i][j+3]+image[i][j+4]+image[i][j+5]+image[i][j-1]+image[i][j-2]+
                               image[i][j-3]+image[i][j-4]+image[i][j-5]) / 16;
            else if(i == 0)
                image[i][j] = (image[i][j]+image[i+1][j]+image[i][j+1]+image[i][j-1]) / 4;
            else if(i == SIZE-1 && (j > 5 && j < 250))
                image[i][j] = (image[i][j]+image[i-1][j] + image[i-2][j] + image[i-3][j]+image[i-4][j]+image[i-5][j]+
                               image[i][j+1]+image[i][j+2]+image[i][j+3]+image[i][j+4]+image[i][j+5]+image[i][j-1]+image[i][j-2]+
                               image[i][j-3]+image[i][j-4]+image[i][j-5]) / 16;
            else if(i == SIZE-1)
                image[i][j] = (image[i][j]+image[i-1][j]+image[i][j+1]+image[i][j-1]) / 4;
            else if(i > 5 && j > 5)
                image[i][j] = (image[i][j]+image[i][j+1]+image[i][j+2]+image[i][j+3]+image[i][j+4]+image[i][j+5]+image[i][j-1]+
                               image[i][j-2]+image[i][j-3]+image[i][j-4]+image[i][j-5]+image[i+1][j]+image[i+2][j]+image[i+3][j]+image[i+4][j]+
                               image[i+5][j]+image[i-1][j]+image[i-2][j]+image[i-3][j]+image[i-4][j]+image[i-5][j])/21;
            else
                image[i][j] = (image[i][j]+image[i][j+1] + image[i][j-1] + image[i+1][j] + image[i-1][j]) / 5;
        }
    }

}
//---------------------------------------------------------------------------------------------------------------------
void invert_image()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            if(image[i][j] == 0)
                image[i][j] = 255;
            else if(image[i][j] == 255)
                image[i][j] = 0;
            else
                image[i][j] = 255 - image[i][j];
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
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
                enlarge_image[i][j] = image[x][y];
                enlarge_image[i+1][j] = image[x][y];
                enlarge_image[i][j+1] = image[x][y];
                enlarge_image[i+1][j+1] = image[x][y];
            }
        }
    }
    else if(choice == 2)
    {
        for(int i = 0, x = 0; i < SIZE; i += 2, x++)
        {
            for(int j = 0, y = 128; j < SIZE; j+=2, y++)
            {
                enlarge_image[i][j] = image[x][y];
                enlarge_image[i+1][j] = image[x][y];
                enlarge_image[i][j+1] = image[x][y];
                enlarge_image[i+1][j+1] = image[x][y];
            }
        }
    }
    else if(choice == 3)
    {
        for(int i = 0, x = 128; i < SIZE; i += 2, x++)
        {
            for(int j = 0, y = 0; j < SIZE; j+=2, y++)
            {
                enlarge_image[i][j] = image[x][y];
                enlarge_image[i+1][j] = image[x][y];
                enlarge_image[i][j+1] = image[x][y];
                enlarge_image[i+1][j+1] = image[x][y];
            }
        }
    }
    else if(choice == 4)
    {
        for(int i = 0, x = 128; i < SIZE; i += 2, x++)
        {
            for(int j = 0, y = 128; j < SIZE; j+=2, y++)
            {
                enlarge_image[i][j] = image[x][y];
                enlarge_image[i+1][j] = image[x][y];
                enlarge_image[i][j+1] = image[x][y];
                enlarge_image[i+1][j+1] = image[x][y];
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
void shuffle_filter()
{
    int q1, q2, q3, q4;
    cout << "Enter the order of quarters:";
    cin >> q1 >> q2 >> q3 >> q4;
    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < 128; j++)
            quarter1[i][j] = image[i][j];
    }
    for(int i = 0; i < 128; i++)
    {
        for(int j = 128; j < SIZE; j++)
            quarter2[i][j] = image[i][j];
    }
    for(int i = 128; i < SIZE; i++)
    {
        for(int j = 0; j < 128; j++)
            quarter3[i][j] = image[i][j];
    }
    for(int i = 128; i < SIZE; i++)
    {
        for(int j = 128; j < SIZE; j++)
            quarter4[i][j] = image[i][j];
    }
    if(q1 == 1)
    {
        for(int i = 0; i < 128; i++)
        {
            for(int j = 0; j < 128; j++)
                shuffle_image[i][j] = quarter1[i][j];
        }
    }
    else if(q1 == 2)
    {
        for(int i = 0, x = 0; i < 128; i++, x++)
        {
            for(int j = 128, y = 0; j < SIZE; j++, y++)
                shuffle_image[x][y] = quarter2[i][j];
        }
    }
    else if(q1 == 3)
    {
        for(int i = 128, x = 0; i < SIZE; i++, x++)
        {
            for(int j = 0, y = 0; j < 128; j++, y++)
                shuffle_image[x][y] = quarter3[i][j];
        }
    }
    else if(q1 == 4)
    {
        for(int i = 128, x = 0; i < SIZE; i++, x++)
        {
            for(int j = 128, y = 0; j < SIZE; j++, y++)
                shuffle_image[x][y] = quarter4[i][j];
        }
    }
    if(q2 == 1)
    {
        for(int i = 0, x = 0; i < 128; i++, x++)
        {
            for(int j = 0, y = 128; j < 128; j++, y++)
                shuffle_image[x][y] = quarter1[i][j];
        }
    }
    else if(q2 == 2)
    {
        for(int i = 0; i < 128; i++)
        {
            for(int j = 128; j < SIZE; j++)
                shuffle_image[i][j] = quarter2[i][j];
        }
    }
    else if(q2 == 3)
    {
        for(int i = 128, x = 0; i < SIZE; i++, x++)
        {
            for(int j = 0, y = 128; j < 128; j++, y++)
                shuffle_image[x][y] = quarter3[i][j];
        }
    }
    else if(q2 == 4)
    {
        for(int i = 128, x = 0; i < SIZE; i++, x++)
        {
            for(int j = 128, y = 128; j < SIZE; j++, y++)
                shuffle_image[x][y] = quarter4[i][j];
        }
    }
    if(q3 == 1)
    {
        for(int i = 0, x = 128; i < 128; i++, x++)
        {
            for(int j = 0, y = 0; j < 128; j++, y++)
                shuffle_image[x][y] = quarter1[i][j];
        }
    }
    else if(q3 == 2)
    {
        for(int i = 0, x = 128; i < 128; i++, x++)
        {
            for(int j = 128, y = 0; j < SIZE; j++, y++)
                shuffle_image[x][y] = quarter2[i][j];
        }
    }
    else if(q3 == 3)
    {
        for(int i = 128; i < SIZE; i++)
        {
            for(int j = 0; j < 128; j++)
                shuffle_image[i][j] = quarter3[i][j];
        }
    }
    else if(q3 == 4)
    {
        for(int i = 128, x = 128; i < SIZE; i++, x++)
        {
            for(int j = 128, y = 0; j < SIZE; j++, y++)
                shuffle_image[x][y] = quarter4[i][j];
        }
    }
    if(q4 == 1)
    {
        for(int i = 0, x = 128; i < 128; i++, x++)
        {
            for(int j = 0, y = 128; j < 128; j++, y++)
                shuffle_image[x][y] = quarter1[i][j];
        }
    }
    else if(q4 == 2)
    {
        for(int i = 0, x = 128; i < 128; i++, x++)
        {
            for(int j = 128, y = 128; j < SIZE; j++, y++)
                shuffle_image[x][y] = quarter2[i][j];
        }
    }
    else if(q4 == 3)
    {
        for(int i = 128, x = 128; i < SIZE; i++, x++)
        {
            for(int j = 0, y = 128; j < 128; j++, y++)
                shuffle_image[x][y] = quarter3[i][j];
        }
    }
    if(q4 == 4)
    {
        for(int i = 128; i < SIZE; i++)
        {
            for(int j = 128; j < SIZE; j++)
                shuffle_image[i][j] = quarter4[i][j];
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------
void rotate_90_degrees()
{
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = i; j < SIZE - i - 1; j++)
        {
            int temp = image[i][j];
            image[i][j] = image[SIZE - 1 - j][i];
            image[SIZE - 1 - j][i] = image[SIZE - 1 - i][SIZE - 1 - j];
            image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
            image[j][SIZE - 1 - i] = temp;
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
//-----------------------------------------------------------------------------------------------------------------
void black_whiteimage()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j< SIZE; j++)
        {
            /* simple code to change from
            normal image to black and white image.
            */
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
// filter to flip the image either vertical or horizontal
void flip_vertical()
{
    for(int i =0; i<SIZE/2; i++)
    {
        for(int j = 0; j<SIZE; j++)
        {
            swap(image[i][j],image[256-i-1][j]);
        }
    }

}
void flip_horizontal()
{
    for(int i =0; i<(SIZE); i++)
    {
        for(int j = 0; j<(SIZE/2); j++)
        {
            swap(image[i][j],image[i][256-j-1]);
        }
    }

}
void flip_image()
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
//---------------------------------------------------------------------------------------------------------------------
void  detect_edges()
{
    black_whiteimage();
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (image[i+1][j]==image[i-1][j]&&image[i][j+1]==image[i][j-1]&&image[i+1][j]==image[i][j-1])
                image2[i][j]=255;
            else
                image2[i][j]=0;
        }
    }
    // for loop to save th image after has  been changed in the second array
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            image[i][j]=image2[i][j];
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
// filter to mirror the image
void mirror_right()
{
    int n = 255;
    for(int row=0;row<SIZE;row++)
    {
        for(int col=255;col>128;col--)
        {
            image[row][col-n] = image[row][col] ;
            n = n - 2;
        }
        n = 255;
    }
}
void mirror_left()
{
    int n = 255;
    for(int row=0;row<SIZE;row++)
    {
        for(int col=255;col>128;col--)
        {
            image[row][col] = image[row][col-n] ;
            n = n - 2;
        }
        n = 255;
    }
}
void mirror_up()
{
    int n=255;
    for(int col=0;col<SIZE;col++)
    {
        for(int row=255;row>128;row--)
        {
            image[row][col] = image[row-n][col] ;
            n = n - 2;
        }
        n = 255;
    }
}
void mirror_down()
{
    int n = 255;
    for(int col=0;col<SIZE;col++)
    {
        for(int row=255;row>128;row--)
        {
            image[row-n][col] = image[row][col]  ;
            n = n - 2;
        }
        n = 255;
    }
}
void mirror_image(){
    int choice;
    cout<<"please enter the number of type of mirroring\n";
    cout << "1 - mirror left\n";
    cout << "2 - mirror right\n";
    cout << "3 - mirror up\n";
    cout << "4 - mirror down\n";
    cin >> choice;
    if(choice == 1)
        mirror_left();
    else if(choice == 2)
        mirror_right();
    else if(choice == 3)
        mirror_up();
    else if(choice == 4)
        mirror_down();
}
//-----------------------------------------------------------------------------------------------
int main()
{
    display_filters();
    load_image();
    if(filter_number == 1)
        black_whiteimage();
    else if(filter_number == 2)
        invert_image();
    else if(filter_number == 3)
        merge_images();
    else if(filter_number == 4)
        flip_image();
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
