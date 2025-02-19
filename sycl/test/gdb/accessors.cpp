// RUN: %clangxx -c -fno-color-diagnostics -std=c++17 -I %sycl_include/sycl -I %sycl_include -Xclang -ast-dump %s | FileCheck %s
// RUN: %clangxx -c -fno-color-diagnostics -std=c++17 -I %sycl_include/sycl -I %sycl_include -Xclang -emit-llvm -g %s -o - | FileCheck %s --check-prefixes CHECK-DEBUG-INFO
// UNSUPPORTED: windows
#include <sycl/sycl.hpp>

void foo(sycl::buffer<int, 1> &BufA) {
  auto HostAcc = BufA.get_access<sycl::access_mode::read>();
}

// AccessorImplHost must have MMemoryRange, MOffset and MData fields

// CHECK: CXXRecordDecl {{.*}} class AccessorImplHost definition
// CHECK-NOT: CXXRecordDecl {{.*}} definition
// CHECK: FieldDecl {{.*}} referenced MOffset
// CHECK-NOT: CXXRecordDecl {{.*}} definition
// CHECK: FieldDecl {{.*}} referenced MMemoryRange
// CHECK-NOT: CXXRecordDecl {{.*}} definition
// CHECK: FieldDecl {{.*}} referenced MData

// accessor.impl must be present and of shared_ptr<AccessorImplHost> type

// CHECK: CXXRecordDecl {{.*}} class AccessorBaseHost definition
// CHECK-NOT: CXXRecordDecl {{.*}} definition
// CHECK: FieldDecl {{.*}} referenced impl {{.*}}:'std::shared_ptr<sycl::detail::AccessorImplHost>'

// LocalAccessorImplHost must have MSize and MMem fields

// CHECK: CXXRecordDecl {{.*}} class LocalAccessorImplHost definition
// CHECK-NOT: CXXRecordDecl {{.*}} definition
// CHECK: FieldDecl {{.*}} referenced MSize
// CHECK-NOT: CXXRecordDecl {{.*}} definition
// CHECK: FieldDecl {{.*}} referenced MMem

// CHECK: CXXRecordDecl {{.*}} class accessor definition
// CHECK-NOT: CXXRecordDecl {{.*}} definition
// CHECK: public {{.*}}:'sycl::detail::AccessorBaseHost'


// CHECK-DEBUG-INFO: !DICompositeType(tag: DW_TAG_class_type, name: "accessor<int, 1, (sycl::_V1::access::mode)1024, (sycl::_V1::access::target)2018, (sycl::_V1::access::placeholder)0, sycl::_V1::ext::oneapi::accessor_property_list<> >", {{.*}}, templateParams: ![[TEMPL_METADATA:[0-9]+]]
// CHECK-DEBUG-INFO: ![[TEMPL_METADATA]] = !{![[DATA_T:[0-9]+]], ![[Dims:[0-9]+]], ![[AccMode:[0-9]+]], ![[AccTarget:[0-9]+]], ![[IsPlh:[0-9]+]], ![[PropListT:[0-9]+]]}
// CHECK-DEBUG-INFO-NEXT: ![[DATA_T]] = !DITemplateTypeParameter(name: "DataT"
// CHECK-DEBUG-INFO-NEXT: ![[Dims]] = !DITemplateValueParameter(name: "Dimensions"
// CHECK-DEBUG-INFO-NEXT: ![[AccMode]] = !DITemplateValueParameter(name: "AccessMode"
// CHECK-DEBUG-INFO-NEXT: ![[AccTarget]] = !DITemplateValueParameter(name: "AccessTarget"
// CHECK-DEBUG-INFO-NEXT: ![[IsPlh]] = !DITemplateValueParameter(name: "IsPlaceholder"
// CHECK-DEBUG-INFO-NEXT: ![[PropListT]] = !DITemplateTypeParameter(name: "PropertyListT"
// CHECK-NOT: !DICompositeType(tag: DW_TAG_class_type, name: "accessor<i
