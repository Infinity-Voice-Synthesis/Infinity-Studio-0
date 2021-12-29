// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: track.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_track_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_track_2eproto

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
#include "note.pb.h"
#include "tparam.pb.h"
#include "wave.pb.h"
#include "effect.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_track_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_track_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_track_2eproto;
namespace infinity {
class Track;
struct TrackDefaultTypeInternal;
extern TrackDefaultTypeInternal _Track_default_instance_;
}  // namespace infinity
PROTOBUF_NAMESPACE_OPEN
template<> ::infinity::Track* Arena::CreateMaybeMessage<::infinity::Track>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace infinity {

// ===================================================================

class Track final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:infinity.Track) */ {
 public:
  inline Track() : Track(nullptr) {}
  ~Track() override;
  explicit constexpr Track(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Track(const Track& from);
  Track(Track&& from) noexcept
    : Track() {
    *this = ::std::move(from);
  }

  inline Track& operator=(const Track& from) {
    CopyFrom(from);
    return *this;
  }
  inline Track& operator=(Track&& from) noexcept {
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
  static const Track& default_instance() {
    return *internal_default_instance();
  }
  static inline const Track* internal_default_instance() {
    return reinterpret_cast<const Track*>(
               &_Track_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Track& a, Track& b) {
    a.Swap(&b);
  }
  inline void Swap(Track* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Track* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Track* New() const final {
    return new Track();
  }

  Track* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Track>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Track& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Track& from);
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
  void InternalSwap(Track* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "infinity.Track";
  }
  protected:
  explicit Track(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kNotesFieldNumber = 10,
    kParamsFieldNumber = 11,
    kWavesFieldNumber = 12,
    kEffectorsFieldNumber = 13,
    kNameFieldNumber = 1,
    kColorFieldNumber = 2,
    kLibraryFieldNumber = 3,
    kDictionaryFieldNumber = 4,
    kTimbreAFieldNumber = 5,
    kTimbreBFieldNumber = 6,
    kIsVoiceFieldNumber = 7,
    kMuteFieldNumber = 8,
    kSoloFieldNumber = 9,
  };
  // repeated .infinity.Note notes = 10;
  int notes_size() const;
  private:
  int _internal_notes_size() const;
  public:
  void clear_notes();
  ::infinity::Note* mutable_notes(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Note >*
      mutable_notes();
  private:
  const ::infinity::Note& _internal_notes(int index) const;
  ::infinity::Note* _internal_add_notes();
  public:
  const ::infinity::Note& notes(int index) const;
  ::infinity::Note* add_notes();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Note >&
      notes() const;

  // repeated .infinity.TrackParam params = 11;
  int params_size() const;
  private:
  int _internal_params_size() const;
  public:
  void clear_params();
  ::infinity::TrackParam* mutable_params(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::TrackParam >*
      mutable_params();
  private:
  const ::infinity::TrackParam& _internal_params(int index) const;
  ::infinity::TrackParam* _internal_add_params();
  public:
  const ::infinity::TrackParam& params(int index) const;
  ::infinity::TrackParam* add_params();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::TrackParam >&
      params() const;

  // repeated .infinity.Wave waves = 12;
  int waves_size() const;
  private:
  int _internal_waves_size() const;
  public:
  void clear_waves();
  ::infinity::Wave* mutable_waves(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Wave >*
      mutable_waves();
  private:
  const ::infinity::Wave& _internal_waves(int index) const;
  ::infinity::Wave* _internal_add_waves();
  public:
  const ::infinity::Wave& waves(int index) const;
  ::infinity::Wave* add_waves();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Wave >&
      waves() const;

  // repeated .infinity.Effector effectors = 13;
  int effectors_size() const;
  private:
  int _internal_effectors_size() const;
  public:
  void clear_effectors();
  ::infinity::Effector* mutable_effectors(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Effector >*
      mutable_effectors();
  private:
  const ::infinity::Effector& _internal_effectors(int index) const;
  ::infinity::Effector* _internal_add_effectors();
  public:
  const ::infinity::Effector& effectors(int index) const;
  ::infinity::Effector* add_effectors();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Effector >&
      effectors() const;

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

  // string color = 2;
  void clear_color();
  const std::string& color() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_color(ArgT0&& arg0, ArgT... args);
  std::string* mutable_color();
  PROTOBUF_MUST_USE_RESULT std::string* release_color();
  void set_allocated_color(std::string* color);
  private:
  const std::string& _internal_color() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_color(const std::string& value);
  std::string* _internal_mutable_color();
  public:

  // string library = 3;
  void clear_library();
  const std::string& library() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_library(ArgT0&& arg0, ArgT... args);
  std::string* mutable_library();
  PROTOBUF_MUST_USE_RESULT std::string* release_library();
  void set_allocated_library(std::string* library);
  private:
  const std::string& _internal_library() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_library(const std::string& value);
  std::string* _internal_mutable_library();
  public:

  // string dictionary = 4;
  void clear_dictionary();
  const std::string& dictionary() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_dictionary(ArgT0&& arg0, ArgT... args);
  std::string* mutable_dictionary();
  PROTOBUF_MUST_USE_RESULT std::string* release_dictionary();
  void set_allocated_dictionary(std::string* dictionary);
  private:
  const std::string& _internal_dictionary() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_dictionary(const std::string& value);
  std::string* _internal_mutable_dictionary();
  public:

  // string timbreA = 5;
  void clear_timbrea();
  const std::string& timbrea() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_timbrea(ArgT0&& arg0, ArgT... args);
  std::string* mutable_timbrea();
  PROTOBUF_MUST_USE_RESULT std::string* release_timbrea();
  void set_allocated_timbrea(std::string* timbrea);
  private:
  const std::string& _internal_timbrea() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_timbrea(const std::string& value);
  std::string* _internal_mutable_timbrea();
  public:

  // string timbreB = 6;
  void clear_timbreb();
  const std::string& timbreb() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_timbreb(ArgT0&& arg0, ArgT... args);
  std::string* mutable_timbreb();
  PROTOBUF_MUST_USE_RESULT std::string* release_timbreb();
  void set_allocated_timbreb(std::string* timbreb);
  private:
  const std::string& _internal_timbreb() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_timbreb(const std::string& value);
  std::string* _internal_mutable_timbreb();
  public:

  // bool isVoice = 7;
  void clear_isvoice();
  bool isvoice() const;
  void set_isvoice(bool value);
  private:
  bool _internal_isvoice() const;
  void _internal_set_isvoice(bool value);
  public:

  // bool mute = 8;
  void clear_mute();
  bool mute() const;
  void set_mute(bool value);
  private:
  bool _internal_mute() const;
  void _internal_set_mute(bool value);
  public:

  // bool solo = 9;
  void clear_solo();
  bool solo() const;
  void set_solo(bool value);
  private:
  bool _internal_solo() const;
  void _internal_set_solo(bool value);
  public:

  // @@protoc_insertion_point(class_scope:infinity.Track)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Note > notes_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::TrackParam > params_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Wave > waves_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Effector > effectors_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr color_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr library_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr dictionary_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr timbrea_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr timbreb_;
  bool isvoice_;
  bool mute_;
  bool solo_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_track_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Track

// string name = 1;
inline void Track::clear_name() {
  name_.ClearToEmpty();
}
inline const std::string& Track::name() const {
  // @@protoc_insertion_point(field_get:infinity.Track.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Track::set_name(ArgT0&& arg0, ArgT... args) {
 
 name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:infinity.Track.name)
}
inline std::string* Track::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:infinity.Track.name)
  return _s;
}
inline const std::string& Track::_internal_name() const {
  return name_.Get();
}
inline void Track::_internal_set_name(const std::string& value) {
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Track::_internal_mutable_name() {
  
  return name_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Track::release_name() {
  // @@protoc_insertion_point(field_release:infinity.Track.name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Track::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:infinity.Track.name)
}

// string color = 2;
inline void Track::clear_color() {
  color_.ClearToEmpty();
}
inline const std::string& Track::color() const {
  // @@protoc_insertion_point(field_get:infinity.Track.color)
  return _internal_color();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Track::set_color(ArgT0&& arg0, ArgT... args) {
 
 color_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:infinity.Track.color)
}
inline std::string* Track::mutable_color() {
  std::string* _s = _internal_mutable_color();
  // @@protoc_insertion_point(field_mutable:infinity.Track.color)
  return _s;
}
inline const std::string& Track::_internal_color() const {
  return color_.Get();
}
inline void Track::_internal_set_color(const std::string& value) {
  
  color_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Track::_internal_mutable_color() {
  
  return color_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Track::release_color() {
  // @@protoc_insertion_point(field_release:infinity.Track.color)
  return color_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Track::set_allocated_color(std::string* color) {
  if (color != nullptr) {
    
  } else {
    
  }
  color_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), color,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:infinity.Track.color)
}

// string library = 3;
inline void Track::clear_library() {
  library_.ClearToEmpty();
}
inline const std::string& Track::library() const {
  // @@protoc_insertion_point(field_get:infinity.Track.library)
  return _internal_library();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Track::set_library(ArgT0&& arg0, ArgT... args) {
 
 library_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:infinity.Track.library)
}
inline std::string* Track::mutable_library() {
  std::string* _s = _internal_mutable_library();
  // @@protoc_insertion_point(field_mutable:infinity.Track.library)
  return _s;
}
inline const std::string& Track::_internal_library() const {
  return library_.Get();
}
inline void Track::_internal_set_library(const std::string& value) {
  
  library_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Track::_internal_mutable_library() {
  
  return library_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Track::release_library() {
  // @@protoc_insertion_point(field_release:infinity.Track.library)
  return library_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Track::set_allocated_library(std::string* library) {
  if (library != nullptr) {
    
  } else {
    
  }
  library_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), library,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:infinity.Track.library)
}

// string dictionary = 4;
inline void Track::clear_dictionary() {
  dictionary_.ClearToEmpty();
}
inline const std::string& Track::dictionary() const {
  // @@protoc_insertion_point(field_get:infinity.Track.dictionary)
  return _internal_dictionary();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Track::set_dictionary(ArgT0&& arg0, ArgT... args) {
 
 dictionary_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:infinity.Track.dictionary)
}
inline std::string* Track::mutable_dictionary() {
  std::string* _s = _internal_mutable_dictionary();
  // @@protoc_insertion_point(field_mutable:infinity.Track.dictionary)
  return _s;
}
inline const std::string& Track::_internal_dictionary() const {
  return dictionary_.Get();
}
inline void Track::_internal_set_dictionary(const std::string& value) {
  
  dictionary_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Track::_internal_mutable_dictionary() {
  
  return dictionary_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Track::release_dictionary() {
  // @@protoc_insertion_point(field_release:infinity.Track.dictionary)
  return dictionary_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Track::set_allocated_dictionary(std::string* dictionary) {
  if (dictionary != nullptr) {
    
  } else {
    
  }
  dictionary_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), dictionary,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:infinity.Track.dictionary)
}

// string timbreA = 5;
inline void Track::clear_timbrea() {
  timbrea_.ClearToEmpty();
}
inline const std::string& Track::timbrea() const {
  // @@protoc_insertion_point(field_get:infinity.Track.timbreA)
  return _internal_timbrea();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Track::set_timbrea(ArgT0&& arg0, ArgT... args) {
 
 timbrea_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:infinity.Track.timbreA)
}
inline std::string* Track::mutable_timbrea() {
  std::string* _s = _internal_mutable_timbrea();
  // @@protoc_insertion_point(field_mutable:infinity.Track.timbreA)
  return _s;
}
inline const std::string& Track::_internal_timbrea() const {
  return timbrea_.Get();
}
inline void Track::_internal_set_timbrea(const std::string& value) {
  
  timbrea_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Track::_internal_mutable_timbrea() {
  
  return timbrea_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Track::release_timbrea() {
  // @@protoc_insertion_point(field_release:infinity.Track.timbreA)
  return timbrea_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Track::set_allocated_timbrea(std::string* timbrea) {
  if (timbrea != nullptr) {
    
  } else {
    
  }
  timbrea_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), timbrea,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:infinity.Track.timbreA)
}

// string timbreB = 6;
inline void Track::clear_timbreb() {
  timbreb_.ClearToEmpty();
}
inline const std::string& Track::timbreb() const {
  // @@protoc_insertion_point(field_get:infinity.Track.timbreB)
  return _internal_timbreb();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Track::set_timbreb(ArgT0&& arg0, ArgT... args) {
 
 timbreb_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:infinity.Track.timbreB)
}
inline std::string* Track::mutable_timbreb() {
  std::string* _s = _internal_mutable_timbreb();
  // @@protoc_insertion_point(field_mutable:infinity.Track.timbreB)
  return _s;
}
inline const std::string& Track::_internal_timbreb() const {
  return timbreb_.Get();
}
inline void Track::_internal_set_timbreb(const std::string& value) {
  
  timbreb_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Track::_internal_mutable_timbreb() {
  
  return timbreb_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Track::release_timbreb() {
  // @@protoc_insertion_point(field_release:infinity.Track.timbreB)
  return timbreb_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Track::set_allocated_timbreb(std::string* timbreb) {
  if (timbreb != nullptr) {
    
  } else {
    
  }
  timbreb_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), timbreb,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:infinity.Track.timbreB)
}

// bool isVoice = 7;
inline void Track::clear_isvoice() {
  isvoice_ = false;
}
inline bool Track::_internal_isvoice() const {
  return isvoice_;
}
inline bool Track::isvoice() const {
  // @@protoc_insertion_point(field_get:infinity.Track.isVoice)
  return _internal_isvoice();
}
inline void Track::_internal_set_isvoice(bool value) {
  
  isvoice_ = value;
}
inline void Track::set_isvoice(bool value) {
  _internal_set_isvoice(value);
  // @@protoc_insertion_point(field_set:infinity.Track.isVoice)
}

// bool mute = 8;
inline void Track::clear_mute() {
  mute_ = false;
}
inline bool Track::_internal_mute() const {
  return mute_;
}
inline bool Track::mute() const {
  // @@protoc_insertion_point(field_get:infinity.Track.mute)
  return _internal_mute();
}
inline void Track::_internal_set_mute(bool value) {
  
  mute_ = value;
}
inline void Track::set_mute(bool value) {
  _internal_set_mute(value);
  // @@protoc_insertion_point(field_set:infinity.Track.mute)
}

// bool solo = 9;
inline void Track::clear_solo() {
  solo_ = false;
}
inline bool Track::_internal_solo() const {
  return solo_;
}
inline bool Track::solo() const {
  // @@protoc_insertion_point(field_get:infinity.Track.solo)
  return _internal_solo();
}
inline void Track::_internal_set_solo(bool value) {
  
  solo_ = value;
}
inline void Track::set_solo(bool value) {
  _internal_set_solo(value);
  // @@protoc_insertion_point(field_set:infinity.Track.solo)
}

// repeated .infinity.Note notes = 10;
inline int Track::_internal_notes_size() const {
  return notes_.size();
}
inline int Track::notes_size() const {
  return _internal_notes_size();
}
inline ::infinity::Note* Track::mutable_notes(int index) {
  // @@protoc_insertion_point(field_mutable:infinity.Track.notes)
  return notes_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Note >*
Track::mutable_notes() {
  // @@protoc_insertion_point(field_mutable_list:infinity.Track.notes)
  return &notes_;
}
inline const ::infinity::Note& Track::_internal_notes(int index) const {
  return notes_.Get(index);
}
inline const ::infinity::Note& Track::notes(int index) const {
  // @@protoc_insertion_point(field_get:infinity.Track.notes)
  return _internal_notes(index);
}
inline ::infinity::Note* Track::_internal_add_notes() {
  return notes_.Add();
}
inline ::infinity::Note* Track::add_notes() {
  ::infinity::Note* _add = _internal_add_notes();
  // @@protoc_insertion_point(field_add:infinity.Track.notes)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Note >&
Track::notes() const {
  // @@protoc_insertion_point(field_list:infinity.Track.notes)
  return notes_;
}

// repeated .infinity.TrackParam params = 11;
inline int Track::_internal_params_size() const {
  return params_.size();
}
inline int Track::params_size() const {
  return _internal_params_size();
}
inline ::infinity::TrackParam* Track::mutable_params(int index) {
  // @@protoc_insertion_point(field_mutable:infinity.Track.params)
  return params_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::TrackParam >*
Track::mutable_params() {
  // @@protoc_insertion_point(field_mutable_list:infinity.Track.params)
  return &params_;
}
inline const ::infinity::TrackParam& Track::_internal_params(int index) const {
  return params_.Get(index);
}
inline const ::infinity::TrackParam& Track::params(int index) const {
  // @@protoc_insertion_point(field_get:infinity.Track.params)
  return _internal_params(index);
}
inline ::infinity::TrackParam* Track::_internal_add_params() {
  return params_.Add();
}
inline ::infinity::TrackParam* Track::add_params() {
  ::infinity::TrackParam* _add = _internal_add_params();
  // @@protoc_insertion_point(field_add:infinity.Track.params)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::TrackParam >&
Track::params() const {
  // @@protoc_insertion_point(field_list:infinity.Track.params)
  return params_;
}

// repeated .infinity.Wave waves = 12;
inline int Track::_internal_waves_size() const {
  return waves_.size();
}
inline int Track::waves_size() const {
  return _internal_waves_size();
}
inline ::infinity::Wave* Track::mutable_waves(int index) {
  // @@protoc_insertion_point(field_mutable:infinity.Track.waves)
  return waves_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Wave >*
Track::mutable_waves() {
  // @@protoc_insertion_point(field_mutable_list:infinity.Track.waves)
  return &waves_;
}
inline const ::infinity::Wave& Track::_internal_waves(int index) const {
  return waves_.Get(index);
}
inline const ::infinity::Wave& Track::waves(int index) const {
  // @@protoc_insertion_point(field_get:infinity.Track.waves)
  return _internal_waves(index);
}
inline ::infinity::Wave* Track::_internal_add_waves() {
  return waves_.Add();
}
inline ::infinity::Wave* Track::add_waves() {
  ::infinity::Wave* _add = _internal_add_waves();
  // @@protoc_insertion_point(field_add:infinity.Track.waves)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Wave >&
Track::waves() const {
  // @@protoc_insertion_point(field_list:infinity.Track.waves)
  return waves_;
}

// repeated .infinity.Effector effectors = 13;
inline int Track::_internal_effectors_size() const {
  return effectors_.size();
}
inline int Track::effectors_size() const {
  return _internal_effectors_size();
}
inline ::infinity::Effector* Track::mutable_effectors(int index) {
  // @@protoc_insertion_point(field_mutable:infinity.Track.effectors)
  return effectors_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Effector >*
Track::mutable_effectors() {
  // @@protoc_insertion_point(field_mutable_list:infinity.Track.effectors)
  return &effectors_;
}
inline const ::infinity::Effector& Track::_internal_effectors(int index) const {
  return effectors_.Get(index);
}
inline const ::infinity::Effector& Track::effectors(int index) const {
  // @@protoc_insertion_point(field_get:infinity.Track.effectors)
  return _internal_effectors(index);
}
inline ::infinity::Effector* Track::_internal_add_effectors() {
  return effectors_.Add();
}
inline ::infinity::Effector* Track::add_effectors() {
  ::infinity::Effector* _add = _internal_add_effectors();
  // @@protoc_insertion_point(field_add:infinity.Track.effectors)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::infinity::Effector >&
Track::effectors() const {
  // @@protoc_insertion_point(field_list:infinity.Track.effectors)
  return effectors_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace infinity

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_track_2eproto
