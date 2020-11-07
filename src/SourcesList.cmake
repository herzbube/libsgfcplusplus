# The export header file is not under source control, it's generated by CMake.
set (
  EXPORT_HEADER_FILE_FOLDER
  ${CMAKE_CURRENT_BINARY_DIR}
)
set (
  EXPORT_HEADER_FILE_NAME
  SgfcPlusPlusExport.h
)

set (
  SOURCES
  document/SgfcComposedPropertyValue.cpp
  document/SgfcDocument.cpp
  document/SgfcGame.cpp
  document/SgfcNode.cpp
  document/SgfcProperty.cpp
  document/SgfcPropertyMetaInfo.cpp
  document/SgfcSinglePropertyValue.cpp
  document/SgfcTreeBuilder.cpp
  document/typedproperty/SgfcBoardSizeProperty.cpp
  document/typedproperty/SgfcGameTypeProperty.cpp
  document/typedpropertyvalue/SgfcColorPropertyValue.cpp
  document/typedpropertyvalue/SgfcDoublePropertyValue.cpp
  document/typedpropertyvalue/SgfcMovePropertyValue.cpp
  document/typedpropertyvalue/SgfcNumberPropertyValue.cpp
  document/typedpropertyvalue/SgfcPointPropertyValue.cpp
  document/typedpropertyvalue/SgfcRealPropertyValue.cpp
  document/typedpropertyvalue/SgfcSimpleTextPropertyValue.cpp
  document/typedpropertyvalue/SgfcStonePropertyValue.cpp
  document/typedpropertyvalue/SgfcTextPropertyValue.cpp
  document/typedpropertyvalue/SgfcUnknownPropertyValue.cpp
  document/typedpropertyvalue/go/SgfcGoMovePropertyValue.cpp
  document/typedpropertyvalue/go/SgfcGoPointPropertyValue.cpp
  document/typedpropertyvalue/go/SgfcGoStonePropertyValue.cpp
  factory/SgfcPlusPlusFactory.cpp
  factory/SgfcPropertyFactory.cpp
  factory/SgfcPropertyValueFactory.cpp
  game/SgfcBoardSize.cpp
  game/go/SgfcGoMove.cpp
  game/go/SgfcGoPoint.cpp
  game/go/SgfcGoStone.cpp
  interface/internal/ISgfcPropertyValueTypeDescriptor.cpp
  interface/public/ISgfcArgument.cpp
  interface/public/ISgfcArguments.cpp
  interface/public/ISgfcBoardSizeProperty.cpp
  interface/public/ISgfcColorPropertyValue.cpp
  interface/public/ISgfcCommandLine.cpp
  interface/public/ISgfcComposedPropertyValue.cpp
  interface/public/ISgfcDocument.cpp
  interface/public/ISgfcDocumentReadResult.cpp
  interface/public/ISgfcDocumentReader.cpp
  interface/public/ISgfcDocumentWriteResult.cpp
  interface/public/ISgfcDocumentWriter.cpp
  interface/public/ISgfcDoublePropertyValue.cpp
  interface/public/ISgfcGame.cpp
  interface/public/ISgfcGameTypeProperty.cpp
  interface/public/ISgfcGoMove.cpp
  interface/public/ISgfcGoMovePropertyValue.cpp
  interface/public/ISgfcGoPoint.cpp
  interface/public/ISgfcGoPointPropertyValue.cpp
  interface/public/ISgfcGoStone.cpp
  interface/public/ISgfcGoStonePropertyValue.cpp
  interface/public/ISgfcMessage.cpp
  interface/public/ISgfcMovePropertyValue.cpp
  interface/public/ISgfcNode.cpp
  interface/public/ISgfcNumberPropertyValue.cpp
  interface/public/ISgfcPointPropertyValue.cpp
  interface/public/ISgfcProperty.cpp
  interface/public/ISgfcPropertyFactory.cpp
  interface/public/ISgfcPropertyValue.cpp
  interface/public/ISgfcPropertyValueFactory.cpp
  interface/public/ISgfcRealPropertyValue.cpp
  interface/public/ISgfcSgfContent.cpp
  interface/public/ISgfcSimpleTextPropertyValue.cpp
  interface/public/ISgfcSinglePropertyValue.cpp
  interface/public/ISgfcStonePropertyValue.cpp
  interface/public/ISgfcTextPropertyValue.cpp
  interface/public/ISgfcTreeBuilder.cpp
  parsing/SgfcDocumentEncoder.cpp
  parsing/SgfcPropertyDecoder.cpp
  parsing/SgfcValueConverter.cpp
  parsing/propertyvaluetypedescriptor/SgfcPropertyBasicValueTypeDescriptor.cpp
  parsing/propertyvaluetypedescriptor/SgfcPropertyComposedValueTypeDescriptor.cpp
  parsing/propertyvaluetypedescriptor/SgfcPropertyDualValueTypeDescriptor.cpp
  parsing/propertyvaluetypedescriptor/SgfcPropertyElistValueTypeDescriptor.cpp
  parsing/propertyvaluetypedescriptor/SgfcPropertyListValueTypeDescriptor.cpp
  sgfc/argument/SgfcArgument.cpp
  sgfc/argument/SgfcArguments.cpp
  sgfc/backend/SgfcBackendController.cpp
  sgfc/backend/SgfcBackendDataWrapper.cpp
  sgfc/backend/SgfcBackendLoadResult.cpp
  sgfc/backend/SgfcBackendSaveResult.cpp
  sgfc/backend/SgfcOptions.cpp
  sgfc/frontend/SgfcCommandLine.cpp
  sgfc/frontend/SgfcDocumentReadResult.cpp
  sgfc/frontend/SgfcDocumentReader.cpp
  sgfc/frontend/SgfcDocumentWriteResult.cpp
  sgfc/frontend/SgfcDocumentWriter.cpp
  sgfc/message/SgfcMessage.cpp
  sgfc/message/SgfcMessageParser.cpp
  sgfc/message/SgfcMessageStream.cpp
  sgfc/save/SgfcSaveStream.cpp
  sgfc/save/SgfcSgfContent.cpp
  SgfcConstants.cpp
  SgfcPrivateConstants.cpp
  SgfcUtility.cpp
  ${PACKAGE_CONFIG_FILE_IN}
  ${SOURCES_LIST_FILE_NAME}
)

set (
  HEADERS_PRIVATE
  document/SgfcComposedPropertyValue.h
  document/SgfcDocument.h
  document/SgfcGame.h
  document/SgfcNode.h
  document/SgfcProperty.h
  document/SgfcPropertyMetaInfo.h
  document/SgfcSinglePropertyValue.h
  document/SgfcTreeBuilder.h
  document/typedproperty/SgfcBoardSizeProperty.h
  document/typedproperty/SgfcGameTypeProperty.h
  document/typedpropertyvalue/SgfcColorPropertyValue.h
  document/typedpropertyvalue/SgfcDoublePropertyValue.h
  document/typedpropertyvalue/SgfcMovePropertyValue.h
  document/typedpropertyvalue/SgfcNumberPropertyValue.h
  document/typedpropertyvalue/SgfcPointPropertyValue.h
  document/typedpropertyvalue/SgfcRealPropertyValue.h
  document/typedpropertyvalue/SgfcSimpleTextPropertyValue.h
  document/typedpropertyvalue/SgfcStonePropertyValue.h
  document/typedpropertyvalue/SgfcTextPropertyValue.h
  document/typedpropertyvalue/SgfcUnknownPropertyValue.h
  document/typedpropertyvalue/go/SgfcGoMovePropertyValue.h
  document/typedpropertyvalue/go/SgfcGoPointPropertyValue.h
  document/typedpropertyvalue/go/SgfcGoStonePropertyValue.h
  factory/SgfcPropertyFactory.h
  factory/SgfcPropertyValueFactory.h
  game/go/SgfcGoMove.h
  game/go/SgfcGoPoint.h
  game/go/SgfcGoStone.h
  interface/internal/ISgfcPropertyValueTypeDescriptor.h
  interface/internal/SgfcMessagePart.h
  interface/internal/SgfcPropertyValueTypeDescriptorType.h
  parsing/SgfcDocumentEncoder.h
  parsing/SgfcPropertyDecoder.h
  parsing/SgfcValueConverter.h
  parsing/propertyvaluetypedescriptor/SgfcPropertyBasicValueTypeDescriptor.h
  parsing/propertyvaluetypedescriptor/SgfcPropertyComposedValueTypeDescriptor.h
  parsing/propertyvaluetypedescriptor/SgfcPropertyDualValueTypeDescriptor.h
  parsing/propertyvaluetypedescriptor/SgfcPropertyElistValueTypeDescriptor.h
  parsing/propertyvaluetypedescriptor/SgfcPropertyListValueTypeDescriptor.h
  sgfc/argument/SgfcArgument.h
  sgfc/argument/SgfcArguments.h
  sgfc/backend/SgfcBackendController.h
  sgfc/backend/SgfcBackendDataState.h
  sgfc/backend/SgfcBackendDataWrapper.h
  sgfc/backend/SgfcBackendLoadResult.h
  sgfc/backend/SgfcBackendSaveResult.h
  sgfc/backend/SgfcDataLocation.h
  sgfc/backend/SgfcOptions.h
  sgfc/frontend/SgfcCommandLine.h
  sgfc/frontend/SgfcDocumentReadResult.h
  sgfc/frontend/SgfcDocumentReader.h
  sgfc/frontend/SgfcDocumentWriteResult.h
  sgfc/frontend/SgfcDocumentWriter.h
  sgfc/message/SgfcMessage.h
  sgfc/message/SgfcMessageParser.h
  sgfc/message/SgfcMessageStream.h
  sgfc/save/SgfcSaveStream.h
  sgfc/save/SgfcSgfContent.h
  SgfcPrivateConstants.h
  SgfcUtility.h
)

set (
  HEADERS_PUBLIC_FOLDER
  ../include
)

set (
  HEADERS_PUBLIC
  ${EXPORT_HEADER_FILE_FOLDER}/${EXPORT_HEADER_FILE_NAME}
  ${HEADERS_PUBLIC_FOLDER}/ISgfcArgument.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcArguments.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcBoardSizeProperty.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcColorPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcCommandLine.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcComposedPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcDocument.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcDocumentReadResult.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcDocumentReader.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcDocumentWriteResult.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcDocumentWriter.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcDoublePropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcGame.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcGameTypeProperty.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcGoMove.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcGoMovePropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcGoPoint.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcGoPointPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcGoStone.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcGoStonePropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcMessage.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcMovePropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcNode.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcNumberPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcPointPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcProperty.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcPropertyFactory.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcPropertyValueFactory.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcRealPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcSgfContent.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcSimpleTextPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcSinglePropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcStonePropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcTextPropertyValue.h
  ${HEADERS_PUBLIC_FOLDER}/ISgfcTreeBuilder.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcArgumentType.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcBoardSize.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcColor.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcConstants.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcCoordinateSystem.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcDouble.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcExitCode.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcGameType.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcGoPointNotation.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcMessageType.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcPlusPlusFactory.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcPropertyType.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcPropertyValueType.h
  ${HEADERS_PUBLIC_FOLDER}/SgfcTypedefs.h
)

set (
  SOURCES_SGFC
  ../sgfc/src/execute.c
  ../sgfc/src/gameinfo.c
  ../sgfc/src/load.c
  ../sgfc/src/main.c
  ../sgfc/src/options.c
  ../sgfc/src/parse.c
  ../sgfc/src/parse2.c
  ../sgfc/src/properties.c
  ../sgfc/src/save.c
  ../sgfc/src/strict.c
  ../sgfc/src/util.c
)

set (
  HEADERS_SGFC
  ../sgfc/src/all.h
  ../sgfc/src/protos.h
)
