// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: track.proto

#include "track.pb.h"

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
namespace infinity {
constexpr Track::Track(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : notes_()
  , params_()
  , waves_()
  , effectors_()
  , name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , color_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , library_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , timbrea_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , timbreb_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , isvoice_(false)
  , mute_(false)
  , solo_(false){}
struct TrackDefaultTypeInternal {
  constexpr TrackDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~TrackDefaultTypeInternal() {}
  union {
    Track _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT TrackDefaultTypeInternal _Track_default_instance_;
}  // namespace infinity
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_track_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_track_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_track_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_track_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::infinity::Track, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::infinity::Track, name_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, color_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, library_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, timbrea_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, timbreb_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, isvoice_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, mute_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, solo_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, notes_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, params_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, waves_),
  PROTOBUF_FIELD_OFFSET(::infinity::Track, effectors_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::infinity::Track)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::infinity::_Track_default_instance_),
};

const char descriptor_table_protodef_track_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013track.proto\022\010infinity\032\nnote.proto\032\014tpa"
  "ram.proto\032\nwave.proto\032\014effect.proto\"\217\002\n\005"
  "Track\022\014\n\004name\030\001 \001(\t\022\r\n\005color\030\002 \001(\t\022\017\n\007li"
  "brary\030\003 \001(\t\022\017\n\007timbreA\030\004 \001(\t\022\017\n\007timbreB\030"
  "\005 \001(\t\022\017\n\007isVoice\030\006 \001(\010\022\014\n\004mute\030\007 \001(\010\022\014\n\004"
  "solo\030\010 \001(\010\022\035\n\005notes\030\t \003(\0132\016.infinity.Not"
  "e\022$\n\006params\030\n \003(\0132\024.infinity.TrackParam\022"
  "\035\n\005waves\030\013 \003(\0132\016.infinity.Wave\022%\n\teffect"
  "ors\030\014 \003(\0132\022.infinity.Effectorb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_track_2eproto_deps[4] = {
  &::descriptor_table_effect_2eproto,
  &::descriptor_table_note_2eproto,
  &::descriptor_table_tparam_2eproto,
  &::descriptor_table_wave_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_track_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_track_2eproto = {
  false, false, 357, descriptor_table_protodef_track_2eproto, "track.proto", 
  &descriptor_table_track_2eproto_once, descriptor_table_track_2eproto_deps, 4, 1,
  schemas, file_default_instances, TableStruct_track_2eproto::offsets,
  file_level_metadata_track_2eproto, file_level_enum_descriptors_track_2eproto, file_level_service_descriptors_track_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_track_2eproto_getter() {
  return &descriptor_table_track_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_track_2eproto(&descriptor_table_track_2eproto);
namespace infinity {

// ===================================================================

class Track::_Internal {
 public:
};

void Track::clear_notes() {
  notes_.Clear();
}
void Track::clear_params() {
  params_.Clear();
}
void Track::clear_waves() {
  waves_.Clear();
}
void Track::clear_effectors() {
  effectors_.Clear();
}
Track::Track(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  notes_(arena),
  params_(arena),
  waves_(arena),
  effectors_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:infinity.Track)
}
Track::Track(const Track& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      notes_(from.notes_),
      params_(from.params_),
      waves_(from.waves_),
      effectors_(from.effectors_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_name().empty()) {
    name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(), 
      GetArenaForAllocation());
  }
  color_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_color().empty()) {
    color_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_color(), 
      GetArenaForAllocation());
  }
  library_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_library().empty()) {
    library_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_library(), 
      GetArenaForAllocation());
  }
  timbrea_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_timbrea().empty()) {
    timbrea_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_timbrea(), 
      GetArenaForAllocation());
  }
  timbreb_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_timbreb().empty()) {
    timbreb_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_timbreb(), 
      GetArenaForAllocation());
  }
  ::memcpy(&isvoice_, &from.isvoice_,
    static_cast<size_t>(reinterpret_cast<char*>(&solo_) -
    reinterpret_cast<char*>(&isvoice_)) + sizeof(solo_));
  // @@protoc_insertion_point(copy_constructor:infinity.Track)
}

inline void Track::SharedCtor() {
name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
color_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
library_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
timbrea_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
timbreb_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&isvoice_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&solo_) -
    reinterpret_cast<char*>(&isvoice_)) + sizeof(solo_));
}

Track::~Track() {
  // @@protoc_insertion_point(destructor:infinity.Track)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Track::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  color_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  library_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  timbrea_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  timbreb_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Track::ArenaDtor(void* object) {
  Track* _this = reinterpret_cast< Track* >(object);
  (void)_this;
}
void Track::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Track::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Track::Clear() {
// @@protoc_insertion_point(message_clear_start:infinity.Track)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  notes_.Clear();
  params_.Clear();
  waves_.Clear();
  effectors_.Clear();
  name_.ClearToEmpty();
  color_.ClearToEmpty();
  library_.ClearToEmpty();
  timbrea_.ClearToEmpty();
  timbreb_.ClearToEmpty();
  ::memset(&isvoice_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&solo_) -
      reinterpret_cast<char*>(&isvoice_)) + sizeof(solo_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Track::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "infinity.Track.name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string color = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_color();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "infinity.Track.color"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string library = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_library();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "infinity.Track.library"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string timbreA = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          auto str = _internal_mutable_timbrea();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "infinity.Track.timbreA"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string timbreB = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_timbreb();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "infinity.Track.timbreB"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bool isVoice = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
          isvoice_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bool mute = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 56)) {
          mute_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bool solo = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 64)) {
          solo_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated .infinity.Note notes = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 74)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_notes(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<74>(ptr));
        } else goto handle_unusual;
        continue;
      // repeated .infinity.TrackParam params = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 82)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_params(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<82>(ptr));
        } else goto handle_unusual;
        continue;
      // repeated .infinity.Wave waves = 11;
      case 11:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 90)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_waves(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<90>(ptr));
        } else goto handle_unusual;
        continue;
      // repeated .infinity.Effector effectors = 12;
      case 12:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 98)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_effectors(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<98>(ptr));
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

::PROTOBUF_NAMESPACE_ID::uint8* Track::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:infinity.Track)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string name = 1;
  if (!this->_internal_name().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "infinity.Track.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  // string color = 2;
  if (!this->_internal_color().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_color().data(), static_cast<int>(this->_internal_color().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "infinity.Track.color");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_color(), target);
  }

  // string library = 3;
  if (!this->_internal_library().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_library().data(), static_cast<int>(this->_internal_library().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "infinity.Track.library");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_library(), target);
  }

  // string timbreA = 4;
  if (!this->_internal_timbrea().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_timbrea().data(), static_cast<int>(this->_internal_timbrea().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "infinity.Track.timbreA");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_timbrea(), target);
  }

  // string timbreB = 5;
  if (!this->_internal_timbreb().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_timbreb().data(), static_cast<int>(this->_internal_timbreb().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "infinity.Track.timbreB");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_timbreb(), target);
  }

  // bool isVoice = 6;
  if (this->_internal_isvoice() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(6, this->_internal_isvoice(), target);
  }

  // bool mute = 7;
  if (this->_internal_mute() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(7, this->_internal_mute(), target);
  }

  // bool solo = 8;
  if (this->_internal_solo() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(8, this->_internal_solo(), target);
  }

  // repeated .infinity.Note notes = 9;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_notes_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(9, this->_internal_notes(i), target, stream);
  }

  // repeated .infinity.TrackParam params = 10;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_params_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(10, this->_internal_params(i), target, stream);
  }

  // repeated .infinity.Wave waves = 11;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_waves_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(11, this->_internal_waves(i), target, stream);
  }

  // repeated .infinity.Effector effectors = 12;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_effectors_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(12, this->_internal_effectors(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:infinity.Track)
  return target;
}

size_t Track::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:infinity.Track)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .infinity.Note notes = 9;
  total_size += 1UL * this->_internal_notes_size();
  for (const auto& msg : this->notes_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // repeated .infinity.TrackParam params = 10;
  total_size += 1UL * this->_internal_params_size();
  for (const auto& msg : this->params_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // repeated .infinity.Wave waves = 11;
  total_size += 1UL * this->_internal_waves_size();
  for (const auto& msg : this->waves_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // repeated .infinity.Effector effectors = 12;
  total_size += 1UL * this->_internal_effectors_size();
  for (const auto& msg : this->effectors_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // string name = 1;
  if (!this->_internal_name().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  // string color = 2;
  if (!this->_internal_color().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_color());
  }

  // string library = 3;
  if (!this->_internal_library().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_library());
  }

  // string timbreA = 4;
  if (!this->_internal_timbrea().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_timbrea());
  }

  // string timbreB = 5;
  if (!this->_internal_timbreb().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_timbreb());
  }

  // bool isVoice = 6;
  if (this->_internal_isvoice() != 0) {
    total_size += 1 + 1;
  }

  // bool mute = 7;
  if (this->_internal_mute() != 0) {
    total_size += 1 + 1;
  }

  // bool solo = 8;
  if (this->_internal_solo() != 0) {
    total_size += 1 + 1;
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Track::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Track::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Track::GetClassData() const { return &_class_data_; }

void Track::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<Track *>(to)->MergeFrom(
      static_cast<const Track &>(from));
}


void Track::MergeFrom(const Track& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:infinity.Track)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  notes_.MergeFrom(from.notes_);
  params_.MergeFrom(from.params_);
  waves_.MergeFrom(from.waves_);
  effectors_.MergeFrom(from.effectors_);
  if (!from._internal_name().empty()) {
    _internal_set_name(from._internal_name());
  }
  if (!from._internal_color().empty()) {
    _internal_set_color(from._internal_color());
  }
  if (!from._internal_library().empty()) {
    _internal_set_library(from._internal_library());
  }
  if (!from._internal_timbrea().empty()) {
    _internal_set_timbrea(from._internal_timbrea());
  }
  if (!from._internal_timbreb().empty()) {
    _internal_set_timbreb(from._internal_timbreb());
  }
  if (from._internal_isvoice() != 0) {
    _internal_set_isvoice(from._internal_isvoice());
  }
  if (from._internal_mute() != 0) {
    _internal_set_mute(from._internal_mute());
  }
  if (from._internal_solo() != 0) {
    _internal_set_solo(from._internal_solo());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Track::CopyFrom(const Track& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:infinity.Track)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Track::IsInitialized() const {
  return true;
}

void Track::InternalSwap(Track* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  notes_.InternalSwap(&other->notes_);
  params_.InternalSwap(&other->params_);
  waves_.InternalSwap(&other->waves_);
  effectors_.InternalSwap(&other->effectors_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &name_, GetArenaForAllocation(),
      &other->name_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &color_, GetArenaForAllocation(),
      &other->color_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &library_, GetArenaForAllocation(),
      &other->library_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &timbrea_, GetArenaForAllocation(),
      &other->timbrea_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &timbreb_, GetArenaForAllocation(),
      &other->timbreb_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Track, solo_)
      + sizeof(Track::solo_)
      - PROTOBUF_FIELD_OFFSET(Track, isvoice_)>(
          reinterpret_cast<char*>(&isvoice_),
          reinterpret_cast<char*>(&other->isvoice_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Track::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_track_2eproto_getter, &descriptor_table_track_2eproto_once,
      file_level_metadata_track_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace infinity
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::infinity::Track* Arena::CreateMaybeMessage< ::infinity::Track >(Arena* arena) {
  return Arena::CreateMessageInternal< ::infinity::Track >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
