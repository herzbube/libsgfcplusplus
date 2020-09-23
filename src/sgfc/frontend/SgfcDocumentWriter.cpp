// Project includes
#include "../../../include/SgfcConstants.h"
#include "../../document/SgfcDocument.h"
#include "../../parsing/SgfcDocumentEncoder.h"
#include "../../SgfcUtility.h"
#include "../message/SgfcMessage.h"
#include "SgfcDocumentWriter.h"
#include "SgfcDocumentWriteResult.h"

// C++ Standard Library includes
#include <iostream>

namespace LibSgfcPlusPlus
{
  SgfcDocumentWriter::SgfcDocumentWriter()
    : backendController(new SgfcBackendController())
  {
  }

  SgfcDocumentWriter::~SgfcDocumentWriter()
  {
  }

  std::shared_ptr<ISgfcDocumentWriteResult> SgfcDocumentWriter::WriteSgfFile(
    std::shared_ptr<ISgfcDocument> document,
    const std::string& sgfFilePath)
  {
    SgfcDocumentEncoder encoder(document);
    std::string sgfContent = encoder.Encode();

    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper =
      std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper(sgfContent));

    std::shared_ptr<SgfcBackendSaveResult> backendSaveResult =
      this->backendController->SaveSgfFile(sgfFilePath, sgfDataWrapper);

    std::shared_ptr<ISgfcDocumentWriteResult> result = std::shared_ptr<ISgfcDocumentWriteResult>(new SgfcDocumentWriteResult(
      backendSaveResult->GetSaveResult()));
    return result;
  }

  std::shared_ptr<ISgfcDocumentWriteResult> SgfcDocumentWriter::WriteSgfContent(
    std::shared_ptr<ISgfcDocument> document,
    std::string& sgfContent)
  {
    std::string tempFilePath = SgfcUtility::GetUniqueTempFilePath();

    auto result = WriteSgfFile(document, tempFilePath);

    if (result->GetExitCode() == SgfcExitCode::FatalError)
    {
      auto deleteTempFileResult = DeleteTempFileOrCreateWriteResultWithErrorMessage(tempFilePath);
      if (deleteTempFileResult->GetExitCode() == SgfcExitCode::FatalError)
        return deleteTempFileResult;

      return result;
    }

    try
    {
      sgfContent = SgfcUtility::ReadFileContent(tempFilePath);
    }
    catch (std::runtime_error&)
    {
      auto deleteTempFileResult = DeleteTempFileOrCreateWriteResultWithErrorMessage(tempFilePath);
      if (deleteTempFileResult->GetExitCode() == SgfcExitCode::FatalError)
        return deleteTempFileResult;

      std::string messageText = "Reading SGF content from temporary file failed: " + tempFilePath;
      auto resultWithErrorMessage = CreateWriteResultWithErrorMessage(
        SgfcConstants::ReadSgfContentFromFilesystemErrorMessageID,
        messageText);
      return resultWithErrorMessage;
    }

    auto deleteTempFileResult = DeleteTempFileOrCreateWriteResultWithErrorMessage(tempFilePath);
    if (deleteTempFileResult->GetExitCode() == SgfcExitCode::FatalError)
      return deleteTempFileResult;

    return result;
  }

  void SgfcDocumentWriter::DebugPrintToConsole(
    std::shared_ptr<ISgfcDocument> document) const
  {
    SgfcDocumentEncoder encoder(document);
    std::string sgfContent = encoder.Encode();
    std::cout << sgfContent;
  }

  std::shared_ptr<ISgfcDocumentWriteResult> SgfcDocumentWriter::DeleteTempFileOrCreateWriteResultWithErrorMessage(
    const std::string& tempFilePath) const
  {
    try
    {
      SgfcUtility::DeleteFileIfExists(tempFilePath);
      return std::shared_ptr<ISgfcDocumentWriteResult>(new SgfcDocumentWriteResult());
    }
    catch (std::runtime_error&)
    {
      std::string messageText = "Deleting temporary file failed: " + tempFilePath;
      return CreateWriteResultWithErrorMessage(
        SgfcConstants::DeleteFileErrorMessageID,
        messageText);
    }
  }

  std::shared_ptr<ISgfcDocumentWriteResult> SgfcDocumentWriter::CreateWriteResultWithErrorMessage(
    int messageID,
    const std::string& messageText) const
  {
    auto message = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      messageID,
      messageText));

    std::vector<std::shared_ptr<ISgfcMessage>> parseResult = { message };

    return std::shared_ptr<ISgfcDocumentWriteResult>(new SgfcDocumentWriteResult(
      parseResult));
  }
}
