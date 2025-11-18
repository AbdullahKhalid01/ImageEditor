#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct Image {
    string type;
    int width, height, maxVal;
    int **pixel;
};

void allocate(Image &img) {
    img.pixel = new int*[img.height];
    for (int i = 0; i < img.height; i++)
        img.pixel[i] = new int[img.width];
}

void freeMemory(Image &img) {
    for (int i = 0; i < img.height; i++)
        delete[] img.pixel[i];
    delete[] img.pixel;
}

bool loadImage(string name, Image &img, bool &isBinary) {
    ifstream file(name, ios::binary);
    if (!file.is_open()) return false;

    getline(file, img.type);        // P2 or P5
    isBinary = (img.type == "P5");

    string comment;
    getline(file, comment);         // skip comment line

    file >> img.width >> img.height >> img.maxVal;
    file.ignore();

    allocate(img);

    if (isBinary) {
        for (int i = 0; i < img.height; i++)
            file.read(reinterpret_cast<char*>(img.pixel[i]), img.width);
    } else {
        for (int i = 0; i < img.height; i++)
            for (int j = 0; j < img.width; j++)
                file >> img.pixel[i][j];
    }

    file.close();
    return true;
}

void saveImage(string name, Image &img, bool isBinary) {
    ofstream out;
    if (isBinary)
        out.open(name, ios::binary);
    else
        out.open(name);

    out << img.type << "\n";
    out << img.width << " " << img.height << "\n";
    out << img.maxVal << "\n";

    if (isBinary) {
        for (int i = 0; i < img.height; i++)
            out.write(reinterpret_cast<char*>(img.pixel[i]), img.width);
    } else {
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++)
                out << img.pixel[i][j] << " ";
            out << "\n";
        }
    }

    out.close();
}

void flipRight(Image &img) {
    for (int i = 0; i < img.height; i++)
        for (int j = 0; j < img.width / 2; j++)
            swap(img.pixel[i][j], img.pixel[i][img.width - 1 - j]);
}

void flipDown(Image &img) {
    for (int i = 0; i < img.height / 2; i++)
        for (int j = 0; j < img.width; j++)
            swap(img.pixel[i][j], img.pixel[img.height - 1 - i][j]);
}

Image rotate90(Image &img) {
    Image r;
    r.type = img.type;
    r.width = img.height;
    r.height = img.width;
    r.maxVal = img.maxVal;
    allocate(r);
    for (int i = 0; i < img.height; i++)
        for (int j = 0; j < img.width; j++)
            r.pixel[j][img.height - 1 - i] = img.pixel[i][j];
    return r;
}

Image rotate180(Image &img) {
    Image r;
    r.type = img.type;
    r.width = img.width;
    r.height = img.height;
    r.maxVal = img.maxVal;
    allocate(r);
    for (int i = 0; i < img.height; i++)
        for (int j = 0; j < img.width; j++)
            r.pixel[img.height - 1 - i][img.width - 1 - j] = img.pixel[i][j];
    return r;
}

Image rotate270(Image &img) {
    Image r;
    r.type = img.type;
    r.width = img.height;
    r.height = img.width;
    r.maxVal = img.maxVal;
    allocate(r);
    for (int i = 0; i < img.height; i++)
        for (int j = 0; j < img.width; j++)
            r.pixel[img.width - 1 - j][i] = img.pixel[i][j];
    return r;
}

int main() {
    while (true) {
        cout << "1. Flip Right\n2. Flip Down\n3. Rotate 90\n4. Rotate 180\n5. Rotate 270\n6. Exit\nChoice: ";
        int ch; cin >> ch;
        if (ch == 6) break;

        string filename; 
        cout << "Enter filename: "; cin >> filename;

        Image img;
        bool isBinary;
        if (!loadImage(filename, img, isBinary)) {
            cout << "File not found.\n";
            continue;
        }

        if (ch == 1) flipRight(img);
        else if (ch == 2) flipDown(img);
        else if (ch == 3) { Image r = rotate90(img); freeMemory(img); img = r; }
        else if (ch == 4) { Image r = rotate180(img); freeMemory(img); img = r; }
        else if (ch == 5) { Image r = rotate270(img); freeMemory(img); img = r; }

        string out;
        cout << "New file name: "; cin >> out;

        saveImage(out, img, isBinary);
        freeMemory(img);

        cout << "Saved.\n";
        Sleep(700);
        system("cls");
    }

    cout << "Thanks!\n";
    return 0;
}
