#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "cylinder.h"

void sofa(Cube & cube2, Cube & cube3,Shader& ourShader, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    Cube cube = Cube();


    


    //Sofa Seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 + 0.15, 0.875));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .125f, 0.55f));
    model = als * translateMatrix * scaleMatrix;
    cube3.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05 - 0.1, 0.1, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f+.2f, .65f, 0.1));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    //cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //Sofa Head-Seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 + 0.5 * 0.2, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .5f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05 - 0.1, 0.1, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.15f, .25f, 0.7f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    //cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 + 0.5 * 0.2, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    //cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //Sofa leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 + 0.5 * 0.2, 0.8 + 0.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    //cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
    cube.drawCube(ourShader, model, 0.0, 0.0, 0.0);

    //Sofa leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.05 - 0.25, 0.1 + 0.5 * 0.2, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    //cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //Sofa leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.05 - 0.025, 0.1 + 0.5 * 0.2, 0.8 + 0.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    //cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
    cube.drawCube(ourShader, model, 0.0, 0.0, 0.0);

    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05 - 0.1, 0.1, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.10f, .3, 0.7f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    // cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.12 + 0.025, 0.1, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.10f, .3f, 0.7f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCube(ourShader, model, 0.0, 0.0, 0.0);
    //cube.drawCubeWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
}
void duvan(Cube& cube2, Cube& cube3, Cylinder& cyl, Cylinder& cyl2, Shader& ourShader, glm::mat4 als) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    
    //base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 0.5, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .125, 1.7f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(ourShader, model);

    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 0.5, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -.35, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(ourShader, model);

    //leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 0.5, 1.7-0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -.35, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(ourShader, model);

    //seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 0.75, -0.1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -.125, 1.85f));
    model = als * translateMatrix * scaleMatrix;
    cube3.drawCubeWithTexture(ourShader, model);

    //back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 1.05, -0.45));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -.05, 0.7f));
    model = als * translateMatrix *rotateYMatrix* scaleMatrix;
    cube2.drawCubeWithTexture(ourShader, model);

    //backseat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(00.0, 1.05, -0.40));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -.05, 0.6f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube3.drawCubeWithTexture(ourShader, model);
    
    

        
   

    //front
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 1.05, 2.20));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -.05, 0.7f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(ourShader, model);

    //frontseat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 1.05, 2.15));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, -.05, 0.6f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube3.drawCubeWithTexture(ourShader, model);

    //pillow1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 0.85, 0.0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.5, 0.1));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cyl2.drawCylinderWithTexture(ourShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether


    //pillow1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 0.85, 1.75));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.5, 0.1));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;

    cyl2.drawCylinderWithTexture(ourShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
    //glBindVertexArray(VAO);



        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 1.05, -0.45));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.075, 0.5, 0.075));
        model = als * translateMatrix * rotateYMatrix * scaleMatrix;

        cyl.drawCylinderWithTexture(ourShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 1.05, 2.15));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.075, 0.5, 0.075));
        model = als * translateMatrix * rotateYMatrix * scaleMatrix;

        cyl.drawCylinderWithTexture(ourShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);



}

#pragma once

