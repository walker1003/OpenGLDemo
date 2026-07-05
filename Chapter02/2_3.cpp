#include <GL/glew.h>	// OpenGl扩展
#include <GLFW/glfw3.h> // OpenGL框架
#include <iostream>
using namespace std;

#define numVAOs 1		// 顶点数组对象（VAO）的数量为1

GLuint renderingProgram;// 存储编译链接后的着色器程序对象的ID
GLuint vao[numVAOs];	// 存储生成的VAO的ID数组

void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);	// 获取着色器错误日志的长度
	if (len > 0) {
		log = (char*)malloc(len);						// 分配内存存储日志
		glGetShaderInfoLog(shader, len, &chWrittn, log);// 获取日志内容
		cout << "Shader Info Log:" << log << endl;
		free(log);										// 释放内存
	}
}

void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);		// 获取连接程序错误日志的长度
	if (len > 0) {
		log = (char*)malloc(len);						// 分配内存存储日志
		glGetProgramInfoLog(prog, len, &chWrittn, log);	// 获取日志内容
		cout << "Program Info Log: " << log << endl;
		free(log);										// 释放内存
	}
}

bool checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();							// 获取OpenGL错误标志
	while (glErr != GL_NO_ERROR) {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

GLuint createShaderProgram() {
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	const char* vshaderSource =		// 顶点着色器代码：决定点的位置
		"#version 430		\n"		// 使用GLSL 4.3版本
		"void main(void)	\n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }"; // 将点固定在裁剪空间的中心(0,0)

	const char* fshaderSource =		// 片元着色器代码：决定点的颜色
		"#version 430		\n"
		"out vec4 color;	\n"		// 输出颜色变量
		"void main(void)	\n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }"; // 设置颜色为蓝色 (R,G,B,A) -> (0,0,1,1)

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);  // 创建顶点着色器对象
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);// 创建片元着色器对象
	GLuint vfprogram = glCreateProgram();				// 创建空的着色器程序对象

	glShaderSource(vShader, 1, &vshaderSource, NULL);	// 加载源码到着色器对象
	glShaderSource(fShader, 1, &fshaderSource, NULL);	// 加载源码到着色器对象

	glCompileShader(vShader);							// 编译顶点着色器
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled); // 检查编译是否成功
	if (vertCompiled != 1) {
		cout << "vertex compilation failed" << endl;
		printShaderLog(vShader);
	}

	glCompileShader(fShader);							// 编译片元着色器
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled); // 检查编译是否成功
	if (fragCompiled != 1) {
		cout << "fragment compilation failed" << endl;
		printShaderLog(fShader);
	}

	glAttachShader(vfprogram, vShader); // 将编译好的着色器附加到程序上
	glAttachShader(vfprogram, fShader); // 将编译好的着色器附加到程序上

	glLinkProgram(vfprogram);			// 链接程序（合并顶点和片元阶段）
	checkOpenGLError();
	glGetProgramiv(vfprogram, GL_LINK_STATUS, &linked); // 检查链接是否成功
	if (linked != 1) {
		cout << "linking failed" << endl;
		printProgramLog(vfprogram);
	}
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
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - program 3", NULL, NULL); // 创建窗口
	glfwMakeContextCurrent(window);					// 设置当前窗口为OpenGL上下文环境
	if (glewInit() != GLEW_OK) { exit(EXIT_SUCCESS); }  // 初始化GLEW（必须在有上下文之后）
	glfwSwapInterval(1);							// 开启垂直同步（同步刷新率）

	init(window);

	while (!glfwWindowShouldClose(window)) {		// 渲染循环
		diaplsy(window, glfwGetTime());				// 执行绘图
		glfwSwapBuffers(window);					// 交换缓冲区（双缓冲技术，防止闪烁）
		glfwPollEvents();							// 处理窗口事件（如关闭、缩放）
	}

	glfwDestroyWindow(window);						// 清理
	glfwTerminate();
	exit(EXIT_SUCCESS);
}