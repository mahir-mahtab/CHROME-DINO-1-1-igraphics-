//
//  Original Author: S. M. Shahriar Nirjon
//  last modified: November 28, 2024
//
//  Version: 2.0.2012.2015.2024
//

#pragma once  // Header guard to prevent multiple inclusions

#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "GL/glut.h"
#include <time.h>
#include <math.h>
#include <GL/glaux.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

typedef struct{
    unsigned char* data;
    int width, height, channels;
} Image;

typedef struct{
    int x, y;
    Image img;
    int visible;
    unsigned char* collisionMask;
    int ignoreColor;
} Sprite;

enum MirrorState {
    HORIZONTAL,
    VERTICAL
};


int iScreenHeight, iScreenWidth;
int iMouseX, iMouseY;
int ifft=0;
void (*iAnimFunction[10])(void)={0};
int iAnimCount=0;
int iAnimDelays[10];
int iAnimPause[10];

bool keyStates[256] = { false };
bool specialKeyStates[256] = { false };

bool leftMouseButtonPressed = false;
bool rightMouseButtonPressed = false;

// Function Declarations
void iDraw();
void iKeyboard(unsigned char);
void iSpecialKeyboard(unsigned char);
void iMouseMove(int, int);
void iPassiveMouseMove(int, int);
void iMouse(int button, int state, int x, int y);
bool isleftmousepressed();
bool isrightmousepressed();
void ishowmanualtext(int x, int y, char* str, int fontsize);
//void ishowheadingtext(int x, int y, char* str, int fontsize, char* fontname, int boldness); 
void iLoadImage(Image* img, const char filename[]);
void iResizeImage(Image* img, int width, int height);
void iShowImage(int x, int y, Image* img);
void iFreeImage(Image* img);
void iShowBMPResized(int x, int y, const char* filename, int width, int height);
void iShowImageRotated(int x, int y, Image* img, double angle, int width, int height); 
void loadandresizeimage(const char* filename, int width, int height);

// Define timer functions compatible with glutTimerFunc
void iA0(int value) { if(!iAnimPause[0]) iAnimFunction[0](); glutTimerFunc(iAnimDelays[0], iA0, 0); }
void iA1(int value) { if(!iAnimPause[1]) iAnimFunction[1](); glutTimerFunc(iAnimDelays[1], iA1, 0); }
void iA2(int value) { if(!iAnimPause[2]) iAnimFunction[2](); glutTimerFunc(iAnimDelays[2], iA2, 0); }
void iA3(int value) { if(!iAnimPause[3]) iAnimFunction[3](); glutTimerFunc(iAnimDelays[3], iA3, 0); }
void iA4(int value) { if(!iAnimPause[4]) iAnimFunction[4](); glutTimerFunc(iAnimDelays[4], iA4, 0); }
void iA5(int value) { if(!iAnimPause[5]) iAnimFunction[5](); glutTimerFunc(iAnimDelays[5], iA5, 0); }
void iA6(int value) { if(!iAnimPause[6]) iAnimFunction[6](); glutTimerFunc(iAnimDelays[6], iA6, 0); }
void iA7(int value) { if(!iAnimPause[7]) iAnimFunction[7](); glutTimerFunc(iAnimDelays[7], iA7, 0); }
void iA8(int value) { if(!iAnimPause[8]) iAnimFunction[8](); glutTimerFunc(iAnimDelays[8], iA8, 0); }
void iA9(int value) { if(!iAnimPause[9]) iAnimFunction[9](); glutTimerFunc(iAnimDelays[9], iA9, 0); }

int iSetTimer(int msec, void (*f)(void))
{
    int i = iAnimCount;

    if(iAnimCount >= 10){ printf("Error: Maximum number of timers used.\n"); return -1; }

    iAnimFunction[i] = f;
    iAnimDelays[i] = msec;
    iAnimPause[i] = 0;

    switch(iAnimCount) {
        case 0: glutTimerFunc(msec, iA0, 0); break;
        case 1: glutTimerFunc(msec, iA1, 0); break;
        case 2: glutTimerFunc(msec, iA2, 0); break;
        case 3: glutTimerFunc(msec, iA3, 0); break;
        case 4: glutTimerFunc(msec, iA4, 0); break;
        case 5: glutTimerFunc(msec, iA5, 0); break;
        case 6: glutTimerFunc(msec, iA6, 0); break;
        case 7: glutTimerFunc(msec, iA7, 0); break;
        case 8: glutTimerFunc(msec, iA8, 0); break;
        case 9: glutTimerFunc(msec, iA9, 0); break;
        default: break;
    }
    iAnimCount++;

    return iAnimCount - 1;
}

void iPauseTimer(int index){
    if(index >= 0 && index < iAnimCount){
        iAnimPause[index] = 1;
    }
}

void iResumeTimer(int index){
    if(index >= 0 && index < iAnimCount){
        iAnimPause[index] = 0;
    }
}

// Existing Function Definitions
void iShowBMP2(int x, int y, char filename[], int ignoreColor)
{
    int  width, height, n;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* image = stbi_load(filename, &width, &height, &n, 4);

    int nPixels = width * height;
    int *rgPixels = new int[nPixels];

    int i,j;
    for (i = 0, j=0; i < nPixels; i++, j += 4)
    {
        int bgr = 0;
        for(int k = 2; k >= 0; k--)
        {
            bgr = ((bgr << 8) | image[j+k]);

        }

        rgPixels[i] = (bgr == ignoreColor) ? 0 : 255;
        rgPixels[i] = ((rgPixels[i] << 24) | bgr);
    }

    glRasterPos2f(x, y);
    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, rgPixels);
    delete[] rgPixels;

    stbi_image_free(image);
}

void iShowBMP(int x, int y, char filename[])
{
    iShowBMP2(x, y, filename, -1 /* ignoreColor */);
}

void iShowBMPResized(int x, int y, const char* filename, int width, int height) {
    Image img;
    iLoadImage(&img, filename);
    if (img.data == nullptr) {
        printf("Failed to load image: %s\n", filename);
        return; // Exit the function if image loading failed
    }
    iResizeImage(&img, width, height);
    iShowImage(x, y, &img);
    iFreeImage(&img);
}

void iLoadImage(Image* img, const char filename[])
{
    stbi_set_flip_vertically_on_load(true);
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    if (img->data == nullptr) {
        printf("Error loading image '%s'\n", filename);
        return;
    }
}

void iFreeImage(Image* img)
{
    stbi_image_free(img->data);
}

void iShowImage2(int x, int y, Image* img, int ignoreColor)
{
    int width = img->width;
    int height = img->height;
    int channels = img->channels;
    unsigned char* data = img->data;
    if (ignoreColor != -1) {
        // Iterate over the pixels
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int index = (y * width + x) * channels;
                // Check if the pixel is the color we want to ignore
                if (data[index] == (ignoreColor & 0xFF) &&
                    data[index + 1] == ((ignoreColor >> 8) & 0xFF) &&
                    data[index + 2] == ((ignoreColor >> 16) & 0xFF)) {
                    // Set the pixel to 0
                    data[index] = 0;
                    data[index + 1] = 0;
                    data[index + 2] = 0;
                    if (channels == 4) {
                        data[index + 3] = 0;
                    }
                }
            }
        }
    }
    glRasterPos2f(x, y);
    glDrawPixels(width, height, (channels == 4)? GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, data);
}

void iShowImage(int x, int y, Image* img)
{
    if (img->data == nullptr) {
        // Image not loaded; skip drawing
        return;
    }
    iShowImage2(x, y, img, -1);
}

void iResizeImage(Image* img, int width, int height)
{
    int imgWidth = img->width;
    int imgHeight = img->height;
    int channels = img->channels;
    unsigned char* data = img->data;
    unsigned char* resizedData = new unsigned char[width * height * channels];
    stbir_resize_uint8(data, imgWidth, imgHeight, 0, resizedData, width, height, 0, channels);
    stbi_image_free(data);
    img->data = resizedData;
    img->width = width;
    img->height = height;
}

void iMirrorImage(Image* img, MirrorState state)
{
    int width = img->width;
    int height = img->height;
    int channels = img->channels;
    unsigned char* data = img->data;
    unsigned char* mirroredData = new unsigned char[width * height * channels];
    if (state == HORIZONTAL) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int index = (y * width + x) * channels;
                int mirroredIndex = (y * width + (width - x - 1)) * channels;
                for (int c = 0; c < channels; c++) {
                    mirroredData[mirroredIndex + c] = data[index + c];
                }
            }
        }
    } else if (state == VERTICAL) {
        for (int y = 0; y < height; y++) {
            int mirroredY = height - y - 1;
            for (int x = 0; x < width; x++) {
                int index = (y * width + x) * channels;
                int mirroredIndex = (mirroredY * width + x) * channels;
                for (int c = 0; c < channels; c++) {
                    mirroredData[mirroredIndex + c] = data[index + c];
                }
            }
        }
    }
    stbi_image_free(data);
    img->data = mirroredData;
}

// ignorecolor = hex color code 0xRRGGBB
void iUpdateCollisionMask(Sprite* s)
{
    Image* img = &s->img;
    int ignorecolor = s->ignoreColor;
    if(ignorecolor == -1){
        s->collisionMask = nullptr;
        return;
    }
    int width = img->width;
    int height = img->height;
    int channels = img->channels;
    unsigned char* data = img->data;
    if (s->collisionMask != nullptr) {
        delete[] s->collisionMask;
    }
    unsigned char* collisionMask = new unsigned char[width * height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels;
            int isTransparent = (channels == 4 && data[index + 3] == 0);
            if ((data[index] == (ignorecolor & 0xFF) &&
                data[index + 1] == ((ignorecolor >> 8) & 0xFF) &&
                data[index + 2] == ((ignorecolor >> 16) & 0xFF)) || 
                isTransparent) {
                collisionMask[y * width + x] = 0;
            } else {
                collisionMask[y * width + x] = 1;
            }
        }
    }
    s->collisionMask = collisionMask;
}

int iCheckCollision(Sprite* s1, Sprite* s2){
    Image* img1 = &s1->img;
    int width1 = img1->width;
    int height1 = img1->height;
    unsigned char* collisionMask1 = s1->collisionMask;
    Image* img2 = &s2->img;
    int width2 = img2->width;
    int height2 = img2->height;
    unsigned char* collisionMask2 = s2->collisionMask;
    int x1 = s1->x;
    int y1 = s1->y;
    int x2 = s2->x;
    int y2 = s2->y;
    // check if the two images overlap
    int startX = (x1 > x2) ? x1 : x2;
    int endX = (x1 + width1 < x2 + width2) ? x1 + width1 : x2 + width2;
    int startY = (y1 > y2) ? y1 : y2;
    int endY = (y1 + height1 < y2 + height2) ? y1 + height1 : y2 + height2;
    int noOverlap = startX >= endX || startY >= endY;
    // If collisionMasks are not set, check the whole image for collision
    if(collisionMask1 == nullptr || collisionMask2 == nullptr){
        return noOverlap ? 0 : 1;
    }
    // now collisionMasks are set. Check only the overlapping region
    if(noOverlap){
        return 0;
    }
    for(int y = startY; y < endY; y++){
        for(int x = startX; x < endX; x++){
            int index1 = (y - y1) * width1 + (x - x1);
            int index2 = (y - y2) * width2 + (x - x2);
            if(collisionMask1[index1] && collisionMask2[index2]){
                return 1;
            }
        }
    }
    return 0;
}

void iLoadSprite(Sprite* s, const char* filename, int ignoreColor){
    iLoadImage(&s->img, filename);
    s->ignoreColor = ignoreColor;
    iUpdateCollisionMask(s);
}

void iSetSpritePosition(Sprite* s, int x, int y){
    s->x = x;
    s->y = y;
}

void iShowSprite(Sprite* s){
    iShowImage2(s->x, s->y, &s->img, s->ignoreColor);
}

void iResizeSprite(Sprite* s, int width, int height){
    iResizeImage(&s->img, width, height);
    iUpdateCollisionMask(s);
}

void iMirrorSprite(Sprite* s, MirrorState state){
    iMirrorImage(&s->img, state);
    iUpdateCollisionMask(s);
}

void iFreeSprite(Sprite* s){
    iFreeImage(&s->img);
    if(s->collisionMask != nullptr){
        delete[] s->collisionMask;
    }
}

// Pixel and Text Functions
void iGetPixelColor (int cursorX, int cursorY, int rgb[])
{
    GLubyte pixel[3];
    glReadPixels(cursorX, cursorY,1,1,
        GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);

    rgb[0] = pixel[0];
    rgb[1] = pixel[1];
    rgb[2] = pixel[2];

    // printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]);
}

void iText(double x, double y, char *str, void* font=GLUT_BITMAP_8_BY_13)
{
    glRasterPos3d(x, y, 0);
    int i;
    for (i=0; str[i]; i++) {
        glutBitmapCharacter(font, str[i]); //,GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_24
    }
}

void iPoint(double x, double y, int size=0)
{
    int i, j;
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    for(i=x-size;i<x+size;i++)
    {
        for(j=y-size; j<y+size;j++)
        {
            glVertex2f(i, j);
        }
    }
    glEnd();
}

void iLine(double x1, double y1, double x2, double y2)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void iFilledPolygon(double x[], double y[], int n)
{
    int i;
    if(n<3)return;
    glBegin(GL_POLYGON);
    for(i = 0; i < n; i++){
        glVertex2f(x[i], y[i]);
    }
    glEnd();
}

void iPolygon(double x[], double y[], int n)
{
    int i;
    if(n<3)return;
    glBegin(GL_LINE_STRIP);
    for(i = 0; i < n; i++){
        glVertex2f(x[i], y[i]);
    }
    glVertex2f(x[0], y[0]);
    glEnd();
}

void iRectangle(double left, double bottom, double dx, double dy)
{
    double x1, y1, x2, y2;

    x1 = left;
    y1 = bottom;
    x2=x1+dx;
    y2=y1+dy;

    iLine(x1, y1, x2, y1);
    iLine(x2, y1, x2, y2);
    iLine(x2, y2, x1, y2);
    iLine(x1, y2, x1, y1);
}

void iFilledRectangle(double left, double bottom, double dx, double dy)
{
    double xx[4], yy[4];
    double x1, y1, x2, y2;

    x1 = left;
    y1 = bottom;
    x2=x1+dx;
    y2=y1+dy;

    xx[0]=x1;
    yy[0]=y1;
    xx[1]=x2;
    yy[1]=y1;
    xx[2]=x2;
    yy[2]=y2;
    xx[3]=x1;
    yy[3]=y2;

    iFilledPolygon(xx, yy, 4);
}

void iFilledCircle(double x, double y, double r, int slices=100)
{
    double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
    dt = 2*PI/slices;
    xp = x+r;
    yp = y;
    glBegin(GL_POLYGON);
    for(t = 0; t <= 2*PI; t+=dt)
    {
        x1 = x + r * cos(t);
        y1 = y + r * sin(t);

        glVertex2f(xp, yp);
        xp = x1;
        yp = y1;
    }
    glEnd();
}

void iCircle(double x, double y, double r, int slices=100)
{
    double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
    dt = 2*PI/slices;
    xp = x+r;
    yp = y;
    for(t = 0; t <= 2*PI; t+=dt)
    {
        x1 = x + r * cos(t);
        y1 = y + r * sin(t);
        iLine(xp, yp, x1, y1);
        xp = x1;
        yp = y1;
    }
}

void iShowCircle(int x, int y, int r, int thickness, int slices=100)
{
    double t, PI=acos(-1.0), dt;
    dt = 2*PI/slices;

    glBegin(GL_TRIANGLE_STRIP);
    for(t = 0; t <= 2*PI+dt; t+=dt)
    {
        double x_outer = x + (r + thickness) * cos(t);
        double y_outer = y + (r + thickness) * sin(t);
        double x_inner = x + r * cos(t);
        double y_inner = y + r * sin(t);

        glVertex2f(x_outer, y_outer);
        glVertex2f(x_inner, y_inner);
    }
    glEnd();
}

void iEllipse(double x, double y, double a, double b, int slices=100)
{
    double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
    dt = 2*PI/slices;
    xp = x+a;
    yp = y;
    for(t = 0; t <= 2*PI; t+=dt)
    {
        x1 = x + a * cos(t);
        y1 = y + b * sin(t);
        iLine(xp, yp, x1, y1);
        xp = x1;
        yp = y1;
    }
}

void iFilledEllipse(double x, double y, double a, double b, int slices=100)
{
    double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
    dt = 2*PI/slices;
    xp = x+a;
    yp = y;
    glBegin(GL_POLYGON);
    for(t = 0; t <= 2*PI; t+=dt)
    {
        x1 = x + a * cos(t);
        y1 = y + b * sin(t);
        glVertex2f(xp, yp);
        xp = x1;
        yp = y1;
    }
    glEnd();
}

void iRotate(double x, double y, double degree)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(degree, 0, 0, 1.0);
    glTranslatef(-x, -y, 0.0);
}

void iUnRotate()
{
    glPopMatrix();
}

void iSetColor(double r, double g, double b)
{
    double mmx;
    mmx = r;
    if(g > mmx)mmx = g;
    if(b > mmx)mmx = b;
    mmx = 255;
    if(mmx > 0){
        r /= mmx;
        g /= mmx;
        b /= mmx;
    }
    glColor3f(r, g, b);
}

void iDelay(int sec)
{
    int t1, t2;
    t1 = time(0);
    while(1){
        t2 = time(0);
        if(t2-t1>=sec)
            break;
    }
}

void iClear()
{
    glClear(GL_COLOR_BUFFER_BIT) ;
    glMatrixMode(GL_MODELVIEW) ;
    glClearColor(0,0,0,0);
    glFlush();
}

void displayFF(void){

    iDraw();
    glutSwapBuffers() ;
}

void animFF(void)
{
    if(ifft == 0){
        ifft = 1;
        iClear();
    }
    glutPostRedisplay();
}



void keyboardHandler1FF(unsigned char key, int x, int y)
{
    keyStates[key] = true;
    iKeyboard(key);
    glutPostRedisplay();
}

void keyboardUpHandlerFF(unsigned char key, int x, int y)
{
    keyStates[key] = false; // Key released
}

void keyboardHandler2FF(int key, int x, int y)
{
    specialKeyStates[key] = true; 
    iSpecialKeyboard(key);
    glutPostRedisplay();
}

void keyboardSpecialUpHandlerFF(int key, int x, int y)
{
    specialKeyStates[key] = false; // Special key released
}

void mouseMoveHandlerFF(int mx, int my)
{
    iMouseX = mx;
    iMouseY = iScreenHeight - my;
    iMouseMove(iMouseX, iMouseY);
    glFlush();
}

void mouseHandlerFF(int button, int state, int x, int y)
{
    iMouseX = x;
    iMouseY = iScreenHeight - y;
    // Update the left and right mouse button states
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            leftMouseButtonPressed = true;
        } else if (state == GLUT_UP) {
            leftMouseButtonPressed = false;
        }
    } else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            rightMouseButtonPressed = true;
        } else if (state == GLUT_UP) {
            rightMouseButtonPressed = false;
        }
    }
    iMouse(button, state, iMouseX, iMouseY);
    glFlush();
}

void mousePassiveMoveHandlerFF(int x, int y)
{
    iMouseX = x;
    iMouseY = iScreenHeight - y;
    iPassiveMouseMove(iMouseX, iMouseY);

    glFlush();
}

void iInitialize(int width=500, int height=500, char *title="iGraphics")
{
    iScreenHeight = height;
    iScreenWidth = width;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA) ;
    glutInitWindowSize(width , height ) ;
    glutInitWindowPosition( 10 , 10 ) ;
    glutCreateWindow(title) ;
    glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;
    glMatrixMode( GL_PROJECTION) ;
    glLoadIdentity() ;
    glOrtho(0.0 , width , 0.0 , height , -1.0 , 1.0) ;
    //glOrtho(-100.0 , 100.0 , -100.0 , 100.0 , -1.0 , 1.0) ;
    //SetTimer(0, 0, 10, timer_proc);

    iClear();

    glutDisplayFunc(displayFF) ;
    glutKeyboardFunc(keyboardHandler1FF); //normal
    glutKeyboardUpFunc(keyboardUpHandlerFF);       // Normal key release
    glutSpecialFunc(keyboardHandler2FF); //special keys
    glutSpecialUpFunc(keyboardSpecialUpHandlerFF); // Special key release
    glutMouseFunc(mouseHandlerFF);
    glutMotionFunc(mouseMoveHandlerFF);
    glutPassiveMotionFunc(mousePassiveMoveHandlerFF);
    glutIdleFunc(animFF) ;

    //
    // Setup Alpha channel testing.
    // If alpha value is greater than 0, then those
    // pixels will be rendered. Otherwise, they would not be rendered
    //
    glAlphaFunc(GL_GREATER,0.0f);
    glEnable(GL_ALPHA_TEST);

    glutMainLoop();
}

bool iIsKeyPressed(unsigned char key)
{
    return keyStates[key];
}

bool iIsSpecialKeyPressed(int key)
{
    return specialKeyStates[key];
}

// Define the functions to return the mouse button states
bool isleftmousepressed() {
    return leftMouseButtonPressed;
}

bool isrightmousepressed() {
    return rightMouseButtonPressed;
}

// Declare and define isspecialkeypressed
bool isspecialkeypressed() {
    for(int i = 0; i < 256; i++) {
        if(specialKeyStates[i]) {
            return true;
        }
    }
    return false;
}

// Function to check collision between two rectangles
bool iCheckCollisionRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return x1 < x2 + w2 && x1 + w1 > x2 &&
           y1 < y2 + h2 && y1 + h1 > y2;
}

void ishowmanualtext(int x, int y, char* str, int fontsize) {
    void* font = GLUT_STROKE_ROMAN; // Use stroke font

    glPushMatrix();
    glTranslatef(x, y, 0);
    float scale = fontsize / 100.0f; // Adjust scaling factor as needed
    glScalef(scale, scale, 1.0f);

    for (char* c = str; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }

    glPopMatrix();
}

/*void ishowheadingtext(int x, int y, char* str, int fontsize, char* fontname, int boldness) {
    void* font;

    // Map fontname and boldness to GLUT font
    if (strcmp(fontname, "Roman") == 0) {
        font = (boldness >= 700) ? GLUT_STROKE_MONO_ROMAN : GLUT_STROKE_ROMAN;
    } else if (strcmp(fontname, "Helvetica") == 0) {
        font = GLUT_STROKE_ROMAN; // Substitute as GLUT doesn't support Helvetica in stroke fonts
    } else {
        font = GLUT_STROKE_ROMAN; // Default font
    }

    glPushMatrix();
    glTranslatef(x, y, 0);
    float scale = fontsize / 100.0f;
    glScalef(scale, scale, 1.0f);

    for (char* c = str; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }

    glPopMatrix();
}*/

void ishowheadingtext(int x, int y, const char* str, float fontsize, const char* fontname, int boldness) {
    void* font = GLUT_STROKE_ROMAN; // Use stroke fonts for scaling

    // Approximate boldness with line width (limited effect)
    if (boldness >= 700) {
        glLineWidth(3.0);
    } else if (boldness >= 500) {
        glLineWidth(2.0);
    } else {
        glLineWidth(1.0);
    }

    glPushMatrix();
    glTranslatef(x, y, 0);

    // Scaling based on fontsize
    // The base size of GLUT_STROKE_ROMAN is approximately 119.05 units in height
    float scale = fontsize / 119.05f;
    glScalef(scale, scale, 1.0f);

    // Render the text using stroke characters
    for (int i = 0; str[i] != '\0'; ++i) {
        glutStrokeCharacter(font, str[i]);
    }

    glPopMatrix();
    glLineWidth(1.0); // Reset line width to default
}