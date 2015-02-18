#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <time.h>  
#include <math.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

class Coin {
    public:
        float x, y, vel_x, vel_y, mass, rad;
        void init(float, float, float, float, float, float);

};

void Coin::init(float x1, float y1, float m, float vx, float vy, float r) {
    x = x1;
    y = y1;
    mass = m;
    rad = r;
    vel_y = vy;
    vel_x = vx;
}

// Function Declarations
void drawScene();
void update(int value);
void drawSquare(float len);
void fillSquare(float len);
void drawRect(float l, float b);
void drawRectFill(float l, float b, float x, float y, int color);
void drawBall(float rad);
void drawCircle(float cx, float cy, float r, int num_segments);
void drawTriangle();
void drawLine(float x1, float y1, float x2, float y2);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void scoreBoard (float x, float y, float z, float space, int score);
void mouse_motion(int x,int y);


// Global Variables

float box_len = 5.5f;
float theta = 0.0f; 
float holes_position = 5.06f;
float holes_radius = 0.4f;
float striker_angle = 0.0f;
float power_y = 0.0f;
int flag_space_hit = 0;
int reset = 0;
float alpha = 0.9f;
Coin coins[9];
int flag[10][10];
Coin striker;
int coin_count = 0;
float coordinates_x[8] = {0.5, 1, -0.5 , -1, 1, -0.5, 0.5, -1};
float coordinates_y[8] = {0.5, -1, 0.5, -1, 1, -0.5, -0.5, 1};
int score = 30;
int color = -1;
int timer = 0;
int black_count = 0, white_count = 0; 
int drag_flag;



int main(int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 3 / 4;
    int windowHeight = h * 3 / 4;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("Carroms");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutMotionFunc(mouse_motion);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}

// Function to draw objects on the screen
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    /*------------------START OF OUTER BOARD------------------*/

    //Outer Box
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    fillSquare(box_len + 1.0f);

    //Inner Box
    glColor3f(1.0f, 0.0f, 0.0f);
    drawSquare(box_len);
    glColor3f(0.968627451f, 0.815686275f, 0.658823529f);
    fillSquare(box_len);

    /*------------------END OF OUTER BOARD------------------*/


    /*------------------START OF CENTRAL CIRCLE------------------*/

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0, 0, 2, 100);
    glPopMatrix();

    /*------------------END OF CENTRAL CIRCLE------------------*/


    /*------------------START OF CORNER POCKETS------------------*/
    
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -8.0f);
    drawCircle(holes_position, holes_position, holes_radius, 100);
    drawCircle(-1 * holes_position, -1 * holes_position, holes_radius, 100);
    drawCircle(holes_position, -1 * holes_position, holes_radius, 100);
    drawCircle(-1 * holes_position, holes_position, holes_radius, 100);
    glPopMatrix();

    /*------------------END OF CORNER POCKETS------------------*/

   
    /*------------------START OF STRIKER LINES------------------*/
    
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    
    //Top Line
    drawLine(-1 * (box_len/2 - 2*2.20 - 0.2f), (box_len/2 - 2*2.20 - 0.2f) , (box_len/2 - 2*2.20 - 0.2f), (box_len/2 - 2*2.20 - 0.2f));
    drawLine(-1 * (box_len/2 - 2*2.20 - 0.2f), (box_len/2 - 2*2.20 - 0.5f) , (box_len/2 - 2*2.20 - 0.2f), (box_len/2 - 2*2.20 - 0.5f));
    glTranslatef(1.8f, 2.0f, 0);
    drawCircle(0, 0, 0.155f, 100);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(0.15f);
    glTranslatef(-3.6f, 0, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0, 0, 0.155f, 100);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(0.15f);
    glTranslatef(1.8f, -2.0f, 0);
    
    //Bottom Line
    glColor3f(0.0f, 0.0f, 0.0f);
    drawLine(-1 * (box_len/2 - 2*2.20 - 0.2f), -1 *(box_len/2 - 2*2.20 - 0.2f) , (box_len/2 - 2*2.20 - 0.2f), -1 * (box_len/2 - 2*2.20 - 0.2f));
    drawLine(-1 * (box_len/2 - 2*2.20 - 0.2f), -1 *(box_len/2 - 2*2.20 - 0.5f) , (box_len/2 - 2*2.20 - 0.2f), -1 * (box_len/2 - 2*2.20 - 0.5f));
    glTranslatef(1.8f, -2.0f, 0);
    drawCircle(0, 0, 0.155f, 100);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(0.15f);
    glTranslatef(-3.6f, 0, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0, 0, 0.155f, 100);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(0.15f);
    glTranslatef(1.8f, 2.0f, 0);
    
    //Left Line
    glColor3f(0.0f, 0.0f, 0.0f);
    drawLine(-1 *(box_len/2 - 2*2.20 - 0.2f), -1 * (box_len/2 - 2*2.20), -1 * (box_len/2 - 2*2.20 - 0.2f), (box_len/2 - 2*2.20));
    drawLine(-1 *(box_len/2 - 2*2.20 - 0.5f), -1 * (box_len/2 - 2*2.20), -1 * (box_len/2 - 2*2.20 - 0.5f), (box_len/2 - 2*2.20));
    glTranslatef(-2.0f, 1.65f, 0);
    drawCircle(0, 0, 0.155f, 100);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(0.15f);
    glTranslatef(0.0f, -3.3f, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0, 0, 0.155f, 100);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(0.15f);
    glTranslatef(2.0f, 1.65f, 0);
    
    //Right Line
    glColor3f(0.0f, 0.0f, 0.0f);
    drawLine((box_len/2 - 2*2.20 - 0.2f), -1 * (box_len/2 - 2*2.20), (box_len/2 - 2*2.20 - 0.2f), (box_len/2 - 2*2.20));
    drawLine((box_len/2 - 2*2.20 - 0.5f), -1 * (box_len/2 - 2*2.20), (box_len/2 - 2*2.20 - 0.5f), (box_len/2 - 2*2.20));
    glTranslatef(2.0f, 1.65f, 0);
    drawCircle(0, 0, 0.155f, 100);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(0.15f);
    glTranslatef(0.0f, -3.3f, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0, 0, 0.155f, 100);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(0.15f);
    
    glPopMatrix();

    /*------------------END OF STRIKER LINES------------------*/
    

    /*------------------START OF STRIKER------------------*/

    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.5f);
    glTranslatef(0, 0, -8.0f);
    if (coin_count == 0) {
        striker.init(1.0f, -4.0f, 2, 4.0f, 4.0f, 0.35f);
        color = -1;
        cout << "Your previous score is: " << score << endl;
        score = 30;
        black_count = 0;
        //cout << "Striker: (" << striker.x << ", " << striker.y << ")" << endl;
        white_count = 0;
        flag_space_hit = 0;
    }
    glTranslatef(striker.x, striker.y, 0);
    //cout << "Striker: (" << striker.x << ", " << striker.y << ")" << endl;
    drawBall(striker.rad);
    glPopMatrix();

    /*------------------END OF STRIKER------------------*/


    /*------------------START OF STRIKER GUIDE LINE------------------*/
    
    if (flag_space_hit == 0) {
        glPushMatrix();
        glTranslatef(0, 0, -8.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(striker.x, striker.y, 0);
        glRotatef(-striker_angle,0.0f,0.0f,1.0f); 
        drawLine(0, 0, 0, 4);
        glPopMatrix();
    }

    /*------------------END OF STRIKER GUIDE LINE------------------*/


    /*------------------START OF POWER GAUGE------------------*/

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(4.0f, -2.0f, 0.0f);
    drawRect(0.3f, 1.2f);
    int color;
    if (power_y < 0.5f)
        color = 1;
    else if (power_y < 0.9f)
        color = 2;
    else
        color = 3;
    drawRectFill(0.3, power_y, -0.15f, -0.6f, color);
    glPopMatrix();

    /*------------------END OF POWER GAUGE------------------*/


    /*------------------START OF COINS------------------*/

    int i;
    if (coin_count <= 0) {
        for (i = 0 ; i < 9 ; i++) {
            coins[i].init(coordinates_x[i], coordinates_y[i], 1, 0, 0, 0.3f);
            if (i == 8)
                coins[i].init(0, 0, 1, 0, 0, 0.3f);
        }
        coin_count = 9;
    }
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    for (i = 0 ; i < 9 ; i++) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(coins[i].x, coins[i].y, 0.0f);
        if (i > 3) {
            glColor3f(1.0f, 1.0f, 1.0f);
            drawCircle(0, 0, coins[i].rad, 100);
            glColor3f(0.0f, 0.0f, 0.0f);
        }
        if (i == 8)
            glColor3f(1.0f, 0.3f, 0.3f);
        drawBall(coins[i].rad);
        if (i < 4 || i == 8) {
            glColor3f(0.0f, 0.0f, 0.0f);
            drawCircle(0, 0, coins[i].rad, 100);
        }
        glTranslatef(-1 * coins[i].x, -1 * coins[i].y, 0.0f);
    }
    glColor3f(0.0f, 0.0f, 0.0f);
    scoreBoard (7.0f, 5.0f, 0.0f, 0.3f, score);

    glPopMatrix();

    /*------------------END OF COINS------------------*/


    glPopMatrix();
    glutSwapBuffers();
}

void scoreBoard (float x, float y, float posz, float space, int p)
{
        int j = 0, k = 0;
        GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;
        if (p < 0) {
            p = p * -1;
            glRasterPos3f ((x - (j * space)), y, posz);    
            glutBitmapCharacter(font_style1, 45);
            j++;
        }

        while(p > 9)
        {
            k = p % 10;
            glRasterPos3f ((x - (j * space)), y, posz);    
            glutBitmapCharacter(font_style1, 48 + k);
            j++;
            p /= 10;
        }
        glRasterPos3f ((x - (j * space)), y, posz);    
        glutBitmapCharacter(font_style1, 48 + p);
}


void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {

    if(((striker.x + striker.rad > box_len && striker.vel_x > 0.0f)) || ((striker.x - striker.rad < (-box_len) && striker.vel_x < 0.0f))) {
        striker.vel_x *= -alpha;
        striker.vel_y *= alpha;
    }
    if(((striker.y + striker.rad > box_len && striker.vel_y > 0.0f)) || ((striker.y - striker.rad < (-box_len) && striker.vel_y < 0.0f))) {
        striker.vel_y *= -alpha;
        striker.vel_x *= alpha;
    }
        
    if (flag_space_hit == 1) {
        int i, j;
        timer++;
        for (i = 0 ; i < 9 ; i++) {
            float matrix[2];
            matrix[0] = coins[i].x - striker.x;
            matrix[1] = coins[i].y - striker.y;
            float dist = sqrt((matrix[0] * matrix[0]) + (matrix[1] * matrix[1]));

            /*------------------------------ STRIKER-COIN COLLISION LOGIC ---------------------------------*/

            if ((dist * dist) <= ((striker.rad + coins[i].rad) * (striker.rad + coins[i].rad)) && flag[9][i] == 0) {
                
                float unit_vec[2], tangential_u[2], v1nf[2], v1tf[2], v2nf[2], v2tf[2], v1[2], v2[2], u1[2], u2[2];
                unit_vec[0] = matrix[0] / dist;
                unit_vec[1] = matrix[1] / dist;
                u1[0] = coins[i].vel_x;
                u1[1] = coins[i].vel_y;
                u2[0] = striker.vel_x;
                u2[1] = striker.vel_y;
                float u1n = unit_vec[0] * u1[0] + unit_vec[1] * u1[1];
                float u2n = unit_vec[0] * u2[0] + unit_vec[1] * u2[1];
                tangential_u[0]=-1*unit_vec[1];
                tangential_u[1]=unit_vec[0];
                float u1t = tangential_u[0] * u1[0] + tangential_u[1] * u1[1];
                float u2t = tangential_u[0] * u2[0] + tangential_u[1] * u2[1];    
                float v1n = (u1n * (coins[i].mass - striker.mass)+ (2 * striker.mass * u2n))/(coins[i].mass + striker.mass);
                float v2n = (u2n * (striker.mass - coins[i].mass)+ (2 * coins[i].mass * u1n))/(coins[i].mass + striker.mass);
                v1nf[0] = v1n * unit_vec[0];
                v1tf[0] = u1t * tangential_u[0];
                v2nf[0] = v2n * unit_vec[0];
                v2tf[0] = u2t * tangential_u[0];
                v1nf[1] = v1n * unit_vec[1];
                v1tf[1] = u1t * tangential_u[1];
                v2nf[1] = v2n * unit_vec[1];
                v2tf[1] = u2t * tangential_u[1];
                v1[0] = v1nf[0] + v1tf[0];
                v1[1] = v1nf[1] + v1tf[1];
                v2[0] = v2nf[0] + v2tf[0];
                v2[1] = v2nf[1] + v2tf[1];
                coins[i].vel_x = v1[0];
                coins[i].vel_y = v1[1];
                striker.vel_x = v2[0];
                striker.vel_y = v2[1];
                coins[i].x += coins[i].vel_x;
                coins[i].y += coins[i].vel_y;
                striker.x += striker.vel_x;
                striker.y += striker.vel_y;
                flag[9][i] = 1;
            }                
            else if ((dist * dist) > ((striker.rad + coins[i].rad) * (striker.rad + coins[i].rad))) {
                flag[9][i] = 0;
            }            
            for (j = i+1 ; j < 9 ; j++) {

                if (i != j) {

                  /*------------------------------ COIN-COIN COLLISION LOGIC ---------------------------------*/

                    matrix[0] = coins[i].x - coins[j].x;
                    matrix[1] = coins[i].y - coins[j].y;
                    float dist = sqrt((matrix[0] * matrix[0]) + (matrix[1] * matrix[1]));
                    if ((dist * dist) <= ((coins[i].rad + coins[i].rad) * (coins[j].rad + coins[i].rad)) && flag[i][j] == 0) {
                        
                        float unit_vec[2], tangential_u[2], v1nf[2], v1tf[2], v2nf[2], v2tf[2], v1[2], v2[2], u1[2], u2[2];
                        unit_vec[0] = matrix[0] / dist;
                        unit_vec[1] = matrix[1] / dist;
                        u1[0] = coins[i].vel_x;
                        u1[1] = coins[i].vel_y;
                        u2[0] = coins[j].vel_x;
                        u2[1] = coins[j].vel_y;
                        float u1n = unit_vec[0] * u1[0] + unit_vec[1] * u1[1];
                        float u2n = unit_vec[0] * u2[0] + unit_vec[1] * u2[1];
                        tangential_u[0]=-1*unit_vec[1];
                        tangential_u[1]=unit_vec[0];
                        float u1t = tangential_u[0] * u1[0] + tangential_u[1] * u1[1];
                        float u2t = tangential_u[0] * u2[0] + tangential_u[1] * u2[1];    
                        float v1n = (u1n * (coins[i].mass - coins[j].mass) + (2 * coins[j].mass * u2n)) / (coins[i].mass + coins[j].mass);
                        float v2n = (u2n * (coins[j].mass - coins[i].mass) + (2 * coins[i].mass * u1n)) / (coins[i].mass + coins[j].mass);
                        v1nf[0] = v1n * unit_vec[0];
                        v2nf[0] = v2n * unit_vec[0];
                        v1tf[0] = u1t * tangential_u[0];
                        v2tf[0] = u2t * tangential_u[0];
                        v1nf[1] = v1n * unit_vec[1];
                        v1tf[1] = u1t * tangential_u[1];
                        v2nf[1] = v2n * unit_vec[1];
                        v2tf[1] = u2t * tangential_u[1];
                        v1[0] = v1nf[0] + v1tf[0];
                        v1[1] = v1nf[1] + v1tf[1];
                        v2[0] = v2nf[0] + v2tf[0];
                        v2[1] = v2nf[1] + v2tf[1];
                        coins[i].vel_x = v1[0];
                        coins[i].vel_y = v1[1];
                        coins[j].vel_x = v2[0];
                        coins[j].vel_y = v2[1];
                        coins[i].x += coins[i].vel_x;
                        coins[i].y += coins[i].vel_y;
                        coins[j].x += coins[j].vel_x;
                        coins[j].y += coins[j].vel_y;
                        flag[i][j] = 1;
                    } 
                    else if ((dist * dist) > ((coins[i].rad + coins[i].rad) * (coins[j].rad + coins[i].rad))) {
                        flag[i][j] = 0;
                    }
                }
            }
            if(((coins[i].x + coins[i].rad > (box_len)) && coins[i].vel_x > 0) || (((coins[i].x - coins[i].rad < (-box_len)) && coins[i].vel_x < 0))) {
                coins[i].vel_x *= -alpha;
                coins[i].vel_y *= alpha;
            }
            if(((coins[i].y + coins[i].rad > box_len) && coins[i].vel_y > 0) || (((coins[i].y - coins[i].rad < -box_len) && coins[i].vel_y < 0))) {
                coins[i].vel_y *= -alpha;
                coins[i].vel_x *= alpha;
            }
            //STRIKER INTO POCKETS
            if((striker.x > 4.71 && striker.y > 4.71) || (striker.x > 4.71 && striker.y < -4.71) || (striker.x < -4.71 && striker.y < -4.71) || (striker.x < -4.71 && striker.y > 4.71)) {
                striker.y = -4.0f;
                striker.x = 1.0f;
                flag_space_hit = 0;
                score -= 10;
                reset = 1;
                for (i = 0; i < 9; i++) {
                    coins[i].vel_x = 0;
                    coins[i].vel_y = 0;
                }
            }
            coins[i].vel_x -= coins[i].vel_x * 0.01f;
            coins[i].vel_y -= coins[i].vel_y * 0.01f;
            coins[i].x += coins[i].vel_x;
            coins[i].y += coins[i].vel_y;
            if((coins[i].x > 4.71 && coins[i].y > 4.71) || (coins[i].x > 4.71 && coins[i].y < -4.71) || (coins[i].x < -4.71 && coins[i].y < -4.71) || (coins[i].x < -4.71 && coins[i].y > 4.71)) {
                coins[i].vel_x = 0;
                coins[i].vel_y = 0;
                coins[i].x =  -8;
                //cout << "Coin " << i << " has been pocketed" << endl;
                coins[i].y = 5 - coin_count;
                if (i < 4 && color == -1)
                    color = 0;
                if (i >= 4 && i < 8 && color == -1)
                    color = 1;
                coin_count--;
                if (coin_count == 0) {
                    coin_count--;
                    striker.y = -4.0f;
                    striker.x = 1.0f;
                    flag_space_hit = 0;
                    reset = 1;
                }
                if (i == 8) {
                    score += 50;
                    white_count++;
                    black_count++;
                }
                if (color == 0) {
                    if (i < 4) {
                        score += 10;
                        black_count++;
                    }
                    else if (i >= 4 && i < 8)
                        score -= 5;
                }
                else if (color == 1) {
                    if (i < 4)
                        score -= 5;
                    else if (i >= 4 && i < 8) {
                        score += 10;
                        white_count++;
                    }
                }
            }
            if (white_count == 5 || black_count == 5) {
                coin_count = 0;
            }
        }
        striker.x += 2 * striker.vel_x;
        striker.y += 2 * striker.vel_y;
        striker.vel_y -= striker.vel_y * 0.01f;
        striker.vel_x -= striker.vel_x * 0.01f;

    }
    int all_stopped = 0, i;
    for (i = 0; i < 9; i++) {
        if (abs(coins[i].vel_x) < 0.0002f && abs(coins[i].vel_y < 0.0002f)) {
            all_stopped = 1;
        }
        else {
            all_stopped = 0;
        }
    }

    if (abs(striker.vel_x) < 0.002f && abs(striker.vel_y) < 0.002f && all_stopped == 1) {
        if (reset == 0) {
            for (i = 0; i < 9; i++) {
                coins[i].vel_x = 0;
                coins[i].vel_y = 0;
            }
            striker.y = -4.0f;
            striker.x = 1.0f;
            flag_space_hit = 0;
            reset = 1;
        }
    }
    if (timer % 100 == 0 && timer != 0)
        score--;
    glutTimerFunc(10, update, 0);
}

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawSquare(float len) {
   
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void fillSquare(float len) {
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
}

void drawRect(float l, float b) {
   
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-l / 2, -b / 2);
    glVertex2f(l / 2, -b / 2);
    glVertex2f(l / 2, b / 2);
    glVertex2f(-l / 2, b / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawRectFill(float l, float b, float x, float y, int color) {
   
    glBegin(GL_QUADS);
    if (color == 1) // Red
        glColor3d(1.0f, 0, 0);
    if (color == 2) // Orange
        glColor3d(1.0f, 0.3f, 0);
    if (color == 3) // Green
        glColor3d(0, 1.0f, 0);
    glVertex2f(x, y);
    glVertex2f(x + l, y);
    glVertex2f(x + l, y + b);
    glVertex2f(x, y + b);
    glEnd();
}

void drawBall(float rad) {
    
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void drawTriangle() {

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.847059f, 0.847059f, 0.74902f, 1.0f);   // Setting a background color
    //glClearColor(0.91f, 0.76f, 0.65f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }

    if (key == 97 || key == 65) { // press 'a' key
        if (flag_space_hit == 0) {
            striker_angle -= 5.0f;
        }
    }

    if (key == 99 || key == 67) { //press 'c' key
        if (flag_space_hit == 0) {
            striker_angle += 5.0f;
        }
    }
    if (key == 32 && flag_space_hit == 0) {
        striker.vel_y = 0.12 * (power_y / 1.2f);
        striker.vel_x = 0.12 * (power_y / 1.2f);
        striker.vel_x = striker.vel_x * sin(DEG2RAD(striker_angle));
        striker.vel_y = striker.vel_y * cos(DEG2RAD(striker_angle));
        flag_space_hit = 1;
        reset = 0;
    }
}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT && (striker.x - 0.1 > (-1 * (box_len - 2*holes_radius - 1.05f)))){
        if (flag_space_hit == 0) {
            striker.x -= 0.1;
        }
    }
    if (key == GLUT_KEY_RIGHT && (striker.x + 0.1 < (box_len - 2*holes_radius - 1.05f))) {
        if (flag_space_hit == 0) {
            striker.x += 0.1;
        }
    }
    if (key == GLUT_KEY_UP)
        power_y += 0.04;
    if (key == GLUT_KEY_DOWN)
        power_y -= 0.04;
    if (power_y < 0)
        power_y = 0;
    if (power_y > 1.2f)
        power_y = 1.2f;
}

void handleMouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN)
    {
        if(button == GLUT_RIGHT_BUTTON) {
            drag_flag = 1;
        }

        if(button == GLUT_LEFT_BUTTON)
        {
            if (flag_space_hit == 0) {
                int ww = glutGet(GLUT_WINDOW_WIDTH);
                int wh = glutGet(GLUT_WINDOW_HEIGHT);
                float hw = (float)ww/2;
                float hh = (float)wh/2;
                float xx = ((float)x - hw)/hw * 8;
                float yy = ((float)y - hh)/-hh * 8;
                //cout << xx << ", " << yy << endl;

                float dist = sqrt((xx - striker.x) * (xx - striker.x) + (yy - striker.y) * (yy - striker.y));
                striker_angle = atan2((xx - striker.x) , (yy - striker.y)) * 50;
                striker.vel_x = 0.12 * dist / 8;
                striker.vel_y = 0.12 * dist / 8;
                //cout << dist << endl;
            }
        }
    }

    if(state == GLUT_UP)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            if (flag_space_hit == 0) {
                //cout << striker_angle << endl;
                striker.vel_x = striker.vel_x * sin(DEG2RAD(striker_angle));
                striker.vel_y = striker.vel_y * cos(DEG2RAD(striker_angle));
                flag_space_hit = 1;
                reset = 0;
            }
        }

        if(button == GLUT_RIGHT_BUTTON)
        {
            drag_flag = 0;
        }
    }
}


void mouse_motion(int x,int y)
{

    int width = glutGet(GLUT_WINDOW_WIDTH);
    float offset = 2 * ((float)x - (width / 2))/width;
        if(drag_flag && (striker.x + 0.1 < (box_len - 2*holes_radius - 1.05f))  && (striker.x - 0.1 > (-1 * (box_len - 2*holes_radius - 1.05f))))
        {
            striker.x = offset * 10; 
        }

        if (drag_flag && (striker.x + 0.1 >= (box_len - 2*holes_radius - 1.05f)) && offset < (((box_len - 2*holes_radius - 1.0f)) / 10))
            striker.x = offset * 10;

        if (drag_flag && (striker.x - 0.1 <= (-1 * (box_len - 2*holes_radius - 1.05f))) && offset > (-1 * (box_len - 2*holes_radius - 1.0f)) / 10)
            striker.x = offset * 10;

        if (striker.x + 0.1 >= (box_len - 2*holes_radius - 1.05f))
            striker.x = box_len - 2*holes_radius - 1.05f;
        if (striker.x - 0.1 <= (-1 * (box_len - 2*holes_radius - 1.05f)))
            striker.x = -1 * (box_len - 2*holes_radius - 1.05f);
}