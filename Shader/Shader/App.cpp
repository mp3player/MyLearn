#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include<regex>
#include<cmath>

#include "ShaderUtil.h"
#include "ObjLoader.h"
#include "PerspectiveCamera.h"
#include "Rect.h"
#include "Cube.h"

#define PI 3.141592653589793
glm::vec3 pos = glm::vec3(0,0,3.1);
PerspectiveCamera camera;
glm::mat4 normalMatrix;
int keyPress = 0;
double posX, posY;

static void traverseMatrix(glm::mat4 mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[i][j] << " \t\t ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
static void scrollFn(GLFWwindow* window, double a, double b) {
    pos[2] += b > 0 ? -pos[2] / 10 : pos[2] / 10;
    camera.setPosition(pos.x, pos.y, pos.z);
}
static void mouseFn(GLFWwindow* window, int a, int mode, int c) {
    std::cout << a << "-" << mode << "-" << c << std::endl;
    keyPress = mode;
    glfwGetCursorPos(window, &posX, &posY);//保存posx,posy
}
static void cursorFn(GLFWwindow* window, double a, double b) {
    //std::cout << a << b << std::endl;
    if (keyPress) {
        double angleX = (a - posX) / 90.0f;
        double angleY = (b - posY) / 90.0f;
        posX = a, posY = b;
        
        camera.view = glm::rotate(camera.view, (float)angleX, glm::vec3(0, 1, 0));
        camera.view = glm::rotate(camera.view, (float)angleY, glm::vec3(1, 0, 0));

        //计算法线矩阵
        normalMatrix = glm::inverse(camera.view);
        normalMatrix = glm::transpose(normalMatrix);

        std::cout << angleX << std::endl;
    }
}

struct SpotLight {
    glm::vec3 color;
    glm::vec3 pos;
    glm::vec3 look;
    float intensity;
};
struct AmbientLight {
    glm::vec3 color;
    float intensity;
};
SpotLight l = {
    glm::vec3(1,0,1),
    glm::vec3(.5,1,.5),
    glm::vec3(0,0,0),
    1.0f
};
AmbientLight ambient = {
    glm::vec3(1,1,1),
    0.5
};

int main()
{
    regex r("2");

    string s = "234123sadf23sfasdf";
    smatch res;
    
    regex_match(s,res, r);

    std::cout << res.size() << std::endl;
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    float width = 640, height = 480;

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetScrollCallback(window, scrollFn);
    glfwSetMouseButtonCallback(window, mouseFn);
    glfwSetCursorPosCallback(window, cursorFn);

    camera = PerspectiveCamera(45.f * PI / 180.f, (float)width / (float)height, .1f, 1000.0f);
    camera.setPosition(pos);

    glm::mat4 modelMatrix = glm::mat4(1.0f);



    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    float startTime = glfwGetTime();
    float endTime = glfwGetTime();
    
    ShaderUtil util = ShaderUtil("./shaders/vertex.vert", "./shaders/fragment.frag");
    int shaderProgram = util.getProgram();

    GLuint vao = util.createVAO();
    glBindVertexArray(vao);

    util.createEBO(Cube::index, sizeof(Cube::index));
    util.setVec3(0, Cube::position, sizeof(Cube::position));
    //util.setVec3(1, Cube::color, sizeof(Rect::color));
    util.setVec2(2, Cube::uv, sizeof(Cube::uv));
    util.setVec3(3, Cube::normal, sizeof(Cube::normal));

    GLuint texture = util.createTexture("./source/z.jpg");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        util.setMat4("projectionMatrix", glm::value_ptr(camera.matrix));
        util.setMat4("viewMatrix", glm::value_ptr(camera.view));
        util.setMat4("modelMatrix", glm::value_ptr(modelMatrix));
        util.setMat4("normalMatrix", glm::value_ptr(normalMatrix));

        //点光源
        util.setVec3U("light.position", glm::value_ptr(l.pos));
        util.setVec3U("light.lookAt", glm::value_ptr(l.look));
        util.setVec3U("light.color", glm::value_ptr(l.color));
        util.setFloat("light.intensity", l.intensity);
        //环境光
        util.setVec3U("ambient.color", glm::value_ptr(ambient.color));
        util.setFloat("ambient.intensity", ambient.intensity);

        
        glUseProgram(shaderProgram);
        glBindVertexArray(vao); 
        //glDrawArrays(GL_LINE_LOOP, 0, 6);
        glDrawElements(GL_TRIANGLES, Cube::length, GL_UNSIGNED_INT, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        util.setInt("images", 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        endTime = glfwGetTime();
        modelMatrix = glm::rotate(modelMatrix, endTime - startTime, glm::vec3(0, 1, 1));
        startTime = endTime;
    }
}