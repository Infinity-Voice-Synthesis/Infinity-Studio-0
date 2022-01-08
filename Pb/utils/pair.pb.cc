// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: utils/pair.proto

#include "utils/pair.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace org {
namespace infinity {
namespace idm {
namespace utils {
constexpr Pair::Pair(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : key_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , value_(int64_t{0}){}
struct PairDefaultTypeInternal {
  constexpr PairDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PairDefaultTypeInternal() {}
  union {
    Pair _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PairDefaultTypeInternal _Pair_default_instance_;
}  // namespace utils
}  // namespace idm
}  // namespace infinity
}  // namespace org
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_utils_2fpair_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_utils_2fpair_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_utils_2fpair_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_utils_2fpair_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::org::infinity::idm::utils::Pair, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::org::infinity::idm::utils::Pair, key_),
  PROTOBUF_FIELD_OFFSET(::org::infinity::idm::utils::Pair, value_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::org::infinity::idm::utils::Pair)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::org::infinity::idm::utils::_Pair_default_instance_),
};

const char descriptor_table_protodef_utils_2fpair_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020utils/pair.proto\022\026org.infinity.idm.uti"
  "ls\"\"\n\004Pair\022\013\n\003key\030\001 \001(\t\022\r\n\005value\030\002 \001(\003b\006"
  "proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_utils_2fpair_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_utils_2fpair_2eproto = {
  false, false, 86, descriptor_table_protodef_utils_2fpair_2eproto, "utils/pair.proto", 
  &descriptor_table_utils_2fpair_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_utils_2fpair_2eproto::offsets,
  file_level_metadata_utils_2fpair_2eproto, file_level_enum_descriptors_utils_2fpair_2eproto, file_level_service_descriptors_utils_2fpair_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_utils_2fpair_2eproto_getter() {
  return &descriptor_table_utils_2fpair_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_utils_2fpair_2eproto(&descriptor_table_utils_2fpair_2eproto);
namespace org {
namespace infinity {
namespace idm {
namespace utils {

// ===================================================================

class Pair::_Internal {
 public:
};

Pair::Pair(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:org.infinity.idm.utils.Pair)
}
Pair::Pair(const Pair& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  key_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_key().empty()) {
    key_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_key(), 
      GetArenaForAllocation());
  }
  value_ = from.value_;
  // @@protoc_insertion_point(copy_constructor:org.infinity.idm.utils.Pair)
}

inline void Pair::SharedCtor() {
key_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
value_ = int64_t{0};
}

Pair::~Pair() {
  // @@protoc_insertion_point(destructor:org.infinity.idm.utils.Pair)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Pair::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  key_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Pair::ArenaDtor(void* object) {
  Pair* _this = reinterpret_cast< Pair* >(object);
  (void)_this;
}
void Pair::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Pair::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Pair::Clear() {
// @@protoc_insertion_point(message_clear_start:org.infinity.idm.utils.Pair)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  key_.ClearToEmpty();
  value_ = int64_t{0};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Pair::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string key = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_key();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "org.infinity.idm.utils.Pair.key"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int64 value = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          value_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Pair::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:org.infinity.idm.utils.Pair)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string key = 1;
  if (!this->_internal_key().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_key().data(), static_cast<int>(this->_internal_key().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "org.infinity.idm.utils.Pair.key");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_key(), target);
  }

  // int64 value = 2;
  if (this->_internal_value() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(2, this->_internal_value(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:org.infinity.idm.utils.Pair)
  return target;
}

size_t Pair::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:org.infinity.idm.utils.Pair)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string key = 1;
  if (!this->_internal_key().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_key());
  }

  // int64 value = 2;
  if (this->_internal_value() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_value());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Pair::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Pair::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Pair::GetClassData() const { return &_class_data_; }

void Pair::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<Pair *>(to)->MergeFrom(
      static_cast<const Pair &>(from));
}


void Pair::MergeFrom(const Pair& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:org.infinity.idm.utils.Pair)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_key().empty()) {
    _internal_set_key(from._internal_key());
  }
  if (from._internal_value() != 0) {
    _internal_set_value(from._internal_value());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Pair::CopyFrom(const Pair& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:org.infinity.idm.utils.Pair)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Pair::IsInitialized() const {
  return true;
}

void Pair::InternalSwap(Pair* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &key_, GetArenaForAllocation(),
      &other->key_, other->GetArenaForAllocation()
  );
  swap(value_, other->value_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Pair::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_utils_2fpair_2eproto_getter, &descriptor_table_utils_2fpair_2eproto_once,
      file_level_metadata_utils_2fpair_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace utils
}  // namespace idm
}  // namespace infinity
}  // namespace org
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::org::infinity::idm::utils::Pair* Arena::CreateMaybeMessage< ::org::infinity::idm::utils::Pair >(Arena* arena) {
  return Arena::CreateMessageInternal< ::org::infinity::idm::utils::Pair >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
