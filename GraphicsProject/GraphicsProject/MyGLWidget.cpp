/***************************************************/
/* Author: Aaron Derstine                          */
/* Course: COMP 361, Computer Graphics             */
/* Date:   Feburary 10, 2014                       */
/* Name:   MyGLWidget.cpp                          */
/* Description: This file defines the widget that  */
/*         renders the OpenGL objects              */
/***************************************************/

#include "MyGLWidget.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Geometry.h"
#include <QtWidgets/QMessageBox>
#include "GraphicsProject.h"

MyGLWidget::MyGLWidget(QWidget* parent) : QGLWidget(parent) 
{
   sceneGraph      = NULL;
   camera          = NULL;
   light           = NULL;
   geometryBuilder = new GeometryBuilder;
   lightGeometry   = geometryBuilder->buildCube();
   //lightGeometry   = NULL;
   highlightSelected = false;
   resetTextFields();
}

MyGLWidget::~MyGLWidget()
{
   if (sceneGraph)      delete sceneGraph;
   if (camera)          delete camera;
   if (light)           delete light;
   if (geometryBuilder) delete geometryBuilder;

   glDeleteBuffers(1, &vbo);
   glDeleteBuffers(1, &cbo);
   glDeleteBuffers(1, &ibo);
   glDeleteBuffers(1, &nbo);

   glDetachShader(shaderProgram, vertexShader);
   glDetachShader(shaderProgram, fragmentShader);
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   glDeleteProgram(shaderProgram);
}

void MyGLWidget::initializeGL() 
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0);

   // generate the buffers for verticies and colors
   glGenBuffers(1, &vbo);
   Geometry::setVBO(vbo);
   glGenBuffers(1, &nbo);
   Geometry::setNBO(nbo);
   glGenBuffers(1, &cbo);
   Geometry::setCBO(cbo);
   glGenBuffers(1, &ibo);
   Geometry::setIBO(ibo);

   // create the shaders
   const char *vertexSource   = textFileRead("lambert.vert");
	const char *fragmentSource = textFileRead("lambert.frag");
   vertexShader   = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram  = glCreateProgram();
	glShaderSource (vertexShader,   1, &vertexSource,   0);
	glShaderSource (fragmentShader, 1, &fragmentSource, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram (shaderProgram);

	vLocation = glGetAttribLocation(shaderProgram, "vs_position");
   Geometry::setVLocation(vLocation);
   cLocation = glGetAttribLocation(shaderProgram, "vs_color");
   Geometry::setCLocation(cLocation);
   nLocation = glGetAttribLocation(shaderProgram, "vs_normal");
   Geometry::setNLocation(nLocation);

   u_projLocation   = glGetUniformLocation(shaderProgram, "u_projMatrix");
   u_modelLocation  = glGetUniformLocation(shaderProgram, "u_modelMatrix");
   u_lightPos       = glGetUniformLocation(shaderProgram, "u_lightPos");
   u_cameraLocation = glGetUniformLocation(shaderProgram, "u_cameraMatrix");
   
   // for indicating which geometry is selected
   u_selected = glGetUniformLocation(shaderProgram, "u_selected");
   glUniform1f(u_selected, 0.0f);
   Geometry::setUSelectedLocation(u_selected);

   Geometry::setUModelLocation(u_modelLocation);
   LightSource::setULightLocation(u_lightPos);
   Camera::setUCameraLocation(u_cameraLocation);

   glUseProgram(shaderProgram);

   // set up attribute arrays and pointers
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(vLocation);
	glVertexAttribPointer(vLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

   glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(cLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

   glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glEnableVertexAttribArray(nLocation);
	glVertexAttribPointer(nLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);	
}

void MyGLWidget::paintGL() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render the scene
   if (light)       light->render();
   if (sceneGraph)  sceneGraph->render();
}

void MyGLWidget::config(QString &configFileText)
{
   // if this is not the first time delete the old data
   if (sceneGraph)  delete sceneGraph;  sceneGraph  = NULL;
   if (camera)      delete camera;      camera      = NULL;
   if (light)       delete light;       light       = NULL;

   // create the light source
   light = new LightSource(lightGeometry);

   // create a scene
   sceneGraph = new SceneGraph(this, geometryBuilder);

   // pass in the config file to the scene graph
   sceneGraph->build(configFileText);

   // center the camera in the middle of the room
   // by default look from 7 units away down the z axis and tilt up a bit
   camera = new Camera(glm::vec3(0.0, 4.0, 6.0), sceneGraph->getCenterOfRoom(), glm::vec3(0.0, 1.0, 0.0));
}

void MyGLWidget::resizeGL(int width, int height) 
{
	glViewport(0, 0, width, height);

	//create the projection matrix
	glm::mat4 projection = glm::perspective(90.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 30.0f);

   glUniformMatrix4fv(u_projLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void MyGLWidget::cameraZoomChanged(Camera::MoveDirection direction)
{
   if (direction == Camera::NONE) return;   
   if (direction == Camera::UP)
   {
      camera->zoom(-0.1);
   }
   else if (direction == Camera::DOWN)
   {
      camera->zoom(0.1);
   }
   this->updateGL();
}

void MyGLWidget::cameraRotateLRChanged(Camera::MoveDirection direction)
{
   if (direction == Camera::NONE) return; 
   if (direction == Camera::LEFT)
   {
      camera->rotateYaw(-1.0);
   }
   else if (direction == Camera::RIGHT)
   {
      camera->rotateYaw(1.0);
   }
   this->updateGL();
}

void MyGLWidget::cameraRotateUDChanged(Camera::MoveDirection direction)
{
   if (direction == Camera::NONE) return;  
   if (direction == Camera::DOWN)
   {
      camera->rotatePitch(-1.0);
   }
   else if (direction == Camera::UP)
   {
      camera->rotatePitch(1.0);
   }
   this->updateGL();
}

void MyGLWidget::lightZChanged(Camera::MoveDirection direction)
{
   if (direction == Camera::NONE) return;   
   if (direction == Camera::UP)
   {
      light->changeZ(-0.5);
   }
   else if (direction == Camera::DOWN)
   {
      light->changeZ(0.5);
   }
   this->updateGL();
}

void MyGLWidget::lightXChanged(Camera::MoveDirection direction)
{
   if (direction == Camera::NONE) return; 
   if (direction == Camera::LEFT)
   {
      light->changeX(-0.5);
   }
   else if (direction == Camera::RIGHT)
   {
      light->changeX(0.5);
   }
   this->updateGL();
}

void MyGLWidget::lightYChanged(Camera::MoveDirection direction)
{
   if (direction == Camera::NONE) return;   
   if (direction == Camera::UP)
   {
      light->changeY(0.5);
   }
   else if (direction == Camera::DOWN)
   {
      light->changeY(-0.5);
   }
   this->updateGL();
}

void MyGLWidget::selectNext()
{
   //QMessageBox::critical(this, "Error", "Next");
   if (!sceneGraph || !highlightSelected) return;
   resetTextFields();
   Node *node = sceneGraph->getSelected();
   node->setSelected(false);
   sceneGraph->selectNext();
   node = sceneGraph->getSelected();
   node->setSelected(true);
   updateGL();
}

void MyGLWidget::selectPrev()
{
   //QMessageBox::critical(this, "Error", "Prev");
   if (!sceneGraph || !highlightSelected) return;
   resetTextFields();
   Node *node = sceneGraph->getSelected();
   node->setSelected(false);
   sceneGraph->selectPrev();
   node = sceneGraph->getSelected();
   node->setSelected(true);
   updateGL();
}

void MyGLWidget::subdivide()
{
   if (!sceneGraph || !highlightSelected) return;
   Node *node = sceneGraph->getSelected();
   sceneGraph->subdivide(node);
   updateGL();   
}

void MyGLWidget::showSelected(bool checked)
{
   highlightSelected = checked;
   if (!sceneGraph) return;
   Node *node = sceneGraph->getSelected();
   node->setSelected(checked);
   updateGL();
}

void MyGLWidget::transform()
{
   if (!sceneGraph || !highlightSelected) return;
   GraphicsProject *proj = dynamic_cast<GraphicsProject*>(this->parentWidget()->parentWidget());
   if (proj == NULL) return;

   Ui::GraphicsProjectClass *ui = proj->getUi();
   Node *node = sceneGraph->getSelected();
   float rotX = ui->rotXEdit->text().toFloat();
   float rotY = ui->rotYEdit->text().toFloat();
   float rotZ = ui->rotZEdit->text().toFloat();
   // had to switch x and z for some reason
   node->rotate(rotX, glm::vec3(0.0,0.0,1.0));
   node->rotate(rotY, glm::vec3(0.0,1.0,0.0));
   node->rotate(rotZ, glm::vec3(1.0,0.0,0.0));

   float scaleX = ui->scaleXEdit->text().toFloat();
   float scaleY = ui->scaleYEdit->text().toFloat();
   float scaleZ = ui->scaleZEdit->text().toFloat();
   scaleX = (scaleX < .001) ? .001 : scaleX;
   scaleY = (scaleY < .001) ? .001 : scaleY;
   scaleZ = (scaleZ < .001) ? .001 : scaleZ;
   node->scale(glm::vec3(scaleX, scaleY, scaleZ));

   float transX = ui->transXEdit->text().toFloat();
   float transY = ui->transYEdit->text().toFloat();
   float transZ = ui->transZEdit->text().toFloat();
   node->translate(glm::vec3(transX, transY, transZ));

   Color::Color newColor = (Color::Color)ui->colorPicker->currentIndex();
   if (newColor != Color::TEST) node->setGeometryColor(newColor);
   
   updateGL();
}

void MyGLWidget::resetTextFields()
{
   GraphicsProject *proj = dynamic_cast<GraphicsProject*>(this->parentWidget()->parentWidget());
   if (proj == NULL) return;

   Ui::GraphicsProjectClass *ui = proj->getUi();
   ui->rotXEdit->setText("0");
   ui->rotYEdit->setText("0");
   ui->rotZEdit->setText("0");

   ui->scaleXEdit->setText("1");
   ui->scaleYEdit->setText("1");
   ui->scaleZEdit->setText("1");

   ui->transXEdit->setText("0");
   ui->transYEdit->setText("0");
   ui->transZEdit->setText("0");

   ui->colorPicker->setCurrentIndex(0);
}

void MyGLWidget::raytrace()
{
   if (!sceneGraph) return;
}

//from swiftless.com
char* MyGLWidget::textFileRead(const char* fileName) 
{
    char* text;
    
    if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");
        
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
            }
            fclose(file);
        }
    }
    return text;
}
