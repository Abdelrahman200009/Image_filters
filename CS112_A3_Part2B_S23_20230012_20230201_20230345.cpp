/*

FCAI – Structured Programming [CS112] – 2024 - Assignment x
Program Name:			CS112_A3_part2B_S23_20230201_20230012_20230345.cpp
Program Description:    ………
Last Modification Date:	xx/xx/xxxx
Author1 and ID and Group:	Abdelrahman Ahmed Abdelbaky Mahmoued && 20230201 && S23
Author2 and ID and Group:	Ahmed Tamed Shawky && 20230012 && S23
Author3 and ID and Group:	 Mohammed Essam Mahmoud && 20230345 && S23
Teaching Assistant:
Who did what:
Abdelrahman Ahmed : Black and white filter && Flip && rotate && Darken and lighten filter && crop images && frame && resize && blur
Ahmed Tamer : grey scale filter && merge images filter && detect images && the land of wano && luffy look purple && skew image && adding two picture (extra)
Mohammed essam : Invert image

Ahmed and Abdelrahman did the menu

 GitHub link: https://github.com/Abdelrahman200009/Image_filters/tree/main
 */

#include "Image_Class.h"
#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
#define nl '\n'
using namespace std;

// Function Prototypes

// General Functions
void menu();
void promptSaveImage(Image& image);
bool is_number(string s);

// Filters
void greyScale(Image& user_img);
void Black_and_white(Image& user_img);
void Invert_Image(Image& user_img);
void Merge_Images(Image& user_img);
void Flip(Image &image);
void rotate(Image &image);
void Darken_lighten(Image &image);
void crop_images(Image &image);
void frame(Image &user_img);
void detect_edges(Image& user_img);
void resize(Image &image);
void blur(Image &image);
void the_land_of_wano(Image& user_img);
void luffy_look_purple(Image& user_img);
void skew_image(Image& user_img);
void adding_two_picture_together(Image& user_img);

int main() {
    menu();
}

// General Functions
void menu() {
    while (true) {
        string imagePath;
        Image userImage;

        cout << nl << "Welcome to the image editing program" << nl;
        cout << "Please enter the image file path (supported formats: jpg, jpeg, png, bmp, tga):" << nl;
        getline(cin, imagePath);

        // Load the image
        try {
            userImage.loadNewImage(imagePath);
        } catch (const invalid_argument& e) {
            cout << "Error loading image: " << e.what() << nl;
            continue;  // Continue the loop to ask for another image
        }

        while (true) {
            cout << nl << "Choose a filter to apply to the image:" << nl;
            cout << "1. Grayscale" << nl;
            cout << "2. Black and White" << nl;
            cout << "3. Invert Image" << nl;
            cout << "4. Merge Images" << nl;
            cout << "5. Flip Image" << nl;
            cout << "6. Rotate Image" << nl;
            cout << "7. Adjust Brightness" << nl;
            cout << "8. Crop Image" << nl;
            cout << "9. Add Frame" << nl;
            cout << "10. Detect Edges" << nl;
            cout << "11. Resize Image" << nl;
            cout << "12. Blur Image" << nl;
            cout << "13. Land of Wano" << nl;
            cout << "14. Luffy Look Purple" << nl;
            cout << "15. Skew Image" << nl;
            cout << "16. Add two Images Together (Extra)" << nl;
            cout << "0. Exit" << nl;
            cout << "Enter your choice:" << nl;

            string input;
            cin >> input;

            // Validate input
            if (!is_number(input)) {
                cout << "Invalid input. Please enter a number." << nl;
                continue;
            }

            int choice = stoi(input);

            // Handle choices
            switch (choice) {
                case 0:  // Exit
                    cout << "Exiting the program." << nl;
                    return;
                case 1:
                    greyScale(userImage);
                    break;
                case 2:
                    Black_and_white(userImage);
                    break;
                case 3:
                    Invert_Image(userImage);
                    break;
                case 4:
                    Merge_Images(userImage);
                    break;
                case 5:
                    Flip(userImage);
                    break;
                case 6:
                    rotate(userImage);
                    break;
                case 7:
                    Darken_lighten(userImage);
                    break;
                case 8:
                    crop_images(userImage);
                    break;
                case 9:
                    frame(userImage);
                    break;
                case 10:
                    detect_edges(userImage);
                    break;
                case 11:
                    resize(userImage);
                    break;
                case 12:
                    blur(userImage);
                    break;
                case 13:
                    the_land_of_wano(userImage);
                    break;
                case 14:
                    luffy_look_purple(userImage);
                    break;
                case 15:
                    skew_image(userImage);
                    break;
                case 16:
                    adding_two_picture_together(userImage);
                    break;
                default:
                    cout << "Invalid choice. Please try again." << nl;
                    break;
            }
        }
    }
}

bool is_number(string s){
    regex number("\\d+");
    return regex_match(s, number);
}

void promptSaveImage(Image& image) {
    cout << "Do you want to save the edited image? (yes/no):" << nl;
    string response;
    cin >> response;

    // Convert response to lowercase for easier comparison
    for (char &character : response) {
        character = tolower(character);
    }

    if (response == "yes") {
        cout << "Enter the filename to save the image (e.g., output.png):" << nl;
        string filename;
        cin >> filename;

        try {
            image.saveImage(filename); // Assuming the Image class has a save function
            cout << "Image saved successfully as " << filename << endl;
        } catch (const invalid_argument& e) {
            cout << "Error saving image:" << e.what() << nl;
        }
    } else {
        cout << "Image not saved." << endl;
    }
}

// Grayscale
void greyScale(Image& user_img)
{
    for (int i = 0; i < user_img.width; ++i)
    {
        for (int j = 0; j < user_img.height; ++j)
        {
            unsigned average = 0;
            for (int k = 0; k < 3; ++k)
            {
                average += user_img(i, j, k);
            }
            user_img.setPixel(i, j, 0, average / 3);
            user_img.setPixel(i, j, 1, average / 3);
            user_img.setPixel(i, j, 2, average / 3);
        }
    }
    promptSaveImage(user_img);
    cout << "Applied grayscale filter." << nl;
}

// B&W
void Black_and_white(Image& user_img)
{
    // Convert image to grey scale
    for (int i = 0; i < user_img.width; ++i)
    {
        for (int j = 0; j < user_img.height; j++)
        {
            unsigned int grey = 0;

            for (int k = 0; k < 3; k++)
            {

                grey += user_img(i, j, k);
            }
            grey /= 3;
            // change every pixel to gray scale
            for (int k = 0; k < 3; ++k)
            {
                user_img(i, j, k) = grey;
            }
        }
    }
    // convert image to black and white
    for (int i = 0; i < user_img.width; ++i)
    {
        for (int j = 0; j < user_img.height; j++)
        {
            unsigned int black = 0;

            for (int k = 0; k < 3; k++)
            {
                black += user_img(i, j, k);
            }
            black /= 3;
            // Threshold for pixels conversion
            black = (black >= 128) ? 255 : 0;

            for (int k = 0; k < 3; k++)
            {
                user_img(i, j, k) = black;
            }
        }
    }
    promptSaveImage(user_img);
    cout << "Applied black and white filter." << nl;
}

// Invert
void Invert_Image(Image& user_img)
{
    // Iterate over each pixel in the image
    for (int i = 0; i < user_img.width; ++i)
    {
        for (int j = 0; j < user_img.height; ++j)
        {
            int X;
            // Iterate over each color channel of the pixel
            for (int k = 0; k < user_img.channels; ++k)
            {
                // Invert the color value by subtracting it from 255
                X = 255 - user_img(i, j, k);
                // Assign the inverted color value back to the image
                user_img(i, j, k) = X;
            }
        }
    }
    promptSaveImage(user_img);
    cout << "Inverted image colors." << nl;
}

// Merge
void Merge_Images(Image& user_img)
{
    Image user_img2;
    while (true)
    {
        string user_img_s2;
        Image newimg;
        cout << "please upload the second image you want to merge with\n";
        cin.ignore();
        getline(cin, user_img_s2);
        try
        {
            user_img2.loadNewImage(user_img_s2);
            break;
        }
        catch (const invalid_argument& e)
        {
            cout << "Error loading image: " << e.what() << nl;
            continue;
        }
    }
    int choice_dimension;
    int w1 = user_img.width;
    int h1 = user_img.height;
    int w2 = user_img2.width;
    int h2 = user_img2.height;
    cout << "do you want the new merged image dimension as\n";
    cout << "[1] dimension of the first image "
         << "width = " << user_img.width << " height = " << user_img.height;
    cout << "\n[2] dimension of the second image "
         << "width = " << user_img2.width << " height = " << user_img2.height << nl;
    cin >> choice_dimension;
    while (true)
    {
        if (choice_dimension == 1)
        {
            Image newimg(user_img.width, user_img.height);
            for (int i = 0; i < user_img.width; ++i)
            {
                for (int j = 0; j < user_img.height; ++j)
                {
                    int x = i * w1 / w2; // Map i from img2 to img1
                    int y = j * h1 / h2; // Map j from img2 to img1

                    // Average pixel values from both images
                    unsigned ave = (user_img(x, y, 0) + user_img2(i, j, 0)) / 2;
                    unsigned ave1 = (user_img(x, y, 1) + user_img2(i, j, 1)) / 2;
                    unsigned ave2 = (user_img(x, y, 2) + user_img2(i, j, 2)) / 2;

                    // Set pixel values in the new image
                    newimg.setPixel(i, j, 0, ave);
                    newimg.setPixel(i, j, 1, ave1);
                    newimg.setPixel(i, j, 2, ave2);
                }
            }
            promptSaveImage(newimg);
            cout << "Merged images." << nl;
            break;
        }
        else if (choice_dimension == 2)
        {
            Image newimg(user_img2.width, user_img2.height);
            for (int i = 0; i < user_img2.width; ++i)
            {
                for (int j = 0; j < user_img2.height; ++j)
                {
                    int x = i * w1 / w2; // Map i from img1 to img2
                    int y = j * h1 / h2; // Map j from img1 to img2

                    // Average pixel values from both images
                    unsigned ave = (user_img(x, y, 0) + user_img2(i, j, 0)) / 2;
                    unsigned ave1 = (user_img(x, y, 1) + user_img2(i, j, 1)) / 2;
                    unsigned ave2 = (user_img(x, y, 2) + user_img2(i, j, 2)) / 2;

                    // Set pixel values in the new image
                    newimg.setPixel(i, j, 0, ave);
                    newimg.setPixel(i, j, 1, ave1);
                    newimg.setPixel(i, j, 2, ave2);
                }
            }
            promptSaveImage(newimg);
            cout << "Merged images." << nl;
            break;
        }
        else
        {
            cout << "invalid choice please enter 1 or 2 only\n";
        }
    }
}

// Flip
void Flip(Image &image )   {

    cout << "1. Flip Horizontally" << nl
         << "2. Flip Vertically"   << nl;

    string choice;
    cin >> choice;

    //Declaring the image dimensions
    Image flipped_img(image.width,image.height);

    if(choice == "1"){
        //flip image horizontally
        for(int i = 0; i < image.width; i++){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //fill the flipped_img pixels
                    flipped_img(i,j,k) = image(image.width - 1 - i,j,k);
                }
            }
        }
        promptSaveImage(flipped_img);
        cout << "Flipped image." << nl;
    }

    else if (choice == "2"){
        //flip image vertically
        for(int i = 0; i < image.width;i++){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //fill the flipped_img pixels
                    flipped_img(i,j,k) = image(i,image.height - 1 - j ,k);
                }
            }
        }
        promptSaveImage(flipped_img);
        cout << "Flipped image." << nl;
    }
    else{
        cout << "Invalid choice please try again: ";
        return;
    }

}

// Rotate
void rotate(Image &image){

    cout << "Choose 1 to rotate image 90 degrees:"  << nl
         << "Choose 2 to rotate image 180 degrees:" << nl
         << "Choose 3 to rotate image 270 degrees:" << nl;
    string choice;
    cin >> choice;

    //rotate image by 270 degrees
    if(choice == "3"){
        //creating blank image with the new dimensions
        Image result(image.height,image.width);

        for(int i = 0; i < image.width; ++i){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //Filling the blank image with pixels
                    result(j,image.width - i - 1,k) = image( i, j,k);
                }
            }
        }
        promptSaveImage(result);
        cout << "Rotated image." << nl;
    }
        //rotate image by 90 degrees
    else if(choice == "1"){
        //creating a blank image with new dimensions
        Image result(image.height,image.width);

        for(int i = 0; i < image.width; ++i){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //filling the blank image with pixels
                    result(image.height - j - 1,i,k) = image( i, j,k);
                }
            }
        }
        promptSaveImage(result);
        cout << "Rotated image." << nl;
    }
        //rotate image by 180 degrees
    else if(choice == "2"){
        //creating blank image to avoid segmentation error
        Image result(image.width,image.height);

        for(int i = 0; i < image.width; ++i){
            for(int j = 0; j < image.height; j++){
                for(int k = 0; k < 3; k++){
                    //filling each pixel
                    result(i,j,k) = image(image.width - 1 - i, image.height - 1 - j,k);
                }
            }
        }
        promptSaveImage(result);
        cout << "Rotated image." << nl;
    }
    else cout << "Invalid choice Please try again :";
}

// Darken and Lighten
void Darken_lighten(Image &image){
    int beta;
    cout << "Enter the value of darkening or brightening" << nl;
    cin >> beta;

    if (beta > 255) beta = 255;
    else if (beta < -255) beta = -255;

    for(int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {

                int new_value = image(i,j,k) + beta;
                //Ensuring the value of doesn't get out of the range of the picture
                new_value = max(0,min(255,new_value));
                image(i,j,k) = new_value;
            }
        }
    }
    promptSaveImage(image);
    cout << "Adjusted brightness." << nl;
}

// Crop
void crop_images(Image &image){
    int x, y, width, height;
    cout << "enter the value of starting pixels and the dimensions of the new image" << nl;
    cin >> x >> y >> width >> height;

    if (width > image.width - x || height > image.height - y){
        cout << "Cropping can't go out of borders" << nl;
        return;
    }

    //Initializing the dimensions of the cropped image
    Image cropped(width , height);
    //iterating of the pixels of the copped image
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < 3; k++){
                //adding the value of x (the starting pixel to from the old photo to i)
                cropped(i,j,k) = image(x + i, y + j,k);
            }
        }
    }
    promptSaveImage(cropped);
    cout << "Cropped image." << nl;
}

// Frame
void frame(Image& user_img) {
    string user_img_s;
    cout << "Choose the color of the frame: " << nl
         << "available colors (red,blue,green,cyan,magenta,yellow,light blue,orange)" << nl;
    cin >> user_img_s;
    int width = 25;
    int height = 25;

    // Initialize color values based on the input string
    int frame_r, frame_g, frame_b;

    // Set frame color based on user input
    if (user_img_s == "red") {
        frame_r = 255;
        frame_g = 0;
        frame_b = 0;
    } else if (user_img_s == "blue") {
        frame_r = 0;
        frame_g = 0;
        frame_b = 255;
    } else if (user_img_s == "green") {
        frame_r = 0;
        frame_g = 255;
        frame_b = 0;
    } else if (user_img_s == "cyan") {
        frame_r = 0;
        frame_g = 255;
        frame_b = 255;
    } else if (user_img_s == "magenta") {
        frame_r = 255;
        frame_g = 0;
        frame_b = 255;
    } else if (user_img_s == "yellow") {
        frame_r = 255;
        frame_g = 255;
        frame_b = 0;
    } else if (user_img_s == "light blue") {
        frame_r = 173;
        frame_g = 216;
        frame_b = 230;
    } else if (user_img_s == "orange") {
        frame_r = 255;
        frame_g = 165;
        frame_b = 0;
    } else {
        // Default to black frame if color is not recognized
        frame_r = 0;
        frame_g = 0;
        frame_b = 0;
    }

    // Create a new image with a frame around the user image
    Image image_new(user_img.width + 2 * width, user_img.height + 2 * height);

    // Copy the user image into the new image with an offset
    for (int i = 0; i < user_img.width; i++) {
        for (int j = 0; j < user_img.height; j++) {
            for (int k = 0; k < 3; k++) {
                image_new(i + width, j + height, k) = user_img(i, j, k);
            }
        }
    }

    // Fill top and bottom parts of the frame with the specified color
    for (int i = 0; i < image_new.width; ++i) {
        for (int j = 0; j < height; ++j) {
            image_new(i, j, 0) = frame_r;
            image_new(i, j, 1) = frame_g;
            image_new(i, j, 2) = frame_b;

            image_new(i, image_new.height - 1 - j, 0) = frame_r;
            image_new(i, image_new.height - 1 - j, 1) = frame_g;
            image_new(i, image_new.height - 1 - j, 2) = frame_b;
        }
    }

    // Fill left and right parts of the frame with the specified color
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < image_new.height; ++j) {
            image_new(i, j, 0) = frame_r;
            image_new(i, j, 1) = frame_g;
            image_new(i, j, 2) = frame_b;

            image_new(image_new.width - 1 - i, j, 0) = frame_r;
            image_new(image_new.width - 1 - i, j, 1) = frame_g;
            image_new(image_new.width - 1 - i, j, 2) = frame_b;
        }
    }

    promptSaveImage(image_new);
    cout << "Added frame to image." << nl;
}

// Detect Image Edges
void detect_edges(Image& user_img){
    Image img2 (user_img.width,user_img.height);
    for (int i = 0; i < user_img.width - 2; i++)
    {

        for (int j = 0; j < user_img.height - 2; j++)
        {
            img2.setPixel(i,j,0,255);
            img2.setPixel(i,j,1,255);
            img2.setPixel(i,j,2,255);


        }
    }

    for (int i = 0; i < user_img.width - 2; i++)
    {

        for (int j = 0; j < user_img.height - 2; j++)
        {
            unsigned completePix = user_img(i, j+1, 0);
            unsigned completePix2 = user_img(i, j, 0);
            unsigned pix1 = user_img(i, j, 1);
            unsigned pix2 = user_img(i, j, 2);
            if (completePix < completePix2 && completePix2 > 125 && completePix < 125)
            {
                img2.setPixel(i,j+1,0,0);
                img2.setPixel(i,j+1,1,0);
                img2.setPixel(i,j+1,2,0);
            }
            else if (completePix2 < completePix && completePix > 125 && completePix2 < 125)
            {
                img2.setPixel(i,j,0,0);
                img2.setPixel(i,j,1,0);
                img2.setPixel(i,j,2,0);
            }
        }
    }
    promptSaveImage(img2);
    cout << "Detected edges." << nl;

}

// Resize
void resize(Image &image){
    int width, height;
    cout << "Enter the width and height of the new image" << nl;
    cin >> width >> height;
    //Making new image with the new dimensions
    Image result(width,height);

    float r1 = (1.0 * image.width) / width; //Converting width to float the dividing to get a ratio
    float r2 = (1.0 * image.height) / height; //Converting height to float
    //Iterating over the new dimensions of the image
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < 3; k++){
                //Calculating the value of each pixel of the new image
                int new_width = round(i*r1);
                int new_height = round(j*r2);
                //equating the new image with the old image index new width and height
                result(i,j,k) = image(new_width,new_height,k);
            }
        }
    }
    promptSaveImage(result);
    cout << "Resized image." << nl;
}

// Blur
void blur(Image &image) {
    int blur;
    cout << "Enter the intensity of blurring (Must be odd)" << nl;
    cin >> blur;
    Image result(image.width, image.height);
    // Check if blur is odd
    if (blur % 2 == 0) {
        cout << "Blur size must be odd. Incrementing blur by 1." << nl;
        blur += 1;
    } else if (blur < 0){
        cout << "Blur can't be negative. Taking absolute value" << nl;
        blur = abs(blur);
    }

    // Adjust kernel size based on blur
    int kernel_size = blur;

    // Middle index of the kernel
    int middle = kernel_size / 2;

    // Loop through the image pixels
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            vector<float> acc = {0, 0, 0};
            // Looping from left of the pixel to its right
            for (int a = -middle; a <= middle; ++a) {
                for (int b = -middle; b <= middle; ++b) {
                    int in = i + a; //Index of the pixel
                    int jn = j + b; //Index of the pixel
                    //making sure not to exceed the image bounds and leaving the edges
                    if (in >= 0 && in < image.width && jn >= 0 && jn < image.height) {
                        // Apply kernel to the image pixel
                        for (int c = 0; c < 3; ++c) {
                            acc[c] += image(in, jn, c);
                        }
                    }
                }
            }
            // Update the result image
            for (int c = 0; c < 3; ++c) {
                result(i, j, c) = acc[c] / (kernel_size * kernel_size);
            }
        }
    }
    promptSaveImage(result);
    cout << "Blurred image." << nl;
}

// Land of Wano
void the_land_of_wano(Image& user_img){
    Image newimg(user_img.width, user_img.height);


    for (int i = 0; i < user_img.width; ++i) {
        for (int j = 0; j < user_img.height; ++j) {

            // Average pixel values from both images
            unsigned ave = (user_img(i, j, 0)+219)/2;
            unsigned ave1 = (user_img(i, j, 1)+219)/2;
            unsigned ave2 = (user_img(i, j, 2) +93) / 2;

            // Set pixel values in the new image
            newimg.setPixel(i, j, 0, ave);
            newimg.setPixel(i, j, 1, ave1);
            newimg.setPixel(i, j, 2, ave2);
        }
    }
    promptSaveImage(newimg);
    cout << "Applied land of Wano filter." << nl;
}

// Purple
void luffy_look_purple(Image& user_img){
    Image newimg(user_img.width, user_img.height);


    for (int i = 0; i < user_img.width; ++i) {
        for (int j = 0; j < user_img.height; ++j) {

            // Average pixel values from both images
            unsigned ave = (user_img(i, j, 0));
            unsigned ave1 = (user_img(i, j, 1));
            unsigned ave2 = (user_img(i, j, 2) );

            // Set pixel values in the new image
            newimg.setPixel(i, j, 0, ave);
            newimg.setPixel(i, j, 1, ave1*0.45);
            newimg.setPixel(i, j, 2, ave2);
        }
    }
    promptSaveImage(newimg);
    cout << "Applied Luffy look (purple) effect." << nl;
}

// Skew
void skew_image(Image& user_img){

    Image newimg(user_img.width, user_img.height);
    for (int i = 0; i < newimg.width; ++i) {
        for (int j = 0; j < newimg.height; ++j) {
            // Average pixel values from both images
            unsigned ave = 255;
            unsigned ave1 = 255;
            unsigned ave2 = 255 ;

            // Set pixel values in the new image
            newimg.setPixel(i, j, 0, ave);
            newimg.setPixel(i,j, 1, ave1);
            newimg.setPixel(i, j, 2, ave2);
        }
    }
    for (int j = 0; j < newimg.height; ++j) {
        for (int i = 0; i < newimg.width; ++i) {
            // Calculate original coordinates
            int originalX = i - -0.8 * (j - user_img.width / 2);
            int originalY = j;

            // Check if original coordinates are within bounds of img1
            if (originalX >= 0 && originalX < user_img.width && originalY >= 0 && originalY < user_img.height) {
                // Get pixel values from img1
                unsigned pix = user_img.getPixel(originalX, originalY, 0);
                unsigned pix1 = user_img.getPixel(originalX, originalY, 1);
                unsigned pix2 = user_img.getPixel(originalX, originalY, 2);

                // Set pixel values in the new image
                newimg.setPixel(i, j, 0, pix);
                newimg.setPixel(i, j, 1, pix1);
                newimg.setPixel(i, j, 2, pix2);
            }
        }
    }
    promptSaveImage(newimg);
    cout << "Skewed image." << nl;
}

// Add Two Images
void adding_two_picture_together(Image& user_img){
    Image user_img2;
    string user_img_s2;
    while (true)
    {
        cout << "please upload the second image you want to merge with\n";
        cin.clear();
        cin.ignore();
        getline(cin, user_img_s2);
        try
        {
            user_img2.loadNewImage(user_img_s2);
            break;
        }
        catch (const invalid_argument& e)
        {
            cout << "Error loading image: " << e.what() << nl;
            continue;
        }
    }
    Image newimg(user_img2.width, user_img2.height);
    int w1 = user_img.width;
    int h1 = user_img.height;
    int w2 = user_img2.width;
    int h2 = user_img2.height;

    for (int i = 0; i < newimg.width; ++i) {
        for (int j = 0; j < newimg.height; ++j) {
            int x = i * w1 / w2; // Map i from img1 to img2
            int y = j * h1 / h2; // Map j from img1 to img2
            newimg(i,j,0) = user_img(x,y,0);
            newimg(i,j,1) = user_img(x,y,1);
            newimg(i,j,2) = user_img(x,y,2);
        }
    }

    Image newimg_horizontal(newimg.width + user_img2.width, max(newimg.height, user_img2.height));
    for (int i = 0; i < newimg_horizontal.width; ++i)
    {
        for (int j = 0; j < newimg_horizontal.height; ++j)
        {
            if (i >= newimg.width - 1)
            {
                newimg_horizontal.setPixel(i, j, 0, user_img2(i - newimg.width + 1, j, 0));
                newimg_horizontal.setPixel(i, j, 1, user_img2(i - newimg.width + 1, j, 1));
                newimg_horizontal.setPixel(i, j, 2, user_img2(i - newimg.width + 1, j, 2));
            }
            else
            {
                newimg_horizontal.setPixel(i, j, 0, newimg(i, j, 0));
                newimg_horizontal.setPixel(i, j, 1, newimg(i, j, 1));
                newimg_horizontal.setPixel(i, j, 2, newimg(i, j, 2));
            }
        }
    }
    promptSaveImage(newimg_horizontal);
    cout << "Added two images together." << nl;
}