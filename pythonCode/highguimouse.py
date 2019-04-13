import cv2
import sys
import math

#To store center and cicumference points
center = (0,0)
circumference = (0,0)

def drawCircle(action, x, y, flags, userdata):
    #referencing global variables
    global center, circumference
    #action to be taken when left mouse button is pressed
    if(action ==  cv2.EVENT_LBUTTONDOWN):
        center = (x,y)
        #draw the center
        cv2.circle(imageClone, center, 2, (0, 0, 255), 5, cv2.LINE_AA)
    #action to be taken when left mouse button is released
    elif action == cv2.EVENT_LBUTTONUP:
        circumference = (x,y)
        #calculate radius of the circle
        radius = math.sqrt(math.pow(center[0] - circumference[0], 2)+ math.pow(center[1] - circumference[1], 2))
        #draw the circle
        cv2.circle(imageClone, center, int(radius), (0, 0, 255), 5, cv2.LINE_AA)
        cv2.imshow("image", imageClone)


inputImage = cv2.imread("../assets/putin.jpg")

#Create a clone of input image to work on
imageClone = inputImage.copy()

#create window to display image
cv2.namedWindow("image", cv2.WINDOW_NORMAL)

#setup callback for mouse event
cv2.setMouseCallback("image", drawCircle)

while True:
    cv2.imshow("image", imageClone)
    cv2.putText(imageClone, "Choose center and drag. Press c to clear and esc to exit", (100, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 5)

    k = cv2.waitKey(10)

    #press esc to exit the program
    if(k == 27):
        break

    #clear the image of all the circles drawn if c button from keyboard is pressed
    if(k == 99):
        imageClone = inputImage.copy()

#close all the opened windows
cv2.destroyAllWindows()