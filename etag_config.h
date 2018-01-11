#pragma once

#include <string>

#include "envoy/server/filter_config.h"

namespace Envoy {
namespace Server {
namespace Configuration {

class EtagConfig : public NamedHttpFilterConfigFactory {
public:
  HttpFilterFactoryCb createFilterFactory(const Json::Object&, const std::string&,
                                          FactoryContext&) override;

  HttpFilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message&,
                                                   const std::string&,
                                                   FactoryContext&) override;

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new Envoy::ProtobufWkt::Empty()};
  }

  std::string name() override { return "etag"; }

};

} // Configuration
} // Server
} // Envoy