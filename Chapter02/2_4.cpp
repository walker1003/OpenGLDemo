#include <GL/glew.h>	// OpenGl扩展
#include <GLFW/glfw3.h> // OpenGL框架
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define numVAOs 1		// 顶点数组对象（VAO）的数量为1

GLuint renderingProgram;// 存储编译链接后的着色器程序对象的ID
GLuint vao[numVAOs];	// 存储生成的VAO的ID数组

string readFile(const char* filePath) { // 读取顶点着色器和片元着色器的文本
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint createShaderProgram() {
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);  // 创建顶点着色器对象
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);// 创建片元着色器对象
	GLuint vfprogram = glCreateProgram();				// 创建空的着色器程序对象

	string vertShaderStr = readFile("vertShader_2_4.glsl");
	string fragShaderStr = readFile("fragShader_2_4.glsl");
	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();

	glShaderSource(vShader, 1, &vertShaderSrc, NULL);	// 加载源码到着色器对象
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);	// 加载源码到着色器对象
	glCompileShader(vShader);							// 编译顶点着色器
	glCompileShader(fShader);							// 编译片元着色器
	
	glAttachShader(vfprogram, vShader); // 将编译好的着色器附加到程序上
	glAttachShader(vfprogram, fShader); // 将编译好的着色器附加到程序上
	glLinkProgram(vfprogram);			// 链接程序（合并顶点和片元阶段）
	
	return vfprogram;					// 返回生成的程序ID
}

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram(); // 创建并存储着色器程序
	glGenVertexArrays(numVAOs, vao);		  // 生成VAO。在现代OpenGL中，即使不传数据也必须绑定一个VAO
	glBindVertexArray(vao[0]);				  // 绑定VAO
}

void diaplsy(GLFWwindow* window, double currentTime) {
	glUseProgram(renderingProgram);			  // 使用我们创建的着色器程序
	glPointSize(30.0f);						  // 设置点的大小为30像素
	glDrawArrays(GL_POINTS, 0, 1);			  // 绘制指令：类型为点，从第0个顶点开始，画1个点
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }		// 初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 设置OpenGL版本提示（4.3版本）
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - program 4", NULL, NULL); // 创建窗口
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