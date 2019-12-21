#include "Shader.hpp"
using std::ifstream;
using std::stringstream;
Shader::Shader(const char* vertexPath, const char* fragmentPath) 
    : hasTes(0), hasGeo(0) {
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();			
    }
    catch (ifstream::failure e){
        throw "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(const char* vertexPath, const char* geoPath, const char* fragmentPath) 
    : hasTes(0), hasGeo(1) {
    string vertexCode, fragmentCode, geoCode;
    ifstream vShaderFile, fShaderFile, gShaderFile;
    vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    gShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try {
        vShaderFile.open(vertexPath); fShaderFile.open(fragmentPath); gShaderFile.open(geoPath);
        stringstream vsshaderStream, fsshaderStream, gShaderStream;
        vsshaderStream << vShaderFile.rdbuf(); // 1
        fsshaderStream << fShaderFile.rdbuf(); // 2
        gShaderStream << gShaderFile.rdbuf();
        vShaderFile.close(); fShaderFile.close(); gShaderFile.close();
        vertexCode = vsshaderStream.str();
        fragmentCode = fsshaderStream.str();
        geoCode = gShaderStream.str();
    }
    catch (ifstream::failure e) {
        throw "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* geoShaderCode = geoCode.c_str();
    unsigned int vertex, fragment, geo;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    geo = glCreateShader(GL_GEOMETRY_SHADER);

    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "V");
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "F");
    glCompileShader(geo);
    checkCompileErrors(geo, "GEO");
    
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, geo);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geo);
}

Shader::Shader(const char* vertexPath, const char* tcsPath, const char* tesPath, const char* fragmentPath) 
    : hasTes(1), hasGeo(0) {
        string vertexCode, fragmentCode, tcsCode, tesCode;
        ifstream vShaderFile, fShaderFile, tcsFile, tesFile;
        vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
        fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
        tcsFile.exceptions (ifstream::failbit | ifstream::badbit);
        tesFile.exceptions (ifstream::failbit | ifstream::badbit);
        try {
            vShaderFile.open(vertexPath); fShaderFile.open(fragmentPath); tcsFile.open(tcsPath); tesFile.open(tesPath);
            stringstream vsshaderStream,  csshaderStream, esshaderStream, fsshaderStream;
            vsshaderStream << vShaderFile.rdbuf(); // 1
            fsshaderStream << fShaderFile.rdbuf(); // 2
            csshaderStream << tcsFile.rdbuf(); // 3
            esshaderStream << tesFile.rdbuf(); // 4
            vShaderFile.close(); fShaderFile.close(); tcsFile.close(); tesFile.close();
            vertexCode = vsshaderStream.str();
            fragmentCode = fsshaderStream.str();
            tcsCode = csshaderStream.str();
            tesCode = esshaderStream.str();
        }
        catch (ifstream::failure e) {
            throw "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        const char* tcShaderCode = tcsCode.c_str();
        const char* teShaderCode = tesCode.c_str();
        unsigned int vertex, fragment, tcs, tes;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
        tes = glCreateShader(GL_TESS_EVALUATION_SHADER);

        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "V");
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "F");
        glShaderSource(tcs, 1, &tcShaderCode, NULL);
        glCompileShader(tcs);
        checkCompileErrors(tcs, "TCS");
        glShaderSource(tes, 1, &teShaderCode, NULL);
        glCompileShader(tes);
        checkCompileErrors(tes, "TES");
        
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, tcs);
        glAttachShader(ID, tes);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteShader(tcs);
        glDeleteShader(tes);
}

Shader::Shader(const char* vertexPath, const char* tcsPath, const char* tesPath, const char* geoPath, const char* fragmentPath) 
    : hasTes(1), hasGeo(1) {
    string vertexCode, fragmentCode, tcsCode, tesCode, geoCode;
    ifstream vShaderFile, fShaderFile, tcsFile, tesFile, gShaderFile;
    vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    tcsFile.exceptions (ifstream::failbit | ifstream::badbit);
    tesFile.exceptions (ifstream::failbit | ifstream::badbit);
    gShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try {
        vShaderFile.open(vertexPath); fShaderFile.open(fragmentPath); tcsFile.open(tcsPath); tesFile.open(tesPath); gShaderFile.open(geoPath);
        stringstream vsshaderStream,  csshaderStream, esshaderStream, fsshaderStream, gShaderStream;
        vsshaderStream << vShaderFile.rdbuf(); // 1
        fsshaderStream << fShaderFile.rdbuf(); // 2
        csshaderStream << tcsFile.rdbuf(); // 3
        esshaderStream << tesFile.rdbuf(); // 4
        gShaderStream << gShaderFile.rdbuf();
        vShaderFile.close(); fShaderFile.close(); tcsFile.close(); tesFile.close(); gShaderFile.close();
        vertexCode = vsshaderStream.str();
        fragmentCode = fsshaderStream.str();
        tcsCode = csshaderStream.str();
        tesCode = esshaderStream.str();
        geoCode = gShaderStream.str();
    }
    catch (ifstream::failure e) {
        throw "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* tcShaderCode = tcsCode.c_str();
    const char* teShaderCode = tesCode.c_str();
    const char* geoShaderCode = geoCode.c_str();
    unsigned int vertex, fragment, tcs, tes, geo;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
    tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
    geo = glCreateShader(GL_GEOMETRY_SHADER);

    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "V");
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "F");
    glShaderSource(tcs, 1, &tcShaderCode, NULL);
    glCompileShader(tcs);
    checkCompileErrors(tcs, "TCS");
    glShaderSource(tes, 1, &teShaderCode, NULL);
    glCompileShader(tes);
    checkCompileErrors(tes, "TES");
    glCompileShader(geo);
    checkCompileErrors(geo, "GEO");
    
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, tcs);
    glAttachShader(ID, tes);
    glAttachShader(ID, geo);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(tcs);
    glDeleteShader(tes);
    glDeleteShader(geo);
}

void Shader::checkCompileErrors(GLuint shader, string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            throw "ERROR::SHADER_COMPILATION_ERROR of type: " + type + string(infoLog);
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            throw "ERROR::PROGRAM_LINKING_ERROR of type: " + type + string(infoLog);
        }
    }
}