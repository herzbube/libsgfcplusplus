// Project includes
#include "SgfcBackendDataWrapper.h"

// SGFC includes
extern "C"
{
  #include <stdio.h>  // required to define size_t and FILE which are used in all.h
  #include "../sgfc/all.h"
  #include "../sgfc/protos.h"
}

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  SgfcBackendDataWrapper::SgfcBackendDataWrapper()
    : sgfData(new SGFInfo())
  {
    // Immediately zero the struct so that FreeSGFInfo() inside the destructor
    // works. This is important in case the destructor runs immediately after
    // the constructor, without SGF content being generated.
    memset(this->sgfData, 0, sizeof(struct SGFInfo));
  }

  SgfcBackendDataWrapper::~SgfcBackendDataWrapper()
  {
    FreeSGFInfo(this->sgfData);
    delete this->sgfData;
    this->sgfData = 0;
  }

  SGFInfo* SgfcBackendDataWrapper::GetSgfData() const
  {
    return this->sgfData;
  }
}
