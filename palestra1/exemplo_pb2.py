# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: exemplo.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='exemplo.proto',
  package='',
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\rexemplo.proto\"<\n\x10OperandosRequest\x12\x12\n\noperandoUm\x18\x01 \x01(\x05\x12\x14\n\x0coperandoDois\x18\x02 \x01(\x05\"\\\n\x11ResultadoResponse\x12\x0c\n\x04soma\x18\x01 \x01(\x05\x12\x11\n\tsubtracao\x18\x02 \x01(\x05\x12\x15\n\rmultiplicacao\x18\x03 \x01(\x02\x12\x0f\n\x07\x64ivicao\x18\x04 \x01(\x02\x32J\n\x0b\x43\x61lculadora\x12;\n\x10\x43\x61lculaOperandos\x12\x11.OperandosRequest\x1a\x12.ResultadoResponse\"\x00\x62\x06proto3'
)




_OPERANDOSREQUEST = _descriptor.Descriptor(
  name='OperandosRequest',
  full_name='OperandosRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='operandoUm', full_name='OperandosRequest.operandoUm', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='operandoDois', full_name='OperandosRequest.operandoDois', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=17,
  serialized_end=77,
)


_RESULTADORESPONSE = _descriptor.Descriptor(
  name='ResultadoResponse',
  full_name='ResultadoResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='soma', full_name='ResultadoResponse.soma', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='subtracao', full_name='ResultadoResponse.subtracao', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='multiplicacao', full_name='ResultadoResponse.multiplicacao', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='divicao', full_name='ResultadoResponse.divicao', index=3,
      number=4, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=79,
  serialized_end=171,
)

DESCRIPTOR.message_types_by_name['OperandosRequest'] = _OPERANDOSREQUEST
DESCRIPTOR.message_types_by_name['ResultadoResponse'] = _RESULTADORESPONSE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

OperandosRequest = _reflection.GeneratedProtocolMessageType('OperandosRequest', (_message.Message,), {
  'DESCRIPTOR' : _OPERANDOSREQUEST,
  '__module__' : 'exemplo_pb2'
  # @@protoc_insertion_point(class_scope:OperandosRequest)
  })
_sym_db.RegisterMessage(OperandosRequest)

ResultadoResponse = _reflection.GeneratedProtocolMessageType('ResultadoResponse', (_message.Message,), {
  'DESCRIPTOR' : _RESULTADORESPONSE,
  '__module__' : 'exemplo_pb2'
  # @@protoc_insertion_point(class_scope:ResultadoResponse)
  })
_sym_db.RegisterMessage(ResultadoResponse)



_CALCULADORA = _descriptor.ServiceDescriptor(
  name='Calculadora',
  full_name='Calculadora',
  file=DESCRIPTOR,
  index=0,
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_start=173,
  serialized_end=247,
  methods=[
  _descriptor.MethodDescriptor(
    name='CalculaOperandos',
    full_name='Calculadora.CalculaOperandos',
    index=0,
    containing_service=None,
    input_type=_OPERANDOSREQUEST,
    output_type=_RESULTADORESPONSE,
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
  ),
])
_sym_db.RegisterServiceDescriptor(_CALCULADORA)

DESCRIPTOR.services_by_name['Calculadora'] = _CALCULADORA

# @@protoc_insertion_point(module_scope)
