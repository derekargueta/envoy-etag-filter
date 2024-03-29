#pragma once

#include <memory>
#include <string>

#include "etag.pb.h"
#include "etag.pb.validate.h"

#include "source/extensions/filters/http/common/factory_base.h"

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
    return std::make_unique<envoy::extensions::filters::http::etag::v3::Filter>();
  }
};

} // Etag
} // HttpFilters
} // Extensions
} // Envoy
