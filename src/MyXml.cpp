#include <exception>
#include "MyXml.h"
#include <iostream>

using namespace std;
using namespace tinyxml2;

MyXml::MyXml() : pDoc(nullptr), parse_pDoc(nullptr), pDeclaration(nullptr), MESSAGE(nullptr), HEADER(nullptr), ParamList(nullptr), Parm1_(nullptr), Parm2_(nullptr), Parm3_(nullptr), Text1_(nullptr), Text2_(nullptr), Text3_(nullptr), RootE(nullptr), MsgType(nullptr), Result(nullptr)
{
    parse_pDoc = std::make_shared<tinyxml2::XMLDocument>();
}

std::string MyXml::creat_Xml(const char* MsgType)
{
    tinyxml2::XMLPrinter printer;
    //消息头
    make_MESSAGE();
    //消息类型
    make_HEADER(MsgType);
    //添加参数1节点
    make_ParamList();
    //转为字符串返回
    pDoc->Accept(&printer);
    ret_xml = printer.CStr();
    return ret_xml;
}

std::string MyXml::creat_Xml(const char* MsgType, const char* Parm_1, const char* text_1)
{
    tinyxml2::XMLPrinter printer;
    //消息头
    make_MESSAGE();
    //消息类型
    make_HEADER(MsgType);
    //添加参数1节点
    make_ParamList();
    //添加参数1节点内容
    add_Parm_1(Parm_1);
    add_Text_1(text_1);
    //转为字符串返回
    pDoc->Accept(&printer);
    ret_xml = printer.CStr();
    return ret_xml;
}

std::string MyXml::creat_Xml(const char* MsgType, const char* Parm_1, const char* text_1, const char* Parm_2, const char* text_2)
{
    tinyxml2::XMLPrinter printer;
    //消息头
    make_MESSAGE();
    //消息类型
    make_HEADER(MsgType);
    //添加参数1节点
    make_ParamList();
    //添加参数1节点内容
    add_Parm_1(Parm_1);
    add_Text_1(text_1);
    //添加参数2节点内容
    add_Parm_2(Parm_2);
    add_Text_2(text_2);
    //转为字符串返回
    pDoc->Accept(&printer);
    ret_xml = printer.CStr();
    return ret_xml;
}

std::string MyXml::creat_Xml(const char* MsgType, const char* Parm_1, const char* text_1, const char* Parm_2, const char* text_2, const char* Parm_3, const char* text_3)
{
    tinyxml2::XMLPrinter printer;
    //消息头
    make_MESSAGE();
    //消息类型
    make_HEADER(MsgType);
    //添加参数1节点
    make_ParamList();
    //添加参数1节点内容
    add_Parm_1(Parm_1);
    add_Text_1(text_1);
    //添加参数2节点内容
    add_Parm_2(Parm_2);
    add_Text_2(text_2);
    //添加参数3节点内容
    add_Parm_3(Parm_3);
    add_Text_3(text_3);
    //转为字符串返回
    pDoc->Accept(&printer);
    ret_xml = printer.CStr();
    return ret_xml;
}

const char* MyXml::get_MsgType(const char* xml)
{
    xml_get_ = xml;
    parse_pDoc->Parse(xml_get_.c_str());
    RootE = parse_pDoc->RootElement();
    if(nullptr == RootE) {
        LOG_WARN << "RootE"
                 << "NULL";
        return "";
    }
    HEADER = RootE->FirstChildElement("HEADER");
    if(nullptr == HEADER) return "";
    MsgType = HEADER->FindAttribute("MsgType");
    if(nullptr == MsgType) return "";
    return MsgType->Value();
}

const char* MyXml::get_oneResult(const char* parm)
{
    if(nullptr == RootE) return "";
    ParamList = RootE->FirstChildElement("ParamList");
    if(nullptr == ParamList) {
        LOG_WARN << parm << "NULL";
        return "";
    }
    Result = ParamList->FirstChildElement(parm);
    if(nullptr == Result) {
        LOG_WARN << parm << "NULL";
        return "";
    }
    if(!Result->GetText()) {
        LOG_WARN << Result->Name() << "NULL";
        return "";
    } else
        return Result->GetText();
}

const char* MyXml::get_firstResult()
{
    if(nullptr == RootE) return "";
    ParamList = RootE->FirstChildElement("ParamList");
    if(nullptr == ParamList) {
        LOG_WARN << "parm"
                 << "NULL";
        return "";
    }
    Result = ParamList->FirstChildElement();
    if(nullptr == Result) {
        LOG_WARN << "parm"
                 << "NULL";
        return "";
    }
    if(!Result->GetText()) {
        LOG_WARN << Result->Name() << "NULL";
        return "";
    } else
        return Result->GetText();
}

XMLTEXT MyXml::get_multiResult()
{
    XMLTEXT vecText;
    if(nullptr == RootE) return vecText;
    ParamList = RootE->FirstChildElement("ParamList");
    childOfParamList = ParamList->FirstChildElement();
    while(childOfParamList) {
        // cout << childOfParamList->Name() << endl;
        if(!childOfParamList->GetText())
            LOG_WARN << childOfParamList->Name() << "NULL";
        else {
            content = childOfParamList->GetText();
            vecText.emplace_back(content);
        }
        childOfParamList = childOfParamList->NextSiblingElement();
        // cout << content << endl;
    }
    return vecText;
}

XMLTEXT MyXml::get_MapInfoReq()
{
    XMLTEXT vecText;
    if(nullptr == RootE) return vecText;
    ParamList = RootE->FirstChildElement("ParamList");
    item = ParamList->FirstChildElement();
    childOfParamList = item->FirstChildElement();
    while(childOfParamList) {
        // cout << childOfParamList->Name() << endl;
        if(!childOfParamList->GetText())
            LOG_WARN << childOfParamList->Name() << "NULL";
        else {
            content = childOfParamList->GetText();
            vecText.emplace_back(content);
        }
        childOfParamList = childOfParamList->NextSiblingElement();
        // cout << content << endl;
    }
    return vecText;
}
