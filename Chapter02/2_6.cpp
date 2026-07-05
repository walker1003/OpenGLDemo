#include <GL/glew.h>	// OpenGl扩展
#include <GLFW/glfw3.h> // OpenGL框架
#include <iostream>
#include <string>
#include <fstream>
#include "Utils.h"
using namespace std;

#define numVAOs 1		// 顶点数组对象（VAO）的数量为1

GLuint renderingProgram;// 存储编译链接后的着色器程序对象的ID
GLuint vao[numVAOs];	// 存储生成的VAO的ID数组
GLuint offestLoc;
float x = 0.0f;
float inc = 0.01f;

void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram(); // 创建并存储着色器程序
	glGenVertexArrays(numVAOs, vao);		  // 生成VAO。在现代OpenGL中，即使不传数据也必须绑定一个VAO
	glBindVertexArray(vao[0]);				  // 绑定VAO
}

void diaplsy(GLFWwindow* window, double currentTime) {
	glUseProgram(renderingProgram);			  // 使用我们创建的着色器程序
	glPointSize(30.0f);						  // 设置点的大小为30像素
	glDrawArrays(GL_TRIANGLES, 0, 3);		  // 绘制指令：类型为三角形，从第0个顶点开始，画3个点
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }		// 初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 设置OpenGL版本提示（4.3版本）
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - program 5", NULL, NULL); // 创建窗口
	glfwMakeContextCurrent(window);					// 设置当前窗口为OpenGL上下文环境
	if (glewInit() != GLEW_OK) { exit(EXIT_SUCCESS); }  // 初始化GLEW（必须在有上下文之后）
	glfwSwapInterval(1);							// 开启垂直同步（同步刷新率）

	init(window);

	while (!glfwWindowShouldClose(window)) {		// 渲染循环
		diaplsy(window, glfwGetTime());				// 执行绘图
		glfwSwapBuffers(window);					// 交换缓冲区（双缓冲技术，防止闪烁）
		glfwPollEvents();							// 处理窗口事件（如关闭、缩放）
	}

	glfwDestroyWindow(window);						// 清理窗口
	glfwTerminate();								// 释放GLFW
	exit(EXIT_SUCCESS);
}