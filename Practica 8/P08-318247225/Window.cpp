#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
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
	mainWindow = glfwCreateWindow(width, height, "Practica08:Iluminación 2", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow-> muevex -= 1.0;
	}

	//Switch 
	if (key == GLFW_KEY_1)
	{
		theWindow->teclas = 1;
	}
	if (key == GLFW_KEY_2)
	{
		theWindow->teclas = 2;
	}
	if (key == GLFW_KEY_3)
	{
		theWindow->teclas = 3;
	}
	if (key == GLFW_KEY_4)
	{
		theWindow->teclas = 4;
	}
	//Lampara
	if (key == GLFW_KEY_C)
	{
		theWindow->valor = true;
	}
	if (key == GLFW_KEY_V)
	{
		theWindow->valor = false;
	}
	//Estrella
	if (key == GLFW_KEY_Z)
	{
		theWindow->valor3 = true;
	}
	if (key == GLFW_KEY_X)
	{
		theWindow->valor3 = false;
	}
	//Movimiento cofre
	if (key == GLFW_KEY_K)
	{
		if (theWindow->articulacion4 > 45.0)
		{
		}
		else {
			theWindow->articulacion4 += 10.0;
		}
	}
	if (key == GLFW_KEY_L)
	{
		if (theWindow->articulacion4 == 0.0)
		{
		}
		else {
			theWindow->articulacion4 -= 10.0;
		}
	}
	//Movimiento Helicoptero
	if (key == GLFW_KEY_F) {
		theWindow->articulacion1 += 10.0;
	}
	if (key == GLFW_KEY_G)
	{
		theWindow->articulacion1 -= 10.0;
	}
	//Llantas
	if (key == GLFW_KEY_H) {
		theWindow->articulacion2 += 10.0;
	}
	if (key == GLFW_KEY_J)
	{
		theWindow->articulacion2 -= 10.0;
	}
	//Encendido luces coche delante atras
	if (key == GLFW_KEY_J)
	{
		theWindow->valor2 = true;
	}
	if (key == GLFW_KEY_H)
	{
		theWindow->valor2 = false;
	}

	//Movimiento coche
	if (key == GLFW_KEY_H) {
		theWindow->articulacion3 += 1.0;
	}
	if (key == GLFW_KEY_J)
	{
		theWindow->articulacion3 -= 1.0;
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
