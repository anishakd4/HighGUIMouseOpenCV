#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat image, imageClone;

//to store center and point on the circumference of the circle
Point center, circumference;

//Callback function which will be called for mouse events
void drawCircle(int action, int x, int y, int flags, void *userdata){
    //action taken when left mouse button pressed
    if(action == EVENT_LBUTTONDOWN){
        center = Point(x,y);
        //Draw the center
        circle(imageClone, center, 1, Scalar(0, 0, 255), 5, CV_AA);
    }
    //acion taken when left mouse button is released
    else if(action ==EVENT_LBUTTONUP){
        circumference = Point(x, y);
        //calculate radius of circle
        float radius =sqrt(pow(center.x - circumference.x, 2)+pow(center.y - circumference.y, 2));
        //Draw circle
        circle(imageClone, center, radius, Scalar(0, 0, 255), 5, CV_AA);
        imshow("image", imageClone);
    }
}

int main(){
    //Read input image
    image = imread("../assets/putin.jpg");

    //Create a clone of input image to work on
    imageClone = image.clone();

    namedWindow("image", WINDOW_NORMAL);

    //set up callback for mouse events
    setMouseCallback("image", drawCircle);

    while(1){
        imshow("image", imageClone);
        putText(imageClone, "Choose cener and drag. Press c to clear. Press esc to exit.", Point(100, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 5);

        int k= waitKey(20);

        //Press sec to exit the program
        if(k == 27){
            break;
        }

        //Press c in keyboard to clear the image of circles
        if(k == 99){
            image.copyTo(imageClone);
        }
    }

    //close all the opended windows
    destroyAllWindows();

    return 0;
}