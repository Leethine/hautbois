#pragma once

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <string>
#include <vector>

namespace hautbois {

class Property {

private:

  std::vector<std::string> _list_of_marks;

protected:

  virtual void setFreeText(const std::string& __freetext);

  virtual bool isValidMark(const std::string& __mark) const;

public:

  Property();

  Property(const std::string& __freetext);

  Property(const Property& __p);

  Property(const Property&& __p);

  virtual ~Property();

  virtual Property& operator=(Property&)=delete;

  virtual std::vector<std::string> toList() const;

  virtual std::string toString() const;

  virtual std::string getDynamic() const;

  virtual std::string getOrnament() const;

  virtual std::string getArticulation() const;

  virtual std::string getExprCtrl() const;

};

} // namespace hautbois

#endif