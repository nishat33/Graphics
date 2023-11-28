#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "sofa.h"

void walls(Cube &cube, Cube &cube2, Cube &cube3, Cube& cube4,  Shader& ourShader, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    
    Cube tcube, scube;


    /*
    string diffuseMapPath = "glass7.jpg"; //loading image path for diffuse.
    string specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube wcube1 = Cube(diffMap, specMap, 52.0f, 0.0f, 0.0f,6.0f, 2.0f);


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
    */
    //back wall

    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, -0.5, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 7, 0.25));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
   
    //left wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(17, -0.45, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 7, 24));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
    Cube gcube;

    //back wall top floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, 6.5, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 6.5, 0.25));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //side wall left top floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 6.5, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, 6));
    model = alTogether * translateMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model, 0.5);

    //side wall left top floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 6.5, 3.2));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, 25));
    model = alTogether * translateMatrix * scaleMatrix;
    gcube.drawCube(ourShader, model, 0.698, 0.811, 0.8, 0.3);

    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model, 0.5);

    

    //side wall left ground floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, 0.0, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, 35));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

   

    
    //sidewall left rest of the door
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, 0.0, 28.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, 5));
    model = alTogether * translateMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model, 0.5);



    //sidewall left rest of the door
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, 0.0, 43.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, -5));
    model = alTogether * translateMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model, 0.5);




    //side wall left top floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, 6.5, 28.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, 15));
    model = alTogether * translateMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model, 0.5);


    for (float i = 0; i <= 35; i = i + 2) {
        //side railing bars
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, 6.5, -6.5+ i));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 3.0, 0.25));
        model = alTogether * translateMatrix * scaleMatrix;
        cube3.drawCubeWithTexture(lightingShader, model);
    }

    //side railing
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, 9.5, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 0.35, 35));
    model = alTogether * translateMatrix * scaleMatrix;
    cube3.drawCubeWithTexture(lightingShader, model);
    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 6.5, 28.5-0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(25, 6.5, 0.25));
    model = alTogether * translateMatrix * scaleMatrix;
    gcube.setMaterialisticProperty(glm::vec3(0.698, 0.811, 0.8), glm::vec3(0.698, 0.811, 0.8), glm::vec3(1, 1, 1), 52.0);
    gcube.drawCubeWithMaterialisticProperty(ourShader, model);


    //front wall big
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, -0.5, 43.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 13.5, 0.25));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //side wall right top floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(43.5 - 0.25, 6.5, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, 50));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //side wall right ground floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(43.5 - 0.25, 0.0, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 6.5, 50));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //side railing
    translateMatrix = glm::translate(identityMatrix, glm::vec3(24.75, 9.5, 33.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 0.35, 10.25));
    model = alTogether * translateMatrix * scaleMatrix;
    cube3.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-100, 30.5, -100));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(200, 0.35, 200));

    model = alTogether * translateMatrix * scaleMatrix;
    cube4.drawCubeWithTexture(lightingShader, model);


    for (float i = 0; i <=10.25; i = i +2) {
        //side railing bars
        translateMatrix = glm::translate(identityMatrix, glm::vec3(24.75, 6.5, 28.5 + 5 + i));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 3.0, 0.25));
        model = alTogether * translateMatrix * scaleMatrix;
        cube3.drawCubeWithTexture(lightingShader, model);
    }
    
   

    
}


void floor(Cube& cube, Cube&cube2, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    /*
    string diffuseMapPath = "tile4.png"; //loading image path for diffuse.
    string specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube fcube = Cube(diffMap, specMap, 52.0f, 0.0f, 0.0f, 5.0f, 6.0f);
    */
    //floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, -0.5, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, .5, 50));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-100, 30.5, -100));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(200, 0.35, 200));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-50.5, -0.65, -50.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(150, .5, 150));
    model = alTogether * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    

    //roof
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, 13, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50.5, .5, 50.5));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //top floor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5,  6.5, -6.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, .5, 35));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //top floor pt2

    translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 6.5, 28.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(18.5, .5, 15));
    model = alTogether * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);



}

void stairs(Cube & cube, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    /*
    string diffuseMapPath = "stairblack.jpg"; //loading image path for diffuse.
    string specularMapPath = "whiteBackground.png"; //loading image path for specular.

    //wrapping           //mapping 
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube scube = Cube(diffMap, specMap, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    */

    float j = 0;
    for (float i = 0; i <= 6.5; i = i + 1.0) {



        translateMatrix = glm::translate(identityMatrix, glm::vec3(16.5+j, 0.0, 28.5-0.25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.75 + i, 5));
        model = alTogether * translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);

        j =j+ 1.5;
    }
}

#pragma once

#pragma once
