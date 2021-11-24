#pragma once
#include <memory>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "tinyxml2.h"
#include "libmevent/base/Logging.h"
typedef std::vector<std::string> XMLTEXT;

class XMLException : public std::exception
{
public:
    XMLException()
    {
    }
};

class MyXml
{
public:
    MyXml();

    const char* get_MsgType(const char* xml);  // tinyxml找不到目标时返回null

    const char* get_oneResult(const char* parm = "Result");

    const char* get_firstResult();

    XMLTEXT get_multiResult();

    XMLTEXT get_MapInfoReq();

    std::string creat_Xml(const char* MsgType);
    /********************************一个参数*****************************************************/
    std::string creat_Xml(const char* MsgType, const char* Parm_1, const char* text_1);

    std::string creat_Xml(const char* MsgType, const char* Parm_1, const char* text_1, const char* Parm_2, const char* text_2);

    std::string creat_Xml(const char* MsgType, const char* Parm_1, const char* text_1, const char* Parm_2, const char* text_2, const char* Parm_3, const char* text_3);

private:
    void make_MESSAGE()
    {
        pDoc = std::make_shared<tinyxml2::XMLDocument>();
        pDeclaration = pDoc->NewDeclaration("xml version = \"1.0\" encoding=\"UTF-8\"");
        pDoc->LinkEndChild(pDeclaration);
        MESSAGE = pDoc->NewElement("MESSAGE");
        MESSAGE->SetAttribute("Verison", "1.0");
        pDoc->LinkEndChild(MESSAGE);
    }

    void make_HEADER(const char* MsgType)
    {
        HEADER = pDoc->NewElement("HEADER");
        HEADER->SetAttribute("MsgType", MsgType);
        HEADER->SetAttribute("MsgSeq", "");
        MESSAGE->InsertEndChild(HEADER);
    }

    void make_ParamList()
    {
        ParamList = pDoc->NewElement("ParamList");
        MESSAGE->InsertEndChild(ParamList);
    }

    void add_Parm_1(const char* Parm_1)
    {
        Parm1_ = pDoc->NewElement(Parm_1);
        ParamList->InsertEndChild(Parm1_);
    }

    void add_Text_1(const char* text_1)
    {
        Text1_ = pDoc->NewText(text_1);
        Parm1_->LinkEndChild(Text1_);
    }
    /********************************二个参数*****************************************************/

    void add_Parm_2(const char* Parm_2)
    {
        Parm2_ = pDoc->NewElement(Parm_2);
        ParamList->InsertEndChild(Parm2_);
    }

    void add_Text_2(const char* text_2)
    {
        Text2_ = pDoc->NewText(text_2);
        Parm2_->LinkEndChild(Text2_);
    }
    /********************************三个参数*****************************************************/

    void add_Parm_3(const char* Parm_3)
    {
        Parm3_ = pDoc->NewElement(Parm_3);
        ParamList->InsertEndChild(Parm3_);
    }

    void add_Text_3(const char* text_3)
    {
        Text3_ = pDoc->NewText(text_3);
        Parm3_->LinkEndChild(Text3_);
    }
    /********************************一个参数*****************************************************/

private:
    std::shared_ptr<tinyxml2::XMLDocument> pDoc;
    std::shared_ptr<tinyxml2::XMLDocument> parse_pDoc;
    tinyxml2::XMLDeclaration* pDeclaration;
    tinyxml2::XMLElement* MESSAGE;    // not thread safe
    tinyxml2::XMLElement* HEADER;     // not thread safe
    tinyxml2::XMLElement* ParamList;  // not thread safe
    tinyxml2::XMLElement* item;
    tinyxml2::XMLElement* childOfParamList;  // not thread safe
    tinyxml2::XMLElement* Parm1_;
    tinyxml2::XMLElement* Parm2_;
    tinyxml2::XMLElement* Parm3_;
    tinyxml2::XMLText* Text1_;
    tinyxml2::XMLText* Text2_;
    tinyxml2::XMLText* Text3_;
    std::string ret_xml;
    tinyxml2::XMLElement* RootE;
    const tinyxml2::XMLAttribute* MsgType;
    tinyxml2::XMLElement* Result;
    std::string xml_get_;
    std::string content;
};
