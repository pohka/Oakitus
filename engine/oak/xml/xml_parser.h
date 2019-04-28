#pragma once
#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <string>
#include <vector>
#include <map>
#include "xml_node.h"

namespace oak
{
  struct XMLToken
  {
    const char id;
    const char ch;
    const char prevCh;
  };

  class XMLParser
  {
    //token IDs
    const char TOKEN_NONE = 1; //no match
    const char TOKEN_TAG_BEGIN = 2; // '<'
    const char TOKEN_TAG_END = 4; // '>'
    const char TOKEN_TAG_BEGIN_CLOSING = 8; // '</'
    const char TOKEN_EQUALS = 16; // '='
    const char TOKEN_QUOTE = 32; // '"'

    //root node
    XMLNode* root = nullptr;

    //token definitions
    static const char TOKEN_COUNT = 5;
    XMLToken tokens[TOKEN_COUNT] =
    {
      { TOKEN_TAG_BEGIN,          '<', NULL },
      { TOKEN_TAG_END,            '>', NULL },
      { TOKEN_TAG_BEGIN_CLOSING,  '/', '<' },
      { TOKEN_EQUALS,             '=', NULL },
      { TOKEN_QUOTE,              '"', NULL }
    };

  public:
    XMLParser();

    //clears the root node during destruction
    ~XMLParser();

    //load the file, returns false if it failed to load
    bool load(const std::string& path);

    bool save(const std::string& path);

    //returns a pointer to the root node
    XMLNode* getRootNode() const;

    //delete all loaded xml nodes
    void clear();

    //if the most recent load() failed then then an error code matches the type of error that occured
    char getErrorCode() const;

  private:
    //finds and returns the token the 2 chars match
    char getTokenID(const char ch, const char prevCh) const;

    //recursively converts a node to string
    std::string nodeToString(const XMLNode& node, const unsigned int depth = 0) const;

    //removes repeated whitespace from text, also removes whitespace at start and end of text
    void trimText(XMLNode* node);

    //error type
    char errorCode = 0;

    //parsing states
    static const char STATE_NONE = 0;
    static const char STATE_OPEN_TAG_BEGIN = 1;
    static const char STATE_ATTRS = 2;
    static const char STATE_ATTR_KEY = 3;
    static const char STATE_ATTR_VALUE = 4;
    static const char STATE_CONTENT = 5;
    static const char STATE_NEXT_TAG = 6;
    static const char STATE_CLOSING_TAG = 7;

    //error codes
    static const char ERROR_NONE = 0;
    static const char ERROR_PARSING_ROOT_TAG = 1; //file did not begin with an opening tag
    static const char ERROR_PARSING_TAG_NAME = 2; //invalid character found in tag name
    static const char ERROR_PARSING_KEY = 3; //invalid character in attribute key
    static const char ERROR_PARSING_TEXT = 4; //unexpected character in textContent
    static const char ERROR_FILE_OPEN = 5; //error opening file stream

  };
}

#endif