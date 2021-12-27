// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: nparam.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_nparam_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_nparam_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_nparam_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_nparam_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_nparam_2eproto;
namespace infinity {
class NoteParam;
struct NoteParamDefaultTypeInternal;
extern NoteParamDefaultTypeInternal _NoteParam_default_instance_;
}  // namespace infinity
PROTOBUF_NAMESPACE_OPEN
template<> ::infinity::NoteParam* Arena::CreateMaybeMessage<::infinity::NoteParam>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace infinity {

// ===================================================================

class NoteParam final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:infinity.NoteParam) */ {
 public:
  inline NoteParam() : NoteParam(nullptr) {}
  ~NoteParam() override;
  explicit constexpr NoteParam(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  NoteParam(const NoteParam& from);
  NoteParam(NoteParam&& from) noexcept
    : NoteParam() {
    *this = ::std::move(from);
  }

  inline NoteParam& operator=(const NoteParam& from) {
    CopyFrom(from);
    return *this;
  }
  inline NoteParam& operator=(NoteParam&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const NoteParam& default_instance() {
    return *internal_default_instance();
  }
  static inline const NoteParam* internal_default_instance() {
    return reinterpret_cast<const NoteParam*>(
               &_NoteParam_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(NoteParam& a, NoteParam& b) {
    a.Swap(&b);
  }
  inline void Swap(NoteParam* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(NoteParam* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline NoteParam* New() const final {
    return new NoteParam();
  }

  NoteParam* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<NoteParam>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const NoteParam& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const NoteParam& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NoteParam* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "infinity.NoteParam";
  }
  protected:
  explicit NoteParam(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 1,
    kVMaxFieldNumber = 2,
    kVMinFieldNumber = 3,
    kVDefaultFieldNumber = 4,
    kValueFieldNumber = 5,
  };
  // string name = 1;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_MUST_USE_RESULT std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // double vMax = 2;
  void clear_vmax();
  double vmax() const;
  void set_vmax(double value);
  private:
  double _internal_vmax() const;
  void _internal_set_vmax(double value);
  public:

  // double vMin = 3;
  void clear_vmin();
  double vmin() const;
  void set_vmin(double value);
  private:
  double _internal_vmin() const;
  void _internal_set_vmin(double value);
  public:

  // double vDefault = 4;
  void clear_vdefault();
  double vdefault() const;
  void set_vdefault(double value);
  private:
  double _internal_vdefault() const;
  void _internal_set_vdefault(double value);
  public:

  // double value = 5;
  void clear_value();
  double value() const;
  void set_value(double value);
  private:
  double _internal_value() const;
  void _internal_set_value(double value);
  public:

  // @@protoc_insertion_point(class_scope:infinity.NoteParam)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  double vmax_;
  double vmin_;
  double vdefault_;
  double value_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_nparam_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NoteParam

// string name = 1;
inline void NoteParam::clear_name() {
  name_.ClearToEmpty();
}
inline const std::string& NoteParam::name() const {
  // @@protoc_insertion_point(field_get:infinity.NoteParam.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void NoteParam::set_name(ArgT0&& arg0, ArgT... args) {
 
 name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:infinity.NoteParam.name)
}
inline std::string* NoteParam::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:infinity.NoteParam.name)
  return _s;
}
inline const std::string& NoteParam::_internal_name() const {
  return name_.Get();
}
inline void NoteParam::_internal_set_name(const std::string& value) {
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* NoteParam::_internal_mutable_name() {
  
  return name_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* NoteParam::release_name() {
  // @@protoc_insertion_point(field_release:infinity.NoteParam.name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void NoteParam::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:infinity.NoteParam.name)
}

// double vMax = 2;
inline void NoteParam::clear_vmax() {
  vmax_ = 0;
}
inline double NoteParam::_internal_vmax() const {
  return vmax_;
}
inline double NoteParam::vmax() const {
  // @@protoc_insertion_point(field_get:infinity.NoteParam.vMax)
  return _internal_vmax();
}
inline void NoteParam::_internal_set_vmax(double value) {
  
  vmax_ = value;
}
inline void NoteParam::set_vmax(double value) {
  _internal_set_vmax(value);
  // @@protoc_insertion_point(field_set:infinity.NoteParam.vMax)
}

// double vMin = 3;
inline void NoteParam::clear_vmin() {
  vmin_ = 0;
}
inline double NoteParam::_internal_vmin() const {
  return vmin_;
}
inline double NoteParam::vmin() const {
  // @@protoc_insertion_point(field_get:infinity.NoteParam.vMin)
  return _internal_vmin();
}
inline void NoteParam::_internal_set_vmin(double value) {
  
  vmin_ = value;
}
inline void NoteParam::set_vmin(double value) {
  _internal_set_vmin(value);
  // @@protoc_insertion_point(field_set:infinity.NoteParam.vMin)
}

// double vDefault = 4;
inline void NoteParam::clear_vdefault() {
  vdefault_ = 0;
}
inline double NoteParam::_internal_vdefault() const {
  return vdefault_;
}
inline double NoteParam::vdefault() const {
  // @@protoc_insertion_point(field_get:infinity.NoteParam.vDefault)
  return _internal_vdefault();
}
inline void NoteParam::_internal_set_vdefault(double value) {
  
  vdefault_ = value;
}
inline void NoteParam::set_vdefault(double value) {
  _internal_set_vdefault(value);
  // @@protoc_insertion_point(field_set:infinity.NoteParam.vDefault)
}

// double value = 5;
inline void NoteParam::clear_value() {
  value_ = 0;
}
inline double NoteParam::_internal_value() const {
  return value_;
}
inline double NoteParam::value() const {
  // @@protoc_insertion_point(field_get:infinity.NoteParam.value)
  return _internal_value();
}
inline void NoteParam::_internal_set_value(double value) {
  
  value_ = value;
}
inline void NoteParam::set_value(double value) {
  _internal_set_value(value);
  // @@protoc_insertion_point(field_set:infinity.NoteParam.value)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace infinity

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_nparam_2eproto
