/* 
Copyright (c) 2011 Andrew Keating

This file is part of 3DMagic.

3DMagic is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

3DMagic is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with 3DMagic.  If not, see <http://www.gnu.org/licenses/>.

*/
/** Implementation file for HemisphereTexShader class
 *
 * @file HemisphereTexShader.cpp
 * @author Andrew Keating
 */

#include <Shaders/HemisphereTexShader.h>

namespace Magic3D
{
	
const char* HemisphereTexShader::vertexSourceName = "shaders/HemisphereTexShader.vp";
const char* HemisphereTexShader::fragmentSourceName = "shaders/HemisphereTexShader.fp";
	
/** Standard constructor
 * @param resourceManager the resource manager to use to find shader source files
 */
HemisphereTexShader::HemisphereTexShader(ResourceManager& resourceManager)
{
	// get vertex and fragment source for shader
	Handle<TextResource> vp = resourceManager.get<TextResource>(HemisphereTexShader::vertexSourceName);
	Handle<TextResource> fp = resourceManager.get<TextResource>(HemisphereTexShader::fragmentSourceName);
	
	// load the shader
	this->programId = Shader::loadShader(vp()->getText(), fp()->getText(), // vertex and fragment source code
					3, 				// two attributes
					0, "vVertex",	// first has shader var name vVertex
					1, "vNormal",   // second has shader var name vNormal
					3, "vTexCoord0" // thrid has shader var name vTexCoord0
	);
	
	// just let go of the handles as we don't need to text ever again
}
	
/// destructor
HemisphereTexShader::~HemisphereTexShader()
{
	// delete the shader from opengl memory
	glDeleteProgram(this->programId);
}
		
	
	
/** Enable this shader to be used on the next drawing operation
 */
void HemisphereTexShader::use()
{
	// set opengl to use this shader
	glUseProgram(this->programId);
	if (glGetError() != GL_NO_ERROR)
		throw MagicExceptionMacro("Could not use shader program");
	
	// set uniforms for shader program to use
	
	// set sky color
	GLint id = glGetUniformLocation(this->programId, "skyColor");
	glUniform3fv(id, 1, skyColor.getInternal());
	
	// set ground color
	id = glGetUniformLocation(this->programId, "groundColor");
	glUniform3fv(id, 1, groundColor.getInternal());
	
	// set light position
	id = glGetUniformLocation(this->programId, "lightPosition");
	glUniform3fv(id, 1, lightPosition.getInternal());
	
	// set mvp matrix
	id = glGetUniformLocation(this->programId, "mvpMatrix");
	glUniformMatrix4fv(id, 1, GL_FALSE, mvpMatrix.getInternal());
	
	// set mv matrix
	id = glGetUniformLocation(this->programId, "mvMatrix");
	glUniformMatrix4fv(id, 1, GL_FALSE, mvMatrix.getInternal());
	
	// set normal matrix
	id = glGetUniformLocation(this->programId, "normalMatrix");
	glUniformMatrix3fv(id, 1, GL_FALSE, normalMatrix.getInternal());
	
	// set texture map
	texture->bind();
	id = glGetUniformLocation(this->programId, "textureMap");
	glUniform1i(id, 0); // use texture state 0
	
	if (glGetError() != GL_NO_ERROR)
		throw MagicExceptionMacro("Could not bind uniforms for shader");
	
	// should be ready to render now
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
};


