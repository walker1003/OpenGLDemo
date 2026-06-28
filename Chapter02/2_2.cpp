#include <GL/glew.h>	// OpenGL扩展
#include <GLFW/glfw3.h> // OpenGL框架
#include <iostream>
using namespace std;

#define numVAOs 1		// 定义需要创建的顶点数组对象（VAO）的数量为 1

GLuint renderingProgram;// 全局变量：存储编译链接后的着色器程序的 ID
GLuint vao[numVAOs];	// 全局变量：存储顶点数组对象（VAO）句柄的数组

GLuint createShaderProgram() {
	const char* vshaderSource =		// 顶点着色器源码：负责计算顶点位置
		"#version 430		\n"		// 指定使用 GLSL 4.30 版本
		"void main(void)	\n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }"; // 将点硬编码在坐标系原点（屏幕中心）

	const char* fshaderSource =		// 片元着色器源码：负责计算像素颜色
		"#version 430		\n"
		"out vec4 color;	\n"		// 输出变量：像素的最终颜色
		"void main(void)	\n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }"; // 将颜色硬编码为蓝色 (R=0, G=0, B=1, A=1)

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);	// 创建顶点着色器对象
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);// 创建片元着色器对象
	GLuint vfprogram = glCreateProgram();				// 创建一个空的着色器程序容器

	glShaderSource(vShader, 1, &vshaderSource, NULL);	// 将源码字符串传递到着色器对象中
	glShaderSource(fShader, 1, &fshaderSource, NULL);	// 将源码字符串传递到着色器对象中
	glCompileShader(vShader);							// 在 GPU 上编译源码
	glCompileShader(fShader);							// 在 GPU 上编译源码

	glAttachShader(vfprogram, vShader);					// 将编译好的着色器附加到程序容器中
	glAttachShader(vfprogram, fShader);					// 将编译好的着色器附加到程序容器中
	glLinkProgram(vfprogram);							// 链接程序：将多个着色器合并成一个可在 GPU 上运行的整体

	return vfprogram;									// 返回链接好的程序 ID
}

void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();			// 创建并存储着色器程序
	glGenVertexArrays(numVAOs, vao);					// 生成顶点数组对象 (VAO)，在核心模式下，OpenGL 要求至少有一个 VAO 才能进行绘制操作
	glBindVertexArray(vao[0]);							// 绑定该 VAO，使其成为当前操作对象
}

void display(GLFWwindow* window, double currentTime) {	// 渲染函数：每帧执行
	glUseProgram(renderingProgram);						// 告诉 OpenGL 使用之前创建的着色器程序进行绘制
	glPointSize(30.0f);									// 设置绘制的点的大小（单位为像素）
	glDrawArrays(GL_POINTS, 0, 1);						// 执行绘制命令，GL_POINTS: 绘制点，0: 从顶点数据的第 0 个索引开始，1: 总共绘制 1 个顶点
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_SUCCESS); }			// 初始化 GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);		// 配置 OpenGL 版本环境 (4.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - program 2", NULL, NULL); // 创建 600x600 的窗口
	glfwMakeContextCurrent(window);						// 激活窗口上下文
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }	// 初始化 GLEW
	glfwSwapInterval(1);								// 开启垂直同步

	init(window);

	while (!glfwWindowShouldClose(window)) {			// 主循环
		display(window, glfwGetTime());					// 调用绘制函数
		glfwSwapBuffers(window);						// 交换前后缓冲区（双缓冲展示）
		glfwPollEvents();								// 轮询操作系统事件
	}

	glfwDestroyWindow(window);							// 当循环结束，销毁窗口并释放资源
	glfwTerminate();									// 终止 GLFW 库
	exit(EXIT_SUCCESS);
}