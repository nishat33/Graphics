#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"

#include "chair.h"

void coffeTable(Cylinder & cyl,Shader& ourShader, Shader& lightingShader, glm::mat4 alTogether)
{

    float rotateAngle_Y = 0.0;

   
    
    Cube cube4 = Cube();

    glm::mat4 rotateY = glm::mat4(1.0f);
    glm::mat4 rotateZ = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    
    
    //base
    for (float i = 0.0f; i < 45.0f; i += 2.50f) {
        //Center

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.7, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.05, 0.5));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        cyl.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);

    }
    
    //leg 1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.7, 0.0));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.85, 0.05));
    model = alTogether * translateMatrix * rotateZMatrix * scaleMatrix;
    //cube3.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
    cube4.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    
    //leg 2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.7, 0.0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.85, 0.05));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    //cube3.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
    cube4.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    //leg 3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.7, 0.0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.85, 0.05));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    cube4.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    //cube3.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
    //leg 4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.7, 0.0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.85, 0.05));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    //cube3.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
    cube4.drawCube(ourShader, model, 0.0, 0.0, 0.0);


    

    
}

void drawer(Cube& cube,Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15, 0.35, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.65, 0.05, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15, 0.35, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.15, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //right

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.75, 0.35, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.15, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //back

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15, 0.35, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.65, 0.15, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //front

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.15, 0.35, 3.20));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.65, 0.15, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.45, 0.425, 3.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025, 0.025, 0.025));
    model = als * translateMatrix * scaleMatrix;
    Sphere sphere ;
    sphere.drawSphere(lightingShader, model);

}
void study_table(Cube& cube, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {
    
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25, 0.5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.75, 0.05, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25+0.05, 0.5+0.01, 2.25+0.01));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.9, 0.5 + 0.01, 2.25 + 0.01));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25 + 0.05, 0.5 + 0.01, 2.25 + 0.85));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    // leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.9, 0.5 + 0.01, 2.25 + 0.85));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

   // model = als*identityMatrix;
  //  drawer(cube,ourShader, lightingShader, model);
   

}

void keyboard_holder(Cube& cube, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //key-board table
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25+0.05, 0.35, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.25-.1, 0.05, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
    //key-board table
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25+0.05, 0.4, 3.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.25-0.1, -0.125, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
  
}

void computer_table(Cube& cube, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25, 0.5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.75, 0.05, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

   

    //left leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25, 0.5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.5, 1.0));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //right leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25+1.75-0.05, 0.5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.5, 1.0));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //right leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25 + 1.25 - 0.05, 0.5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.35, 1.0));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //bottom
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25 + 1.25 - 0.05, 0.15, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, -0.05, 1.0));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //drawer(cube, ourShader, lightingShader, scaleMatrix);

}


void study_table2(Cube& cube, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25, 0.5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.75, 0.05, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25, .5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.75, 0.7, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25, .5 + 0.7, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.75, 0.05, 0.35));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //top-rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25, .5 + 0.2, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.75, 0.05, 0.35));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
    
    //side-1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25, .5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.7, 0.35));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //side-2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25+1.75-0.05, .5, 2.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.7, 0.35));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);


    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25 + 0.05, 0.5 + 0.01, 2.25 + 0.01));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); 
    //leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.9, 0.5 + 0.01, 2.25 + 0.01));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.25 + 0.05, 0.5 + 0.01, 2.25 + 0.85));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    // leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.9, 0.5 + 0.01, 2.25 + 0.85));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    model = als * identityMatrix;
    drawer(cube, ourShader, lightingShader, model);


}


void bedsidetable(Cube& cube, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 0.05, 1.5));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    Cube cube2;
    //glass
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.5, 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1-0.05, 0.05, 1.5-0.05));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCube(ourShader, model, 0.698, 0.811, 0.8,0.5);

    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1-0.05, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 1.5-0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1-0.05, 0.75, 1.5-0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


}

void Ltable(Cube& cube, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.05, 1.5));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
    // frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.05, 5));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
    
    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3 - 0.05, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 1.5-0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5 - 0.05, 0.75, 1.5-0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg5
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5, 0.75, 5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg6
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3 - 0.05, 0.75, 5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

}

void dressingTable(Cube& cube,Cylinder& cyl, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //head

    //base
    for (float i = 0.0f; i < 45.0f; i += 2.50f) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75, 1.5, 0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.02, 0.5));
        model = als * translateMatrix * rotateXMatrix * rotateYMatrix * scaleMatrix;
        cyl.drawCylinderWithTexture(lightingShader, model);
    }
    Cylinder cyl2;
    //base
    for (float i = 0.0f; i < 45.0f; i += 2.50f) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75, 1.5, 0.002));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.45, 0.02, 0.45));
        model = als * translateMatrix * rotateXMatrix * rotateYMatrix * scaleMatrix;
        cyl2.drawCylinder(ourShader, model, 0.698, 0.811, 0.8, 1);
    }
    //head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.5, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1., -0.75, 0.025));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    Cube cube3;

    //headayna
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.3, 1.5, 0.002));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1-0.1, -0.75, 0.025));
    model = als * translateMatrix * scaleMatrix;
    cube3.drawCube(ourShader, model, 0.698, 0.811, 0.8, 1);

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, -0.25, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    Sphere sphere = Sphere();
    translateMatrix = glm::translate(identityMatrix, glm::vec3(.75, 0.65, 1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 0.05, 0.05));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(ourShader, model);

    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5 - 0.05, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 1 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5 - 0.05, 0.75, 1 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

}


void diningTable(Cube& cube, Cylinder& cyl, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

  

    //base
    for (float i = 0.0f; i < 45.0f; i += 2.50f) {
        //Center

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.20, 1.02, 0.5));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.040, 0.5));
        model = als * translateMatrix * rotateYMatrix * scaleMatrix;
        cyl.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);

    }

    //base
    for (float i = 0.0f; i < 45.0f; i += 2.50f) {
        //Center

        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.30, 1.02, 0.5));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.040, 0.5));
        model = als * translateMatrix * rotateYMatrix * scaleMatrix;
        cyl.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);

    }
    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 1 - (0.065 / 2), 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.065, 1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);


    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 1, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.025, -1, .025));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.45, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.025, .025));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    

    //leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5-0.025, 1, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.025, -1, .025));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 1, 1- 0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.025, -1, .025));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.45, 1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.025, .025));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);


    //leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5-0.025, 1, 1- 0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.025, -1, .025));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
 
}



#pragma once
