#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "Shader.h"
#include <string.h>
#include <algorithm>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window, int key, int scancode, int action, int mods);
float mixValue;
int main(void)
{
	// init 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glViewport(0, 0, 800, 600);

	glClearColor(0.3, 0.4, 0.75, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	int success = true;
	char infoLog[512];

	// Shader
	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

	// VAO, VBO
	float vertices[] = {
		// 位置              // 颜色			   // 材質座標
		 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // 右下
		-1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // 左下
		-1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f   // 顶部
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// VAO 
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// set how to explain VBO (coord, color, texCoord);
	// layout, vecN 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// input setup
	glfwSetKeyCallback(window, process_input);

	 //創建材質
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// 加載圖片一
	int width, height, nChannels;
	// 圖片翻轉打開 (座標系的不同)
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("assets/A.png", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAIL TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);
	
	// 創建另一個材質
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// 載入另一張圖片
	data = stbi_load("assets/B.png", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAIL TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);
	
	shader.use();
	// or shader.setInt("texture1", 0);
	glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader.ID, "texture2"), 1);

	mixValue = 0.5;
	while (!glfwWindowShouldClose(window))
	{
		// 背景顏色
		glClearColor(0.2, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.setFloat("mixValue", mixValue);
		// bind Texture to corresponding texture units 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// enableShader
		shader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// release 
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	return;
}
void process_input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, true); break;
			case GLFW_KEY_ENTER:
			{
				GLint polygonMode;
				glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
				if (polygonMode == GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			case GLFW_KEY_UP:
			{
				std::cout << "Press UP" << std::endl;
				mixValue = std::min(mixValue + 0.1f, 1.0f);
				break;
			}
			case GLFW_KEY_DOWN:
			{
				std::cout << "Press Down" << std::endl;
				mixValue = std::max(mixValue - 0.1f, 0.0f);
				break;
			}
			std::cout << mixValue << std::endl;
		}
	}
	return;
}