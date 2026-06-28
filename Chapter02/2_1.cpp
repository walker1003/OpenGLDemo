#include <GL/glew.h>    // OpenGL扩展
#include <GLFW/glfw3.h> // OpenGL框架
#include <iostream>

using namespace std;

void init(GLFWwindow* window) { } // 初始化函数，用于在程序开始前加载着色器、设置缓冲区对象等

void display(GLFWwindow* window, double currentTime) { // 渲染函数，负责具体的绘图操作
	glClearColor(01.0, 0.0, 0.0, 1.0); // 设置清除颜色缓冲区时使用的颜色。参数为 (R, G, B, A)，设置为红色，不透明
	glClear(GL_COLOR_BUFFER_BIT);	  // 清除指定的缓冲区。GL_COLOR_BUFFER_BIT 表示清除颜色缓冲区，使其填满上面 glClearColor 设置的红色
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }	   // 初始化 GLFW 库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 设置 OpenGL 主版本号为 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 设置 OpenGL 次版本号为 3
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - program 1", NULL, NULL); // 创建一个窗口对象。参数：宽(600), 高(600), 标题, 全屏模式(NULL), 共享资源窗口(NULL)
	glfwMakeContextCurrent(window);				   // 将创建的窗口的 OpenGL 上下文设置为当前线程的主上下文
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); } // 初始化 GLEW。glewInit 必须在有了 OpenGL 上下文（即执行完上一步）之后调用
	glfwSwapInterval(1);						   // 设置垂直同步（V-Sync）。参数 1 表示缓冲区交换频率与显示器刷新率同步（通常为 60FPS）

	init(window);								   // 调用自定义初始化函数

	while (!glfwWindowShouldClose(window)) {	   // 循环检测窗口是否应该关闭（例如用户点击了关闭按钮）
		display(window, glfwGetTime());			   // 调用渲染函数。glfwGetTime() 获取自 GLFW 初始化以来的运行时间（以秒为单位）
		glfwSwapBuffers(window);				   // 交换缓冲区。OpenGL 使用双缓冲技术，绘图在后缓冲区进行，此函数将其显示到前缓冲区（屏幕）
		glfwPollEvents();						   // 轮询并处理队列中的所有事件（如窗口大小调整、按键按下、鼠标移动等）
	}

	glfwDestroyWindow(window);					   // 当循环结束，销毁窗口并释放资源
	glfwTerminate();							   // 终止 GLFW 库
	exit(EXIT_SUCCESS);							   // 正常退出程序
}