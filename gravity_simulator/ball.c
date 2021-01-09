#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

#define B_Max 2     //ボールの数
#define L_Max 1     //脚の数
#define G 9.80665   //重力加速度
#define Lwall -40   //左の壁
#define Rwall 40    //右の壁
#define ceiling 60  //天井
#define bed -30     //床
#define Hanpatu 0.8 //反発係数
#define Masatu 0.9  //摩擦力

int u = 0;
int syu = 0; //周回数
int bow = 0;
double h = 0.00001;  //フレーム
double width[B_Max]; //壁判定
double B_touch;
double L_touch[B_Max];
double height[B_Max];
int number = 0;
double Dt = 0;
double Time = 0;
int flag[B_Max] = {};
double F = 10;
double tilt[L_Max];
double segment[L_Max];
double Q[L_Max], P[L_Max], q[L_Max], p[L_Max], d[L_Max];

/*
static GLfloat	ang[B_Max];//角度移動
static GLfloat	a[B_Max];//横移動
static GLfloat	b[B_Max];//縦移動
*/
static GLfloat dt = 0.1; //速度制御

//ボールの構造体
struct ball
{
    int id;                 //番号
    double r;               //半径
    double m;               //質量
    double l;               //慣性	d/dt(mv)
    double x, y, tht;       //ボールの位置、高さ、角度
    double dx, dy, dtht;    //ボールの横移動速度、縦移動速度、角速度
    double ddx, ddy, ddtht; //ボールの横移動加速度、縦移動加速度、角加速度
};

struct ball BALL[B_Max];

//脚の構造体
struct leg
{
    int id;                            //番号
    double base_point_x, base_point_y; //支点
    double move_point_x, move_point_y; //力点
    double longer;                     //脚の長さ
    double r;
    double tht;   //初期角度
    double force; //威力
};

struct leg LEG[L_Max];

//壁の初期判定
void start(void)
{
    for (number = 0; number < B_Max; number++)
    {
        width[B_Max] = 2;
    }
}

//ボールの情報操作
void make_ball(void)
{

    for (number = 0; number < B_Max; number++)
    {
        srand((int)time(NULL));

        BALL[number].id = number + 1;

        BALL[number].r = 3 + number;
        BALL[number].m = 0.02;
        BALL[number].l = 0;
        BALL[number].x = 10 + number * 10;
        BALL[number].y = 10;
        BALL[number].tht = 45 + 180;
        BALL[number].dx = 0;
        BALL[number].dy = BALL[number].m * -G;
        BALL[number].dtht = 3;

        u++;
    }
}

//脚の情報操作
void make_leg(void)
{
    double leg_x, leg_y;

    for (number = 0; number < L_Max; number++)
    {
        srand((int)time(NULL));

        LEG[number].id = number + 1;

        LEG[number].base_point_x = 0;
        LEG[number].base_point_y = 0;
        LEG[number].move_point_x = 20;
        LEG[number].move_point_y = 20;
        leg_x = LEG[number].base_point_x - LEG[number].move_point_x;

        if (leg_x < 0)
        {
            leg_x = -leg_x;
        }

        leg_y = LEG[number].base_point_y - LEG[number].move_point_y;

        if (leg_y < 0)
        {
            leg_y = -leg_y;
        }
        LEG[number].r = 3;
        LEG[number].tht = 10;
        LEG[number].force = 2;
    }
}

//表示操作
void display(void)
{
    double i, x[number], y[number], circleAng;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    /*//天井
	glBegin(GL_LINES);
	glVertex2d(Lwall,ceiling);
	glVertex2d(Rwall,ceiling);
	glEnd();*/
    //床
    glBegin(GL_LINES);
    glVertex2d(Lwall, bed);
    glVertex2d(Rwall, bed);
    glEnd();
    //右壁
    glBegin(GL_LINES);
    glVertex2d(Rwall, ceiling);
    glVertex2d(Rwall, bed);
    glEnd();
    //左壁
    glBegin(GL_LINES);
    glVertex2d(Lwall, ceiling);
    glVertex2d(Lwall, bed);
    glEnd();
    /*
	//脚
	for(number = 0;number < L_Max;number++)
	{
		glPushMatrix();
		glTranslatef(LEG[number].move_point_x, LEG[number].move_point_y, 0.0);
		glRotatef(LEG[number].tht, 0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2d(LEG[number].base_point_x, LEG[number].base_point_y);
		glVertex2d(LEG[number].move_point_x, LEG[number].move_point_y);
		for(i = 0;i < 360;i++)
		{
			circleAng	= i * 3.141592 / 180;
			x[number]	= sin(circleAng) * LEG[number].r;
			y[number]	= cos(circleAng) * LEG[number].r;
			glVertex2d(x[number] + LEG[number].move_point_x, LEG[number].move_point_y + y[number]);
		}
		glEnd();
		glPopMatrix();
	}
*/
    //玉
    for (number = 0; number < B_Max; number++)
    {
        glPushMatrix();
        glTranslatef(BALL[number].x, BALL[number].y, 0.0);
        glRotatef(BALL[number].tht, 0.0, 0.0, 1.0);
        glBegin(GL_POLYGON); //LINE_LOOP);
        for (i = 0; i < /*90*/ 360; i++)
        {
            circleAng = i * 3.141592 / 180;
            x[number] = sin(circleAng) * BALL[number].r;
            y[number] = cos(circleAng) * BALL[number].r;
            glVertex2d(x[number], y[number]);
        }
        //回転確認
        /*		for(i = 90;i < 110;i++)
		{
			glVertex2d(0, 0);
		}
		for(i = 110;i < 360;i++)
		{
			circleAng	= i * 3.141592 / 180;
			x[number]	= sin(circleAng) * BALL[number].r;
			y[number]	= cos(circleAng) * BALL[number].r;
			glVertex2d(x[number], y[number]);
		}*/
        glEnd();
        glPopMatrix();
    }
    glutSwapBuffers();
}
/*
//kick
void kick(int dd)
{

	L_touch[dd]	= pow(pow(LEG[0].move_point_x - BALL[dd].x, 2.0) + pow(LEG[0].move_point_y - BALL[dd].y, 2.0), 0.5);

	//ball同士のあたり判定
	if(L_touch[dd] <= LEG[0].r + BALL[dd].r)
	{
		if(width[dd] == 0||width[dd] == 2)
		{
			width[dd]	= 1;
			BALL[dd].ddx	= BALL[dd].ddx + LEG[0].force * cos(LEG[0].tht * 3.141592 / 180) * h;
			BALL[dd].ddy	= BALL[dd].ddy + LEG[0].force * sin(LEG[0].tht * 3.141592 / 180) * h;
		}

		else
		{
			//width[number]	= 0;
		}

	}


}
*/
//物理演算
void simu_1(void)
{
    int gg, ggg;

    //ボールの判定
    for (number = 0; number < B_Max; number++)
    {

        B_touch = pow(pow(BALL[0].x - BALL[1].x, 2.0) + pow(BALL[0].y - BALL[1].y, 2.0), 0.5);

        //kick
        //		kick(number);

        //ball同士のあたり判定
        if (B_touch <= BALL[0].r + BALL[1].r)
        {
            if (width[number] == 0 || width[number] == 2)
            {
                width[number] = 1;
            }

            else
            {
                width[number] = 0;
            }
        }

        //初期入力
        if (syu == 0)
        {
            BALL[number].ddx = BALL[number].dx * h;
            BALL[number].ddy = BALL[number].dy * h;
            BALL[number].ddtht = BALL[number].dtht * 0.5;
        }

        //右壁判定
        if (BALL[number].x >= Rwall - BALL[number].r)
        {
            width[number] = 0;
        }

        //左壁判定
        if (BALL[number].x <= BALL[number].r + Lwall)
        {
            width[number] = 1;
        }

        //右移動
        if (width[number] == 0 || width[number] == 2)
        {
            BALL[number].x = BALL[number].x + BALL[number].ddx;

            if (flag[number] != 2)
            {
                BALL[number].tht = BALL[number].tht + BALL[number].ddtht;
            }

            if (BALL[number].tht > 360.0)
            {
                BALL[number].tht = 0;
            }
        }

        //左移動
        else if (width[number] == 1)
        {
            BALL[number].x = BALL[number].x - BALL[number].ddx;
            if (flag[number] != 2)
            {
                BALL[number].tht = BALL[number].tht - BALL[number].ddtht;
            }
            if (BALL[number].tht < 0.0)
            {
                BALL[number].tht = 360.0;
            }
        }

        //床との衝突
        if (BALL[number].y <= bed + BALL[number].r)
        {
            BALL[number].ddy = -BALL[number].dy * Hanpatu;
            BALL[number].dy = BALL[number].dy * Hanpatu;
            BALL[number].ddx = BALL[number].dy * cos(BALL[number].dtht * 3.141592 / 180);
            BALL[number].ddtht = BALL[number].ddtht - BALL[number].ddtht * 0.1;
        }

        else
        {
            BALL[number].ddy = BALL[number].ddy - G * h;
        }

        BALL[number].y = BALL[number].y + BALL[number].ddy;

        glutPostRedisplay();

        //周回判定
        flag[number] = 1;
    }

    //周回数
    syu++;
}
/*
void simu_2(void)
{
	simu_1();
	//脚の回転
	if(LEG[0].tht < 270&&LEG[0].tht > 0)
	{
		LEG[0].tht	= LEG[0].tht + 0.1;
	}
	glutPostRedisplay();

}
*/
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(simu_1);
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(NULL); //simu_2);
        }
        break;
    default:
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '\x1b')
    {
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    start();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 1200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    make_ball();
    make_leg();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
