uniform float normScale;
uniform sampler2D secondImage;
uniform sampler2D baseImage;

void main() 
{
	vec4 offset=gl_Vertex;
	vec4 v;
	// change vertex offset based on texture information
	vec4 tex = texture2D(baseImage,gl_MultiTexCoord0.st);

	offset.y = (tex.r +tex.g +tex.b)*normScale;
	 
	// Set the position of the current vertex 
	gl_Position = gl_ModelViewProjectionMatrix * offset;

	// pass texture coordinates from VS to FS.
	// "gl_MultiTexCoord0" has the texture coordinates assigned to this vertex in the first set of coordinates.
	// This index has to do with the set of texture COORDINATES, it is NOT RELATED to the texture UNIT.
	// "gl_TexCoord[0]" is a built-in varying that will be interpolated in the FS.
	gl_TexCoord[0] = gl_MultiTexCoord0;
}