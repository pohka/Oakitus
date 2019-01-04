#include "var.h"
#include "meta_def.h"

using namespace oak;

var::var()
{
  str = "";
  type = VAR_STRING;
}

var::var(const var& v)
{
  set(v.str, v.type);
}

var::var(const std::string& str, const unsigned char type)
{
  set(str, type);
}

void var::set(const std::string& str, const unsigned char type)
{
  this->type = type;
  //string
  if (type == VAR_STRING)
  {
    this->str = str;
  }
  //number
  else if (type == VAR_NUMBER)
  {
    this->str = "";
    char decimalCount = 0;
    for (unsigned int i = 0; i < str.size(); i++)
    {
      char ch = str[i];

      if (isspace(ch) && this->str.size() > 0)
      {
        return;
      }
      else if (ch <= '9' && ch >= '0')
      {
        this->str += ch;
      }
      else if (ch == '.')
      {
        if (decimalCount == 0)
        {
          this->str += ch;
          decimalCount++;
        }
        else
        {
          return;
        }
      }
    }
  }
  //bool
  else if (type == VAR_BOOL)
  {
    if (str[0] == 'f' || str[0] == 'F')
    {
      this->str = "false";
    }
    else
    {
      this->str = "true";
    }
  }
}


const float var::toNumber() const
{
  float num;
  switch (type)
  {
    case VAR_NUMBER: num = std::stof(str); break;
    case VAR_BOOL:
      if (str[0] == 't')
      {
        num = 1.0f;
      }
      else
      {
        num = 0.0f;
      }
      break;
    case VAR_STRING: num = 0.0f; break;
  }

  return num;
}

const int var::toInt() const
{
  int num;
  switch (type)
  {
    case VAR_NUMBER: num = std::stoi(str); break;
    case VAR_BOOL:
      if (str[0] == 't')
      {
        num = 1;
      }
      else
      {
        num = 0;
      }
      break;
    case VAR_STRING: num = 0; break;
  }

  return num;
}

const std::string& var::toString() const
{
  return str;
}

const bool var::toBool() const
{
  return (str == "true");
}
