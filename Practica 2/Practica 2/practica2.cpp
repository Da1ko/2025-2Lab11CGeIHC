//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
//Agregar shaders
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá

static const char* fRojoShader = "shaders/rojo.frag";
static const char* fVerdeShader = "shaders/verde.frag";
static const char* fAzulShader = "shaders/azul.frag";
static const char* fCafeShader = "shaders/cafe.frag";
static const char* fVerdeOscuroShader = "shaders/verdeOscuro.frag";
static const char* vShaderUniversal = "shaders/universal.vert";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front con triangulos
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	//Vertices de las letras que ya tenemos
	//A cada vertices un color
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B
			/**
			-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			*/

			//Letra A
			-0.6f,  0.6f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.6f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.7f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
	 
			-0.6f,  0.6f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.5f,  0.6f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.6f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,

			-0.6f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.5f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.5f, 0.6f, 0.5f,					0.0f,	0.0f,	1.0f,

			-0.6f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.7f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.7f, 0.2f, 0.5f,					0.0f,	0.0f,	1.0f,

			-0.7f, 0.2f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.6f, 0.2f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.6f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,

			-0.5f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.5f, 0.6f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.4f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,

			-0.4f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.5f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.5f, 0.2f, 0.5f,					0.0f,	0.0f,	1.0f,

			-0.5f, 0.2f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.4f, 0.2f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.4f, 0.5f, 0.5f,					0.0f,	0.0f,	1.0f,

			-0.6f, 0.4f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.5f, 0.4f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.6f, 0.3f, 0.5f,					0.0f,	0.0f,	1.0f,

			-0.5f, 0.4f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.6f, 0.3f, 0.5f,					0.0f,	0.0f,	1.0f,
			-0.5f, 0.3f, 0.5f,					0.0f,	0.0f,	1.0f,


			//Letra I
			0.2f, 0.7f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.4f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.2f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,

			0.4f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.4f, 0.7f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.2f, 0.7f, 0.5f,					0.0f,	1.0f,	0.6f,

			0.4f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.4f, 0.7f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.5f, 0.7f, 0.5f,					0.0f,	1.0f,	0.6f,


			0.4f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.5f, 0.7f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.5f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,

			0.3f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.4f, 0.3f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.3f, 0.3f, 0.5f,					0.0f,	1.0f,	0.6f,

			0.3f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.4f, 0.6f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.4f, 0.3f, 0.5f,					0.0f,	1.0f,	0.6f,

			0.2f, 0.3f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.2f, 0.2f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.5f, 0.2f, 0.5f,					0.0f,	1.0f,	0.6f,

			0.5f, 0.3f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.5f, 0.2f, 0.5f,					0.0f,	1.0f,	0.6f,
			0.2f, 0.3f, 0.5f,					0.0f,	1.0f,	0.6f,

			//Letra S

			-0.4f, -0.2f, 0.5f,					1.0f,	0.8f,	0.2f,
			-0.4f, -0.1f, 0.5f,					1.0f,	0.8f,	0.2f,
			-0.6f, -0.1f, 0.5f,					1.0f,	0.8f,	0.2f,

			-0.6f, -0.1f, 0.5f,					1.0f,	0.8f,	0.2f, 
			-0.4f, -0.2f, 0.5f,					1.0f,	0.8f,	0.2f,
			-0.6f, -0.2f, 0.5f,					1.0f,	0.8f,	0.2f,

			-0.6f, -0.2f, 0.5f,					1.0f,	0.8f,	0.2f,
			-0.6f, -0.1f, 0.5f,					1.0f,	0.8f,	0.2f,
			-0.7f, -0.2f, 0.5f,					1.0f,	0.8f,	0.2f,

			-0.7f, -0.2f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.6f, -0.2f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.7f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.6f, -0.2f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.7f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.6f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.7f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.6f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.6f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.6f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.6f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.5f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.6f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.5f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.5f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.5f, -0.3f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.5f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.4f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.5f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.4f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.5f, -0.5f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.4f, -0.4f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.5f, -0.5f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.4f, -0.5f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.5f, -0.5f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.4f, -0.5f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.5f, -0.6f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.5f, -0.5f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.5f, -0.6f, 0.5f,					1.0f, 0.8f, 0.2f,
			-0.7f, -0.5f, 0.5f,					1.0f, 0.8f, 0.2f,

			-0.5f, -0.6f, 0.0f,					1.0f, 0.8f, 0.2f,
			-0.7f, -0.5f, 0.0f,					1.0f, 0.8f, 0.2f,
			-0.7f, -0.6f, 0.0f,					1.0f, 0.8f, 0.2f,

			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,576);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

		// Triángulo azul
	GLfloat vertices_trianguloazul[] = {
		// X       Y       Z       R     G     B
		-1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f, // Azul
		1.0f,  -1.0f, 0.5f, 0.0f, 0.0f, 1.0f, // 
		0.0f,  1.0f,  0.5f, 0.0f, 0.0f, 1.0f, // 
	};
	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	// Triángulo verde
	GLfloat vertices_trianguloverde[] = {
		// X       Y       Z       R     G     B
		-1.0f, -1.0f, 0.5f, 0.0f, 0.5f, 0.0f, // Verde
		1.0f,  -1.0f, 0.5f, 0.0f, 0.5f, 0.0f, // 
		0.0f,  1.0f,  0.5f, 0.0f, 0.5f, 0.0f, // 
	};
	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	// Cuadrado rojo
	GLfloat vertices_cuadrorojo[] = {
		// X       Y       Z       R     G     B
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Rojo
		0.5f,  -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Rojo
		0.5f,   0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Rojo
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Rojo
		0.5f,   0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Rojo
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Rojo
	};
	MeshColor* cuadrorojo = new MeshColor();
	cuadrorojo->CreateMeshColor(vertices_cuadrorojo, 36);
	meshColorList.push_back(cuadrorojo);

	// Cuadrado verde
	GLfloat vertices_cuadradoverde[] = {
		// X       Y       Z       R     G     B
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Verde
		0.5f,  -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Verde
		0.5f,   0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Verde
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Verde
		0.5f,   0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Verde
		-0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Verde
	};
	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	// Cuadrado café
	GLfloat vertices_cuadracafe[] = {
		// X       Y       Z       R     G     B
		-0.5f, -0.5f, 0.5f, 0.478f, 0.255f, 0.067f, // Café
		0.5f,  -0.5f, 0.5f, 0.478f, 0.255f, 0.067f, // Café
		0.5f,   0.5f, 0.5f, 0.478f, 0.255f, 0.067f, // Café
		-0.5f, -0.5f, 0.5f, 0.478f, 0.255f, 0.067f, // Café
		0.5f,   0.5f, 0.5f, 0.478f, 0.255f, 0.067f, // Café
		-0.5f,  0.5f, 0.5f, 0.478f, 0.255f, 0.067f, // Café
	};
	MeshColor* cuadracafe = new MeshColor();
	cuadracafe->CreateMeshColor(vertices_cuadracafe, 36);
	meshColorList.push_back(cuadracafe);

}


void CreateShaders()
{
	Shader* shaderRojo = new Shader();
	shaderRojo->CreateFromFiles(vShaderUniversal, fRojoShader);
	shaderList.push_back(*shaderRojo);

	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles(vShaderUniversal, fVerdeShader);
	shaderList.push_back(*shaderVerde);

	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles(vShaderUniversal, fAzulShader);
	shaderList.push_back(*shaderAzul);

	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles(vShaderUniversal, fCafeShader);
	shaderList.push_back(*shaderCafe);

	Shader* shaderVerdeOsc = new Shader();
	shaderVerdeOsc->CreateFromFiles(vShaderUniversal, fVerdeOscuroShader);
	shaderList.push_back(*shaderVerdeOsc);

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1); //Guarda en una lista el elemento

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
    // =========== 2D =============
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

	// =========== 3D =============
	//60 grados es un cono de perspectiva, aspect ratio cercano a 1
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);


	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad,Si esta dentro desborda memoria
	

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		

		//================= LETRAS =====================											
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[6].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f)); //Asi se puede ver los valores que son dibujados fuera de z no visible
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor(); //Triangulo azul grande con rojo
		
		// 
		// 
		//================= FIGURAS =====================
		/*
		// Triángulo azul (ubicado en la parte superior)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f); // Resetear la matriz de modelo
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -5.0f)); // Trasladamos el triángulo azul
		model = glm::scale(model, glm::vec3(0.6f, 0.3f, 0.6f)); //Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor(); // Triángulo azul

		// Triángulo verde (ubicado en la parte inferior derecha)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.7f, -0.6f, -4.0f)); // Trasladamos el triángulo verde
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));//Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor(); // Triángulo verde

		// Triángulo verde (ubicado en la parte inferior izquierda)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.7f, -0.6f, -5.0f)); // Trasladamos el triángulo verde
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));//Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor(); // Triángulo verde

		// Cuadrado rojo (ubicado en el centro)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -4.0f)); // Trasladamos el cuadrado rojo
		model = glm::scale(model, glm::vec3(1.0f, 1.2f, 1.0f)); //Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor(); // Cuadrado rojo

		// Cuadrado verde (ventana izq)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.2f, -0.2f, -3.0f)); // Trasladamos el cuadrado verde
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); //Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[5]->RenderMeshColor(); // Cuadrado verde

		// Cuadrado verde (ventana der)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.2f, -0.2f, -3.0f)); // Trasladamos el cuadrado verde
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); //Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[5]->RenderMeshColor(); // Cuadrado verde

		// Cuadrado verde (puerta)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -3.0f)); // Trasladamos el cuadrado verde
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.3f)); //Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[5]->RenderMeshColor(); // Cuadrado verde

		// Cuadrado café (ubicado en la parte inferior derecha)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.7f, -0.9f, -4.0f)); // Trasladamos el cuadrado café
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); //Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColor(); // Cuadrado café

		// Cuadrado café (ubicado en la parte inferior izquierda)
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.7f, -0.9f, -4.0f)); // Trasladamos el cuadrado café
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); //Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[6]->RenderMeshColor(); // Cuadrado café
		*/

		// =============== CUBOS Y PIRAMIDES =====================
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		/* CODIGO DE EJEMPLO PRACTICA 2
		
		shaderList[4].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //Cubo
		
		*/
		/*
	
		// Cubo rojo
		shaderList[0].useShader(); //Shader del color rojo
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0; 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -4.0f)); // Trasladamos el cuadrado rojo
		model = glm::scale(model, glm::vec3(1.0f, 1.2f, 1.0f)); //Tamaño adecuado
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //Cubo

		//Cubo verde ventana izq
		shaderList[1].useShader(); //Shader del color verde
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, -0.2f, -3.0f)); // Trasladamos el cuadrado verde
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); //Tamaño adecuado
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //Cubo

		//Cubo verde ventana der
		shaderList[1].useShader(); //Shader del color verde
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, -0.2f, -3.0f)); // Trasladamos el cuadrado verde
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); //Tamaño adecuado
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //Cubo

		//Cubo verde puerta
		shaderList[1].useShader(); //Shader del color verde
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -3.6f)); // Trasladamos el cuadrado verde
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.3f)); //Tamaño adecuado
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //Cubo

		//Cubo cafe der
		shaderList[3].useShader(); //Shader del color cafe
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.9f, -3.0f)); // Trasladamos el cuadrado café
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); //Tamaño adecuado
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //Cubo

		//Cubo cafe izq
		shaderList[3].useShader(); //Shader del color cafe
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.9f, -3.0f)); // Trasladamos el cuadrado café
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); //Tamaño adecuado
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); //Cubo

		//Piramide azul techo
		shaderList[2].useShader(); //Shader del color azul
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0; 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.0f)); // Trasladamos el triángulo azul
		model = glm::scale(model, glm::vec3(1.0f, 0.7f, 1.0f)); //Tamaño adecuado
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //Piramide

		//Piramide oscuro derecha
		shaderList[4].useShader(); //Shader del color oscuro
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0; 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.6f, -3.0f)); // Trasladamos el triángulo verde
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));//Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //Piramide

		//Piramide oscuro derecha
		shaderList[4].useShader();  //Shader del color oscuro
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 1.0;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.6f, -3.0f)); // Trasladamos el triángulo verde
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotacion
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));//Tamaño adecuado
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); //Piramide
		*/

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/