#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <SFML/OpenGL.hpp>
#include <GL/glut.h>

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>


// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

void resizeGL( int w, int h ) {
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 120.0, (GLdouble)w/(GLdouble)h, 0.5, 500.0 );
    glMatrixMode( GL_MODELVIEW );
}

void computePos(float deltaMove) {

    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

int main(int argc, char **argv) {

    sf::RenderWindow window( sf::VideoMode(800,600,32), "SFML OpenGL" );

    // init GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glEnable(GL_DEPTH_TEST);

    sf::Text testtext;

    testtext.setString("werwer");

    while( window.isOpen() ) {
        sf::Event event;
        while( window.pollEvent( event ) ) {
            if( event.type==sf::Event::Closed )
                window.close();
        }
        window.setActive();

        deltaAngle = 0.0f, deltaMove = 0.0f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) deltaAngle = -0.01f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) deltaAngle = 0.01f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) deltaMove = 1.0f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) deltaMove = -1.0f;

        computeDir(deltaAngle);
        computePos(deltaMove);

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(50.0, 1.0, 1.0, 70.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(  x, 1.0f, z,//eye's position
                    x+lx, 1.0f,  z+lz,//where the eye is looking (point)
                    0.0f, 1.0f,  0.0f);//translations

        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_QUADS);
            glVertex3f(-10.0f, 0.0f, -10.0f);
            glVertex3f(-10.0f, 0.0f,  10.0f);
            glVertex3f( 10.0f, 0.0f,  10.0f);
            glVertex3f( 10.0f, 0.0f, -10.0f);
        glEnd();

        glColor3f(0.4f, 0.4f, 0.4f);
        glTranslatef(0,2,0);
        glutSolidTeapot(.5);

        window.pushGLStates();
        window.draw(testtext);
        window.popGLStates();

        window.display();

    }
    return 1;
}