#include <cstring>
#include <utility>
#include "my_string.h"

void Swap(String& first, String& second) {
  std::swap(first.size_, second.size_);
  std::swap(first.capacity_, second.capacity_);
  std::swap(first.string_, second.string_);
  delete[] second.string_;
  second.string_ = new char[1];
  second.string_[0] = 0;
  second.size_ = 0;
}

String::String() {
  string_[0] = 0;
}

String::String(const char* str) {
  *this = String();
  if (str != nullptr) {
    reserve(static_cast<int>(strlen(str)) + 1);
    size_ = strlen(str);
    std::snprintf(string_, size_ + 1, "%s", str);
  }
}

void String::reserve(int new_capacity) {
  if (new_capacity <= size_) {
    return;
  }
  capacity_ = std::max(new_capacity, 1);
  char* buf = new char[capacity_];
  for (int i = 0; i <= size_; ++i) {
    buf[i] = string_[i];
  }
  delete[] string_;
  string_ = buf;
}

String::String(int count, char ch) {
  reserve(count + 1);
  size_ = count;
  for (int i = 0; i < count; ++i) {
    string_[i] = ch;
  }
  string_[size_] = '\0';
}

String::String(const String& rhs) {
  reserve(rhs.length() + 1);
  size_ = rhs.size_;
  std::snprintf(string_, size_ + 1, "%s", rhs.string_);
  string_[size_] = 0;
}

int String::length() const {
  return size_;
}

String::~String() {
  delete[] string_;
}

String& String::operator=(const String& rhs) {
  if (*this == rhs) {
    return *this;
  }
  reserve(rhs.length() + 1);
  size_ = rhs.size_;
  std::snprintf(string_, size_ + 1, "%s", rhs.string_);
  return *this;
}

String::String(String&& rhs) noexcept {
  Swap(*this, rhs);
}

String& String::operator=(String&& rhs) noexcept {
  if (*this == rhs) {
    return *this;
  }
  Swap(*this, rhs);
  return *this;
}

bool String::empty() const {
  return (size_ == 0);
}

char* String::c_str() const {
  return string_;
}

char& String::operator[](int index) {
  return *(string_ + index);
}

const char& String::operator[](int index) const {
  return *(string_ + index);
}

char& String::front() {
  return *string_;
}

char& String::back() {
  return *(string_ + size_ - 1);
}

const char& String::front() const {
  return *string_;
}

const char& String::back() const {
  return *(string_ + size_ - 1);
}

void String::push_back(char ch) {
  if (size_ + 1 >= capacity_) {
    reserve(capacity_ * 2);
  }
  string_[size_] = ch;
  string_[size_ + 1] = '\0';
  ++size_;
}

void String::pop_back() {
  --size_;
  string_[size_] = '\0';
}

void String::clear() {
  size_ = 0;
  string_[0] = '\0';
}

void String::insert(int index, const String& str) {
  char* new_string = new char[size_ + str.size_ + 1];
  std::strncpy(new_string, string_, index);
  for (int i = 0; i < str.size_; ++i) {
    new_string[i + index] = str.string_[i];
  }
  for (int i = index; i < size_; ++i) {
    new_string[i + str.size_] = string_[i];
  }
  size_ = size_ + str.size_;
  std::swap(string_, new_string);
  delete[] new_string;
  string_[size_] = '\0';
}

std::ostream& operator<<(std::ostream& os, String& str) {
  for (int i = 0; i < str.size_; ++i) {
    os << str[i];
  }
  return os;
}

void String::insert(int index, const char* str, int count) {
  char* new_string = new char[size_ + count + 1];
  std::strncpy(new_string, string_, index);
  for (int i = 0; i < count; ++i) {
    new_string[index + i] = str[i];
  }
  for (int i = index; i < size_; ++i) {
    new_string[i + count] = string_[i];
  }
  size_ = size_ + count;
  std::swap(string_, new_string);
  delete[] new_string;
  string_[size_] = '\0';
}

void String::erase(int index, int count) {
  count = std::min(size_ - index, count);
  char* new_string = new char[size_ - count + 1];
  for (int i = 0; i < index; ++i) {
    new_string[i] = string_[i];
  }
  for (int i = index + count; i < size_; ++i) {
    new_string[i - count] = string_[i];
  }
  size_ -= count;
  std::swap(string_, new_string);
  delete[] new_string;
  string_[size_] = '\0';
}

int String::compare(const String& rhs) const {
  int result = strncmp(string_, rhs.string_, std::min(size_, rhs.size_));
  if (result > 0) {
    return 1;
  } else if (result < 0) {
    return -1;
  }
  if (size_ != rhs.length()) {
    return ((size_ < rhs.size_) ? -1 : 1);
  }
  return 0;
}

int String::compare(const char* str) const {
  return this->compare(String(str));
}

String String::operator+(const String& rhs) const {
  String result;
  result.reserve(size_ + rhs.size_);
  std::strncpy(result.string_, string_, size_ - 1);
  std::strncpy(result.string_ + size_ - 1, rhs.string_, rhs.size_);
  result.size_ = size_ + rhs.size_ - 1;
  return *this;
}

String& String::operator+=(const String& rhs) {
  *this = *this + rhs;
  return *this;
}

bool String::operator==(const String& rhs) const {
  return (this->compare(rhs) == 0);
}

bool String::operator==(const char* rhs) const {
  return (this->compare(String(rhs)) == 0);
}

bool String::operator!=(const String& rhs) const {
  return !(*this == rhs);
}

bool String::operator<(const String& rhs) const {
  return (this->compare(rhs) == -1);
}

bool String::operator>(const String& rhs) const {
  return (this->compare(rhs) == 1);
}

bool String::operator<=(const String& rhs) const {
  return ((*this == rhs) || (*this < rhs));
}

bool String::operator>=(const String& rhs) const {
  return ((*this == rhs) || (*this > rhs));
}

bool String::operator!=(const char* rhs) const {
  return (*this != String(rhs));
}

bool String::operator<(const char* rhs) const {
  return (*this < String(rhs));
}

bool String::operator>(const char* rhs) const {
  return (*this > String(rhs));
}
bool String::operator<=(const char* rhs) const {
  return (*this <= String(rhs));
}

bool String::operator>=(const char* rhs) const {
  return (*this >= String(rhs));
}

bool operator==(const char* lhs, const String& rhs) {
  return (String(lhs) == rhs);
}

bool operator!=(const char* lhs, const String& rhs) {
  return (String(lhs) != rhs);
}

bool operator<(const char* lhs, const String& rhs) {
  return (String(lhs) < rhs);
}

bool operator>(const char* lhs, const String& rhs) {
  return (String(lhs) > rhs);
}

bool operator<=(const char* lhs, const String& rhs) {
  return (String(lhs) <= rhs);
}

bool operator>=(const char* lhs, const String& rhs) {
  return (String(lhs) >= rhs);
}

