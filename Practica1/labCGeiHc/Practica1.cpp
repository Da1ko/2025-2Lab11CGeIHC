#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <stdlib.h> // Para rand()
#include <time.h>   // Para time()
#include <Windows.h> // Para Sleep()

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

//Vertex Shader
//recibir color, salida Vcolor
//Hardcoding
//En las siguientes practicas estaran en la carpeta de shaders
//Es un programador para la gpu
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(0.0f,0.0f,0.0f,0.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = { //x,y,z
	/*//Cuadrado
     -0.05f,  0.05f, 0.0f,  
	 -0.05f, -0.05f, 0.0f,  
	 0.05f, -0.05f, 0.0f,  

	 0.05f, -0.05f, 0.0f,  
	 0.05f,  0.05f, 0.0f,  
	 -0.05f,  0.05f, 0.0f,   

	 //Rombo
	 0.1f, -0.1f, 0.0f,  
	 0.3f, -0.1f, 0.0f,  
	 0.2f,  0.1f, 0.0f,  // pico superior

	 0.1f, -0.1f, 0.0f,  
	 0.3f, -0.1f, 0.0f,  
	 0.2f,  -0.3f, 0.0f   // pico inferior
	 */

	//Letra A
	 -0.6f,  0.6f, 0.0f, //H
	 -0.6f, 0.5f, 0.0f, //J
	 -0.7f, 0.5f, 0.0f, //I
	 
	 -0.6f,  0.6f, 0.0f, //H
	 -0.5f,  0.6f, 0.0f, //K
	 -0.6f, 0.5f, 0.0f, //J

	 -0.6f, 0.5f, 0.0f, //J
	 -0.5f, 0.5f, 0.0f, //L
	 -0.5f, 0.6f, 0.0f, //K

	 -0.6f, 0.5f, 0.0f, //J
	 -0.7f, 0.5f, 0.0f, //I
	 -0.7f, 0.2f, 0.0f, //V

	 -0.7f, 0.2f, 0.0f, //V
	 -0.6f, 0.2f, 0.0f, //W
	 -0.6f, 0.5f, 0.0f, //J

	 -0.5f, 0.5f, 0.0f, //L
	 -0.5f, 0.6f, 0.0f, //K
	 -0.4f, 0.5f, 0.0f, //M

	 -0.4f, 0.5f, 0.0f, //M
	 -0.5f, 0.5f, 0.0f, //L
	 -0.5f, 0.2f, 0.0f, //Z

	 -0.5f, 0.2f, 0.0f, //Z
	 -0.4f, 0.2f, 0.0f, //A1
	 -0.4f, 0.5f, 0.0f, //M 

	 -0.6f, 0.4f, 0.0f, //N
	 -0.5f, 0.4f, 0.0f, //R
	 -0.6f, 0.3f, 0.0f, //Q

	 -0.5f, 0.4f, 0.0f, //R
	 -0.6f, 0.3f, 0.0f, //Q
	 -0.5f, 0.3f, 0.0f, //U


	 //Letra I
	 0.2f, 0.7f, 0.0f, //T1
	 0.4f, 0.6f, 0.0f, //D1
	 0.2f, 0.6f, 0.0f, //U1

	 0.4f, 0.6f, 0.0f, //D1
	 0.4f, 0.7f, 0.0f, //R1
	 0.2f, 0.7f, 0.0f, //T1

	 0.4f, 0.6f, 0.0f, //D1
     0.4f, 0.7f, 0.0f, //R1
	 0.5f, 0.7f, 0.0f, //Q1
     

	 0.4f, 0.6f, 0.0f, //D1
	 0.5f, 0.7f, 0.0f, //Q1
	 0.5f, 0.6f, 0.0f, //P1

	 0.3f, 0.6f, 0.0f, //C1
	 0.4f, 0.3f, 0.0f, //N1
	 0.3f, 0.3f, 0.0f, //G1

	 0.3f, 0.6f, 0.0f, //C1
	 0.4f, 0.6f, 0.0f, //D1
	 0.4f, 0.3f, 0.0f, //N1

	 0.2f, 0.3f, 0.0f, //H1
	 0.2f, 0.2f, 0.0f, //I1
	 0.5f, 0.2f, 0.0f, //L1

	 0.5f, 0.3f, 0.0f, //M1
	 0.5f, 0.2f, 0.0f, //L1
     0.2f, 0.3f, 0.0f, //H1

	 //Letra S

	 -0.4f, -0.2f, 0.0f, //A2
	 -0.4f, -0.1f, 0.0f, //V1
	 -0.6f, -0.1f, 0.0f, //Z1

	 -0.6f, -0.1f, 0.0f, //Z1
	 -0.4f, -0.2f, 0.0f, //A2
	 -0.6f, -0.2f, 0.0f, //C2

	 -0.6f, -0.2f, 0.0f, //C2
	 -0.6f, -0.1f, 0.0f, //Z1
	 -0.7f, -0.2f, 0.0f, //D2

	 -0.7f, -0.2f, 0.0f, //D2
	 -0.6f, -0.2f, 0.0f, //C2
	 -0.7f, -0.3f, 0.0f, //E2

	 -0.6f, -0.2f, 0.0f, //C2
	 -0.7f, -0.3f, 0.0f, //E2
	 -0.6f, -0.3f, 0.0f, //F2

	 -0.7f, -0.3f, 0.0f, //E2
	 -0.6f, -0.3f, 0.0f, //F2
	 -0.6f, -0.4f, 0.0f, //I2

	 -0.6f, -0.3f, 0.0f, //F2
	 -0.6f, -0.4f, 0.0f, //I2
	 -0.5f, -0.3f, 0.0f, //G2

	 -0.6f, -0.4f, 0.0f, //I2
	 -0.5f, -0.3f, 0.0f, //G2
	 -0.5f, -0.4f, 0.0f, //J2

	 -0.5f, -0.3f, 0.0f, //G2
	 -0.5f, -0.4f, 0.0f, //J2
	 -0.4f, -0.4f, 0.0f, //H2

	 -0.5f, -0.4f, 0.0f, //J2
	 -0.4f, -0.4f, 0.0f, //H2
	 -0.5f, -0.5f, 0.0f, //M2

	 -0.4f, -0.4f, 0.0f, //H2
	 -0.5f, -0.5f, 0.0f, //M2
	 -0.4f, -0.5f, 0.0f, //K2

	 -0.5f, -0.5f, 0.0f, //M2
	 -0.4f, -0.5f, 0.0f, //K2
	 -0.5f, -0.6f, 0.0f, //R2

	 -0.5f, -0.5f, 0.0f, //M2
	 -0.5f, -0.6f, 0.0f, //R2
	 -0.7f, -0.5f, 0.0f, //O2

	 -0.5f, -0.6f, 0.0f, //R2
	 -0.7f, -0.5f, 0.0f, //O2
	 -0.7f, -0.6f, 0.0f, //P2
	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es est�tico pues no se modificar�n los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos, cantidad de columnas, 0 datos saltados
		glEnableVertexAttribArray(0);
		//agregar valores a v�rtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Funci�n para agregar los shaders a la tarjeta gr�fica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el c�digo
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevenci�n de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el c�digo a la tarjeta gr�fica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gr�fica
	 //verificaciones y prevenci�n de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}

}

// Inicializa la semilla del generador de n�meros aleatorios
void initRandom() {
	srand((unsigned int)time(0)); //Unsigned porque se necesita que el valor random sea positivo 
}

// Genera un color aleatorio en el rango [0,1]
float nuevoColor() {
	return (float)rand() / (float)RAND_MAX;
}

int main()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "PRACTICA 1: Introduccion a OPENGL", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tr�angulo
	CrearTriangulo();
	CompileShaders();
	//int cambioColor=0;
	initRandom(); // Inicializa el generador aleatorio

	float colorR = nuevoColor();
	float colorG = nuevoColor();
	float colorB = nuevoColor();
	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();
	/*
			if (cambioColor == 0) {
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f); //Color de la consola
			//glClear(GL_COLOR_BUFFER_BIT);
			Sleep(1000);
		}

		if (cambioColor == 1) {
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f); //Color de la consola
			//glClear(GL_COLOR_BUFFER_BIT);
			Sleep(1000);
		}

		if (cambioColor == 2) {
			glClearColor(0.0f, 0.0f, 1.0f, 0.0f); //Color de la consola
			//glClear(GL_COLOR_BUFFER_BIT);
			Sleep(1000);
		}
	*/
		//Se pone el color nuevo generado
		glClearColor(colorR, colorG, colorB, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Sleep(2000); // Espera 2 segundos antes de cambiar el color
		//Se genera un nuevo color
		colorR = nuevoColor();
		colorG = nuevoColor();
		colorB = nuevoColor();

		//cambioColor = (cambioColor + 1) % 3;
		glUseProgram(shader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,96); //Los datos que voy a mandar
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}
	return 0;
}