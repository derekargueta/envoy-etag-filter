#pragma once

#include <string>

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

class EtagFilter : public StreamDecoderFilter {
public:
  EtagFilter();
  ~EtagFilter();

  void onDestroy() override;

  FilterHeadersStatus decodeHeaders(HeaderMap& headers, bool) override;
  FilterDataStatus decodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus decodeTrailers(HeaderMap&) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) override;

private:
  StreamDecoderFilterCallbacks* decoder_callbacks_{};
};

} // Http
} // Envoy
