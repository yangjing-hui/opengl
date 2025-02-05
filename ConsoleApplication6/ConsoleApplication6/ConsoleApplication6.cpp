#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
int num = 0;
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//鼠标滚轮输入 鼠标滚轮事件也是回调函数的方式来实现输入与处理。

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);
    Shader ourShader("3.3.shader.vs", "3.3.shader.fs"); // you can name your shader files however you like
    float vertices[] = {
         0.2f,  0.1f,  0.1f,  0.0f, 0.0f,
         0.7f,  0.1f,  0.1f,  1.0f, 0.0f,
         0.7f,  0.6f,  0.1f,  1.0f, 1.0f,
         0.7f,  0.6f,  0.1f,  1.0f, 1.0f,
         0.2f,  0.6f,  0.1f,  0.0f, 1.0f,
         0.2f,  0.1f,  0.1f,  0.0f, 0.0f,//1

         0.2f,  0.1f,  0.6f,  0.0f, 0.0f,
         0.7f,  0.1f,  0.6f,  1.0f, 0.0f,
         0.7f,  0.6f,  0.6f,  1.0f, 1.0f,
         0.7f,  0.6f,  0.6f,  1.0f, 1.0f,
         0.2f,  0.6f,  0.6f,  0.0f, 1.0f,
         0.2f,  0.1f,  0.6f,  0.0f, 0.0f,//2

         0.2f,  0.6f,  0.6f,  1.0f, 0.0f,
         0.2f,  0.6f,  0.1f,  1.0f, 1.0f,
         0.2f,  0.1f,  0.1f,  0.0f, 1.0f,
         0.2f,  0.1f,  0.1f,  0.0f, 1.0f,
         0.2f,  0.1f,  0.6f,  0.0f, 0.0f,
         0.2f,  0.6f,  0.6f,  1.0f, 0.0f,//3

         0.7f,  0.6f,  0.6f,  1.0f, 0.0f,
         0.7f,  0.6f,  0.1f,  1.0f, 1.0f,
         0.7f,  0.1f,  0.1f,  0.0f, 1.0f,
         0.7f,  0.1f,  0.1f,  0.0f, 1.0f,
         0.7f,  0.1f,  0.6f,  0.0f, 0.0f,
         0.7f,  0.6f,  0.6f,  1.0f, 0.0f,//4

         0.2f,  0.1f,  0.1f,  0.0f, 1.0f,
         0.7f,  0.1f,  0.1f,  1.0f, 1.0f,
         0.7f,  0.1f,  0.6f,  1.0f, 0.0f,
         0.7f,  0.1f,  0.6f,  1.0f, 0.0f,
         0.2f,  0.1f,  0.6f,  0.0f, 0.0f,
         0.2f,  0.1f,  0.1f,  0.0f, 1.0f,//5

         0.2f,  0.6f,  0.1f,  0.0f, 1.0f,
         0.7f,  0.6f,  0.1f,  1.0f, 1.0f,
         0.7f,  0.6f,  0.6f,  1.0f, 0.0f,
         0.7f,  0.6f,  0.6f,  1.0f, 0.0f,
         0.2f,  0.6f,  0.6f,  0.0f, 0.0f,
         0.2f,  0.6f,  0.1f,  0.0f, 1.0f//6
    };

    float vertices1[] = {
        1.6f, 1.0f, -0.1f, 0.0f, 1.0f,
        1.6f, 0.0f, -0.1f, 1.0f, 1.0f,
        0.6f, 0.0f, -0.1f, 1.0f, 0.0f,
        0.6f, 1.0f, -0.1f, 0.0f, 0.0f
    };


    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    float vertices2[] = {
        -0.5f, 1.25f, -0.1f, 0.0f, 0.75f,
        0.0f, 0.5f, -0.1f, 0.5f, 0.0f,
        0.5f, 1.25f, -0.1f,1.0f, 0.75f,
        -0.5f, 0.75f, -0.1f, 0.0f, 0.25f,
        0.0f, 1.5f, -0.1f, 0.5f, 1.0f,
        0.5f, 0.75f, -0.1f, 1.0f, 0.25f,
    };

    GLuint indices1[] = {
        0, 1, 2,
        3, 4, 5,
    };

    float vertices3[] = {
        0.0f, 0.814f-0.5f, -0.1f, 0.5f, 0.814f,
        0.0f, 0.364f-0.5f, -0.1f, 0.5f, 0.364f,
        0.42795f, 0.5031f-0.5f, -0.1f, 0.42795f+0.5f, 0.5031f,

        0.42795f, 0.5031f-0.5f, -0.1f, 0.42795f+ 0.5f, 0.5031f,
        0.0f, 0.364f-0.5f, -0.1f, 0.5f, 0.364f,
        0.2645f, 0.0f-0.5f, -0.1f, 0.2645f+0.5f, 0.0f,

        0.2645f, 0.0f-0.5f, -0.1f, 0.2645f+ 0.5f, 0.0f,
        0.0f, 0.364f-0.5f, -0.1f, 0.5f, 0.364f,
        -0.2645f, 0.0f-0.5f, -0.1f, -0.2645f+ 0.5f, 0.0f,

        -0.2645f, 0.0f-0.5f, -0.1f, -0.2645f+ 0.5f, 0.0f,
        0.0f, 0.364f-0.5f, -0.1f, 0.5f, 0.364f,
        -0.42795f, 0.5031f-0.5f, -0.1f, -0.42795f+ 0.5f, 0.5031f,

        -0.42795f, 0.5031f-0.5f, -0.1f, -0.42795f+ 0.5f, 0.5031f,
        0.0f, 0.364f-0.5f, -0.1f, 0.5f, 0.364f,
        0.0f, 0.814f-0.5f, -0.1f,  0.5f, 0.814f,
    };

    GLuint indices2[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
    };
    unsigned int VBO[4], VAO[4], EBO[3];
    glGenVertexArrays(5, VAO);
    glGenBuffers(5, VBO);
    glGenBuffers(4, EBO);
    glBindVertexArray(0);

    //立方体
    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //矩形
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 *sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //六角星
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //五边形
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //texture1
    unsigned int texture, texture1, texture2;//创建纹理
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);//绑定纹理

    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //下面这句用来翻转图片y轴，因为图片y轴正方向的定义往往和opengl的相反，所以在加载图片前加上这一句
    stbi_set_flip_vertically_on_load(true);
    /* stbi_load函数参数分别表示：图像文件的位置、图像的宽度、高度和颜色通道。
    我们之后生成纹理的时候会用到的图像的宽度和高度的。*/
    //记得图像路径根据你们的图像位置更改，我这里是把纹理图像和addTexture.cpp放在了同一级目录下了
    int width, height, nrChannels;
    unsigned char* data = stbi_load("baby.jpg", &width, &height, &nrChannels, 0);//注意自己纹理图片的格式,可能是png,jpg等
    //注意，这里输出的channels数如果是3，说明没有透明度通道 glTexImage2D中应该是GL_RGB,而非GL_RGBA
    std::cout << width << " " << height << " " << nrChannels << std::endl;
    if (data)
    {
        //用载入的图片数据生成一个纹理，纹理可以通过glTexImage2D来生成：
       // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐远纹理
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);//释放内存

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("bear.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("drink.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindTexture(GL_TEXTURE_2D, texture1);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        //glActiveTexture(GL_TEXTURE0);
        if (num <= 500)
            glBindTexture(GL_TEXTURE_2D, texture);
        else if (num >= 500 && num <= 1000)
            glBindTexture(GL_TEXTURE_2D, texture1);
        else
            glBindTexture(GL_TEXTURE_2D, texture2);
        ourShader.use();
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);


        // calculate the model matrix for each object and pass it to shader before drawing
        {    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[0]);
        float angle = 50.0;
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMat4("model", model);
    }

        // render box
        //立方体
        glBindVertexArray(VAO[0]);
        {    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[0]);
        float angle = 50.0;
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMat4("model", model);
        }
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //矩形
        glBindVertexArray(VAO[1]);
        {    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[0]);
        float angle = 50.0;
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMat4("model", model);
        }
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

        //六角星
        glBindVertexArray(VAO[2]);
        {    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[0]);
        float angle = 50.0;
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMat4("model", model);
        }
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

        //五边形
        glBindVertexArray(VAO[3]);
        {    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[0]);
        float angle = 50.0;
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMat4("model", model);
        }
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        num++;
        if (num == 1500)num = 1;


    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = lastX - xpos;
    float yoffset = ypos - lastY; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
