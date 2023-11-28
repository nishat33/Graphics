#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "cylinder.h"

void weardrobe(Cube& cube2,  Shader& ourShader, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5-0.125, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 1.25, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 2.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.25, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 1-0.125));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 2, .125f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    Cube cube;
    //door
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.125, -0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 2-0.125, .125f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCube(ourShader, model, 0.455,0.639,0.634,0.5);
}

void weardrobe2(Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5 - 0.125, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 1.25, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 2.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.25, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 1 - 0.125));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 2, .125f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    Cube cube;
    //door
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.125, -0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 2 - 0.125, .125f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
}

void weardrobe3(Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2 - 0.125, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.625, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 1.25, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.25, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 2.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.25, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.25f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 1 - 0.125));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 2, .125f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    Cube cube;
    //door
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.25, 0.125, -0.1250));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 2-0.125, 0.125f));
    //model = als * translateMatrix * scaleMatrix;
    //cube.drawCube(ourShader, model, 0.698, 0.811, 0.8, 1);

    //door
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.125, -0.05));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 2 - 0.125, .125f));
    //model = als * translateMatrix * scaleMatrix;
    //cube.drawCube(ourShader, model, 0.698, 0.811, 0.8, 0.3);
}

void weardrobe4(Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.5 - 0.125, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.85, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.15, 0.125, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.09f, 2, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //tak1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.85+0.125, 0.5, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.095, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //tak2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.85 + 0.125, 1.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.095, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //tak3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.85 + 0.125, 1.5, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.095, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 2.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //racktop
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.5, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.25f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //tacktop
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.5, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.25f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //tacktop
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.25, 1.0, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.25f, .125, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    //back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 1 - 0.125));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5, 2, .125f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    Cube cube;
   

}




#pragma once

#pragma once
