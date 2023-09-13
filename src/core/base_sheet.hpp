#pragma once

#ifndef BASE_SHEET_H
#define BASE_SHEET_H

#include <string>
#include "base_bar.hpp"

namespace hautbois {
namespace core {

class BaseSheet {
 private:
  std::string _title;
  std::string _subtitle;
  std::string _subsubtitle;
  std::string _composer;

  std::string _opus;
  std::string _opus_system;
  UInt32 _opus_number;
  std::string _work_type;
  std::vector<std::string> _tags;

  std::vector<BaseBar*> _bars;

  // BaseSheetProperty * _property;

 public:
  BaseSheet();
  BaseSheet(BaseSheet& ivRh);

  virtual void setTitle(const std::string& ivTitle);
  virtual void setSubtitle(const std::string& ivTitle);
  virtual void setSubsubTitle(const std::string& ivTitle);
  virtual void setComposer(const std::string& ivName);
  virtual void setOpus(const std::string& ivOpusSystem, const UInt32 ivOpusNumber);

  virtual std::string getTitle() const;
  virtual std::string getSubtitle() const;
  virtual std::string getSubsubtitle() const;
  virtual std::string getComposer() const;
  virtual std::string getOpus() const;
  virtual std::string getOpusSystem() const;
  virtual UInt32 getOpusNumber() const;

  virtual BaseBar * getBarNumber(const UInt32 ivBarNbr) const;
  virtual void appendBar(BaseBar * ivNewBar);
  virtual UInt32 countBars() const;
};

} // namespace core
} // namespace hautbois

#endif