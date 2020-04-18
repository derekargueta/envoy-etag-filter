#include "etag_config.h"

#include <memory>
#include <string>

#include "etag.h"

#include "common/protobuf/utility.h"
#include "envoy/registry/registry.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Etag {

Http::FilterFactoryCb EtagConfig::createFilterFactoryFromProtoTyped(const envoy::extensions::filters::http::etag::v3::Filter&,
                                                                    const std::string&,
                                                                    Server::Configuration::FactoryContext&) {

  return [](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamFilter(std::make_shared<Filter>());
  };
}

static Registry::RegisterFactory<EtagConfig, Server::Configuration::NamedHttpFilterConfigFactory> register_;

} // Etag
} // HttpFilters
} // Extensions
} // Envoy