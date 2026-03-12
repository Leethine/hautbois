#include "note_tuplet.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"

namespace hautbois {
namespace core {

bool cmpNoteValue() const;

bool cmpNoteNumber() const;

void Tuplet::addPitch(Pitch * __p);

void Tuplet::setPitch(Pitch * __p);

void Tuplet::addDuration(Duration * __d);

void Tuplet::setDuration(Duration * __d);

void Tuplet::addProperty(Property * __p);

void Tuplet::setProperty(Property * __p);

void Tuplet::clearPitch();

void Tuplet::clearDuration();

void Tuplet::clearProperty();

std::string filterProperty(const std::string& __text) const;

Tuplet();

Tuplet(const std::initializer_list<std::string> __group);

Tuplet(const std::vector<std::string>& __group);

Tuplet(const std::initializer_list<std::string> __group,
         const int& num, const int& denom);

Tuplet(const std::vector<std::string>& __group,
         const int& num, const int& denom);

Tuplet(const std::initializer_list<std::string> __group,
         const int& denom, const std::string& dots);

Tuplet(const std::vector<std::string>& __group,
         const int& denom, const std::string& dots);

Tuplet(Tuplet& __note);
  
Tuplet(Tuplet&& __note);

Tuplet& operator=(const Tuplet& __n);

~Tuplet();

void Tuplet::updateDuration(const std::string& __context);

void Tuplet::updateDuration(const std::string& __context, size_t __pos);
  
void Tuplet::updatePitch(const std::string& __context);

void Tuplet::updatePitch(const std::string& __context, size_t __pos);

void Tuplet::updateProperty(const std::string& __context);

void Tuplet::updateProperty(const std::string& __context, size_t __pos);

void Tuplet::setTied();

void Tuplet::setTied(size_t __pos);

void Tuplet::setUntied();

void Tuplet::setUntied(size_t __pos);

int Tuplet::getSize() const;

bool isValid() const;

bool isTied() const;

bool isTied(size_t __pos) const;

bool Tuplet::hasDuration() const;
  
bool Tuplet::hasPitch() const;

bool Tuplet::hasProperty() const;

bool Tuplet::hasDuration(size_t __pos) const;
  
bool Tuplet::hasPitch(size_t __pos) const;

bool Tuplet::hasProperty(size_t __pos) const;

const Duration * Tuplet::getDuration() const;

const Duration * Tuplet::getDuration(size_t __pos) const;

const Pitch * Tuplet::getPitch() const;

const Pitch * Tuplet::getPitch(size_t __pos) const;

const Property * Tuplet::getProperty() const;

const Property * Tuplet::getProperty(size_t __pos) const;

std::string Tuplet::getPropertyStr() const;

std::string Tuplet::getPropertyStr(size_t __pos) const;

int Tuplet::getPitchSize() const;

int Tuplet::getDurationSize() const;

int Tuplet::getPropertySize() const;

void Tuplet::modify(const std::string& __context);

std::string Tuplet::toString() const;

void * Tuplet::toStream(const std::string& __context, void * __ostream) const;

} // namespace core
} // namespace hautbois