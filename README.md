PGM Image Editor Documentation

Project Title: PGM Image Editor

Objective: 
To create a C++ program that can read, manipulate, and save PGM (Portable Gray Map) images in both ASCII (P2) and Binary (P5) formats. The program supports image operations like flipping and rotation.

Features: 
1. Auto-detects the PGM format (ASCII or Binary) based on the magic number.
2. Supports dynamic memory allocation for images.
3. Operations supported:
   - Flip Right
   - Flip Down
   - Rotate 90 degrees
   - Rotate 180 degrees
   - Rotate 270 degrees
5. Saves the modified image in the same format as the input.
6. Simple, clean interface for user interaction.

Program Structure:
1.	Struct: Image
    - Contains type (P2 or P5), width, height, maxVal, and dynamically allocated 2D array pixel.
2.	Memory Management Functions:
    - allocate(Image &img): Allocates memory for the 2D pixel array.
    - freeMemory(Image &img): Frees allocated memory for the image.
3.	File Handling Functions:
    - loadImage(string name, Image &img, bool &isBinary): Reads the PGM file, detects format, and loads the pixels.
    - saveImage(string name, Image &img, bool isBinary): Saves the image in either ASCII or Binary format.
4.	Image Manipulation Functions:
    - flipRight(Image &img): Flips the image horizontally.
    - flipDown(Image &img): Flips the image vertically.
    - rotate90(Image &img): Rotates the image 90 degrees clockwise.
    - rotate180(Image &img): Rotates the image 180 degrees.
    - rotate270(Image &img): Rotates the image 270 degrees clockwise.
5.	main() function:
    - Displays menu for user to select operation.
    - Loads the image and detects format automatically.
    - Performs the selected operation.
    - Saves the modified image.
    - Repeats until user chooses to exit.

Usage Instructions: 
1. Compile the program using a C++ compiler.
2. Run the executable.
3. Select the desired operation from the menu.
4. Enter the PGM file name.
5. Enter the output file name.
6. The program will save the modified image in the same format as input.

Notes: 
- Only PGM images are supported.
- Binary and ASCII formats are both handled automatically.
- Dynamic memory ensures large images can be processed efficiently.
- Ensure the input PGM file has proper header format (magic number, width, height, max value).

Authors:
- Aila Kanwal 
- Abdullah Khalid 

Course: BSCS, PUCIT Lahore

