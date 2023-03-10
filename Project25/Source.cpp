#include<stdio.h>
#include<iostream>
#include<locale.h>
#include<stdlib.h>
#include <math.h>
#include<stdbool.h>
#include <string>
#include <typeinfo>
#include <limits>

using namespace std;

template <class T>
class Image {
private:
    T** matrix;
    int _maxX, _maxY;

public:
    Image(int x, int y);

    Image(const Image& img);

    ~Image();

    Image<T> operator+(const Image<T>& img);
    
    Image<T> operator*(const Image<T>& img);

    Image<T> operator+(T value);

    Image<T> operator*(T value);

   Image<T> operator!();

    void set(int x, int y, T value);

    T get(int x, int y);

    friend ostream& operator<<(ostream& out, const  Image& img) {
        for (int i = 0; i < img._maxX; i++) {
            for (int j = 0; j < img._maxY; j++) {
                out << img(i, j) << " ";
            }
            out << endl;
        }
        return out;
    }

    double fill_ratio();

   friend Image<T> cret_circle(Image<T>& img, int x, int y, int r, T value) {
       Image<T> tmp(img._maxX, img._maxY);
       for (int i = 0; i < img._maxX; i++) {
           for (int j = 0; j < img._maxY; j++) {

               if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r)
                   tmp(i, j) = value;
           }
       }
        return tmp;
   }

   Image<T>& operator=(const Image<T>& img);

    void change();

    T operator()(int x, int y) const;

    T& operator()(int x, int y);
};

template<class T>
Image<T>::Image(int x, int y) {
    _maxX = x;
    _maxY = y;

    matrix = new T * [_maxX];
    for (int i = 0; i < _maxX; i++)
        matrix[i] = new T[_maxY];

    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            matrix[i][j] = 0;
        }
    }
}

template<>
Image<char>::Image(int x, int y) {
    _maxX = x;
    _maxY = y;

    matrix = new char* [_maxX];
    for (int i = 0; i < _maxX; i++)
        matrix[i] = new char[_maxY];

    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            matrix[i][j] = '0';
        }
    }
}

template<class T>
Image<T>:: Image<T>(const Image<T>& img) {
    _maxX = img._maxX;
    _maxY = img._maxY;

    matrix = new T * [_maxX];
    for (int i = 0; i < _maxX; i++)
        matrix[i] = new T[_maxY];

    for (int i = 0; i < _maxX; i++)
        for (int j = 0; j < _maxY; j++)
            matrix[i][j] = img(i, j);
}

template<class T>
Image<T>::~Image() {
    for (int i = 0; i < _maxX; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

template<class T>
Image<T>& Image<T>::operator=(const Image<T>& img) {
    if (this == &img)
        return *this;

    for (int i = 0; i < _maxX; i++)
        delete[] matrix[i];

    delete[] matrix;

    _maxX = img._maxX;
    _maxY = img._maxY;

    matrix = new T * [_maxX];
    for (int i = 0; i < _maxX; i++)
        matrix[i] = new T[_maxY];

    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            matrix[i][j] = img(i, j);
        }
    }
    return *this;
}

template<class T>
void Image<T>::set(int x, int y, T value) {
        matrix[x][y] = value;
}

template<class T>
T Image<T>::get(int x, int y) {
        return matrix[x][y];
}

template<class T>
Image<T> Image<T>::operator+(const Image<T>& img) {
    Image<T> result(_maxX, _maxY);

    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {

            if ((double)matrix[i][j] + img(i, j) > numeric_limits<T>::max() || (double)matrix[i][j] + img(i, j) < numeric_limits<T>::min())
                result(i, j) = 0;
            else
                result(i, j) = matrix[i][j] + img(i, j);
        }
    }
    return result;
}

template<class T>
Image<T>  Image<T>::operator*(const Image<T>& img) {
    Image<T> result(_maxX, _maxY);

    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            if ((double)matrix[i][j] * img(i, j) > numeric_limits<T>::max() || (double)matrix[i][j] * img(i, j) < numeric_limits<T>::min())
                result(i, j) = 0;
            else
                result(i, j) = matrix[i][j] * img(i, j);
        }
    }

    return result;
}

template<class T>
Image<T> Image<T>::operator+(T value) {
    Image<T> result(_maxX, _maxY);

    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            if (matrix[i][j] + value > numeric_limits<T>::max() || (double)matrix[i][j] + (double)value < numeric_limits<T>::min())
                result(i, j) = 0;
            else
                result(i, j) = matrix[i][j] + value;
        }
    }
    return result;
}

template<class T>
Image<T> Image<T>::operator*(T value) {
   Image<T> result(_maxX, _maxY);

   for (int i = 0; i < _maxX; i++) {
       for (int j = 0; j < _maxY; j++) {
           if ((double)matrix[i][j] * value > numeric_limits<T>::max() || (double)matrix[i][j] * value < numeric_limits<T>::min())
               result(i, j) = 0;
           else
               result(i, j) = matrix[i][j] * value;
       }
   }
    return result;
}

template<>
Image<char> Image<char>::operator+(const Image<char>& img) {
    Image<char> result(_maxX, _maxY);

    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {

            if ((double)matrix[i][j] + img(i, j) > numeric_limits<char>::max() || (double)matrix[i][j] + img(i, j) < numeric_limits<char>::min())
                result(i, j) = '0';
            else
                /*result(i, j) = (char)((double)matrix[i][j] + (double)img(i, j));*/
                result(i, j) = matrix[i][j] + img(i, j);
        }
    }
    return result;
}

template<>
Image<char> Image<char>::operator*(const Image<char>& img) {
    Image<char> result(_maxX, _maxY);

    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            if ((double)matrix[i][j] * img(i, j) > numeric_limits<char>::max() || (double)matrix[i][j] * img(i, j) < numeric_limits<char>::min())
                result(i, j) = '0';
            else
                result(i, j) = matrix[i][j] * img(i, j);
        }
    }

    return result;
}

//template<>
//Image<char> Image<char>::operator+(char value) {
//    Image<char> result(_maxX, _maxY);
//    if (value == '0')
//        value = (char)0;
//    else
//        value = (char)1;
//    for (int i = 0; i < _maxX; i++) {
//        for (int j = 0; j < _maxY; j++) {
//            if ((char)(((double)matrix[i][j] + (double)value)) > numeric_limits<char>::max() || (char)(((double)matrix[i][j] + (double)value)) < numeric_limits<char>::min())
//                result(i, j) = (char)0;
//            else
//                result(i, j) = matrix[i][j] + value;
//                
//        }
//    }
//    return result;
//}
//
//
//template<>
//Image<char> Image<char>::operator*(char value) {
//    Image<char> result(_maxX, _maxY);
//    if (value == '0')
//        value = (char)0;
//    else
//        value = (char)1;
//    for (int i = 0; i < _maxX; i++) {
//        for (int j = 0; j < _maxY; j++) {
//            if ((double)matrix[i][j] * (double)value > numeric_limits<char>::max() || (double)matrix[i][j] * (double)value < numeric_limits<char>::min())
//                result(i, j) = '0';
//            else {
//                result(i, j) = matrix[i][j] * value;
//            }
//        }
//    }
//    return result;
//}


template<class T>
Image<T> Image<T>::operator!() {
    Image<T> result(_maxX, _maxY);
    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) { 
            if (matrix[i][j] == 0) {
                matrix[i][j] = numeric_limits<T>::max();
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
    return result;
}

template<>
Image<char> Image<char>::operator!() {
    Image<char> result(_maxX, _maxY);
    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            if (matrix[i][j] == '0')
                matrix[i][j] = numeric_limits<char>::max(); 
            else
                matrix[i][j] = '0';
        }
    }
    return result;
}

template<class T>
double  Image<T>::fill_ratio() {
    int count = 0;
    for (int i = 0; i < _maxX; i++)
        for (int j = 0; j < _maxY; j++)
            if (matrix[i][j] != 0)
                count++;

    return (double)count / (double)(_maxX * _maxY);
}

template<>
double Image<char>::fill_ratio() {
    int count = 0;

    for (int i = 0; i < _maxX; i++)
        for (int j = 0; j < _maxY; j++)
            if (matrix[i][j] != '0')
                count++;

    return (double)count / (double)(_maxX * _maxY);
}

template<class T>
T  Image<T>::operator()(int x, int y) const {
    return matrix[x][y];
}

template<class T>
T& Image<T>::operator()(int x, int y) {
    return matrix[x][y];
}

template<class T>
void Image<T>::change() {
    T value;
    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            cin >> value;
            if (value > numeric_limits<T>::max() || value < numeric_limits<T>::min()) {
                    cout << "Error" << endl;
                    cin >> value;
            }
            matrix[i][j] = value;
        }
        cout << endl;
    }
}

template<>
void Image<char>::change() {
    char value;
    for (int i = 0; i < _maxX; i++) {
        for (int j = 0; j < _maxY; j++) {
            cin >> value;
            matrix[i][j] = value;
        }
        cout << endl;
    }
}

template<class T>
void menu(Image<T>& img1, Image<T>& img2, int X, int Y) {
    while (true) {
        int i;
        cout << "1. Create a circle" << endl;
        cout << "2. Print a image" << endl;
        cout << "3. Invert a image" << endl;
        cout << "4. Sum two images" << endl;
        cout << "5. Sum image with bool" << endl;
        cout << "6. Multiply two images" << endl;
        cout << "7. Multiply image with bool" << endl;
        cout << "8. Fill ratio" << endl;
        cout << "9. Change the composition" << endl;
        cout << "10. Index: replace" << endl;
        cout << "11.Index: browse" << endl;
        cout << "12. Complete" << endl;
        cin >> i;

        switch (i) {
        case 1: {
            int x, y, radius;
            cout << "Enter the coordinates of the center and the radius of the circle" << endl;
            cin >> x >> y >> radius;
            if ((x - radius) < 0 || (y - radius) < 0 || (x + radius) > X || (y + radius) > Y) {
                while ((x - radius) < 0 || (y - radius) < 0 || (x + radius) > X || (y + radius) > Y) {
                    cout << "Error" << endl;
                    cout << "Enter the coordinates of the center and the radius of the circle" << endl;
                    cin >> x >> y >> radius;
                }
            }
            cout << "Enter the value of the pixel" << endl;
            T value;
            cin >> value;
            /*Image<T> tmp*/ img1 = cret_circle(img1, x, y, radius, value);
            cout << img1;
            break;
        }
        case 2: {
            cout << img1;
            break;
        }
        case 3: {
            !img1;
            break;
        }
        case 4: {
            img1 = img1 + img2;
            break;
        }
        case 5: {
            T value;
            cout << "Enter a value" << endl;
            cin >> value;
            img1 = img1 + value;
            break;
        }
        case 6: {
            img1 = img1 * img2;
            break;
        }
        case 7: {
            T value;
            cout << "Enter a value" << endl;
            cin >> value;
            img1 = img1 * value;
            break;
        }
        case 8: {
            cout << img1.fill_ratio() << endl;
            break;
        }
        case 9: {
            cout << "Enter a value" << endl;
            img1.change();

            break;
        }
        case 10: {
            T value;
            int x, y;
            cout << "enter the X and Y values" << endl;
            cin >> x >> y;
            if (x < 0 || x > X || y < 0 || y > Y) {
                while (x < 0 || x > X || y < 0 || y > Y) {
                    cout << "Error" << endl;
                    cout << "enter the X and Y values" << endl;
                    cin >> x >> y;
                }
            }
                cout << "Enter a value" << endl;
                    cin >> value;
                img1(x, y) = value;
                break;
        }
        case 11: {
            int x, y;
            cout << "enter the X and Y values" << endl;
            cin >> x >> y;
            if (x < 0 || x > X || y < 0 || y > Y) {
                while (x < 0 || x > X || y < 0 || y > Y) {
                    cout << "Error" << endl;
                    cout << "enter the X and Y values" << endl;
                    cin >> x >> y;
                }
            }
            cout << img1(x, y) << endl;
            break;
        }
        case 12: {
            return;
            break;
        }
        default: {
            cout << "Error" << endl;
            cin >> i;
            break;
        }
        
        }
    }
}
template<class T>
void select_img(Image<T>& img1, Image<T>& img2, int x, int y) {
    int num;
    while (true) {
        cout << "Select image" << endl;
        cout << "1. First Image" << endl;
        cout << "2. Second Image" << endl;
        cout << "3. Complete" << endl;
        cin >> num;
        switch (num) {
        case 1:
            menu(img1, img2, x, y);
            break;
        case 2:
            menu(img2, img1, x, y);
            break;
        case 3:
            return;
        default:
            cout << "Error" << endl;
            break;
        }
    }
}

void create_by_type(int type) {
    int x, y;
    cout << "Enter X and Y of the image" << endl;
    cin >> x >> y;
    if (x < 0 || y < 0) {
        while (x < 0 || y < 0) {
            cout << "Enter X and Y of the image" << endl;
            cin >> x >> y;
        }
    }
    if (type == 1) {
        Image<bool> img1(x, y);
        Image<bool> img2(x, y);
        select_img<bool>(img1, img2, x, y);
    }
    if (type == 2) {
        Image<char> img1(x, y);
        Image<char> img2(x, y);
        select_img<char>(img1, img2, x, y);
    }
    if (type == 3) {
        Image<short> img1(x, y);
        Image<short> img2(x, y);
        select_img<short>(img1, img2, x, y);
    }
    if (type == 4) {
        Image<float> img1(x, y);
        Image<float> img2(x, y);
        select_img<float>(img1, img2, x, y);
    }
}

void select_type() {
    while (true) {
        int i;
        cout << "Select type" << endl;
        cout << "1. bool" << endl;
        cout << "2. char" << endl;
        cout << "3. short" << endl;
        cout << "4. float" << endl;
        cout << "5. complete" << endl;
        cin >> i;
        switch (i) {
        case 1: {
            create_by_type(1);
            break;
        }
        case 2: {
            create_by_type(2);
            break;
        }
        case 3: {
            create_by_type(3);
            break;
        }
        case 4: {
            create_by_type(4);
            break;
        }
        case 5: {
            return;
        }
        default: {
            cout << "Error" << endl;
            break;
        }
        }
    }
}

int main() {
    select_type();

    return 0;
}