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
  sgfc/backend/SgfcBackendController.h
  sgfc/backend/SgfcBackendDataState.h
  sgfc/backend/SgfcBackendDataWrapper.h
  sgfc/backend/SgfcBackendLoadResult.h
  sgfc/backend/SgfcBackendSaveResult.h
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
  HEADERS_PUBLIC
  ../include/ISgfcBoardSizeProperty.h
  ../include/ISgfcColorPropertyValue.h
  ../include/ISgfcCommandLine.h
  ../include/ISgfcComposedPropertyValue.h
  ../include/ISgfcDocument.h
  ../include/ISgfcDocumentReadResult.h
  ../include/ISgfcDocumentReader.h
  ../include/ISgfcDocumentWriteResult.h
  ../include/ISgfcDocumentWriter.h
  ../include/ISgfcDoublePropertyValue.h
  ../include/ISgfcGame.h
  ../include/ISgfcGameTypeProperty.h
  ../include/ISgfcGoMove.h
  ../include/ISgfcGoMovePropertyValue.h
  ../include/ISgfcGoPoint.h
  ../include/ISgfcGoPointPropertyValue.h
  ../include/ISgfcGoStone.h
  ../include/ISgfcGoStonePropertyValue.h
  ../include/ISgfcMessage.h
  ../include/ISgfcMovePropertyValue.h
  ../include/ISgfcNode.h
  ../include/ISgfcNumberPropertyValue.h
  ../include/ISgfcPointPropertyValue.h
  ../include/ISgfcProperty.h
  ../include/ISgfcPropertyFactory.h
  ../include/ISgfcPropertyValue.h
  ../include/ISgfcPropertyValueFactory.h
  ../include/ISgfcRealPropertyValue.h
  ../include/ISgfcSgfContent.h
  ../include/ISgfcSimpleTextPropertyValue.h
  ../include/ISgfcSinglePropertyValue.h
  ../include/ISgfcStonePropertyValue.h
  ../include/ISgfcTextPropertyValue.h
  ../include/ISgfcTreeBuilder.h
  ../include/SgfcBoardSize.h
  ../include/SgfcColor.h
  ../include/SgfcConstants.h
  ../include/SgfcCoordinateSystem.h
  ../include/SgfcDouble.h
  ../include/SgfcExitCode.h
  ../include/SgfcGameType.h
  ../include/SgfcGoPointNotation.h
  ../include/SgfcMessageType.h
  ../include/SgfcPlusPlusFactory.h
  ../include/SgfcPropertyType.h
  ../include/SgfcPropertyValueType.h
  ../include/SgfcTypedefs.h
)

set (
  SOURCES_SGFC
  ../sgfc/execute.c
  ../sgfc/gameinfo.c
  ../sgfc/load.c
  ../sgfc/main.c
  ../sgfc/parse.c
  ../sgfc/parse2.c
  ../sgfc/properties.c
  ../sgfc/save.c
  ../sgfc/strict.c
  ../sgfc/util.c
)

set (
  HEADERS_SGFC
  ../sgfc/all.h
  ../sgfc/protos.h
)