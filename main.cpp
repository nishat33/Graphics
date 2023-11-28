//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "walls.h"
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "cube.h"
#include "stb_image.h"
#include "directionalLight.h"
#include "SpotLight.h"
#include "texture.h"
#include "chair.h"
#include "sphere.h"
#include "sofa.h"
#include "rack.h"
#include "lamp.h"
#include "bed.h"
#include "cylinder.h"
#include "roundTable.h"
#include "weardrobe.h"
#include <iostream>
#include "swing.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
//unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);

void scsToWcs(float sx, float sy, float wcsv[3]);
long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);
void drawCurve(Shader ourShader, glm::mat4 moveMatrix, unsigned int VAO, vector<int> indices, glm::vec4 color, float rotateAngleTest_Y)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;

    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngleTest_Y), glm::vec3(0.0f, 1.0f, 0.0f));

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;

    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", color);
    ourShader.setFloat("material.shininess", 32.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);                       
    glBindVertexArray(0);
}
float inc=0.0;
// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// model, view & projection matrix
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

// viewport
GLint viewport[4];

/////////////////////////////////////////////////////////////
float wcsClkDn[3], wcsClkUp[3];
vector <float> cntrlPoints;
vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;

bool isOn = true;
bool isFan = false;

void updateSpotlight(const Shader & shader,const glm::vec3& direction)
{
    shader.setVec3("spotlight.direction", direction);
    
}

void readControlPointsFromFile(const char* filename, std::vector<float>& controlPoints) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        float x, y, z;
        if (!(iss >> x >> y >> z)) {
            std::cout << "Error reading control points from file." << std::endl;
            return;
        }
        cntrlPoints.push_back(x);
        cntrlPoints.push_back(y);
        cntrlPoints.push_back(z);
    }

    file.close();
}
class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];
int mouseButtonFlag = 0;
FILE* fp;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAO;
bool isdoorOpen = false;
bool isVdoorOpen = false;
bool isdrawerOpen = false;
bool almaridoor = false;
float rotateLamp = 0.0;

float doorOpen = 2.25;
// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

float doorMove = 33.5;
float scaleDrawer = 0.0;

float swingAmplitude = 0.5f; // Adjust the amplitude of the swing motion
float swingFrequency = 1.0f; // Adjust the frequency of the swing motion



// camera
Camera camera(glm::vec3(-7, 2.1f, 24.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// lights
// positions of the point lights
glm::vec3 pointLightPositions[] = {
     glm::vec3(0.5f,  6.45f,  4.5),
     //glm::vec3(1.5f,  4.5f,  -6.5 + 0.25f),
     glm::vec3(0.5,  3.2f,   2.5 + 0.25f),
     //glm::vec3(-1.5f,  4.5f,  -6.5 + 0.25f),
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.14f,  //k_l
    0.07f, //k_q
    1       // light number
);

PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.14f,  //k_l
    0.07f, //k_q
    2      // light number
);

DirLight dirLight(
    -0.2f, -1.0f, -0.3f,
    0.45f, 0.45f, 0.45f,
    0.6f,0.6f,0.6f,     // diffuse
    0.5f, 0.5f, 0.5f
);
SpotLight spotLight(
    18, 5.5, 10,
    0.5f + inc, -0.5f+ inc , -0.5f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,   //k_c
    0.045f,  //k_l
    0.0075f, //k_q
    12.5f,
    17.0f
);



// light settings
bool dirLightOn = true;
bool pointLightOn = true;
bool spotLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
float moveKeyboard = 0.0f;
bool isKeyboard = false;
bool isAlna = false;
// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

float rotationAngle = 0.0f;

float gravity = 9.81f;  // Acceleration due to gravity
float pendulumLength = 1.0f;
bool isLamp = false;

void print_menu() {
    cout << "Press key A to move left" << endl;
    cout << "Press key D to move right" << endl;
    cout << "Press key W to move forward" << endl;
    cout << "Press key S to move backwards" << endl;
    cout << "Press key E to move upwards" << endl;
    cout << "Press key R to move downwards" << endl;
    cout << "Press key Q  and Z to rotate along z axis" << endl;
    cout << "Press key C and X to rotate along x axis to move" << endl;
    cout << "Press key Y and V to rotate along y axis" << endl;
    cout << "Press key L to open the entry-door" << endl;
    cout << "Press key K to open the balcondy-door" << endl;
    cout << "Press key M to open the desk-drawer" << endl;
    cout << "Press key N to open the computer-table drawer" << endl;
    cout << "Press key O to open the door-of weardrobe" << endl;
    cout << "Press key U and P to rotate the lamp and change the direction of spotlight" << endl;
    cout << "Press key F to turn to turn on or off the fan" << endl;

}


float rotateFan = 0.0;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Furniture Showoom", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    



    // build and compile our shader zprogram
    // ------------------------------------
    //buildCircle(1, 12);
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    Shader EmmissivelightingShader("EmissiveVertex.vs", "EmissiveFragment.fs");
    Shader lightingShader("vertexShaderLighting.vs", "fragmentShaderlighting.fs");

    string diffuseMapPath = "emoji.png"; //loading image path for diffuse.
    string specularMapPath = "whiteBackground.png"; //loading image path for specular.

                                                                //wrapping           //mapping 
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 3.0f);


    


    diffuseMapPath = "wood4.jpg"; //loading image path for diffuse.
    specularMapPath = "black.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube rcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder rcyl= Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "glass7.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wcube1 = Cube(diffMap, specMap, 52.0f, 0.0f, 0.0f, 6.0f, 2.0f);


    diffuseMapPath = "wall5.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wcube2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 5.0f, 2.0f);

    diffuseMapPath = "stairblack.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wcube3 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 5.0f, 2.0f);

    diffuseMapPath = "stairblack.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube scube = Cube(diffMap, specMap, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder cylr = Cylinder(diffMap, specMap, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "tile4.png"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube fcube = Cube(diffMap, specMap, 52.0f, 0.0f, 0.0f, 5.0f, 6.0f);
    Cube fcube2 = Cube(diffMap, specMap, 52.0f, 0.0f, 0.0f, 2.0f, 4.0f);

    string diffuseMapPath2 = "green3.jpg"; //loading image path for diffuse.
    string specularMapPath2 = "black.png"; //loading image path for specular.
    //wrapping           //mapping 
    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cylinder cyl2 = Cylinder(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    diffuseMapPath = "sofacushion3.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "green3.jpg"; //loading image path for diffuse.
    specularMapPath = "Black.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube3 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "wood2.jpg"; //loading image path for diffuse.
    specularMapPath = "black.png"; //loading image path for specular.

    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder bcyl = Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "fabric2.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bcube2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 4.0f, 5.0f);
    Cylinder bcyl2=Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 4.0f, 5.0f);

    diffuseMapPath = "blanket3.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bcube3 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 4.0f, 5.0f);

    diffuseMapPath = "pillow.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube bcube4 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 4.0f, 5.0f);


    diffuseMapPath = "computer_table.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube ccube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 6.0f);
    Cylinder ccyl= Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 6.0f);
    diffuseMapPath = "red.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube rscube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 1.0f);

    diffuseMapPath = "redfabric.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube rscube2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 1.0f);

    diffuseMapPath = "blanket.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wscube2 = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder cyl4=Cylinder(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "steel.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube stealcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath = "road.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube gcube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 20.0f, 20.0f);


    diffuseMapPath = "bluesky.jpg"; //loading image path for diffuse.
    specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube skycube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 2.0f, 2.0f);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    const char* controlPointsFile = "C:/Users/user/Downloads/Lab 5/Curve/points you can copy.txt";
    const char* vasePointsFile = "C:/Users/user/Downloads/Lab 5/Curve/vasepoint.txt";
    // Read control points from file
    readControlPointsFromFile(controlPointsFile, cntrlPoints);

    loadBezierCurvePoints = true;
    showHollowBezier = true;

    // render loop
    // -----------

    float rotatedoor = 0.0;
    // point light 1
    print_menu();
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

        // render
        // ------
        glClearColor(0.482f, 0.490f, 0.722f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShaderWithTexture.use();
        
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model,moveMatrix,doormodel2;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, .5, .5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        lightingShaderWithTexture.use();



       
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        
        static double lastUpdateTime = glfwGetTime();

       
        double currentTime = glfwGetTime();

        if (currentTime - lastUpdateTime >=120.0) {
            dirLight.ambient = glm::vec3(0.25, 0.25, 0.25);
            dirLight.diffuse = glm::vec3(0.25, 0.25, 0.25);
        }


        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        
        //Emi
        EmmissivelightingShader.use();
        EmmissivelightingShader.setMat4("projection", projection);
        EmmissivelightingShader.setMat4("view", view);



        EmmissivelightingShader.setVec3("emissiveColor", glm::vec3(0.0, 1.0, 1.0));  // Adjust the color as needed
        EmmissivelightingShader.setVec3("objectColor", glm::vec3(0.0, 0.5, 0.5));    // Adjust the color as needed


        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4

        dirLight.setUpDirLight(lightingShaderWithTexture);
        spotLight.setUpSpotLight(lightingShaderWithTexture);


        pointlight1.setUpPointLight(lightingShader);
        pointlight3.setUpPointLight(lightingShader);
        spotLight.setUpSpotLight(lightingShader);
        dirLight.setUpDirLight(lightingShader);
        // ... other uniform settings ...
 
   
        //interior plan
        
      

        walls(wcube1,wcube2, wcube3, skycube, lightingShader, lightingShaderWithTexture, model);
        floor(fcube,gcube, lightingShaderWithTexture, model);
        stairs(scube, lightingShaderWithTexture, model);


        Cube ggcube;

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 6.5, doorOpen));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, -3.05, -2.5));
        moveMatrix = identityMatrix * translateMatrix * scaleMatrix;
        doormodel2 =  moveMatrix;
        ourShader.setMat4("model", doormodel2);
        ggcube.drawCube(ourShader, doormodel2, 0.698, 0.811, 0.8, 0.3);

        if (isVdoorOpen and doorOpen <= 2.25 and doorOpen > -0.4) {

            doorOpen -= 0.1;

        }

        else if (!isVdoorOpen and doorOpen >= -0.5 and doorOpen < 2.25) {
            doorOpen += 0.1;
        }
        
        Cube gcube;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.25, 0.0, doorMove));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, 5));
        moveMatrix = identityMatrix * translateMatrix * scaleMatrix;
        model = model * moveMatrix;

        ourShader.setMat4("model", model);
        gcube.drawCube(ourShader, model, 0.698, 0.811, 0.8, 0.3);

       

        if (isdoorOpen and doorMove<=33.5 and doorMove>30.6) {
            
            doorMove -= .1;

        }

        else if (!isdoorOpen and doorMove >= 30.5 and doorMove < 33.5) {
            doorMove += 0.1;
        }

        //drawTree(ccube, identityMatrix, lightingShaderWithTexture, 10.0f, 90.0f * (3.1416 / 180.0f), 8);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X+2.5, 0.25, translate_Z));
        model = translateMatrix * rotateZMatrix;
        sofa(cube2, cube3, ourShader, lightingShaderWithTexture, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.5, translate_Y, 2.5f));

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, scale_Y, scale_Z));    
        model = model *translateMatrix* rotateYMatrix *scaleMatrix;
        sofa(cube2, cube3, ourShader, lightingShaderWithTexture, model);
        
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.75f+2.5, 0.25, 2.75f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, scale_Y, scale_Z));
        model =  translateMatrix * rotateYMatrix * scaleMatrix;
        sofa(cube2, cube3,ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5, 0.25, 5.5));
        model = translateMatrix * rotateZMatrix;
        sofa(rscube, rscube2, ourShader, lightingShaderWithTexture, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.5, translate_Y, 2.5f));

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, scale_Y, scale_Z));
        model = model * translateMatrix * rotateYMatrix * scaleMatrix;
        sofa(rscube, rscube2, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.05f, 0.25, 8.75f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, scale_Y, scale_Z));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        sofa(rscube, rscube2, ourShader, lightingShaderWithTexture, model);


       
        translateMatrix = glm::translate(identityMatrix, glm::vec3(3, 0.25, 9));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, scale_Y, scale_Z));
        model = identityMatrix * translateMatrix * scaleMatrix;
        lightingShaderWithTexture.setMat4("model", model);
        computer_table(bcube, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(3, 0.25, 9+ moveKeyboard));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, scale_Y, scale_Z));
        model = identityMatrix * translateMatrix * scaleMatrix;
        moveMatrix = identityMatrix * model;
        lightingShaderWithTexture.setMat4("model", model);
        keyboard_holder(bcube, ourShader, lightingShaderWithTexture, model);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.25, 9));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, scale_Y, scale_Z));
        model =identityMatrix* translateMatrix * scaleMatrix;
        
        lightingShaderWithTexture.setMat4("model", model);
        study_table(bcube, ourShader, lightingShaderWithTexture, model);

        moveMatrix = identityMatrix;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.25, 9 + scaleDrawer));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, scale_Y, scale_Z));
        model = identityMatrix * translateMatrix * scaleMatrix;
        moveMatrix = identityMatrix*model;
        lightingShaderWithTexture.setMat4("model", moveMatrix);
        drawer(bcube, ourShader, lightingShaderWithTexture, moveMatrix);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.0, -4.50));
        model = identityMatrix * translateMatrix;
        study_table(ccube, ourShader, lightingShaderWithTexture, model);








        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.75, 0.0, -4.50));
        model = identityMatrix * translateMatrix;
        computer_table(rcube, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.25, 0.0, -4.50));
        model = identityMatrix * translateMatrix;
        study_table(rcube, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.75, 0.0, -4.50));
        model = identityMatrix * translateMatrix;
        computer_table(bcube, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, translate_Y, 4.75f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_Y, 0.85, scale_Z));
        model =translateMatrix* scaleMatrix;
        coffeTable(cyl2,ourShader,lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, translate_Y,7.75f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_Y, 0.85, scale_Z));
        model = translateMatrix * scaleMatrix;
        coffeTable(cylr, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, translate_Y, 10.75f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_Y, 0.85, scale_Z));
        model = translateMatrix * scaleMatrix;
        coffeTable(ccyl, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, -0.25, 5));
        model =identityMatrix* translateMatrix ;
        duvan(ccube,wscube2,ccyl,cyl4,lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, -0.25, 1));
        model = identityMatrix * translateMatrix;
        duvan(bcube, bcube2, bcyl, bcyl2, lightingShaderWithTexture, model);

       

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4, translate_Y, 13));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model =identityMatrix* translateMatrix*rotateYMatrix ;

        study_table2(bcube, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.5, -0.25, 3.75));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, .5, .5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        rack1(rcube,lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.35,0,-2.5));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, .5, .5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        boxshelf(ccube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, -0.05, 3.75));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, .5, .5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        boxshelf(rcube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(8.5, -0.25, 9));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, .5, .5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        rack1(ccube, lightingShaderWithTexture, model);

      
        ////light
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75, 3.0, 0.0));
        //scaleMatrix= glm::scale(identityMatrix, glm::vec3(.025, 0.5, .025));
        //model = identityMatrix * translateMatrix*scaleMatrix;
        //cube.drawCube(ourShader, model, 0.0,0.0,0.0);

        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75, 2.95, 0.0));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(.125, .125, .125));
        //model = identityMatrix * translateMatrix*scaleMatrix;
        //Sphere sphere = Sphere();
        //sphere.drawSphere(EmmissivelightingShader, model);
        
        

        //room 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, translate_Y, 2.00f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix;
        bed(bcube, bcube2, bcube3, bcube4, lightingShaderWithTexture, model);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.5, translate_Y, 2.00f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix;
        bed(rcube, bcube2, bcube3, bcube4, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(13.5, translate_Y, 2.00f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix;
        bed(ccube, bcube2, bcube3, bcube4, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, translate_Y, 5.00f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix;
        bed2(bcube, bcube2, bcube3, bcube4,bcyl, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.5, translate_Y, 5.00f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix;
        bed2(rcube, bcube2, bcube3, bcube4, rcyl, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(13.5, translate_Y,5.00f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix;
        bed2(ccube, bcube2, bcube3, bcube4, ccyl, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 0.0, 8.00f));
        model = identityMatrix*translateMatrix;
        alna(bcube, bcyl, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.5, 0.0, 8.00f));
        model = identityMatrix * translateMatrix;
        alna(rcube, bcyl, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(13.5, 0.0, 8.00f));
        model = identityMatrix * translateMatrix;
        alna(ccube, bcyl, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(18, 0.0, 2.00f));
        model = translateMatrix * rotateYMatrix;
        weardrobe(ccube, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 0.0, 2.00f));
        model = translateMatrix * rotateYMatrix;
        weardrobe2(rcube, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(20.5, 0.0, 5.00f));
        model = translateMatrix * rotateYMatrix;
        weardrobe(ccube, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(18.5, 0.0, 5.00f));
        model = translateMatrix * rotateYMatrix;
        weardrobe3(ccube, ourShader, lightingShaderWithTexture, model);

        glm::mat4 model2;


        if (almaridoor) {
            rotatedoor += 1.0;
            if (rotatedoor >90.0) {
                rotatedoor = 90.0f;
            }
            translateMatrix = glm::translate(identityMatrix, glm::vec3(16.5, 0.125, 5.00f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-rotatedoor), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 2 - 0.125, 0.105f));
            model2 = translateMatrix * rotateYMatrix* scaleMatrix;
            cube.drawCube(ourShader, model2, 0.698, 0.811, 0.8, 1);
        }
        
        else {
            rotatedoor -= 1.0;
            if (rotatedoor <= 0.0) {
                rotatedoor = 0.0f;
            }
            translateMatrix = glm::translate(identityMatrix, glm::vec3(16.5, 0.125, 5.00f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-rotatedoor), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 2 - 0.125, 0.105f));
            model = translateMatrix * rotateYMatrix* scaleMatrix;
            cube.drawCube(ourShader, model, 0.698, 0.811, 0.8, 1);
        }

       
        
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(21, 0.0, 7.50f));
        model =identityMatrix* translateMatrix* rotateYMatrix;
        weardrobe4(stealcube, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(19, 0.0, 10.50f));
        model = identityMatrix * translateMatrix ;
        bedsidetable(bcube, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(16, 0.0, 10.50f));
        model = identityMatrix * translateMatrix;
        bedsidetable(rcube, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(13, 0.0, 10.50f));
        model = identityMatrix * translateMatrix;
        bedsidetable(ccube, ourShader, lightingShaderWithTexture, model);


        //top floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2, 3.25, 0));
        model = identityMatrix * translateMatrix;
        swing(wcube3, ccube, ccyl,ourShader, lightingShaderWithTexture, model);
        
        float time = glfwGetTime();
        float theta = glm::radians(30.0f) * std::sin(std::sqrt(gravity / pendulumLength) * time);

        glm::mat4 rotateMatrix, modelMatrix;

        rotateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.7f, 0.0f)) *  
            glm::rotate(identityMatrix, theta, glm::vec3(1.0f, 0.0, 0.0f)) *  
            glm::translate(identityMatrix, glm::vec3(0.0f, -1.7f, 0.0f));  

        // Combine translation and rotation
        modelMatrix = translateMatrix * rotateMatrix;
        dolna(bcube3, rcube, bcyl, ourShader, lightingShaderWithTexture, modelMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(2, 3.25, 3));
        model = identityMatrix * translateMatrix;
        swing(bcube3, rcube, bcyl, ourShader, lightingShaderWithTexture, model);
        modelMatrix = translateMatrix * rotateMatrix;
        dolna(rcube, ccube, ccyl, ourShader, lightingShaderWithTexture, modelMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(2, 3.25, 6));
        model = identityMatrix * translateMatrix;
        swing(rcube, bcube, rcyl, ourShader, lightingShaderWithTexture, model);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2, 3.25, 6));
        modelMatrix = translateMatrix * rotateMatrix;
        dolna(ccube, ccube, ccyl, ourShader, lightingShaderWithTexture, modelMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(2, 3.25, 9));
        model = identityMatrix * translateMatrix;
        swing(wcube3, ccube, bcyl, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(2, 3.25, 9));
        modelMatrix = translateMatrix * rotateMatrix;
        dolna(bcube, rcube, ccyl, ourShader, lightingShaderWithTexture, modelMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 3.25, 0));
        model = identityMatrix * translateMatrix;
        diningTable(wcube3, cylr, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.25, 3.5, -0.5));
        model = identityMatrix * translateMatrix;
        chair(wcube3, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.25, 3.5, -0.5));
        model = identityMatrix * translateMatrix;
        chair(wcube3, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.25, 3.5, 1));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        model = identityMatrix * translateMatrix* rotateYMatrix;
        chair(wcube3, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.25, 3.5, 1));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        model = identityMatrix * translateMatrix* rotateYMatrix;
        chair(wcube3, lightingShaderWithTexture, model);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 3.25, 5));
        model = identityMatrix * translateMatrix;
        diningTable(ccube, ccyl, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.25, 3.5, 4.5));
        model = identityMatrix * translateMatrix;
        chair(ccube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.25, 3.5, 4.5));
        model = identityMatrix * translateMatrix;
        chair(ccube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.25, 3.5, 6));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        model = identityMatrix * translateMatrix * rotateYMatrix;
        chair(ccube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.25, 3.5, 6));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        model = identityMatrix * translateMatrix * rotateYMatrix;
        chair(ccube, lightingShaderWithTexture, model);




        translateMatrix = glm::translate(identityMatrix, glm::vec3(5, 3.25, 10));
        model = identityMatrix * translateMatrix;
        diningTable(rcube, rcyl, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.25, 3.5, 9.5));
        model = identityMatrix * translateMatrix;
        chair(rcube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.25, 3.5, 9.5));
        model = identityMatrix * translateMatrix;
        chair(rcube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.25, 3.5, 11));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        model = identityMatrix * translateMatrix * rotateYMatrix;
        chair(rcube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.25, 3.5, 11));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        model = identityMatrix * translateMatrix * rotateYMatrix;
        chair(rcube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(8, 3.25, 0));
        model = identityMatrix * translateMatrix;
        dressingTable(ccube,ccyl, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(8, 3.25, 4));
        model = identityMatrix * translateMatrix;
        dressingTable(rcube, rcyl, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(8, 3.25, 8));
        model = identityMatrix * translateMatrix;
        dressingTable(bcube, bcyl, ourShader, lightingShaderWithTexture, model);
        

        translateMatrix = glm::translate(identityMatrix, glm::vec3(11, 3.3, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.5f, 1.5f));
        model = identityMatrix * translateMatrix*scaleMatrix;
        revolving_chair(bcube, bcyl, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(13.5, 3.3, 0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.5f, 1.5f));
        model = identityMatrix * translateMatrix * scaleMatrix;
        revolving_chair(rcube, rcyl, ourShader, lightingShaderWithTexture, model);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(11, 3.3, 3));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.5f, 1.5f));
        model = identityMatrix * translateMatrix* scaleMatrix;
        revolving_chair(wcube3, ccyl, ourShader, lightingShaderWithTexture, model);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(13.5, 3.3, 3));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.5f, 1.5f));
        model = identityMatrix * translateMatrix * scaleMatrix;
        revolving_chair(ccube, ccyl, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(18, 3.3, 0));
        model = identityMatrix * translateMatrix;
        Ltable(ccube, ourShader, lightingShaderWithTexture, model);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(18, 3.3, 20));
        rotateYMatrix = glm::scale(identityMatrix,  glm::vec3(1.0f, 1.0f, -1.0f));
        model = identityMatrix * translateMatrix*rotateYMatrix;
        Ltable(rcube, ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(18, 5.5, 10));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025, 0.05, -0.75));
        model =  translateMatrix * scaleMatrix;
        rcube.drawCubeWithTexture(lightingShaderWithTexture, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

        translateMatrix = glm::translate(identityMatrix, glm::vec3(18, 5.5, 10-0.75));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025, -2.0, 0.025));
        model = translateMatrix * scaleMatrix;
        rcube.drawCubeWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2, 3.5, 10 - 0.75));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
        model = translateMatrix * scaleMatrix;
        fchair(cube3, wcube3, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2, 3.5, 10 - 0.75));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, -1.0));
        model = translateMatrix * scaleMatrix;
        fchair(cube3, wcube3, lightingShaderWithTexture, model);
        

        translateMatrix = glm::translate(identityMatrix, glm::vec3(14, 3.5, 10 - 0.75));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, -1.0));
        model = translateMatrix * scaleMatrix;
        coffeTable(bcyl2,ourShader, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(14, 3.5, 9 - 0.75));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
        model = translateMatrix * scaleMatrix;
        chair(rcube, lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 3.00, 0.05));
    
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.25, 0.05));
        model = translateMatrix *  scaleMatrix;
        ccyl.drawCylinderWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 2.75, 0.05));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.15, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ccyl.drawCylinderWithTexture(lightingShaderWithTexture, model);

        if (isFan) {
            rotateFan = rotateFan + 4.5;
            if (rotateFan > 360.0) {
                rotateFan = 0.0;
            }
            
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 2.75, 0));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y+ rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.25, 0.15, 0.5));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture (lightingShaderWithTexture,model);

            
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-125.0f+rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);


            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(245.0f+ rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.15, 3.25));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 2.75, 0));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.25, 0.15, 0.5));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);

            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-125.0f + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);


            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(240.0f + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.15, 3.25));
            
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }


        //fan2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(15.125, 3.00, 0.05));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.25, 0.05));
        model = translateMatrix * scaleMatrix;
        ccyl.drawCylinderWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(15.125, 2.75, 0.05));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.15, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        ccyl.drawCylinderWithTexture(lightingShaderWithTexture, model);

        if (isFan) {
            rotateFan = rotateFan + 1.0;
            if (rotateFan > 360.0) {
                rotateFan = 0.0;
            }

            translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 2.75, 0));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.25, 0.15, 0.5));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);


            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-125.0f + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);


            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(245.0f + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.15, 3.25));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 2.75, 0));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.25, 0.15, 0.5));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);

            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-125.0f + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);


            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(240.0f + rotateFan), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.15, 3.25));

            model = translateMatrix * rotateYMatrix * scaleMatrix;
            rcube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }


        glm::mat4 model3;
        if (loadBezierCurvePoints)
        {
            bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
            loadBezierCurvePoints = false;
            showHollowBezier = true;
            showControlPoints = false;
        }
        if (showHollowBezier)
        {
           
                if (rotateLamp >90.0) {
                    rotateLamp = 90.f;
                }
                else if (rotateLamp <-90.0) {
                    rotateLamp = -90.0f;
                }
                float theta = glm::radians(rotateLamp);

                float x = std::sin(theta);
                float y = std::cos(theta);// Assuming no change in the y-direction
                float z = 0.0;

      

                inc = rotateLamp;
                spotLight.direction = glm::vec3(-x,-y,-z);
                translateMatrix = glm::translate(identityMatrix, glm::vec3(18, 3.75, 10));
                rotateYMatrix = glm::translate(identityMatrix, glm::vec3 (0, 2, 0)) *
                glm::rotate(identityMatrix, glm::radians(rotateLamp), glm::vec3(0.0,0.0f, -1.0f)) *
                glm::translate(identityMatrix, glm::vec3(0, -2, 0));
                model3 = translateMatrix * rotateYMatrix;

                lightingShader.use();

                lightingShader.setMat4("model", model3);
                lightingShader.setVec3("material.ambient", glm::vec3(0.3f, 0.0f, 0.3f));
                lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
                lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
                lightingShader.setFloat("material.shininess", 32.0f);

                glBindVertexArray(bezierVAO);
                glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
                glBindVertexArray(0);

            
            
           
        }
        spotLight.setUpSpotLight(lightingShader);
        spotLight.setUpSpotLight(lightingShaderWithTexture);
        glDepthMask(GL_TRUE);


        // we now draw as many light bulbs as we have point lights.
        for (unsigned int i = 0; i < 2; i++)
        {
            
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(1.5,0.05,0.05f)); // Make it a smaller cube
            if (isOn) {
                cube.drawCube(ourShader, model, 0.8f, 0.8f, 0.8f);
            }
            else {
                cube.drawCube(EmmissivelightingShader, model);
            }
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }




    

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        pointlight1.turnOn();
        pointlight3.turnOn();
        isOn = true;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        pointlight1.turnOff();
        pointlight3.turnOff();
        isOn = false;
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        spotLight.turnDiffuseOn();
        dirLight.turnDiffuseOn();

    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {

        pointlight1.turnOff();
        pointlight3.turnOff();
        dirLight.turnOff();
        spotLight.turnOff();

    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        dirLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        dirLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        spotLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        spotLight.turnOff();
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        if (almaridoor) {
            almaridoor = false;
        }
        else {
            almaridoor = true;

        }

    }

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
     /*   if (isLamp) {
            isLamp = false;
        }
        else {
            isLamp = true;

        }*/

        rotateLamp += 10.0;

    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        /*   if (isLamp) {
               isLamp = false;
           }
           else {
               isLamp = true;

           }*/

        rotateLamp -= 10.0;

    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {

        isdoorOpen = !isdoorOpen;

    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {

        isVdoorOpen = !isVdoorOpen;


    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {

        if (isdrawerOpen) {
            scaleDrawer += .1;
            if (scaleDrawer >= 1.0) {
                scaleDrawer = 1.0;
                isdrawerOpen = false;
            }
        }
        else {
            scaleDrawer -= .1;
            if (scaleDrawer <= 0.0) {
                scaleDrawer = 0.0;
                isdrawerOpen = true;
            }
        }


    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {

        if (isFan) {
            isFan = false;
        }
        else {
            isFan = true;
        }


    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {

        if (isAlna) {
            isAlna = false;
        }
        else {
            isAlna = true;
        }


    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {

        if (isKeyboard) {
            moveKeyboard += .1;
            if (moveKeyboard >= 0.75) {
                moveKeyboard = 1.0;
                isKeyboard = false;
            }
        }
        else {
            moveKeyboard -= .1;
            if (moveKeyboard <= 0.0) {
                moveKeyboard = 0.0;
                isKeyboard = true;
            }
        }


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

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

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


unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true); //loading texture
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0); //call by referencing width, height, and then channels
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); //0->bitp level. if incresead the resolution will drop
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS); //texturemapping and wrapping , along S axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT); //for T axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin); //minification mode filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    //binding with texture id.

    return textureID;
}

// This function converts the screen coordinates to world coordinates
// ---------------------------------------------------------------------------------------------
void scsToWcs(float sx, float sy, float wcsv[3])
{

    glm::vec4 winCoordinateVector; //vector to hold screen x,y,z coordinates
    glm::vec4 worldCoordinateVector; //vector to hold world x,y,z coordinates

    glGetIntegerv(GL_VIEWPORT, viewport); //get the viewport info

    // setup screen coordinates values
    winCoordinateVector.x = sx;
    winCoordinateVector.y = (float)viewport[3] - (float)sy; // reversed since y-coordinates go from bottom to top
    winCoordinateVector.z = 0.0f;
    winCoordinateVector.w = 1.0f;

    // prepare viewport matrix
    float v_l = viewport[0], v_b = viewport[1], v_r = viewport[2], v_t = viewport[3];
    glm::mat4 viewportMat = glm::mat4(1.0f);
    viewportMat[0].x = (v_r - v_l) / 2.0f;  viewportMat[1].x = 0.0f; viewportMat[2].x = 0.0f;  viewportMat[3].x = (v_r + v_l) / 2.0f;
    viewportMat[0].y = 0.0f; viewportMat[1].y = (v_t - v_b) / 2.0f;  viewportMat[2].y = 0.0f;  viewportMat[3].y = (v_t + v_b) / 2.0f;
    viewportMat[0].z = 0.0f; viewportMat[1].z = 0.0f; viewportMat[2].z = 0.5f;  viewportMat[3].z = 0.5f;
    viewportMat[0].w = 0.0f; viewportMat[1].w = 0.0f; viewportMat[2].w = 0.0f;  viewportMat[3].w = 1.0f;

    //get the world coordinates from the screen coordinates
    worldCoordinateVector = glm::inverse(viewportMat * projection * view * model) * winCoordinateVector;
    wcsv[0] = worldCoordinateVector.x / worldCoordinateVector.w;
    wcsv[1] = worldCoordinateVector.y / worldCoordinateVector.w;
    wcsv[2] = worldCoordinateVector.z / worldCoordinateVector.w;
}

// glfw: whenever mouse button is pressed, this callback is called
// -------------------------------------------------------



long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}
