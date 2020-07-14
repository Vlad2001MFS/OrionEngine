#pragma once
#include "../Core/Common.h"
#include <string>

namespace oe {

typedef Handle<int, class TAG_ConstantID, -1> ConstantID;
//typedef Handle<int, class TAG_VertexAttribID, -1> VertexAttribID;
//typedef Handle<int, class TAG_SubrountineID, -1> SubrountineID;

class Program {
public:
    Program(const std::string &vsCode, const std::string &psCode, const std::string &defines);
    Program(const std::string &filename, const std::string &defines);
	~Program();

    uint GetHandle() const;
    const std::string &GetVSCode() const;
    const std::string &GetPSCode() const;
    const std::string &GetDefines() const;
    ConstantID GetConstantID(const std::string &name) const;
    //VertexAttribID GetVertexAttribID(const std::string &name) const;
    bool HasConstant(const std::string &name) const;
    //bool HasVertexAttrib(const std::string &name) const;

private:
    uint mProgram;
    std::string mVSCode, mPSCode, mDefines;
};

}