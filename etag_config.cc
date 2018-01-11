#include <iostream>
#include <string>

#include "etag_config.h"

#include "etag.h"

#include "common/protobuf/utility.h"
#include "envoy/registry/registry.h"

namespace Envoy {
namespace Server {
namespace Configuration {

HttpFilterFactoryCb EtagConfig::createFilterFactory(const Json::Object&, const std::string&,
                                                    FactoryContext&) {

  return [](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::EtagFilter()});
  };
}

HttpFilterFactoryCb EtagConfig::createFilterFactoryFromProto(const Protobuf::Message&,
                                                             const std::string&,
                                                             FactoryContext&) {

  return [](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::EtagFilter()});
  };
}

static Registry::RegisterFactory<EtagConfig, NamedHttpFilterConfigFactory> register_;

} // Configuration
} // Server
} // Envoy