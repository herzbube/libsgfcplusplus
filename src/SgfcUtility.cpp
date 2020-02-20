// Project includes
#include "SgfcUtility.h"

namespace LibSgfcPlusPlus
{
  SgfcExitCode SgfcUtility::GetSgfcExitCodeFromMessageCollection(
    const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection)
  {
    bool warningMessageFound = false;
    bool errorMessageFound = false;
    bool fatalErrorMessageFound = false;

    for (const auto& message : messageCollection)
    {
      switch (message->GetMessageType())
      {
        case SgfcMessageType::Warning:
          warningMessageFound = true;
          break;
        case SgfcMessageType::Error:
          errorMessageFound = true;
          break;
        case SgfcMessageType::FatalError:
          fatalErrorMessageFound = true;
          break;
      }
    }

    if (fatalErrorMessageFound)
      return SgfcExitCode::FatalError;
    if (errorMessageFound)
      return SgfcExitCode::Error;
    else if (warningMessageFound)
      return SgfcExitCode::Warning;
    else
      return SgfcExitCode::Ok;
  }

  bool SgfcUtility::GetIsSgfDataValidFromMessageCollection(
    const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection)
  {
    for (const auto& message : messageCollection)
    {
      if (message->GetMessageType() == SgfcMessageType::FatalError)
        return false;
    }

    return true;
  }
}
