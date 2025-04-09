/*
Práctica 7: Iluminación 1 
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
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture dado8;
//Mi coche
Texture cocheTexture;
Texture llantasTexture;
Texture rinTexture;
Texture cofreTexture;
//Lampara
Texture focoTexture;
Texture lamparaTexture;
//Estrella
Texture estrellaTexture;


Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model coche;
Model ojos;
Model cofre;
Model llantaDelanteraIzq;
Model llantaDelanteraDer;
Model llantaTraseraIzq;
Model llantaTraseraDer;
Model lampara;
Model estrella;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLightsD[MAX_SPOT_LIGHTS];
SpotLight spotLightsA[MAX_SPOT_LIGHTS];
PointLight pointLights2[MAX_POINT_LIGHTS];
PointLight pointLights3[MAX_POINT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


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

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


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

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CrearDado()
{
	
	unsigned int octaedro_indices[] = {
		// Parte de arriba son 4 triángulos
		0, 1, 2,   // Frente
		3, 4, 5,   // Derecha
		6, 7, 8,   // Izquierda
		9, 10, 11, // Atras
		// Parte de abajo igual son 4 triángulos
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23
	};
	//Ejercicio de clase 1
	GLfloat octaedro_vertices[] = {
		// Parte de arriba
		//X		Y		Z		S		T		NX		NY		NZ
		//1
		0.0f,  1.0f,  0.0f,    0.49f, 0.73f,   -1.0f,  1.0f,  -1.0f,  //Pico superior
		1.0f,  0.0f,  0.0f,    0.71f, 0.51f,   -1.0f,  -1.0f,  0.0f, //Pico derecha
		0.0f,  0.0f,  1.0f,    0.27f, 0.51f,   0.0f,  -1.0f,  -1.0f,  //Pico izquierda
		//7
		0.0f,  1.0f,  0.0f,    0.52f, 0.74f,   0.0f,  -1.0f, 1.0f, //Pico superior
		0.0f,  0.0f, -1.0f,    0.96f, 0.73f,   0.0f,  -1.0f, 1.0f, //Pico izquierda
		1.0f,  0.0f,  0.0f,    0.75f, 0.52f,   -1.0f,  -1.0f,  0.0f, //Pico derecha
		//5
		0.0f,  1.0f,  0.0f,    0.52f, 0.76f,  1.0f,  -1.0f,  0.0f,
	   -1.0f,  0.0f,  0.0f,    0.74f, 0.98f,  1.0f,  -1.0f,  0.0f,
		0.0f,  0.0f, -1.0f,    0.96f, 0.76f,   0.0f,  -1.0f, 1.0f,
		//3
		0.0f,  1.0f,  0.0f,    0.46f, 0.74f,  1.0f,  -1.0f,  0.0f,
		0.0f,  0.0f,  1.0f,    0.24f, 0.52f,   0.0f,  -1.0f,  -1.0f,
	   -1.0f,  0.0f,  0.0f,    0.025f, 0.74f,  1.0f,  -1.0f,  0.0f,

	   // Parte de abajo
	   //4
	   0.0f, -1.0f,  0.0f,    0.5f, 0.27f,   0.0f, 1.0f,  -1.0f, //Pico abajo
	   0.0f,  0.0f,  1.0f,    0.27f, 0.49f,   0.0f, 1.0f,  -1.0f, //Pico izquierda
	   1.0f,  0.0f,  0.0f,    0.71f, 0.48f,   -1.0f, 1.0f,  0.0f,  //Pico derecha
	   //6
	   0.0f, -1.0f,  0.0f,    0.53f, 0.26f,   0.0f, 1.0f, 1.0f, //Pico abajo
	   1.0f,  0.0f,  0.0f,    0.75f, 0.47f,   -1.0f, 1.0f,  0.0f,  //Pico derecha
	   0.0f,  0.0f, -1.0f,    0.97f, 0.26f,   0.0f, 1.0f, 1.0f, //Pico izquierda
	   //8
	   0.0f, -1.0f,  0.0f,    0.53f, 0.23f,  1.0f, 1.0f,  0.0f,
	   0.0f,  0.0f, -1.0f,    0.96f, 0.23f,   0.0f, 1.0f, 1.0f,
	  -1.0f,  0.0f,  0.0f,    0.75f, 0.02f,  1.0f, 1.0f,  0.0f,
	  //2
	   0.0f, -1.0f,  0.0f,    0.46f, 0.26f,  1.0f, 1.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,    0.03f, 0.26f,  1.0f, 1.0f,  0.0f,
	   0.0f,  0.0f,  1.0f,    0.24f, 0.47f,   0.0f, 1.0f,  -1.0f
	};
	Mesh* dadoOcto = new Mesh();
	dadoOcto->CreateMesh(octaedro_vertices, octaedro_indices, 192, 48);
	meshList.push_back(dadoOcto);

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
	CrearDado();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	//============== TEXTURAS ==============
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	dado8 = Texture("Textures/dado8caras.jpg");
	dado8.LoadTextureA();

	//Coche
	cocheTexture = Texture("Textures/Ojos.jpg");
	cocheTexture.LoadTextureA();
	llantasTexture = Texture("Textures/cauchoTextura.jpg");
	llantasTexture.LoadTextureA();
	rinTexture = Texture("Textures/rinTextura.jpg");
	rinTexture.LoadTextureA();
	cofreTexture = Texture("Textures/cofreTextura.jpg");
	cofreTexture.LoadTextureA();

	//Lampara
	focoTexture = Texture("Textures/texturaLampara1.jpg");
	focoTexture.LoadTextureA();
	lamparaTexture = Texture("Textures/texturaLampara2.jpg");
	lamparaTexture.LoadTextureA();

	//Estrella
	estrellaTexture = Texture("Textures/texEs.jpg");
	estrellaTexture.LoadTextureA();

	//============== Modelos =============
	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	//Coche
	coche = Model();
	coche.LoadModel("Models/cocheTexturizado.obj");
	ojos = Model();
	ojos.LoadModel("Models/ojos.obj");
	cofre = Model();
	cofre.LoadModel("Models/cofreTexturizado.obj");
	llantaDelanteraIzq = Model();
	llantaDelanteraIzq.LoadModel("Models/llantaTexturizada4.obj");
	llantaDelanteraDer = Model();
	llantaDelanteraDer.LoadModel("Models/llantaTexturizada3.obj");
	llantaTraseraIzq = Model();
	llantaTraseraIzq.LoadModel("Models/llantaTexturizada2.obj");
	llantaTraseraDer = Model();
	llantaTraseraDer.LoadModel("Models/llantaTexturizada1.obj");
	//Lampara
	lampara = Model();
	lampara.LoadModel("Models/lamparaTexturizada.obj");
	//Estrella
	estrella = Model();
	estrella.LoadModel("Models/estrella.obj");
	

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.1f, 0.1f, //Itensidad ambiental(intensidad iluminacion) y difusa(saturacion del color)
		0.0f, -1.0f, 0.0f);
	

	unsigned int spotLightCount = 0;
	unsigned int spotLightCount2 = 0;
	unsigned int spotLightCount3 = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija verde
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f, //Color
		1.0f, 2.0f,
		5.0f, 1.0f, 0.0f, //Posicion
		0.0f, -1.0f, 0.0f, //Direccion
		1.0f, 0.0f, 0.0f, //Ec segundo grado sin atenuar
		30.0f); //Angulo apertura
	spotLightCount++;

	//EJERCICIO 2 REPORTE PRÁCTICA 7 
	//LUZ PUNTUAL DE COLOR AMARILLO
	spotLights[2] = SpotLight(1.0f, 1.0f, 0.0f, //Color azul
		5.0f, 1.0f,
		0.0f, 0.0f, 0.0f, //Posicion
		0.0f, -1.0f, 0.0f, //Direccion
		1.0f, 0.5f, 0.0f, //Atenuacion
		30.0f); //Angulo apertura
	spotLightCount++;

	spotLights[3] = SpotLight(
		0.3f, 0.9f, 0.3f,   // Color verde claro
		10.0f, 5.0f,        // Intensidad ambiental y difusa
		0.0f, 0.0f, 0.0f,   // Posición
		0.0f, 0.0f, -1.0f,  // Dirección
		1.0f, 0.09f, 0.032f,// Atenuación 
		30.0f               // Ángulo de apertura
	);
	spotLightCount++;


	//EJERCICIO 2 SPOTLIGHT DE COLOR AZUL DELANTERO
	//FARO DEL COCHE 
	spotLightsD[0] = SpotLight(0.0f, 0.0f, 1.0f, //Color azul
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f, //Posicion
		0.0f, 0.0f, -1.0f, //Direccion
		1.0f, 0.012f, 0.0009f, //Atenuacion
		25.0f); //Angulo apertura
	spotLightCount2++;

	//SPOTLIGHT DE COLOR ROSA TRASERO
	//FARO DEL COCHE 
	spotLightsA[0] = SpotLight(1.0f, 0.0f, 1.0f, //Color azul
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f, //Posicion
		0.0f, 0.0f, 1.0f, //Direccion
		1.0f, 0.012f, 0.0009f, //Atenuacion
		25.0f); //Angulo apertura
	spotLightCount3++;

	

	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	unsigned int pointLightCount2 = 0;
	unsigned int pointLightCount3 = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.5f, 1.0f, //Itensidad ambiental(radio de alcance, ilumina mas fuerte) y difusa(como ilumina al objeto, >1 es mas fuerte)
		-6.0f, 1.5f, 1.5f, //Posicion
		0.3f, 0.2f, 0.1f); //Es la atenuacion (mover para ver que sucede, no pueden ser 0 los 3)
	pointLightCount++;

	//Luz puntal random 
	pointLights[1] = PointLight(1.0f, 0.5f, 1.0f,
		0.5f, 1.0f, //Itensidad ambiental(radio de alcance, ilumina mas fuerte) y difusa(como ilumina al objeto, >1 es mas fuerte)
		-10.0f, 1.5f, 1.5f, //Posicion
		0.3f, 0.2f, 0.1f); //Es la atenuacion (mover para ver que sucede, no pueden ser 0 los 3)
	pointLightCount++;

	//Luz lampara encendida
	pointLights2[0] = PointLight(1.0f, 1.0f, 1.0f,
		1.5f, 10.0f, 
		0.0f, 23.0f, -4.5,
		1.0f, 0.09f, 0.032f); 
	pointLightCount2++;

	//Luz estrella
	pointLights3[0] = PointLight(1.0f, 1.0f, 0.0f,
		1.5f, 10.0f,
		-30.0f, -1.0f, -10.0,
		1.0f, 0.09f, 0.032f);
	pointLightCount3++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
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
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
			glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);

		int modoLuz = 0; // 0: solo base, 1: luces basicas y cofre, 2: luces coche, 3: luz lampara, 4: luz estrella
		modoLuz = mainWindow.tecla(); // Cambia el modo de luz según la entrada del usuario
		switch (modoLuz) {
		case 1: // Solo luces básicas
			shaderList[0].SetPointLights(pointLights, pointLightCount);
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
			break;

		case 2: //Coche
			if (mainWindow.getvalor2() == true) {
				shaderList[0].SetPointLights(pointLights, pointLightCount);
				shaderList[0].SetSpotLights(spotLightsD, spotLightCount2);
			}
			if (mainWindow.getvalor2() == false) {
				shaderList[0].SetPointLights(pointLights, pointLightCount);
				shaderList[0].SetSpotLights(spotLightsA, spotLightCount3);
			}
			break;

		case 3: // Lampara
			if (mainWindow.getvalor() == true) {
				shaderList[0].SetPointLights(pointLights, pointLightCount);
				shaderList[0].SetSpotLights(spotLights, spotLightCount);
			}
			if (mainWindow.getvalor() == false) {
				shaderList[0].SetPointLights(pointLights, pointLightCount);
				shaderList[0].SetPointLights(pointLights2, pointLightCount2);
			}
			break;

		case 4: //Estrella
			if (mainWindow.getvalor3() == true) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
			}
			if (mainWindow.getvalor3() == false) {
				shaderList[0].SetPointLights(pointLights, pointLightCount);
				shaderList[0].SetPointLights(pointLights3, pointLightCount3);
			}
			break;

		default: // Ninguna luz
			break;
		}

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 posicionLuz;
		glm::vec4 nuevaPosicion;
		glm::vec3 posicionLuzHeli;
		glm::vec4 nuevaPosicionHeli;
		glm::vec3 posicionLuzCofre;
		glm::vec4 nuevaPosicionCofre;

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		//Piramide para la luz
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 15.0f, -40.0f));
		model = glm::scale(model, glm::vec3(15.0f, 25.0f, 15.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();


		//EJERCICIO DE CLASE
		//EJERCICIO 1 CUBO 8 CARAS:
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.5f, 4.5f, -2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dado8.UseTexture();
		meshList[4]->RenderMesh();

		// ==================== REPORTE PRACTICA 8 ====================

		model = glm::mat4(1.0);
		//Inicio coche
		model = glm::translate(model, glm::vec3(30.0f, 0.2f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getarticulacion3()));
		//Posicion de la luz respecto a la posicion del coche
		if (mainWindow.getvalor2() == true) {
			posicionLuz = glm::vec3(0.0f, 0.0f, -16.0f);
		}
		else {
			posicionLuz = glm::vec3(0.0f, 0.0f, 16.0f);
		}
		nuevaPosicion = model * glm::vec4(posicionLuz, 1.0f);
		// Se actualiza la posicion para la luz
		if (mainWindow.getvalor2() == true) {
			spotLightsD[0].SetPos(nuevaPosicion);
		}
		else {
			spotLightsA[0].SetPos(nuevaPosicion);
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		coche.RenderModel();

		//Cofre
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.0f, 7.6f, -5.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(1.0f, 0.0f, 0.0f));
		posicionLuzCofre = glm::vec3(0.0f, 2.0f, -8.5f);
		nuevaPosicionCofre = model * glm::vec4(posicionLuzCofre, 1.0f);
		spotLights[3].SetPos(nuevaPosicionCofre);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cofre.RenderModel();
		model = modelaux;

		//Ojos
		modelaux = model;
		model = glm::translate(model, glm::vec3(0.0f, 9.6f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ojos.RenderModel();
		model = modelaux;

		//Rueda 1 (VIENDO DESDE LA PARTE DE ENFRENTE DEL COCHE - DELANTERA DERECHA)
		modelaux = model;
		model = glm::translate(model, glm::vec3(-9.0f, 1.5f, -11.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaDelanteraDer.RenderModel();
		model = modelaux;

		//Rueda 2 (VIENDO DESDE LA PARTE DE ENFRENTE DEL COCHE - DELANTERA IZQUIERDA)
		modelaux = model;
		model = glm::translate(model, glm::vec3(9.0f, 1.5f, -11.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaDelanteraIzq.RenderModel();
		model = modelaux;

		//Rueda 3 (VIENDO DESDE LA PARTE DE ENFRENTE DEL COCHE - TRASERA DERECHA)
		modelaux = model;
		model = glm::translate(model, glm::vec3(-9.0f, 1.5f, 10.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaTraseraDer.RenderModel();
		model = modelaux;

		//Rueda 4 (VIENDO DESDE LA PARTE DE ENFRENTE DEL COCHE - TRASERA IZQUIERDA)
		modelaux = model;
		model = glm::translate(model, glm::vec3(9.0f, 1.5f, 10.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llantaTraseraIzq.RenderModel();
		model = modelaux;


		//EJERCICIO 1 Y 2 HELICOPTERO
		//Helicoptero con luz
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//Articulacion para mover el helicoptero
		model = glm::translate(model, glm::vec3(0.0f, mainWindow.getarticulacion1(), 0.0f));
		//Posición de la luz respecto al helicoptero
		posicionLuzHeli = glm::vec3(0.0f, 0.5f, 0.0f);
		nuevaPosicionHeli = model * glm::vec4(posicionLuzHeli, 1.0f);
		// Se actualiza la posicion para la luz
		spotLights[2].SetPos(nuevaPosicionHeli);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//EJERCICIO 3 LAMPARA
		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -10.0));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		//Estrella
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		estrella.RenderModel();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		//Tiene traslucides por ende va al final
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		//blending: transparencia o traslucidez
		//Siempre mandarlo hacia abajo para que no desaparezca otros objetos
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
