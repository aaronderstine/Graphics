/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   MyGLWidget.h                            */
/* Description: This file defines the widget that  */
/*         renders the OpenGL objects              */
/***************************************************/

#pragma once
#define GLEW_STATIC
#include "glew.h"
#include "glm/glm.hpp"
#include <QGLWidget>
#include <stdlib.h>
#include "SceneGraph.h"
#include "CameraSlider.h"
#include "Camera.h"
#include "LightSource.h"
#include "GeometryBuilder.h"

class MyGLWidget : public QGLWidget
{
   Q_OBJECT
public:
	MyGLWidget(QWidget *parent);
	~MyGLWidget();

   // This virtual function is called once before the first call to paintGL() or resizeGL(), 
   // and then once whenever the widget has been assigned a new QGLContext.
   // This function should set up any required OpenGL context rendering flags, defining display lists, etc.
	void initializeGL();

   // This virtual function is called whenever the widget needs to be painted.
	void paintGL();

   // This virtual function is called whenever the widget has been resized. The new size is passed in width and height.
	void resizeGL(int width, int height);

   // creates the scene graph with the config file passed in as a string
   void config(QString &configFileText);

	// helper function to read shader source and put it in a char array
	// thanks to Swiftless.com
	char* textFileRead(const char* fileName);

   public slots:
      void cameraZoomChanged(Camera::MoveDirection direction);
      void cameraRotateLRChanged(Camera::MoveDirection direction);
      void cameraRotateUDChanged(Camera::MoveDirection direction);

      // transformations
      void selectNext();
      void selectPrev();
      void subdivide();
      void showSelected(bool checked);
      void transform();
      void raytrace();

      // reuse the camera slider to control the light
      void lightZChanged(Camera::MoveDirection direction);
      void lightXChanged(Camera::MoveDirection direction);
      void lightYChanged(Camera::MoveDirection direction);

private:
   SceneGraph      *sceneGraph;
   Camera          *camera;
   LightSource     *light;
   GeometryBuilder *geometryBuilder;
   Geometry        *lightGeometry;

   bool highlightSelected;

   void resetTextFields();

   // shader handles
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

   // vertex buffer handles
	GLuint vbo;
	GLuint vLocation;
   // color buffer handles
   GLuint cbo;
   GLuint cLocation;
   // normal buffer handles
   GLuint nbo;
   GLuint nLocation;
   // index buffer handle
   GLuint ibo;

   GLuint meshvbo;
   GLuint meshnbo;
   GLuint meshcbo;

   // uniform handles
	GLuint u_projLocation;
   GLuint u_modelLocation;
   GLuint u_lightPos;
   GLuint u_cameraLocation;
   GLuint u_selected;
};

