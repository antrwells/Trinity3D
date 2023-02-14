#pragma once
#include <string>
#include <vector>
#include <memory>


class ASTNode {
public:
    virtual ~ASTNode() {}
    void AddNode(ASTNode* node)
    {
        m_Nodes.push_back(node);
    };
    const std::string& getName() const {
        return m_name;
    }
protected:

    std::vector<ASTNode*> m_Nodes;
    std::string m_name;

};

class ASTExpression : public ASTNode {};

class ASTFunctionCall : public ASTNode {
public:
    ASTFunctionCall()
    {

    }
    
    void addArgument(ASTNode* node){
        m_arguments.push_back(node);
	}

    const std::vector<ASTNode*>& getArguments() const {
        return m_arguments;
    }

private:
    //ASTNode* m_function;

    std::vector<ASTNode*> m_arguments;
};


class ASTModule : public ASTNode {
public:
    ASTModule(const std::string& name)
         //m_name(name)
    {
        m_name = name;
    }

   
    
private:
    

};

class ASTIdentifier : public ASTNode {
public:
    ASTIdentifier(const std::string& name)
        : m_name(name)
    {}

    const std::string& getName() const {
        return m_name;
    }

private:
    std::string m_name;
};