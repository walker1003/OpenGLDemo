#include <GL/glew.h>	// OpenGL扩展
#include <GLFW/glfw3.h> // OpenGL框架
#include <iostream>

using namespace std;

void init(GLFWwindow* window) {
	int size;				// 定义一个整数变量，用来接收查询结果

	// glGetIntegerv 是 OpenGL 的状态查询函数
	// GL_MAX_TEXTURE_IMAGE_UNITS 表示我们要查询：在片元着色器中可以同时使用的最大纹理单元（Texture Units）数量
	// 查询结果将被存储在变量 size 中
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &size);
	cout << size << endl;
}

void display(GLFWwindow* window, double currentTime) {}  // 这里代码为空，表示每一帧都不进行具体的绘图操作（窗口将显示默认背景色，通常是黑色）

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }		// 初始化 GLFW 库，如果失败则退出程序
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	// 设置 OpenGL 版本提示：主版本号 4，次版本号 3 (即使用 OpenGL 4.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - supplemental notes", NULL, NULL); // 创建一个 600x600 像素的窗口，标题为 "Chapter 2 - supplemental notes"
	glfwMakeContextCurrent(window);					// 将该窗口的 OpenGL 上下文设置为当前线程的主上下文
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); } // 初始化 GLEW 以加载 OpenGL 函数指针。必须在 glfwMakeContextCurrent 之后调用
	glfwSwapInterval(1);							// 设置垂直同步（V-Sync）：1 表示每帧至少等待一次屏幕刷新，防止画面撕裂

	init(window);									// 调用定义的 init 函数，在控制台输出纹理单元数量

	while (!glfwWindowShouldClose(window)) {		// 渲染循环：只要窗口没被关闭，就一直运行
		display(window, glfwGetTime());				// 调用 display（虽然目前是空的）
		glfwSwapBuffers(window);					// 交换前后缓冲区（显示绘制内容）
		glfwPollEvents();							// 处理窗口事件（如鼠标点击、按键等）
	}

	glfwDestroyWindow(window);						// 销毁窗口并释放相关资源
	glfwTerminate();								// 终止 GLFW 库
	exit(EXIT_SUCCESS);								// 正常退出
}