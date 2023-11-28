#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "cube.h"
#include "texture.h"
#include "stb_image.h"



void chair(Cube &cube, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    //Sofa Seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.3, -0.9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, .2f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.3 + 0.5 * 0.2, -0.9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, .5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.3 + 0.5 * 0.2, -0.9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.3 + 0.5 * 0.2, -0.9 + 0.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 0.3 + 0.5 * 0.2, -0.9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5 , 0.3 + 0.5 * 0.2, -0.9 + 0.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);



}

void arms(Cube& cube, Cylinder& cyl, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //arms
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15, .025f, 0.025f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15, 0, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.025, 0.05));
    model = als * translateMatrix * rotateXMatrix * rotateYMatrix * scaleMatrix;
    cyl.drawCylinder(ourShader, model, 0.0, 0.0, 0.0, 1.0);
}


void revolving_chair(Cube& cube, Cylinder & cyl, Shader& ourShader, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
  

    //swing-seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.5, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //center
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.5, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.035f, -.2f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.3, 0.25));
    model = als * identityMatrix*translateMatrix;
    arms(cube, cyl, ourShader, lightingShader, model);

    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = als *identityMatrix*translateMatrix* rotateYMatrix;
    arms(cube, cyl, ourShader, lightingShader, model);

    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(240.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = als * identityMatrix * translateMatrix * rotateYMatrix;
    arms(cube, cyl, ourShader, lightingShader, model);




    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.7, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle12
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.7, 0.5 - 0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.1750f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(.5-0.025, 0.7, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle22
    translateMatrix = glm::translate(identityMatrix, glm::vec3(.5-0.025, 0.7, 0.5 - 0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.1750f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 0.5 + 0.025 * 0.2, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, .5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);





}

void fchair(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    //Sofa Seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1, 0.3, -0.9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, .15f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //hande
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 0.65, -0.95));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, .05f, 0.65f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);


    //hande
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, 0.65, -0.95));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, .05f, 0.65f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.3 + 0.5 * 0.2, -0.9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, .5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.65, -0.95+0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.65f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(1.0, 0.0, 0.0));
    model = als * translateMatrix * rotateYMatrix* scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //Sofa leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.65, -0.55-0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.65f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-15.0f), glm::vec3(1.0, 0.0, 0.0));

    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, 0.65, -0.9 + 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.65f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(1.0, 0.0, 0.0));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //Sofa leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, 0.65, -0.45 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.65f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-15.0f), glm::vec3(1.0, 0.0, 0.0));

    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);



}

void fans(Cylinder& cyl, Cube& gcube, glm::mat4 model, Shader& ourShader) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix;

    float rotateAngle_X = 0.0;
    float rotateAngle_Y = 0.0;
    float rotateAngle_Z = 0.0;
    //rope
    translateMatrix = glm::translate(identityMatrix, glm::vec3(.125, 0.0, 0.0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 1.25, 0.05));
    model = translateMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model);


   
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.0, 0.05));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        cyl.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
        cyl.drawCylinderWithMaterialisticProperty(ourShader, model);

    

    //hand1
    //glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.025, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.25, 0.15, 0.5));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model);


    //hand2
    //glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.025, 0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-125.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-3.20, 0.15, 0.5));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model);

    //hand3
    //glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.025, 0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(240.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.15, 3.25));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model);

    


}

#pragma once
