// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: project.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_project_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_project_2eproto

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
#include "track.pb.h"
#include "pattern.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_project_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_project_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_project_2eproto;
namespace org {
namespace infinity {
namespace idm {
class Project;
struct ProjectDefaultTypeInternal;
extern ProjectDefaultTypeInternal _Project_default_instance_;
}  // namespace idm
}  // namespace infinity
}  // namespace org
PROTOBUF_NAMESPACE_OPEN
template<> ::org::infinity::idm::Project* Arena::CreateMaybeMessage<::org::infinity::idm::Project>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace org {
namespace infinity {
namespace idm {

// ===================================================================

class Project final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:org.infinity.idm.Project) */ {
 public:
  inline Project() : Project(nullptr) {}
  ~Project() override;
  explicit constexpr Project(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Project(const Project& from);
  Project(Project&& from) noexcept
    : Project() {
    *this = ::std::move(from);
  }

  inline Project& operator=(const Project& from) {
    CopyFrom(from);
    return *this;
  }
  inline Project& operator=(Project&& from) noexcept {
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
  static const Project& default_instance() {
    return *internal_default_instance();
  }
  static inline const Project* internal_default_instance() {
    return reinterpret_cast<const Project*>(
               &_Project_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Project& a, Project& b) {
    a.Swap(&b);
  }
  inline void Swap(Project* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Project* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Project* New() const final {
    return new Project();
  }

  Project* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Project>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Project& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Project& from);
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
  void InternalSwap(Project* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "org.infinity.idm.Project";
  }
  protected:
  explicit Project(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kAuthorsFieldNumber = 6,
    kTracksFieldNumber = 7,
    kPatternsFieldNumber = 8,
    kEditorFieldNumber = 5,
    kTimeFieldNumber = 1,
    kBeatFieldNumber = 2,
    kTempoFieldNumber = 3,
    kSRateFieldNumber = 4,
  };
  // repeated string authors = 6;
  int authors_size() const;
  private:
  int _internal_authors_size() const;
  public:
  void clear_authors();
  const std::string& authors(int index) const;
  std::string* mutable_authors(int index);
  void set_authors(int index, const std::string& value);
  void set_authors(int index, std::string&& value);
  void set_authors(int index, const char* value);
  void set_authors(int index, const char* value, size_t size);
  std::string* add_authors();
  void add_authors(const std::string& value);
  void add_authors(std::string&& value);
  void add_authors(const char* value);
  void add_authors(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& authors() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_authors();
  private:
  const std::string& _internal_authors(int index) const;
  std::string* _internal_add_authors();
  public:

  // repeated .org.infinity.idm.Track tracks = 7;
  int tracks_size() const;
  private:
  int _internal_tracks_size() const;
  public:
  void clear_tracks();
  ::org::infinity::idm::Track* mutable_tracks(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Track >*
      mutable_tracks();
  private:
  const ::org::infinity::idm::Track& _internal_tracks(int index) const;
  ::org::infinity::idm::Track* _internal_add_tracks();
  public:
  const ::org::infinity::idm::Track& tracks(int index) const;
  ::org::infinity::idm::Track* add_tracks();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Track >&
      tracks() const;

  // repeated .org.infinity.idm.Pattern patterns = 8;
  int patterns_size() const;
  private:
  int _internal_patterns_size() const;
  public:
  void clear_patterns();
  ::org::infinity::idm::Pattern* mutable_patterns(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Pattern >*
      mutable_patterns();
  private:
  const ::org::infinity::idm::Pattern& _internal_patterns(int index) const;
  ::org::infinity::idm::Pattern* _internal_add_patterns();
  public:
  const ::org::infinity::idm::Pattern& patterns(int index) const;
  ::org::infinity::idm::Pattern* add_patterns();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Pattern >&
      patterns() const;

  // string editor = 5;
  void clear_editor();
  const std::string& editor() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_editor(ArgT0&& arg0, ArgT... args);
  std::string* mutable_editor();
  PROTOBUF_MUST_USE_RESULT std::string* release_editor();
  void set_allocated_editor(std::string* editor);
  private:
  const std::string& _internal_editor() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_editor(const std::string& value);
  std::string* _internal_mutable_editor();
  public:

  // uint32 time = 1;
  void clear_time();
  ::PROTOBUF_NAMESPACE_ID::uint32 time() const;
  void set_time(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_time() const;
  void _internal_set_time(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 beat = 2;
  void clear_beat();
  ::PROTOBUF_NAMESPACE_ID::uint32 beat() const;
  void set_beat(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_beat() const;
  void _internal_set_beat(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // double tempo = 3;
  void clear_tempo();
  double tempo() const;
  void set_tempo(double value);
  private:
  double _internal_tempo() const;
  void _internal_set_tempo(double value);
  public:

  // uint64 sRate = 4;
  void clear_srate();
  ::PROTOBUF_NAMESPACE_ID::uint64 srate() const;
  void set_srate(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_srate() const;
  void _internal_set_srate(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // @@protoc_insertion_point(class_scope:org.infinity.idm.Project)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> authors_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Track > tracks_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Pattern > patterns_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr editor_;
  ::PROTOBUF_NAMESPACE_ID::uint32 time_;
  ::PROTOBUF_NAMESPACE_ID::uint32 beat_;
  double tempo_;
  ::PROTOBUF_NAMESPACE_ID::uint64 srate_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_project_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Project

// uint32 time = 1;
inline void Project::clear_time() {
  time_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Project::_internal_time() const {
  return time_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Project::time() const {
  // @@protoc_insertion_point(field_get:org.infinity.idm.Project.time)
  return _internal_time();
}
inline void Project::_internal_set_time(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  time_ = value;
}
inline void Project::set_time(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_time(value);
  // @@protoc_insertion_point(field_set:org.infinity.idm.Project.time)
}

// uint32 beat = 2;
inline void Project::clear_beat() {
  beat_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Project::_internal_beat() const {
  return beat_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Project::beat() const {
  // @@protoc_insertion_point(field_get:org.infinity.idm.Project.beat)
  return _internal_beat();
}
inline void Project::_internal_set_beat(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  beat_ = value;
}
inline void Project::set_beat(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_beat(value);
  // @@protoc_insertion_point(field_set:org.infinity.idm.Project.beat)
}

// double tempo = 3;
inline void Project::clear_tempo() {
  tempo_ = 0;
}
inline double Project::_internal_tempo() const {
  return tempo_;
}
inline double Project::tempo() const {
  // @@protoc_insertion_point(field_get:org.infinity.idm.Project.tempo)
  return _internal_tempo();
}
inline void Project::_internal_set_tempo(double value) {
  
  tempo_ = value;
}
inline void Project::set_tempo(double value) {
  _internal_set_tempo(value);
  // @@protoc_insertion_point(field_set:org.infinity.idm.Project.tempo)
}

// uint64 sRate = 4;
inline void Project::clear_srate() {
  srate_ = uint64_t{0u};
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Project::_internal_srate() const {
  return srate_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Project::srate() const {
  // @@protoc_insertion_point(field_get:org.infinity.idm.Project.sRate)
  return _internal_srate();
}
inline void Project::_internal_set_srate(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  srate_ = value;
}
inline void Project::set_srate(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_srate(value);
  // @@protoc_insertion_point(field_set:org.infinity.idm.Project.sRate)
}

// string editor = 5;
inline void Project::clear_editor() {
  editor_.ClearToEmpty();
}
inline const std::string& Project::editor() const {
  // @@protoc_insertion_point(field_get:org.infinity.idm.Project.editor)
  return _internal_editor();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Project::set_editor(ArgT0&& arg0, ArgT... args) {
 
 editor_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:org.infinity.idm.Project.editor)
}
inline std::string* Project::mutable_editor() {
  std::string* _s = _internal_mutable_editor();
  // @@protoc_insertion_point(field_mutable:org.infinity.idm.Project.editor)
  return _s;
}
inline const std::string& Project::_internal_editor() const {
  return editor_.Get();
}
inline void Project::_internal_set_editor(const std::string& value) {
  
  editor_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Project::_internal_mutable_editor() {
  
  return editor_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Project::release_editor() {
  // @@protoc_insertion_point(field_release:org.infinity.idm.Project.editor)
  return editor_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Project::set_allocated_editor(std::string* editor) {
  if (editor != nullptr) {
    
  } else {
    
  }
  editor_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), editor,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:org.infinity.idm.Project.editor)
}

// repeated string authors = 6;
inline int Project::_internal_authors_size() const {
  return authors_.size();
}
inline int Project::authors_size() const {
  return _internal_authors_size();
}
inline void Project::clear_authors() {
  authors_.Clear();
}
inline std::string* Project::add_authors() {
  std::string* _s = _internal_add_authors();
  // @@protoc_insertion_point(field_add_mutable:org.infinity.idm.Project.authors)
  return _s;
}
inline const std::string& Project::_internal_authors(int index) const {
  return authors_.Get(index);
}
inline const std::string& Project::authors(int index) const {
  // @@protoc_insertion_point(field_get:org.infinity.idm.Project.authors)
  return _internal_authors(index);
}
inline std::string* Project::mutable_authors(int index) {
  // @@protoc_insertion_point(field_mutable:org.infinity.idm.Project.authors)
  return authors_.Mutable(index);
}
inline void Project::set_authors(int index, const std::string& value) {
  authors_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set:org.infinity.idm.Project.authors)
}
inline void Project::set_authors(int index, std::string&& value) {
  authors_.Mutable(index)->assign(std::move(value));
  // @@protoc_insertion_point(field_set:org.infinity.idm.Project.authors)
}
inline void Project::set_authors(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  authors_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:org.infinity.idm.Project.authors)
}
inline void Project::set_authors(int index, const char* value, size_t size) {
  authors_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:org.infinity.idm.Project.authors)
}
inline std::string* Project::_internal_add_authors() {
  return authors_.Add();
}
inline void Project::add_authors(const std::string& value) {
  authors_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:org.infinity.idm.Project.authors)
}
inline void Project::add_authors(std::string&& value) {
  authors_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:org.infinity.idm.Project.authors)
}
inline void Project::add_authors(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  authors_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:org.infinity.idm.Project.authors)
}
inline void Project::add_authors(const char* value, size_t size) {
  authors_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:org.infinity.idm.Project.authors)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
Project::authors() const {
  // @@protoc_insertion_point(field_list:org.infinity.idm.Project.authors)
  return authors_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
Project::mutable_authors() {
  // @@protoc_insertion_point(field_mutable_list:org.infinity.idm.Project.authors)
  return &authors_;
}

// repeated .org.infinity.idm.Track tracks = 7;
inline int Project::_internal_tracks_size() const {
  return tracks_.size();
}
inline int Project::tracks_size() const {
  return _internal_tracks_size();
}
inline ::org::infinity::idm::Track* Project::mutable_tracks(int index) {
  // @@protoc_insertion_point(field_mutable:org.infinity.idm.Project.tracks)
  return tracks_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Track >*
Project::mutable_tracks() {
  // @@protoc_insertion_point(field_mutable_list:org.infinity.idm.Project.tracks)
  return &tracks_;
}
inline const ::org::infinity::idm::Track& Project::_internal_tracks(int index) const {
  return tracks_.Get(index);
}
inline const ::org::infinity::idm::Track& Project::tracks(int index) const {
  // @@protoc_insertion_point(field_get:org.infinity.idm.Project.tracks)
  return _internal_tracks(index);
}
inline ::org::infinity::idm::Track* Project::_internal_add_tracks() {
  return tracks_.Add();
}
inline ::org::infinity::idm::Track* Project::add_tracks() {
  ::org::infinity::idm::Track* _add = _internal_add_tracks();
  // @@protoc_insertion_point(field_add:org.infinity.idm.Project.tracks)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Track >&
Project::tracks() const {
  // @@protoc_insertion_point(field_list:org.infinity.idm.Project.tracks)
  return tracks_;
}

// repeated .org.infinity.idm.Pattern patterns = 8;
inline int Project::_internal_patterns_size() const {
  return patterns_.size();
}
inline int Project::patterns_size() const {
  return _internal_patterns_size();
}
inline ::org::infinity::idm::Pattern* Project::mutable_patterns(int index) {
  // @@protoc_insertion_point(field_mutable:org.infinity.idm.Project.patterns)
  return patterns_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Pattern >*
Project::mutable_patterns() {
  // @@protoc_insertion_point(field_mutable_list:org.infinity.idm.Project.patterns)
  return &patterns_;
}
inline const ::org::infinity::idm::Pattern& Project::_internal_patterns(int index) const {
  return patterns_.Get(index);
}
inline const ::org::infinity::idm::Pattern& Project::patterns(int index) const {
  // @@protoc_insertion_point(field_get:org.infinity.idm.Project.patterns)
  return _internal_patterns(index);
}
inline ::org::infinity::idm::Pattern* Project::_internal_add_patterns() {
  return patterns_.Add();
}
inline ::org::infinity::idm::Pattern* Project::add_patterns() {
  ::org::infinity::idm::Pattern* _add = _internal_add_patterns();
  // @@protoc_insertion_point(field_add:org.infinity.idm.Project.patterns)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::org::infinity::idm::Pattern >&
Project::patterns() const {
  // @@protoc_insertion_point(field_list:org.infinity.idm.Project.patterns)
  return patterns_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace idm
}  // namespace infinity
}  // namespace org

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_project_2eproto
