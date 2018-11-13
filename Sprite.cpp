#include "Sprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Oakitus.h"
#include "Texture.h"


Sprite::Sprite(std::string src, int x, int y, int w, int h, unsigned int shaderID)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	if (shaderID != NULL)
	{
		this->shaderID = shaderID;
	}
	else 
	{
		shaderID = Oakitus::defaultShaderID;
	}


	float vertices[] = {
		// positions          // texture coords
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, //bottom left
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, //bottom right
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, //top right

		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, //top right
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, //top left
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, //botom right
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	this->texture = new Texture(src.c_str());
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

std::string Sprite::getSrc()
{
	return this->src;
}

unsigned int Sprite::getVAO()
{
	return this->VAO;
}

void Sprite::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture->getID());
	glBindVertexArray(this->VAO);

	glm::mat4 model = glm::mat4(1.0);
	glm::vec3 pos(entity->position->x, entity->position->y, entity->position->z);
	model = glm::translate(model, pos);


	Shader* shader = Oakitus::getShaderByID(this->shaderID);

	shader->setMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}