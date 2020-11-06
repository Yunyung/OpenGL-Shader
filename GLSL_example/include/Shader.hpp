
GLuint VAO, VBO[3], EBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int DissolveProgram;
unsigned int ToonProgram;
unsigned int PhongProgram;
unsigned int ExampleProgram;

#define ERROR_MESSAGE_LOG_SIZE 512
int success;
char infoLog[ERROR_MESSAGE_LOG_SIZE];

bool CreateShader(unsigned int &shaderInstance, unsigned int shaderType, const GLchar* shaderSource) {

	shaderInstance = glCreateShader(shaderType);

	// 1 stands for one string in vertexShaderSource
	glShaderSource(shaderInstance, 1, &shaderSource, NULL);
	glCompileShader(shaderInstance);

	glGetShaderiv(shaderInstance, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderInstance, ERROR_MESSAGE_LOG_SIZE, NULL, infoLog);
		// std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return success;
}

bool CreateProgram(unsigned int &shaderProgramInstance, int n_args, ...)
{
	shaderProgramInstance = glCreateProgram();

	va_list ap;
	va_start(ap, n_args);
	for (int i = 0; i < n_args; i++) {
		int shaderID = va_arg(ap, unsigned int);
		glAttachShader(shaderProgramInstance, shaderID);
	}
	va_end(ap);

	glLinkProgram(shaderProgramInstance);

	glGetProgramiv(shaderProgramInstance, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramInstance, ERROR_MESSAGE_LOG_SIZE, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
	}
	else {
		va_start(ap, n_args);
		for (int i = 0; i < n_args; i++) {
			int shaderID = va_arg(ap, unsigned int);
			glDeleteShader(shaderID);
		}
		va_end(ap);
	}

	return success;
}

char *ReadShader(const char * shaderpath)
{
	FILE *fp;
	fp = fopen(shaderpath, "r");
	char *buffer = (char *)malloc(sizeof(char) * 4096);
	char *data = (char *)malloc(sizeof(char) * 4096);
	data[0] = '\0';
	while (fgets(buffer, 4096, fp) != NULL)
	{
		strcat(data, buffer);
	}
	free(buffer);
	fclose(fp);

	return data;
}