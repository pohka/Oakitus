#ifndef XML_NODE_H
#define XML_NODE_H

#include <string>
#include <vector>
#include <map>

namespace oak
{
  class XMLNode
  {
    XMLNode* parent;
    std::string tag;
    std::string text = "";
    std::map<std::string, std::string> attrs = {};
    std::vector<XMLNode*> children;

  public:
    friend class XMLParser;
    XMLNode();
    ~XMLNode();


    //Attributes
    //------------------------------------
    //get all attrs
    const std::map<std::string, std::string>& getAttrs() const;
    //get attribute value
    std::string getAttr(const std::string& key) const;
    //retruns true if attributes have a matching key
    bool hasAttr(const std::string& key) const;
    //set an attribute
    void setAttr(const std::string& key, const std::string& value);


    //Tag
    //------------------------------------
    //get tag
    const std::string& getTag() const;
    //set tag
    void setTag(const std::string& tag);


    //Text
    //------------------------------------
    //get text
    const std::string& getTextContent() const;
    //set text
    void setTextContent(const std::string& text);

    //Child nodes
    //------------------------------------
    //get child nodes
    const std::vector<XMLNode*>& getChildNodes() const;

    //add a child node to the end of children
    void addChildNode(XMLNode* node);
  };
}

#endif