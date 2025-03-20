/*
Práctica 5: Optimización y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Model Goddard_M;
Model cola;
Model prueba2;
Model cuerpo;
Model cabeza;
Model mandibula;
Model pata1;
Model pata2;
Model pata3;
Model pata4;
Model coche;
Model carroceria;
Model rueda1;
Model rueda2;
Model rueda3;
Model rueda4;
Model cofre;
Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	cola = Model();
	prueba2 = Model();
	Goddard_M = Model();
	cuerpo = Model();
	cabeza = Model();
	mandibula = Model();
	pata1 = Model();
	pata2 = Model();
	pata3 = Model();
	pata4 = Model();
	coche = Model();
	carroceria = Model();
	rueda1 = Model();
	rueda2 = Model();
	rueda3 = Model();
	rueda4 = Model();
	cofre = Model();
	carroceria.LoadModel("Models/carroceria.obj");
	rueda1.LoadModel("Models/Llanta1.obj");
	rueda2.LoadModel("Models/Llanta2.obj");
	rueda3.LoadModel("Models/Llanta3.obj");
	rueda4.LoadModel("Models/Llanta4.obj");
	cofre.LoadModel("Models/cofre.obj");
	coche.LoadModel("Models/cocheCompleto.obj");
	cola.LoadModel("Models/colaprueba.obj");
	cuerpo.LoadModel("Models/cuerpo.obj");
	cabeza.LoadModel("Models/cabeza.obj");
	mandibula.LoadModel("Models/mandibula.obj");
	pata1.LoadModel("Models/pata1.obj");
	pata2.LoadModel("Models/pata2.obj");
	pata3.LoadModel("Models/pata3.obj");
	pata4.LoadModel("Models/pata4.obj");
	prueba2.LoadModel("Models/sincolaprueba.obj");



	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();
		// ============== PRACTICA 5 COCHE ==============
	/*	1. - Importar su modelo de coche propio dentro del escenario a una escala adecuada.
		2. - Importar sus 4 llantas y acomodarlas jerárquicamente, agregar el mismo valor de rotación a las llantas para que al presionar puedan rotar hacia adelante y hacia atrás.
		3. - Importar el cofre del coche, acomodarlo jerárquicamente y agregar la rotación para poder abrir y cerrar.
		4. - Agregar traslación con teclado para que pueda avanzar y retroceder de forma independiente*/

		color = glm::vec3(0.10f, 0.10f, 0.44f); //Color del coche
		model = glm::mat4(1.0);
		//Inicio coche
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getarticulacion3()));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carroceria.RenderModel();
		
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		//Cofre
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.0f, 7.6f, -5.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cofre.RenderModel();
		model = modelaux;

		color = glm::vec3(0.0f, 1.0f, 1.0f);
		//Rueda 1 (VIENDO DESDE LA PARTE DE ENFRENTE DEL COCHE - DELANTERA DERECHA)
		modelaux = model;
		model = glm::translate(model, glm::vec3(-9.0f, 1.5f, -11.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rueda1.RenderModel();
		model = modelaux;

		//Rueda 2 (VIENDO DESDE LA PARTE DE ENFRENTE DEL COCHE - DELANTERA IZQUIERDA)
		modelaux = model;
		model = glm::translate(model, glm::vec3(9.0f, 1.5f, -11.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rueda2.RenderModel();
		model = modelaux;

		//Rueda 3 (VIENDO DESDE LA PARTE DE ENFRENTE DEL COCHE - TRASERA DERECHA)
		modelaux = model;
		model = glm::translate(model, glm::vec3(-9.0f, 1.5f, 10.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rueda3.RenderModel();
		model = modelaux;

		//Rueda 4 (VIENDO DESDE LA PARTE DE ENFRENTE DEL COCHE - TRASERA IZQUIERDA)
		modelaux = model;
		model = glm::translate(model, glm::vec3(9.0f, 1.5f, 10.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		rueda4.RenderModel();
		model = modelaux;

		// ================== EJERCICIO ===================
		/* 
		//------------*INICIA DIBUJO DE NUESTROS DEMÁS OBJETOS-------------------*
		//Goddard
		//Siguientes modelos
		// Ejercicio:
		//1.-  Importar por separado y agregar jerarquía:
		//		-Cuerpo
		//		-cabeza
		//		-Mandibula inferior
		//		- Cada una de las 4 patas como un solo modelo
		//2.- Hacer que al presionar una tecla cada pata pueda rotar un máximo de 45° "hacia adelante y hacia atrás"
		
		//Inicio
		//Cuerpo
		color = glm::vec3(0.0f, 0.0f, 0.0f); //modelo de goddard de color negro
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
		//modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Goddard_M.RenderModel();//modificar por el modelo sin las 4 patas y sin cola
		cuerpo.RenderModel();
		
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		//En sesión se separara una parte del modelo de Goddard y se unirá por jeraquía al cuerpo
		
		modelaux = model;
		//Cola
		model = glm::translate(model, glm::vec3(-1.5f, -0.5f, -0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cola.RenderModel();
		model = modelaux;

		//pata delantera derecha
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		modelaux = model;
		model = glm::translate(model, glm::vec3(1.0f, -0.6f, 0.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pata1.RenderModel();
		model = modelaux;

		// pata delantera izquierda
		color = glm::vec3(0.5f, 1.0f, 0.3f);
		modelaux = model;
		model = glm::translate(model, glm::vec3(1.0f, -0.6f, -0.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pata2.RenderModel();
		model = modelaux;
		//pata trasera derecha
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		modelaux = model;
		model = glm::translate(model, glm::vec3(-0.5f, -1.2f, 0.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pata4.RenderModel();
		model = modelaux;

		//pata trasera izquierda
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		modelaux = model;
		model = glm::translate(model, glm::vec3(-0.5f, -1.2f, -0.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pata3.RenderModel();
		model = modelaux;
		
		//Cabeza
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		modelaux = model;
		model = glm::translate(model, glm::vec3(1.4f, 0.5f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cabeza.RenderModel();
		model = modelaux;
		//Mandibula
		color = glm::vec3(0.0f, 0.5f, 1.0f);
		modelaux = model;
		model = glm::translate(model, glm::vec3(2.5f, 0.5f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mandibula.RenderModel();
		model = modelaux;
		*/

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}
