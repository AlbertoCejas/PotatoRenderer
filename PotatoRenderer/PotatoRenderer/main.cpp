
#define BASIC_SAMPLE

#ifndef BASIC_SAMPLE

#include "core/Application.h"
#include <ctime>

int main()
{
	Application app;

	app.init();

	int64_t deltaMicroseconds = 0;

	while (app.mustExit() == false)
	{
		clock_t begin_time = clock();

		app.update(deltaMicroseconds);
		app.render();

		deltaMicroseconds = (clock() - begin_time) * 1000000 / CLOCKS_PER_SEC;
	}

	return true;
}

#else


#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include "utils/stb_image.h"

#include "render/ShaderProgram.h"
#include "render/OrthographicCamera.h"
#include "render/PerspectiveCamera.h"
#include "render/Mesh.h"
#include "vld.h"
#include "math/MathUtils.h"
#include "render/ShapeRenderer.h"

#include "render/Texture.h"
#include "render/TextureRegion.h"
#include "render/Sprite.h"
#include "render/SpriteBatch.h"



#include "utils/stb_image.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "layout (location = 1) in vec3 color;\n"
                                   "out vec3 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = vec4(position, 1.0);\n"
                                   "ourColor = color;\n"
                                   "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
                                     "in vec3 ourColor;\n"
                                     "out vec4 color;\n"
                                     "void main()\n"
                                     "{\n"
                                     "color = vec4(ourColor, 1.0f);\n"
                                     "}\n\0";

bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

float Yaw = 0.0f;
float Pitch = 0.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void Do_Movement(float deltaTime, BaseCamera& camera);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "PotatoRenderer", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Setup some OpenGL options
	// glEnable(GL_DEPTH_TEST);

	/*

	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
	    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
	    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	*/

	/*
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
	    // Positions        // Colors
	    0.5f, -0.5f, 1.0f,  1.0f, 0.0f, 0.0f, // Bottom Right
	    -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Left
	    0.0f,  0.5f, 1.0f,  0.0f, 0.0f, 1.0f  // Top
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO

	GLfloat verticesData1[] =
	{
	    // Positions        // Colors
	    0.0f, 0.0f, -10.0f,  1.0f, 0.0f, 0.0f, // Bottom Right
	    -50.0f, 0.0f, -10.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
	    -25.0f, 50.0f, -10.0f,  1.0f, 0.0f, 0.0f  // Top
	};

	GLfloat verticesData2[] =
	{
	    // Positions        // Colors
	    50.0f, 0.0f, 10.0f,  0.0f, 1.0f, 0.0f, // Bottom Right
	    0.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, // Bottom Left
	    25.0f, 50.0f, 10.0f,  0.0f, 1.0f, 0.0f  // Top
	};

	ShaderProgram shader(false, true, false);

	std::vector<VertexAttribute> attributes;
	attributes.reserve(2);
	attributes.push_back(VertexAttribute::position());
	attributes.push_back(VertexAttribute::color());

	Mesh mesh1(true, 5000, attributes);
	mesh1.bind(shader);
	mesh1.setVertices(verticesData1, 3);

	Mesh mesh2(true, 5000, attributes);
	mesh2.bind(shader);
	mesh2.setVertices(verticesData2, 3);

	Mesh mesh3(true, 5000, attributes);
	mesh3.bind(shader);
	mesh3.setVertices(vertices, 3);

	*/

	double deltaTime = 0.0f;
	double lastFrame = 0.0f;

	//OrthographicCamera camera((float)WIDTH, (float)HEIGHT);
	PerspectiveCamera camera((float)WIDTH, (float)HEIGHT);
	camera.translate(0, 0, 100);
	camera.update();

	ShapeRenderer shapeRenderer;
	SpriteBatch spriteBatch(1000);

	Texture boxTexture("assets/texture.jpg");
	TextureRegion boxRegion(boxTexture);
	Sprite boxSprite(boxRegion);

	Texture boxTexture2("assets/texture.jpg");
	TextureRegion boxRegion2(boxTexture2);
	Sprite boxSprite2(boxRegion2, .0f, .0f, .0f, 50.0f, 50.0f, 0.0f);
	boxSprite2.setColor(Color::RED);

	Sprite boxSprite2Clone(boxRegion2, .0f, .0f, .0f, 50.0f, 50.0f, 0.0f);
	boxSprite2Clone.translate(50.0f, 0.0f, 0.0f);

	Sprite boxSprite2CloneClone(boxRegion2, .0f, .0f, .0f, 50.0f, 50.0f, 0.0f);
	boxSprite2CloneClone.translate(100.0f, 0.0f, 0.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		Do_Movement((float)deltaTime, camera);

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		spriteBatch.begin(camera);
		spriteBatch.render(boxSprite);
		spriteBatch.render(boxSprite2);
		spriteBatch.render(boxSprite2Clone);
		spriteBatch.render(boxSprite2CloneClone);
		spriteBatch.end();


		shapeRenderer.begin(camera.getCombined(), DrawMode::FILLED);
		{
			shapeRenderer.triangle
			(
			    0.0f, 0.0f, 0.0f,
			    50.0f, 0.0f, 0.0f,
			    25.0f, 50.0f, 0.0f,
			    Color::BLACK
			);
			shapeRenderer.rectangle
			(
			    -10.0f, 20.0f, 0.0f,
			    -30.0f, 20.0f, 0.0f,
			    -30.0f, 40.0f, 0.0f,
			    -10.0f, 40.0f, 0.0f,
			    Color::GRAY
			);

			shapeRenderer.circle(0.0f, 0.0f, 0.0f, 5.0f, 20, Color::BLACK);
			shapeRenderer.circle(10.0f, 0.0f, 0.0f, 5.0f, 20, Color::ORANGE);
		}
		shapeRenderer.end();


		/*
		shapeRenderer.begin(camera.getCombined(), DrawMode::LINES);
		{
		    shapeRenderer.triangle
		    (
		        0.0f, 0.0f, 10.0f,
		        -50.0f, 0.0f, 10.0f,
		        -25.0f, 50.0f, 10.0f,
		        Color::ORANGE
		    );
		    shapeRenderer.rectangle
		    (
		        10.0f, 20.0f, 0.0f,
		        30.0f, 20.0f, 0.0f,
		        30.0f, 40.0f, 0.0f,
		        10.0f, 40.0f, 0.0f,
		        Color::ORANGE
		    );
		    shapeRenderer.line
		    (
		        0.0f, -10.0f, 0.0f,
		        10.0f, -10.0f, 0.0f,
		        Color::PINK
		    );
		}
		shapeRenderer.end();
		*/
		//glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Properly de-allocate all resources once they've outlived their purpose
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int, int action, int)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void mouse_callback(GLFWwindow*, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (GLfloat) xpos;
		lastY = (GLfloat)ypos;
		firstMouse = false;
	}

	GLfloat xoffset = (GLfloat)xpos - lastX;
	GLfloat yoffset = lastY - (GLfloat)ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;

	float sentitivity = 0.25f;

	xoffset *= sentitivity;
	yoffset *= sentitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (true)
	{
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}

		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}
	}
}


void scroll_callback(GLFWwindow*, double, double)
{
	//camera.ProcessMouseScroll(yoffset);
}

void Do_Movement(float deltaTime, BaseCamera& camera)
{
	float speed = 100.0f;
	GLfloat velocity = speed * deltaTime;

	// Camera controls
	if (keys[GLFW_KEY_W])
	{
		camera.translate(camera.getDirection() * velocity);
	}

	if (keys[GLFW_KEY_S])
	{
		camera.translate(-camera.getDirection() * velocity);
	}

	Vector3<float> right(camera.getDirection());
	right.cross(camera.getUp()).normalize();

	if (keys[GLFW_KEY_A])
	{
		camera.translate(-right * velocity);
	}

	if (keys[GLFW_KEY_D])
	{
		camera.translate(right * velocity);
	}

	if (Yaw != 0 || Pitch != 0)
	{
		Vec3f direction(camera.getDirection());
		//Vec3f right(camera.getDirection());
		//right.cross(camera.getUp());
		//right.normalize();
		camera.rotateDegrees(right.x, right.y, right.z, Pitch);
		camera.rotateDegrees(.0f, 1.0f, 0.0f, -Yaw); // This should be the updated UP vector of the camera

		Yaw = .0f;
		Pitch = .0f;
	}

	camera.update();

}

#endif