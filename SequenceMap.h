//Yi Zong Kuang
//Sequence Map Header.
//The data container, stores a recognition ID, and an vector of string associated with it.
#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <string>
#include <vector>
#include <iostream>

class SequenceMap {
 public:
  // Big Five.
  SequenceMap() = default;
  SequenceMap(const SequenceMap &rhs) = default;
  SequenceMap& operator=(const SequenceMap &rhs) = default;
  SequenceMap(SequenceMap &&rhs) = default;
  SequenceMap& operator=(SequenceMap &&rhs) = default;
  ~SequenceMap() = default; 
  // End of Big Five. //

  // HW fct.
  // Two parameter constructor.
  SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro) : recognition_sequence_(a_rec_seq) {
    enzyme_acronyms_.push_back(an_enz_acro);
  }

  // Overloaded < for comparision.
  bool operator<(const SequenceMap &rhs) const {
    return recognition_sequence_ < rhs.recognition_sequence_;
  }

  // Overloaded << for cout operation.
  friend std::ostream &operator<<(std::ostream &out, const SequenceMap &rhs) {
    for (unsigned int i = 0; i < rhs.enzyme_acronyms_.size(); ++i) {
      out << rhs.enzyme_acronyms_[i] << " ";
    }  
    return out;
  }

  // Merg the vector from parameter to the object calling this fct.
  void Merge(const SequenceMap &other_sequence) {
    for (unsigned int i = 0; i < other_sequence.enzyme_acronyms_.size(); ++i) {
      this->enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
    }
    return;
  }


 private:
  std::string recognition_sequence_;
  std::vector<std::string> enzyme_acronyms_;
};

#endif
