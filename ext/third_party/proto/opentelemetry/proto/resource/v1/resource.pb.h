// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: opentelemetry/proto/resource/v1/resource.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_opentelemetry_2fproto_2fresource_2fv1_2fresource_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_opentelemetry_2fproto_2fresource_2fv1_2fresource_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "opentelemetry/proto/common/v1/common.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_opentelemetry_2fproto_2fresource_2fv1_2fresource_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_opentelemetry_2fproto_2fresource_2fv1_2fresource_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_opentelemetry_2fproto_2fresource_2fv1_2fresource_2eproto;
namespace opentelemetry {
namespace proto {
namespace resource {
namespace v1 {
class Resource;
struct ResourceDefaultTypeInternal;
extern ResourceDefaultTypeInternal _Resource_default_instance_;
}  // namespace v1
}  // namespace resource
}  // namespace proto
}  // namespace opentelemetry
PROTOBUF_NAMESPACE_OPEN
template<> ::opentelemetry::proto::resource::v1::Resource* Arena::CreateMaybeMessage<::opentelemetry::proto::resource::v1::Resource>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace opentelemetry {
namespace proto {
namespace resource {
namespace v1 {

// ===================================================================

class Resource final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:opentelemetry.proto.resource.v1.Resource) */ {
 public:
  inline Resource() : Resource(nullptr) {}
  ~Resource() override;
  explicit PROTOBUF_CONSTEXPR Resource(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Resource(const Resource& from);
  Resource(Resource&& from) noexcept
    : Resource() {
    *this = ::std::move(from);
  }

  inline Resource& operator=(const Resource& from) {
    CopyFrom(from);
    return *this;
  }
  inline Resource& operator=(Resource&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
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
  static const Resource& default_instance() {
    return *internal_default_instance();
  }
  static inline const Resource* internal_default_instance() {
    return reinterpret_cast<const Resource*>(
               &_Resource_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Resource& a, Resource& b) {
    a.Swap(&b);
  }
  inline void Swap(Resource* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Resource* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Resource* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Resource>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Resource& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Resource& from) {
    Resource::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Resource* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "opentelemetry.proto.resource.v1.Resource";
  }
  protected:
  explicit Resource(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kAttributesFieldNumber = 1,
    kDroppedAttributesCountFieldNumber = 2,
  };
  // repeated .opentelemetry.proto.common.v1.KeyValue attributes = 1;
  int attributes_size() const;
  private:
  int _internal_attributes_size() const;
  public:
  void clear_attributes();
  ::opentelemetry::proto::common::v1::KeyValue* mutable_attributes(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::opentelemetry::proto::common::v1::KeyValue >*
      mutable_attributes();
  private:
  const ::opentelemetry::proto::common::v1::KeyValue& _internal_attributes(int index) const;
  ::opentelemetry::proto::common::v1::KeyValue* _internal_add_attributes();
  public:
  const ::opentelemetry::proto::common::v1::KeyValue& attributes(int index) const;
  ::opentelemetry::proto::common::v1::KeyValue* add_attributes();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::opentelemetry::proto::common::v1::KeyValue >&
      attributes() const;

  // uint32 dropped_attributes_count = 2;
  void clear_dropped_attributes_count();
  uint32_t dropped_attributes_count() const;
  void set_dropped_attributes_count(uint32_t value);
  private:
  uint32_t _internal_dropped_attributes_count() const;
  void _internal_set_dropped_attributes_count(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:opentelemetry.proto.resource.v1.Resource)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::opentelemetry::proto::common::v1::KeyValue > attributes_;
    uint32_t dropped_attributes_count_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_opentelemetry_2fproto_2fresource_2fv1_2fresource_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Resource

// repeated .opentelemetry.proto.common.v1.KeyValue attributes = 1;
inline int Resource::_internal_attributes_size() const {
  return _impl_.attributes_.size();
}
inline int Resource::attributes_size() const {
  return _internal_attributes_size();
}
inline ::opentelemetry::proto::common::v1::KeyValue* Resource::mutable_attributes(int index) {
  // @@protoc_insertion_point(field_mutable:opentelemetry.proto.resource.v1.Resource.attributes)
  return _impl_.attributes_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::opentelemetry::proto::common::v1::KeyValue >*
Resource::mutable_attributes() {
  // @@protoc_insertion_point(field_mutable_list:opentelemetry.proto.resource.v1.Resource.attributes)
  return &_impl_.attributes_;
}
inline const ::opentelemetry::proto::common::v1::KeyValue& Resource::_internal_attributes(int index) const {
  return _impl_.attributes_.Get(index);
}
inline const ::opentelemetry::proto::common::v1::KeyValue& Resource::attributes(int index) const {
  // @@protoc_insertion_point(field_get:opentelemetry.proto.resource.v1.Resource.attributes)
  return _internal_attributes(index);
}
inline ::opentelemetry::proto::common::v1::KeyValue* Resource::_internal_add_attributes() {
  return _impl_.attributes_.Add();
}
inline ::opentelemetry::proto::common::v1::KeyValue* Resource::add_attributes() {
  ::opentelemetry::proto::common::v1::KeyValue* _add = _internal_add_attributes();
  // @@protoc_insertion_point(field_add:opentelemetry.proto.resource.v1.Resource.attributes)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::opentelemetry::proto::common::v1::KeyValue >&
Resource::attributes() const {
  // @@protoc_insertion_point(field_list:opentelemetry.proto.resource.v1.Resource.attributes)
  return _impl_.attributes_;
}

// uint32 dropped_attributes_count = 2;
inline void Resource::clear_dropped_attributes_count() {
  _impl_.dropped_attributes_count_ = 0u;
}
inline uint32_t Resource::_internal_dropped_attributes_count() const {
  return _impl_.dropped_attributes_count_;
}
inline uint32_t Resource::dropped_attributes_count() const {
  // @@protoc_insertion_point(field_get:opentelemetry.proto.resource.v1.Resource.dropped_attributes_count)
  return _internal_dropped_attributes_count();
}
inline void Resource::_internal_set_dropped_attributes_count(uint32_t value) {
  
  _impl_.dropped_attributes_count_ = value;
}
inline void Resource::set_dropped_attributes_count(uint32_t value) {
  _internal_set_dropped_attributes_count(value);
  // @@protoc_insertion_point(field_set:opentelemetry.proto.resource.v1.Resource.dropped_attributes_count)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace v1
}  // namespace resource
}  // namespace proto
}  // namespace opentelemetry

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_opentelemetry_2fproto_2fresource_2fv1_2fresource_2eproto
