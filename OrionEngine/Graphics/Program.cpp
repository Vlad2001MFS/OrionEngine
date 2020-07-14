#include "Program.h"
#include "../Core/Debug.h"
#include "../Core/File.h"
#include "../Core/StringUtils.h"
#include "glew.h"
#include <vector>
#include <algorithm>

namespace oe {

uint CreateProgram(const std::string & vsCode, const std::string & psCode, const std::string & defines) {
    uint program = glCreateProgram();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint ps = glCreateShader(GL_FRAGMENT_SHADER);

    int result = false, logLength = 0;

    std::string definesStr;
    if (!defines.empty())
        for (auto &it : StringUtils::Split(defines, ';'))
            definesStr += "#define " + it + "\n";

    std::string vsCodeWithDefines;
    if (StringUtils::Contains(StringUtils::BeforeFirst(StringUtils::AfterFirst(vsCode, '#'), '\n'), "version"))
        vsCodeWithDefines = "#" + StringUtils::BeforeFirst(StringUtils::AfterFirst(vsCode, '#'), '\n') + "\n" + 
                            definesStr + StringUtils::AfterFirst(StringUtils::AfterFirst(vsCode, '#'), '\n');
    const char *vsSource[] = { vsCodeWithDefines.data() };
    int vsSourceLength[] = { vsCodeWithDefines.length() };
    glShaderSource(vs, 1, vsSource, vsSourceLength);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> error(logLength);
        glGetShaderInfoLog(vs, logLength, NULL, error.data());
        OE_LOG_ERROR("Failed to compile vertex shader. Error:\n%s", error.data());
    }

    std::string psCodeWithDefines;
    if (StringUtils::Contains(StringUtils::BeforeFirst(StringUtils::AfterFirst(psCode, '#'), '\n'), "version"))
        psCodeWithDefines = "#" + StringUtils::BeforeFirst(StringUtils::AfterFirst(psCode, '#'), '\n') + "\n" +
                            definesStr + StringUtils::AfterFirst(StringUtils::AfterFirst(psCode, '#'), '\n');
    const char *psSource[] = { psCodeWithDefines.data() };
    int psSourceLength[] = { psCodeWithDefines.length() };
    glShaderSource(ps, 1, psSource, psSourceLength);
    glCompileShader(ps);
    glGetShaderiv(ps, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderiv(ps, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> error(logLength);
        glGetShaderInfoLog(ps, logLength, NULL, error.data());
        OE_LOG_ERROR("Failed to compile pixel shader. Error:\n%s", error.data());
    }

    glAttachShader(program, vs);
    glAttachShader(program, ps);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> error(logLength);
        glGetProgramInfoLog(program, logLength, NULL, error.data());
        OE_LOG_ERROR("Failed to link program. Error:\n%s", error.data());
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> error(logLength);
        glGetProgramInfoLog(program, logLength, NULL, error.data());
        OE_LOG_ERROR("Failed to validate program. Error:\n%s", error.data());
    }

    glDetachShader(program, vs);
    glDeleteShader(vs);
    glDetachShader(program, ps);
    glDeleteShader(ps);
    return program;
}

Program::Program(const std::string & vsCode, const std::string & psCode, const std::string & defines)
    : mProgram(CreateProgram(vsCode, psCode, defines)), mVSCode(vsCode), mPSCode(psCode), mDefines(defines) { }

Program::Program(const std::string & filename, const std::string & defines)
    : mProgram(0) { 
    constexpr char VERTEX_SHADER_ID[] = "@VertexShader";
    constexpr uint VERTEX_SHADER_ID_SIZE = sizeof(VERTEX_SHADER_ID) - 1;
    constexpr char PIXEL_SHADER_ID[] = "@PixelShader";
    constexpr uint PIXEL_SHADER_ID_SIZE = sizeof(PIXEL_SHADER_ID) - 1;
    std::string text = File(filename, FileMode::Read).ReadAllText();
    std::string code[2];
    int target = 0;
    for (uint i = 0; i < text.length(); i++) {
        const char &ch = text[i];
        std::string str = text.substr(i, std::min(VERTEX_SHADER_ID_SIZE, static_cast<unsigned int>(text.length() - i)));
        if (str == VERTEX_SHADER_ID) {
            target = 0;
            i += VERTEX_SHADER_ID_SIZE;
        }
        else if (text.substr(i, std::min(PIXEL_SHADER_ID_SIZE, static_cast<unsigned int>(text.length() - i))) == PIXEL_SHADER_ID) {
            target = 1;
            i += PIXEL_SHADER_ID_SIZE;
        }
        else
            code[target] += ch;
    }
    mVSCode = code[0];
    mPSCode = code[1];
    mDefines = defines;
    mProgram = CreateProgram(code[0], code[1], defines);
}

Program::~Program() {
    glDeleteProgram(mProgram);
}

uint Program::GetHandle() const {
    return mProgram;
}

const std::string & Program::GetVSCode() const {
    return mVSCode;
}

const std::string & Program::GetPSCode() const {
    return mPSCode;
}

const std::string & Program::GetDefines() const {
    return mDefines;
}

ConstantID Program::GetConstantID(const std::string & name) const {
    return ConstantID(glGetUniformLocation(mProgram, name.data()));
}

//VertexAttribID Program::GetVertexAttribID(const std::string & name) const {
//    return VertexAttribID(glGetAttribLocation(mProgram, name.data()));
//}

bool Program::HasConstant(const std::string & name) const {
    return GetConstantID(name).IsValid();
}

//bool Program::HasVertexAttrib(const std::string & name) const {
//    return GetVertexAttribID(name).IsValid();
//}

}