

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cylinder.h"
#include "cube.h"

void rack1(Cube &cube, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    /*
    string diffuseMapPath = "wood4.jpg"; //loading image path for diffuse.
    string specularMapPath = "black.png"; //loading image path for specular.

    //wrapping           //mapping 
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    */



    


    //rack-1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, 0.5, -2.75f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .125f, 0.55f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //first
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.35f, 0.6, -2.75f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f,1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .125f, 0.55f));
    model = als * translateMatrix * rotateXMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //first
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.85f, 1.1, -2.75f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .125f, 0.55f));
    model = als * translateMatrix * rotateXMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //first
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.35f, 1.6, -2.75f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .125f, 0.55f));
    model = als * translateMatrix * rotateXMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //first
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.85f, 2.1, -2.75f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .125f, 0.55f));
    model = als * translateMatrix * rotateXMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //first
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.35f, 2.6, -2.75f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, .125f, 0.55f));
    model = als * translateMatrix * rotateXMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
}


void box(Cube &cube, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    /*
    string diffuseMapPath = "wood4.jpg"; //loading image path for diffuse.
    string specularMapPath = "black.png"; //loading image path for specular.

    //wrapping           //mapping 
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    */
    //bottom
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, 0.0, 2.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .125f, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, 1.0, 2.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .125f, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //left
    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, 0.0, 2.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 1.0f, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //right

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.25f - 0.125f, 0.0, 2.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 1.0f, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
}

void boxshelf(Cube &cube, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(14.25f, 0.0, 2.0));

    model = als*identityMatrix*translateMatrix*rotateYMatrix;
    box(cube, lightingShader, model);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(15.25f, .5, 2.0));
    model =als* identityMatrix * translateMatrix * rotateYMatrix;
    box(cube, lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(14.25f, 1.5, 2.0));
    model = als*identityMatrix * translateMatrix * rotateYMatrix;
    box(cube,lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(15.25f, 2.0, 2.0));
    model =als* identityMatrix * translateMatrix * rotateYMatrix;
    box(cube, lightingShader, model);


}

void stand(Cube& cube, Shader& lightingShader, float height, glm::mat4 als) {
    
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //stand
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 1.5f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    Sphere sphere = Sphere();
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625, 1.5, 0.2625));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);
}

void alna(Cube& cube, Cylinder & cyl, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
     


    //base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25,0, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, .125f, 0.25f));
    model = als * translateMatrix*scaleMatrix;
    cyl.drawCylinderWithTexture(lightingShader, model);

    //stand
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25,0, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 1.65f, 0.025f));
    model = als * translateMatrix*scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    Sphere sphere = Sphere();
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625, 1.65, 0.2625));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
   model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.0, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625+0.475, 1.0+0.0125, 0.2625));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.0, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625 , 1.0 + 0.0125, 0.2625 + 0.475));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.0, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, -0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625, 1.0 + 0.0125, (0.2625 - 0.475)));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.0, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.5f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625 - 0.475, 1.0 + 0.0125, 0.2625));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);


    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.25, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625 + 0.475, 1.25 + 0.0125, 0.2625));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.25, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625, 1.25 + 0.0125, 0.2625 + 0.475));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.25, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, -0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625, 1.25 + 0.0125, (0.2625 - 0.475)));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.25, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.5f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625 - 0.475, 1.25 + 0.0125, 0.2625));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);


    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.5, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625 + 0.475, 1.5 + 0.0125, 0.2625));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.5, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625, 1.5 + 0.0125, 0.2625 + 0.475));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.5, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, -0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625, 1.5 + 0.0125, (0.2625 - 0.475)));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);

    //handle4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 1.5, 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.5f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2625 - 0.475, 1.5 + 0.0125, 0.2625));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, model);
}


void goltable(Cylinder& cyl, Cube& cube, Shader& lightingShader, glm::mat4 als) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, 0.75, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.05, 0.8));
    model = als * translateMatrix * scaleMatrix;
    cyl.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

 

    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1 - 0.05, 0.75, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.75, 1.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1 - 0.05, 0.75, 1.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, -0.75, 0.05));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

}
#pragma once

#pragma once
#pragma once
