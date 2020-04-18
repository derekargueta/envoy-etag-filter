#pragma once

#include <string>

#include "etag.pb.h"
#include "etag.pb.validate.h"

#include "extensions/filters/http/common/factory_base.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Etag {

class EtagConfig : public Common::FactoryBase<envoy::extensions::filters::http::etag::v3::Filter> {
public:
  EtagConfig() : FactoryBase("etag") {}

  Http::FilterFactoryCb createFilterFactoryFromProtoTyped(const envoy::extensions::filters::http::etag::v3::Filter&,
                                                        const std::string&,
                                                        Server::Configuration::FactoryContext&) override;

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new Envoy::ProtobufWkt::Empty()};
  }
};

} // Etag
} // HttpFilters
} // Extensions
} // Envoy